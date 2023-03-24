#pragma once
#include <string>
#include <iostream>
#include "SDL.h";
#include <SDL_ttf.h>
class Text
{
private:
	int x, y;
	SDL_Surface* text_surf;
	SDL_Rect dstrect;
	SDL_Color foreground;
	TTF_Font* font;
	std::string text;
public:
	void createText(TTF_Font* font,SDL_Color foreground, std::string text,int x,int y);
	void createText(SDL_Color foreground, std::string text, int x, int y);
	void fixMemoryLeak();
	int gexX();
	int getY();
	void setFont(int size);
	void draw(SDL_Surface* surfaceWindow);
	std::string getText();
	void setText(std::string text);
	void setColor(int R, int G, int B);
	Text();
};

