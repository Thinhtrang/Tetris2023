#pragma once
#include"tetris.hpp"


using namespace std;


void XepGach :: setTime(Uint32 time)
{
    currentTime = time;
}
bool XepGach :: CheckFocusWithRect(int &x , const int& y, const SDL_Rect& rect)
{
    if(x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) return true;
    return false;
}
int XepGach :: Menu()
{
    int ans = 0;
    if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		gWindow = SDL_CreateWindow("XEP GACH NAO!",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
        int imgFlags = IMG_INIT_PNG;
        int initted = IMG_Init(imgFlags);
            if ((initted & imgFlags) != imgFlags)
                std::cout << "Failed to init required png support\n" << "IMG_Init() Error : " << IMG_GetError() << std::endl;
        SDL_Surface* loadSurf = IMG_Load("images/menu1.png");
        hinhnen1 = SDL_CreateTextureFromSurface(gRenderer, loadSurf);
        SDL_FreeSurface(loadSurf);
	}
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)>= 0)
    {
        AmThanhMenu = Mix_LoadMUS("audio/backgroundMusic.wav");
        MouseClick = Mix_LoadWAV("audio/mouseclick.wav");
        Mix_PlayMusic(AmThanhMenu,-1);

    }
	if(TTF_Init() != -1)
    {
        menu_font = TTF_OpenFont("font/VHMUSTI.TTF",24);
    }
	SDL_RenderCopy(gRenderer,hinhnen1,NULL, NULL);

    const int kMenuItemNum = 2;
    SDL_Rect pos_arr[2];
    SetViTri(pos_arr[0],100,330,140,30);
    SetViTri(pos_arr[1],100,360,50,30);

    TextObject text_menu[kMenuItemNum];
    string s1 = "PLAY GAME";
    text_menu[0].setText(s1);
    text_menu[0].setColor(TextObject :: WHITE_TEXT);
    string s2 = "EXIT";
    text_menu[1].setText(s2);
    text_menu[1].setColor(TextObject :: WHITE_TEXT);

    bool selected[kMenuItemNum] = {0,0};

    int xm = 0; int ym = 0;
	SDL_Event menu_e;
	while(true)
    {
        for(int i = 0; i < 2; i++)
        {
            text_menu[i].loadFromRenderText(menu_font,gRenderer);
            text_menu[i].RenderText(gRenderer,pos_arr[i].x,pos_arr[i].y);

        }
        while(SDL_PollEvent(&menu_e))
        {
            switch(menu_e.type)
            {
                case SDL_QUIT:
                    return 2;
                case SDL_MOUSEMOTION:
                    xm = menu_e.motion.x;
                    ym = menu_e.motion.y;
                    for(int i = 0; i < kMenuItemNum; i++)
                    {
                        if(CheckFocusWithRect(xm,ym,pos_arr[i]))
                        {
                            if(selected[i] == false)
                            {
                                selected[i] = 1;
                                text_menu[i].setColor(TextObject :: RED_TEXT);
                            }
                        }
                        else
                        {
                            if(selected[i] == true)
                            {
                                selected[i] = 0;
                                text_menu[i].setColor(TextObject :: WHITE_TEXT);
                                SDL_RenderPresent(gRenderer);

                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    xm = menu_e.button.x;
                    ym = menu_e.button.y;
                    Mix_PlayChannel(-1,MouseClick,0);
                    for(int i = 0; i < kMenuItemNum; i++)
                    {
                        if(CheckFocusWithRect(xm,ym,pos_arr[i]))
                        {
                            SDL_Delay(2000);
                            return i+1;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    switch (menu_e.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                       return 2;
                    }
                default:
                    break;
            }
        }
        SDL_RenderPresent(gRenderer);
    }
	return 1;
}
XepGach :: XepGach()
{

}
XepGach :: ~XepGach()
{

}
bool XepGach :: check()
{
    for(int i = 0; i < 4; i++)
    {
        if(a[i].x < 0 || a[i].x >= Cols || a[i].y >= Rows ) return false;
        else if(playingField[a[i].y][a[i].x]) return false;
    }
    return true;
}
bool XepGach :: KhoiTao()
{

	if (SDL_Init(SDL_INIT_EVERYTHING |SDL_INIT_AUDIO) == 0)
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
		if (gWindow != NULL)
		{
			if (gRenderer != NULL)
			{

                SDL_SetRenderDrawColor(gRenderer,255,255,255,255);
                score_.setColor(255,255,255);
                int imgFlags = IMG_INIT_PNG;
                int initted = IMG_Init(imgFlags);
                if ((initted & imgFlags) != imgFlags)
                    std::cout << "Failed to init required png support\n" << "IMG_Init() Error : " << IMG_GetError() << std::endl;
                SDL_Surface* loadSurf = IMG_Load("images/a3.png");
                hinhnen = SDL_CreateTextureFromSurface(gRenderer, loadSurf);
                SDL_FreeSurface(loadSurf);
                loadSurf = IMG_Load("images/tiles.png");
                cucgach = SDL_CreateTextureFromSurface(gRenderer, loadSurf);
                SDL_FreeSurface(loadSurf);
                loadSurf = IMG_Load("images/add.png");
                vien = SDL_CreateTextureFromSurface(gRenderer,loadSurf);
                SDL_FreeSurface(loadSurf);
                loadSurf = IMG_Load("images/Finish2.png");
                go_img = SDL_CreateTextureFromSurface(gRenderer,loadSurf);
                SDL_FreeSurface(loadSurf);

                if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)>= 0)
                {
                    AmThanhNen = Mix_LoadMUS("audio/Tetris.wav");
                    XoaHang = Mix_LoadWAV("audio/clear.wav");
                    DiChuyenTraiPhai = Mix_LoadWAV("audio/move2.wav");
                    Rotate = Mix_LoadWAV("audio/rotate.wav");
                    GameOver = Mix_LoadWAV("audio/gameover.wav");
                    GoDown = Mix_LoadWAV("audio/drop.wav");
                    HardDrop = Mix_LoadWAV("audio/harddrop.wav");
                    Mix_PlayMusic(AmThanhNen,-1);
                }
                if(TTF_Init() != -1)
                {
                    ScoreFont = TTF_OpenFont("font/VHMUSTI.TTF",14);
                }
                CucGachTiepTheo();
			}
            else
				return false;
		}
		else
			return false;
	}
	else
		return false;

	Chay = true;
	return true;
}

void XepGach :: CucGachTiepTheo()
{
    colorNum = 1 + rand() % 7;
    n = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = Tetrimino[n][i] % 2;
		a[i].y = int(Tetrimino[n][i] / 2);
	}
}

