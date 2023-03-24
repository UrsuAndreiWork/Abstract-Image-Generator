#pragma once
#include <string>
#include <iostream>
#include "SDL.h";
class Button
{
private:
	int x, y;
	int dimensionX, dimensionY;
	SDL_Rect* srcrect;
	SDL_Rect* dstrect;
	SDL_Surface* picture;
public:
	Button(int x, int y, int dimensionX, int dimensionY);
	Button();
	int getX();
	int getY();
	void setPath(std::string path);
	bool verifyCollisionWithMouse(int mouseX,int mouseY);
	void draw(SDL_Surface* gScreenSurface);
	void changeColor(int R,int G, int B);
	~Button();
};

