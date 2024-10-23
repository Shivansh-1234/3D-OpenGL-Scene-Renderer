#include "Input.h"

Input::Input()
    :mouseX(0), mouseY(0) {
    keyStates = SDL_GetKeyboardState(NULL);
}

Input::~Input() = default;

void Input::update() {
    SDL_PumpEvents();

    keyStates = SDL_GetKeyboardState(NULL);
}

void Input::handleEvent(const SDL_Event &event) {
    if(event.type == SDL_MOUSEMOTION) {
        mouseX = event.motion.x;
        mouseY = event.motion.y;
    }
    if(event.type == SDL_MOUSEBUTTONDOWN) {
        mouseButtonStates[event.button.button] = true;
    }
    if(event.type == SDL_MOUSEBUTTONUP) {
        mouseButtonStates[event.button.button] = false;
    }
    if (event.type == SDL_KEYDOWN && !event.key.repeat) {
        keyDown[event.key.keysym.scancode] = true;
    }
    if (event.type == SDL_KEYUP) {
        keyReleased[event.key.keysym.scancode] = true;
    }
}

bool Input::isKeyPressed(SDL_Scancode key) {
    return keyStates[key] == 1;
}

bool Input::isKeyDown(SDL_Scancode key) {
    bool keyD = keyDown[key];
    keyDown.clear();
    return keyD;
}

bool Input::isKeyReleased(SDL_Scancode key) {
    bool keyR = keyReleased[key];
    keyReleased.clear();
    return keyR;
}

bool Input::isMouseButtonPressed(Uint8 mButton) {
    //iterate through mouse button map, if map has that button return if its true or not
    auto iterator = mouseButtonStates.find(mButton);
    if(iterator != mouseButtonStates.end()) {
        return iterator->second;
    }
    return false;
}

void Input::getMousePos(int &xPos, int &yPos) {
    xPos = mouseX;
    yPos = mouseY;
}

void Input::getMousePosCentered(int& xPos, int& yPos, int screenWidth, int screenHeight) {
    getMousePos(xPos, yPos);

    xPos = xPos - (screenWidth / 2);
    yPos = (screenHeight / 2) - yPos;
}