void XepGach :: XuLiSuKien()
{

    SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			Chay = false;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
            case SDLK_ESCAPE:
                Chay= false;
			case SDLK_UP:
			    Mix_PlayChannel(-1,Rotate,0);
				LatNguoc = true;
				break;
			case SDLK_LEFT:
			    Mix_PlayChannel(-1,DiChuyenTraiPhai,0);
				DiChuyen = -1;
				break;
			case SDLK_RIGHT:
			    Mix_PlayChannel(-1,DiChuyenTraiPhai,0);
				DiChuyen = 1;
				break;
            case SDLK_m:
                Mix_PauseMusic();
                break;
            case SDLK_n:
                Mix_PlayMusic(AmThanhNen,-1);
                break;
			default:
				break;
			}
		default:
			break;
		}
	}
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_DOWN])
        {
            delay = 50;
            Mix_PlayChannel(-1,GoDown,0);
        }
        if(state[SDL_SCANCODE_SPACE])
        {
            Mix_PlayChannel(-1,HardDrop,0);
            delay = 10;
        }
}
void XepGach :: SetViTri(SDL_Rect& rect, int x, int y, int w, int h)
{
    rect.x = x; rect.y = y; rect.w = w; rect.h = h;
}
void XepGach :: DiChuyenRect(SDL_Rect& rect, int x, int y)
{
    rect.x += x;
    rect.y += y;
}
void XepGach :: logicGame()
{
    for(int i = 0; i < 4; i++)
    {
        b[i] = a[i];
        a[i].x += DiChuyen;
    }
    if(!check()) for(int i = 0; i < 4; i++)  a[i] = b[i];
    if(LatNguoc && n!=2)
    {
        Position p = a[1];
		for (int i = 0; i < 4; i++)
		{
			int x = a[i].y - p.y;
			int y = a[i].x - p.x;
			a[i].x = p.x - x;
			a[i].y = p.y + y;
        }
        if (!check()) for (int i=0;i<4;i++) a[i]=b[i];
    }

    if(currentTime - StartTime > delay)
    {
        for(int i = 0; i < 4; i++) a[i] = b[i];
        for(int i = 0; i < 4; i++) a[i].y += 1;
        if(!check())
        {
            for(int i = 0; i < 4; i++) playingField[b[i].y][b[i].x] = colorNum;
            CucGachTiepTheo();
        }
        StartTime = currentTime;
    }



    int k = Rows - 1;
    for(int i = k; i> 0; i--)
    {
        int cnt = 0;
        for(int j = 0; j < Cols; j++)
        {
            if(playingField[i][j]) cnt++;
            playingField[k][j] = playingField[i][j];
        }

        if(cnt < Cols)
        {
        k--;
        }
        if(cnt == Cols)
        {
            Mix_PlayChannel(-1,XoaHang,0);
            mark_value += 100;
        }
    }
    for(int i = 0; i < Cols; i++)
    if(playingField[1][i])
    {
        SDL_Rect Game_over;
        SetViTri(Game_over,SCREEN_WIDTH/4,SCREEN_HEIGHT/4,160,160);
        SDL_RenderCopy(gRenderer,go_img,NULL,&Game_over);
        SDL_RenderPresent(gRenderer);
        Mix_PauseMusic();
        Mix_PlayChannel(-1,GameOver,0);
        SDL_Delay(2000);
        Chay = false;
    }
    DiChuyen = 0;
    LatNguoc = false;
    delay = 500;
}
void XepGach :: setDiem( TextObject txt)
{
    std :: string val_str_mark;
    std :: string strMark = "Your score: ";
    val_str_mark = std :: to_string(mark_value);
    strMark += val_str_mark;
    txt.setText(strMark);
    txt.loadFromRenderText(ScoreFont,gRenderer);
    txt.RenderText(gRenderer,220,100);
}
void XepGach :: updateRender()
{
    SDL_RenderCopy(gRenderer,hinhnen,NULL,NULL);

    for(int i = 0; i < Rows; i++)
    {
        for(int j = 0; j < Cols; j++)
        {
            if(playingField[i][j])
            {
                SetViTri(srcR, playingField[i][j] * 18);
				SetViTri(destR, j * 18, i * 18);
				DiChuyenRect(destR, 18, 480 - (Rows + 1) * 18);
				if(i >= 3) SDL_RenderCopy(gRenderer, cucgach, &srcR, &destR);
            }
        }
    }
    for(int i = 0; i < 4; i++)
    {
        SetViTri(srcR, colorNum * 18);
        SetViTri(destR, a[i].x *18, a[i].y * 18);
        DiChuyenRect(destR, 18, 480 - (Rows + 1) * 18);
        SDL_RenderCopy(gRenderer, cucgach, &srcR, &destR);
    }

    setDiem(score_);

    SDL_Rect RectVien[2];
    SetViTri(RectVien[0],15,15,80,80);
    SetViTri(RectVien[1],90,15,80,80);
    SDL_RenderCopy(gRenderer,vien,NULL,&RectVien[1]);
    SDL_RenderCopy(gRenderer,vien,NULL,&RectVien[0]);

    SDL_RenderPresent(gRenderer);
}
void XepGach :: Huy()
{
    Mix_FreeMusic(AmThanhNen);
    Mix_FreeMusic(AmThanhMenu);
    Mix_FreeChunk(XoaHang);
    Mix_FreeChunk(DiChuyenTraiPhai);
    Mix_FreeChunk(GameOver);
    Mix_FreeChunk(GoDown);
     Mix_FreeChunk(HardDrop);
    Mix_FreeChunk(MouseClick);
    Mix_FreeChunk(Rotate);
    TTF_CloseFont(ScoreFont);

    score_.Free();
    AmThanhMenu = NULL;
    DiChuyenTraiPhai = NULL;
    XoaHang = NULL;
    AmThanhNen = NULL;
    GameOver = NULL;
    GoDown = NULL;
     HardDrop = NULL;
    MouseClick = NULL;
    Rotate = NULL;
    ScoreFont = NULL;

    SDL_DestroyTexture(cucgach);
	SDL_DestroyTexture(hinhnen);
    SDL_DestroyTexture(hinhnen1);
    SDL_DestroyTexture(go_img);
	SDL_DestroyTexture(vien);
	SDL_DestroyRenderer(gRenderer);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}
