

#include "Graphics/WindowManager.h"

int main(int argc, char* args []) {

    WindowManager& window_manager = WindowManager::getInstance();

    window_manager.createWindow("OpenGL", 1920, 1080);

    window_manager.updateWindow();

    window_manager.cleanUp();

    return 0;
}
