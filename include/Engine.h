#pragma once
#include <string>
#include <iostream>
#include "Button.h"
#include "Text.h"


class Engine
{
private:
    const int SCREEN_WIDTH = 1080;
    const int SCREEN_HEIGHT = 920;
    Text* textGenerator[3];
    Button* buttonsMenu[4];
    Button* buttonsImageViewer[4];
    Button* buttonsImageGenerator[6];
    Button* dropdownButtons[7];
    int actualMenu = 0;
    SDL_Color white = { 255, 255,255 };
    SDL_Color black = { 0, 0, 0 };

public:
    bool init();
    void closeWindow(SDL_Window* window);
    void startProgram();
    void loadButtons();
    void loadText();
    void resetColor(int goodIndex);
};

