#include"textObject.h"
using namespace std;
TextObject :: TextObject()
{
}
TextObject :: ~TextObject()
{

}
bool TextObject :: loadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font,str_val.c_str(),color_text);
    if(text_surface)
    {
        texture_ = SDL_CreateTextureFromSurface(screen,text_surface);
        width_ = text_surface->w;
        height_ = text_surface->h;
        SDL_FreeSurface(text_surface);
    }
    return texture_ != NULL;
}
void TextObject :: Free()
{
    if(texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}
void TextObject :: setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    color_text.r = red;
    color_text.g = green;
    color_text.b = blue;
}
void TextObject :: setColor(int type)
{
    if( type ==  RED_TEXT)
    {
        SDL_Color color = {255,0,0};
        color_text = color;
    }
    else if( type == WHITE_TEXT)
    {
        SDL_Color color = {255,255,255};
        color_text = color;
    }
    else if( type == BLACK_TEXT)
    {
        SDL_Color color = {0,0,0};
        color_text = color;
    }
}
void TextObject :: setRect(int x, int y)
{

}
void TextObject :: RenderText(SDL_Renderer* screen, int xp, int yp,
                    SDL_Rect* clip, double angle, SDL_Point* center,
                    SDL_RendererFlip flip)
{
    SDL_Rect RenderQuad = { xp, yp, width_, height_};
    if(clip != NULL)
    {
        RenderQuad.w = clip -> w;
        RenderQuad.h = clip -> h;
    }
    SDL_RenderCopyEx(screen, texture_, clip, &RenderQuad, angle,center, flip);
}


























