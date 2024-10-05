#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL_image.h"
#include <unordered_map>

class Input {
public:
    Input();
    ~Input();

    void update();//must be called before poll events!(will fix later)
    void handleEvent(const SDL_Event& event);

    bool isKeyPressed(SDL_Scancode key);
    bool isKeyDown(SDL_Scancode key);
    bool isKeyReleased(SDL_Scancode key);
    bool isMouseButtonPressed(Uint8 mButton);
     //TODO: change this to return a vector after making vec2 class
    void getMousePos(int &xPos, int& yPos);
    void getMousePosCentered(int& xPos, int& yPos, int screenWidth, int screenHeight);

private:
    std::unordered_map<Uint8, bool> mouseButtonStates;
    std::unordered_map<SDL_Scancode, bool> keyDown;
    std::unordered_map<SDL_Scancode, bool> keyReleased;
    const Uint8* keyStates;
    int mouseX;
    int mouseY;
};



#endif //INPUT_H
