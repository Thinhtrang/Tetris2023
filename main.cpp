#pragma once
#include"tetris.hpp"

using namespace std;

int main(int argc, char* argv[])
{
        XepGach* newXepGach = new XepGach();


        int ans = newXepGach->Menu();
        if(ans == 1)
        {
            if (newXepGach->KhoiTao())
            {
                while(newXepGach->DangChay())
                {
                    newXepGach->setTime(SDL_GetTicks());
                    newXepGach->XuLiSuKien();
                    newXepGach->logicGame();
                    //newXepGach->setDiem(score_);
                    newXepGach->updateRender();
                }
                newXepGach->Huy();
            }
        }
        else if(ans == 2) return 0;
    return 0;
}














