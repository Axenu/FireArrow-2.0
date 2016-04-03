#include <FA/FAAnimation.h>

FAAnimation::FAAnimation() {

}

FAAnimation::FAAnimation(int numberOfFrames) {
	this->numberOfFrames = numberOfFrames;
	this->frames = new FAFrame*[numberOfFrames];
	this->index = 0;
	this->timePerFrame = 1.5;
}

void FAAnimation::addFrame(FAFrame *frame) {
	this->frames[index++] = frame;
}

void FAAnimation::getDiffAndFrame(float time, float &diff, int &frame) {
	diff = fmod(time, timePerFrame);
	frame = (int) ((time - diff)/timePerFrame);
	diff /= timePerFrame;
	if (frame >= numberOfFrames - 1) {
		frame = -1;
	}
}

glm::quat FAAnimation::getQuatAtTime(float diff, int frame, int bone) {
	
	glm::quat f = frames[frame]->getQuaternionOfBone(bone);
	glm::quat l = frames[frame+1]->getQuaternionOfBone(bone);
	
	glm::quat q = glm::mix(f, l, diff);
	
	return q;
}

FAAnimation::~FAAnimation() {
	for (int i = 0; i < numberOfFrames; i++) {
		delete frames[i];
	}
	delete[]frames;
}