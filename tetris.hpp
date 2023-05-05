#include <SDL.h>
#include <SDL_image.h>
#include<SDL_mixer.h>
#include <stdio.h>
#include <string>
#include<iostream>
#include<time.h>
#include<SDL_ttf.h>
#include"textObject.h"
class XepGach
{
public:
    XepGach();
    ~XepGach();
    bool DangChay()
    {
        return Chay;
    }
    void setDiem(TextObject txt);
    int Menu();
    void setTime(Uint32 time);
    bool check();
	bool KhoiTao();
	void CucGachTiepTheo();
	void XuLiSuKien();
	void SetViTri(SDL_Rect& rect, int x = 0, int y = 0, int w = 18, int h = 18);
	void DiChuyenRect(SDL_Rect& rect, int x, int y);
	void logicGame();
	void updateRender();
	void Huy();
	bool CheckFocusWithRect(int &x , const int& y, const SDL_Rect& rect);
    TextObject score_;


private:

    const int SCREEN_WIDTH = 320;
    const int SCREEN_HEIGHT = 480;
    const static int Rows = 24;
    const static int Cols = 10;
    int playingField[Rows][Cols] ={0};
    struct Position
    {
      int x,y;
    } a[4], b[4], c[4];

    SDL_Surface* gMenuImg = NULL;
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Renderer* MenuRender = NULL;

    SDL_Texture* cucgach = NULL;
    SDL_Texture* hinhnen = NULL;
    SDL_Texture* hinhnen1 = NULL;
    SDL_Texture* vien = NULL;

    Mix_Music* AmThanhNen = NULL;
    Mix_Music* AmThanhMenu = NULL;
    Mix_Chunk* XoaHang = NULL;
    Mix_Chunk* DiChuyenTraiPhai = NULL;
    Mix_Chunk* GameOver = NULL;
    Mix_Chunk* GoDown = NULL;
    Mix_Chunk* MouseClick = NULL;
    Mix_Chunk* HardDrop = NULL;
    Mix_Chunk* Rotate = NULL;

    TTF_Font* ScoreFont = NULL;
    TTF_Font* menu_font = NULL;

    const int Tetrimino[7][4] ={
    1,3,5,7, // I
    3,5,4,7, // T
    4,5,6,7, // O
    3,5,4,6, // Z
    2,4,5,7, // S
    2,4,6,7, // L
    3,5,7,6  // J
    };
    SDL_Rect srcR = { 0, 0, 18, 18};
    SDL_Rect destR = {0, 0, 18, 18};
    int DiChuyen = 0;
    bool LatNguoc = false;
    bool Chay = false;
    Uint32 StartTime = 0, currentTime = 0;
    int colorNum = 0;
    int delay = 500;
    int n;
    int mark_value;
};


















