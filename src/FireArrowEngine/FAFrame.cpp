#include <FA/FAFrame.h>

FAFrame::FAFrame() {
	
}

FAFrame::FAFrame(int numberOfBones){
	this->numberOfBones = numberOfBones;
	this->index = 0;
	this->boneRotations = new glm::quat[numberOfBones];
}

void FAFrame::addQuaternion(glm::quat &quat) {
	this->boneRotations[this->index++] = quat;
}

glm::quat &FAFrame::getQuaternionOfBone(int bone) {
	return this->boneRotations[bone];
}

FAFrame::~FAFrame() {
	delete[]boneRotations;
}