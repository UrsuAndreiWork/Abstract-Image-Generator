#include "Button.h"
#include "SDL.h";


Button::Button() {

}

Button::Button(int x, int y, int dimensionX, int dimensionY)
{
	this->x = x;
	this->y = y;
	this->dimensionX = dimensionX;
	this->dimensionY = dimensionY;
	srcrect=new SDL_Rect();
	dstrect=new SDL_Rect();
	srcrect->w = dimensionX;
	srcrect->h = dimensionY;
	dstrect->y = y;
	dstrect->x = x;

	picture = new SDL_Surface();
}

int Button::getX() {
	return x;
}

int Button::getY() {
	return y;
}

void Button::setPath(std::string path)
{
	const char* newPath = path.c_str();
	picture= SDL_LoadBMP(newPath);
	if (picture == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
	}
}

void Button::draw(SDL_Surface* gScreenSurface) {


SDL_BlitSurface(picture, srcrect, gScreenSurface, dstrect);
}

void Button::changeColor(int R,int G,int B)
{
    SDL_SetSurfaceColorMod(picture,R,G,B);
}

Button::~Button()
{
	SDL_FreeSurface(picture);

}

bool Button::verifyCollisionWithMouse(int mouseX,int mouseY)
{
	if (mouseX >= x && mouseX <= x+ dimensionX && mouseY >= y && mouseY <=y+ dimensionY) {
		return true;
	}
	return false;
}
