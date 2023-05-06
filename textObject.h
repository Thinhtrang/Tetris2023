#include<SDL_ttf.h>
#include<SDL.h>
#include<bits/stdc++.h>

using namespace std;
class TextObject
{
public:
    TextObject();
    ~TextObject();
    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2
    };
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setColor(int type);
    void setRect(int x, int y);
    bool loadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
    void Free();
    void RenderText(SDL_Renderer* screen, int xp, int yp,
                    SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    void setText(const string& text) { str_val = text; }
    string GetText() { return str_val; }
private:
    string str_val;
    SDL_Color color_text;
    SDL_Texture* texture_;
    int width_;
    int height_;
};
