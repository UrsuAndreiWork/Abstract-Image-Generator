#include "Text.h"

void Text::createText(TTF_Font* font, SDL_Color foreground, std::string text, int x, int y)
{this->text = text;
    text_surf = TTF_RenderText_Solid(font, this->text.c_str(), foreground);
    dstrect.x = x;
    dstrect.y = y;
    this->foreground = foreground;
    this->font = font;

}

void Text::createText(SDL_Color foreground, std::string text, int x, int y)
{
    text_surf = TTF_RenderText_Solid(font, this->text.c_str(), foreground);
    dstrect.x = x;
    dstrect.y = y;
    this->text = text;
    //this->foreground = foreground;
    //this->font = font;
}
void Text::fixMemoryLeak() {
    text_surf = TTF_RenderText_Solid(font, this->text.c_str(), foreground);
}

int Text::gexX()
{
    return x;
}

int Text::getY()
{
    return y;
}

Text::Text() {

}
void Text::setFont(int size) {
   this->font = TTF_OpenFont("OpenSans-Bold.ttf", size);
}

void Text::draw(SDL_Surface* surfaceWindow)
{
    SDL_BlitSurface(text_surf, NULL, surfaceWindow, &dstrect);
    SDL_FreeSurface(text_surf);
}

std::string Text::getText() {
    return text;
}


void Text::setText(std::string text)
{
    SDL_FreeSurface(text_surf);
    text_surf = TTF_RenderText_Solid(font, text.c_str(), foreground);
}

void Text::setColor(int R, int G, int B)
{
    foreground.r=R;
    foreground.g = G;
    foreground.g = B;
}
