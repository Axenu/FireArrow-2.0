#include <FA/FAArmature.h>

FAArmature::FAArmature() {
	this->rootBone = nullptr;
	this->activeAnimation = nullptr;
}

void FAArmature::setRootBone(FABone *bone) {
	this->rootBone = bone;
}

void FAArmature::addBone(FABone *bone) {
	this->bones.push_back(bone);
}

FABone* FAArmature::getBone(int index) {
	if (index < this->bones.size()) {
		return this->bones[index];
	}
	return nullptr;
}

FABone* FAArmature::getRootBone() {
	return this->rootBone;
}

int FAArmature::getNumberOfBones() {
	return (int) this->bones.size();
}

float* FAArmature::getAnimatedXForm() {
	return &this->animatedXForm[0][0][0];
}

void FAArmature::addAnimation(FAAnimation *animation) {
	this->animations.push_back(animation);
}

void FAArmature::runAnimation(int index) {
	if (index >= animations.size() || index < 0) return;
	this->activeAnimation = animations[index];
	this->animationDuration = 0;
}

void FAArmature::adjustPositions(FABone *b, glm::vec3 diff) {
    b->setPosition(b->getPosition() - diff);
    glm::vec3 newDiff = diff + b->getPosition();
    for (FABone *f : b->getChildren()) {
        adjustPositions(f, newDiff);
    }
}

void FAArmature::setupBoneMatrices(FABone *b) {
    glm::mat4 S = glm::scale(glm::mat4(1), b->getScale());
    glm::mat4 R = glm::rotate(glm::mat4(1), b->getRotation().x, glm::vec3(1,0,0));
    R = glm::rotate(R, b->getRotation().y, glm::vec3(0,1,0));
    R = glm::rotate(R, b->getRotation().z, glm::vec3(0,0,1));
    glm::mat4 T = glm::translate(glm::mat4(1), b->getPosition());
    b->setLocalMatrix(T*R*S);
    
    if (b->getParent() != nullptr) {
        b->setCombinedMatrix(b->getParent()->getCombinedMatrix() * b->getLocalMatrix());
    } else {
        b->setCombinedMatrix(b->getLocalMatrix());
    }
    
    invBindPose.push_back(glm::inverse(b->getCombinedMatrix()));
    
    animatedXForm.push_back(b->getCombinedMatrix());
    
    for (FABone *c : b->getChildren()) {
        setupBoneMatrices(c);
    }
}

int FAArmature::calculateBoneMatrices(FABone *b, int i) {
    glm::mat4 S = glm::scale(glm::mat4(1), b->getScale());
    glm::mat4 R = glm::rotate(glm::mat4(1), b->getRotation().x, glm::vec3(1,0,0));
    R = glm::rotate(R, b->getRotation().y, glm::vec3(0,1,0));
    R = glm::rotate(R, b->getRotation().z, glm::vec3(0,0,1));
    glm::mat4 T = glm::translate(glm::mat4(1), b->getPosition());
    b->setLocalMatrix(T*R*S);
    
    if (b->getParent() != nullptr) {
        b->setCombinedMatrix(b->getParent()->getCombinedMatrix() * b->getLocalMatrix());
    } else {
        b->setCombinedMatrix(b->getLocalMatrix());
    }
    animatedXForm[i] = b->getCombinedMatrix() * invBindPose[i];
    
    for (FABone *c : b->getChildren()) {
        i = calculateBoneMatrices(c, i + 1);
    }
    return i;
}

int FAArmature::calculateBoneMatricesFromQuaternions(FABone *b, int i) {
	if (b->getParent() != nullptr) {
		b->setCombinedMatrix(b->getParent()->getCombinedMatrix() * b->getLocalMatrix());
	} else {
		b->setCombinedMatrix(b->getLocalMatrix());
	}
	animatedXForm[i] = b->getCombinedMatrix() * invBindPose[i];
	
	for (FABone *c : b->getChildren()) {
		i = calculateBoneMatricesFromQuaternions(c, i + 1);
	}
	return i;
}

void FAArmature::update(float dt) {
//	bones[2]->setRotation(glm::vec3(0,0,bones[2]->getRotation().z + dt));

    // update bones from animation
	if (activeAnimation != nullptr) {
		glm::quat q = glm::quat();
		float diff;
		int frame;
		activeAnimation->getDiffAndFrame(animationDuration, diff, frame);
		if (frame != -1) {
			for (int i = 0; i < this->bones.size(); i++) {
				q = activeAnimation->getQuatAtTime(diff, frame, i);
				
				glm::mat4 S = glm::scale(glm::mat4(1), this->bones[i]->getScale());
				glm::mat4 R = glm::toMat4(q);
				glm::mat4 T = glm::translate(glm::mat4(1), this->bones[i]->getPosition());
				this->bones[i]->setLocalMatrix(T*R*S);
//				std::cout << q.x << ", "<< q.y << ", "<< q.z << ", "<< q.w << std::endl;
			}
			animationDuration+=0.01;
		} else {
			//stop animation
			activeAnimation = nullptr;
		}
		calculateBoneMatricesFromQuaternions(rootBone, 0);
	} else {
		calculateBoneMatrices(rootBone, 0);
	}
}

FAArmature::~FAArmature() {

}