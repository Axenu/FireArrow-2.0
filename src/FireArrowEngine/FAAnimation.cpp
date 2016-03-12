#include <FA/FAAnimation.h>

FAAnimation::FAAnimation() {

}

FAAnimation::FAAnimation(int numberOfFrames, int numberOfBones) {
	this->numberOfFrames = numberOfFrames;
	this->numberOfBones = numberOfBones;
	this->keyframes = new glm::quat**[numberOfFrames];
	for (int i = 0; i < numberOfFrames; i++) {
		this->keyframes[i] = new glm::quat*[numberOfBones];
	}
}

void FAAnimation::setQuaternion(int frame, int bone, glm::quat q) {
	this->keyframes[frame][bone] = &q;
}

FAAnimation::~FAAnimation() {

}