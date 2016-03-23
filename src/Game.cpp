#include "Game.h"

Game::Game() {
    initEngine();
}

void Game::init() {
    
}

FAScene* Game::setInitialScene() {
    return new testScene();
}

void Game::setWindowAttributes() {
    this->setWindowsSize(1920, 1080);
    this->setSamples(4);
    this->setDecorated(false);
    this->setWindowColor(glm::vec3(95.0/255.0,95.0/255.0,95.0/255.0));
}

Game::~Game() {
    
}