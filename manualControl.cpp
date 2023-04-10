#include "manualControl.h"

ManualControl::ManualControl()
{
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    middleW = screenWidth / 2;
    middleH = screenHeight / 2;
}

bool ManualControl::isKeyPressed(short key)
{
    if (key == VK_UP)
        return (GetAsyncKeyState(VK_UP) & 0x01);
    if (key == VK_DOWN)
        return (GetAsyncKeyState(VK_DOWN) & 0x01);
    if (key == VK_LEFT)
        return (GetAsyncKeyState(VK_LEFT) & 0x01);
    if (key == VK_RIGHT)
        return (GetAsyncKeyState(VK_RIGHT) & 0x01);
    if (key == KEY_A)
        return (GetAsyncKeyState(KEY_A) & 0x01);
    if (key == KEY_W)
        return (GetAsyncKeyState(KEY_W) & 0x01);
    
    return false;
}

std::list<short>& ManualControl::getPressedKeys()
{
    pressedKeys.clear();
    if (GetKeyState(VK_RIGHT) & 0x80) pressedKeys.push_back(VK_RIGHT);
    if (GetKeyState(VK_LEFT) & 0x80) pressedKeys.push_back(VK_LEFT);
    if (GetKeyState(VK_UP) & 0x80) pressedKeys.push_back(VK_UP);
    if (GetKeyState(VK_DOWN) & 0x80) pressedKeys.push_back(VK_DOWN);
    return pressedKeys;
}

int ManualControl::getDisplaySizeX(){
    return screenWidth;
}

int ManualControl::getDisplaySizeY(){
    return screenHeight;
}

int ManualControl::getDisplayMiddleX(){
    return middleW;
}

int ManualControl::getDisplayMiddleY(){
    return middleH;
}

int ManualControl::getMouseX(){
    POINT position;
    GetCursorPos(&position);
    return position.x;
}

int ManualControl::getMouseY(){
    POINT position;
    GetCursorPos(&position);
    return position.y;
}
