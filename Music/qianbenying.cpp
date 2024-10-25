#include <iostream>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include <thread>

using namespace std;
HMIDIOUT handle;

enum Scale
{
    Rest = 0, C8 = 108, B7 = 107, A7s = 106, A7 = 105, G7s = 104, G7 = 103, F7s = 102, F7 = 101, E7 = 100,
    D7s = 99, D7 = 98, C7s = 97, C7 = 96, B6 = 95, A6s = 94, A6 = 93, G6s = 92, G6 = 91, F6s = 90, F6 = 89,
    E6 = 88, D6s = 87, D6 = 86, C6s = 85, C6 = 84, B5 = 83, A5s = 82, A5 = 81, G5s = 80, G5 = 79, F5s = 78,
    F5 = 77, E5 = 76, D5s = 75, D5 = 74, C5s = 73, C5 = 72, B4 = 71, A4s = 70, A4 = 69, G4s = 68, G4 = 67,
    F4s = 66, F4 = 65, E4 = 64, D4s = 63, D4 = 62, C4s = 61, C4 = 60, B3 = 59, A3s = 58, A3 = 57, G3s = 56,
    G3 = 55, F3s = 54, F3 = 53, E3 = 52, D3s = 51, D3 = 50, C3s = 49, C3 = 48, B2 = 47, A2s = 46, A2 = 45,
    G2s = 44, G2 = 43, F2s = 42, F2 = 41, E2 = 40, D2s = 39, D2 = 38, C2s = 37, C2 = 36, B1 = 35, A1s = 34,
    A1 = 33, G1s = 32, G1 = 31, F1s = 30, F1 = 29, E1 = 28, D1s = 27, D1 = 26, C1s = 25, C1 = 24, B0 = 23,
    A0s = 22, A0 = 21
};

enum Voice
{
    X1 = C2, X2 = D2, X3 = E2, X4 = F2, X5 = G2, X6 = A2, X7 = B2,
    L1 = C3, L2 = D3, L3 = E3, L4 = F3, L5 = G3, L6 = A3, L7 = B3,
    M1 = C4, M2 = D4, M3 = E4, M4 = F4, M5 = G4, M6 = A4, M7 = B4,
    H1 = C5, H2 = D5, H3 = E5, H4 = F5, H5 = G5, H6 = A5, H7 = B5,
    Y1= C6, Y2= D6, Y3= E6, Y4= F6, Y5 = G6, Y6 = A6, Y7 = B6,
    _ = 0XFF
};

int ans = 1;
int ans2 = 1000;
int gao = 0x7f;
int zhong =0x40;
int voice = 0x0;
int sleep =240;
int sta = 240;
int stb = 240;

void TH1()
{
    int tmp=0;
    int th1[]=
    {
        H2,700,H2,700,H1,H2,700,H2,700,H1,H2,700,H2,700,H1,H2,_,H4,_, H2,700,H2,700,H1,H2,700,H2,700,H1, 
        H2,_,H6,_,H5,_,H6,_, 
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300, H5,H6,0,H2,H1,H2,H1,300,H4,400,H3,H4,H3,300,H2,H1,
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,H5,H6,Y1,Y4,0,Y3,Y4,Y3,Y2,300,Y1,H6,                 
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,H4,400,H3,H4,H3,300,H2,H1,
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,H5,H6,Y1,Y4,0,Y3,Y4,Y3,Y2,300,Y1,H6,                  
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,00,H4,400,H3,H4,H3,300,H2,H1,
        H2,0,H1,H2,300,H4,0,H2,H4,300,H5,0,H5,H6,Y1,Y4,H6,Y1,300,
        Y4,400,Y3,Y4,Y3,300,Y2,Y1,Y2,_,Y2,Y4,
        500,H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,
        H5,H6,0,H2,H1,H2,H1,300,H4,400,H3,H4,H3,300,H2,H1,
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,
        H5,H6,Y1,Y4,0,Y3,Y4,Y3,Y2,300,Y1,H6,
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,
        H5,H6,0,H2,H1,H2,H1,300,H4,400,H3,H4,H3,300,H2,H1,
        H5,0,H6,Y1,Y2,Y1,H6,H5,300,H2,H4,H5,H6,
        H2,700,H2,700,H1,H2,_,_,_,600,
        H2,_,H2,700,0,H1,300,H2,H4,H4,H5,
        H2,_,H2,700,0,H1,300,H2,H1,M6,H1,
        H2,_,H2,700,0,H1,300,H2,H4,H5,H6,
        H6,_,800,H5,H6,H5,300,H4,_,H2,_,
        H2,_,H2,700,0,H1,300,H2,H4,H4,H5,
        H2,_,H2,700,0,H1,300,H2,H1,H1,M6,
        H2,_,H2,700,0,H1,300,H1,H2,H4,H5,
        H6,_,800,H5,H6,H5,300,H4,_,H2,_,
        H4,_,H3,_,H2,_,H1,_,
        H1,0,H1,H2,300,M6,M5,M6,_,_,_,
        M6,H1,H2,_,H5,_,H3,_,
        H4,_,H3,H1,H2,_,_,_,
        H4,_,H3,_,H2,_,H1,_,
        H1,0,H1,H2,300,M6,M5,M6,_,M6,H1,
        H2,H2,_,H2,H4,_,H5,_,
        H3,_,_,_,_,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        Y1,Y2,H5,H4,H6,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        (H7 - 1),H6,H5,H4,H4,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        Y1,Y2,H5,H4,H6,_,H2,H4,
        (H7 - 1),_,H6,_,H5,_,H4,_,
        H5,H6,H3,H1,H2,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        Y1,Y2,H5,H4,H6,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        (H7 - 1),H6,H5,H4,H4,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        Y1,Y2,H5,H4,H6,_,H2,H4,
        (H7 - 1),_,H6,_,H5,_,H4,_,
        H5,H4,H6,Y1,Y2,_,_,_,
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300, H5,H6,0,H2,H1,H2,H1,300,H4,400,H3,H4,H3,300,H2,H1,
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,H5,H6,Y1,Y4,0,Y3,Y4,Y3,Y2,300,Y1,H6,                 
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,H4,400,H3,H4,H3,300,H2,H1,
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,H5,H6,Y1,Y4,0,Y3,Y4,Y3,Y2,300,Y1,H6,                  
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,00,H4,400,H3,H4,H3,300,H2,H1,
        H2,0,H1,H2,300,H4,0,H2,H4,300,H5,0,H5,H6,Y1,Y4,H6,Y1,300,
        Y4,400,Y3,Y4,Y3,300,Y2,Y1,Y2,_,Y2,Y4,
        500,H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,
        H5,H6,0,H2,H1,H2,H1,300,H4,400,H3,H4,H3,300,H2,H1,
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,
        H5,H6,Y1,Y4,0,Y3,Y4,Y3,Y2,300,Y1,H6,
        H5,H6,0,H2,H1,H2,H1,300,H5,H6,0,H2,H1,H2,H1,300,
        H5,H6,0,H2,H1,H2,H1,300,H4,400,H3,H4,H3,300,H2,H1,
        H5,0,H6,Y1,Y2,Y1,H6,H5,300,H2,H4,H5,H6,
        H2,700,H2,700,H1,H2,_,_,_,600,
        H2,_,H2,700,0,H1,300,H2,H4,H4,H5,
        H2,_,H2,700,0,H1,300,H2,H1,M6,H1,
        H2,_,H2,700,0,H1,300,H2,H4,H5,H6,
        H6,_,800,H5,H6,H5,300,H4,_,H2,_,
        H2,_,H2,700,0,H1,300,H2,H4,H4,H5,
        H2,_,H2,700,0,H1,300,H2,H1,H1,M6,
        H2,_,H2,700,0,H1,300,H1,H2,H4,H5,
        H6,_,800,H5,H6,H5,300,H4,_,H2,_,
        H4,_,H3,_,H2,_,H1,_,
        H1,0,H1,H2,300,M6,M5,M6,_,_,_,
        M6,H1,H2,_,H5,_,H3,_,
        H4,_,H3,H1,H2,_,_,_,
        H4,_,H3,_,H2,_,H1,_,
        H1,0,H1,H2,300,M6,M5,M6,_,M6,H1,
        H2,H2,_,H2,H4,_,H5,_,
        H3,_,_,_,_,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        Y1,Y2,H5,H4,H6,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        (H7 - 1),H6,H5,H4,H4,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        Y1,Y2,H5,H4,H6,_,H2,H4,
        (H7 - 1),_,H6,_,H5,_,H4,_,
        H5,H6,H3,H1,H2,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        Y1,Y2,H5,H4,H6,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        (H7 - 1),H6,H5,H4,H4,_,H2,H4,
        H5,700,H5,700,H6,H6,_,_,H6,
        Y1,Y2,H5,H4,H6,_,H2,H4,
        (H7 - 1),_,H6,_,H5,_,H4,_,
        H5,H4,H6,Y1,Y2,_,_,_,
        Y2,Y2,Y2,Y2,Y2,Y2,0,Y2,Y1,300,H6,
        H5,H5,H5,H5,H5,H5,0,H5,H4,300,H2,
        Y2,Y2,Y2,Y2,Y2,Y2,0,Y2,Y1,300,H6,
        M5,0,M6,M5,M6,H1,H2,H4,H6,Y1,Y2,Y4,300,Y3,0,H2,H4,300,
        0,H6,H4,H2,H6,H6,H6,H4,H2,H6,H4,H2,H6,H6,H6,H4,H2,300,
        0,(H7-1),H5,(H3+1),(H7-1), (H7 - 1), (H7 - 1),H5,(H3+1), (H7 - 1), H5, (H3 + 1), (H7 - 1), (H7 - 1), (H7 - 1), H5, (H3 + 1),300,
        0, (H7 - 1), H4, H2, (H7 - 1), (H7 - 1), (H7 - 1), H4, H2, 0, (H7 - 1), H4, H2, (H7 - 1), (H7 - 1), (H7 - 1), H4, H2,
        0, H5, H3, H1, H5, H5, H5, H3, H1, H6, H3, H1, H6, H6, H6, H3, H1, 300,
        0, H6, H4, H2, H6, Y1, H6, H4, H2, H5, H4, H2, H6, Y4, Y2, H6, H4, 300,
        0, (H7 - 1), H4, H2, (H7 - 1), Y2, H7, H4, H2, (H7 - 1), H4, H2, (H7 - 1), Y4, Y3, Y2, H7, 300,
        0, Y2, (H7 + 1), H4, (H7 + 1), Y4, (H7 + 1), Y2, Y4, (Y7 + 1), Y4, Y2, H7, H7, H5, H2, M7, 300,
        H1, _, 0, M1, M3, M5, H1, 300, (H2 - 1), _, 0, (M2 - 1), M4, (M6 - 1), H2, 300,
        0, H5, H6, H4, H6, H5, H4, H3, H2, H3, H2, H1, H2, H2, H1, M6, M5, 300,
        0, M6, M5, M4, M6, M5, M4, M3, M4, 300, M2, _, _, _,
        M2, M3, M4, M6, 0, M5, M6, H2, H3, H4, H3, H2, H4,300,
        H5, H4, 400, Y1, H6, Y1, H6, Y1, H6, 300, Y1, _, _, _,
        H4, 0, H2, (M7 - 1), M4, M7, H2, H4, 300, H5, 0, H3, H1, M5, H1, H3, H5, 300,
        H6, 700, (H5 + 1), 700, 0, H6, H5, 300, H6, _, _, _,
        H4, _, H3, _, H2, _, H1, _,
        H1, 0, H1, H2, 300, M6, M5, M6, _, _, _,
        M6, H1, H2, _, H5, _, H3, _,
        H4, _, H3, H1, H2, _, _, _,
        H4, _, H3, _, H2, _, H1, _,
        H1, 0, H1, H2, 300, M6, M5, M6, _, M6, H1,
        H2, H2, _, H2, H4, _, H5, _,
        H3, _, _, _, _, _, H2, H4,
        H5, 700, H5, 700, H6, H6, _, _, H6,
        Y1, Y2, H5, H5, H4, H6, _, H2, H4,
        H5, 700, H5, 700, H6, H6, _, _, H6,
        (H7 - 1), H6, H5, H4, H4, _, H2, H4,
        H5, 700, H5, 700, H6, H6, _, _, H6,
        Y1, Y2, H5, H5, H4, H6, _, H2, H4,
        (H7 - 1), _, H6, _, H5, _, H4, _,
        H5, H6, H5, H6, H6, _, H3, H5,
        H6, 700, H6, 700, H7, H7, _, _, H7,
        Y2, Y3, H6, H5, H7, _, H3, H5,
        H6, 700, H6, 700, H7, H7, _, _, H7,
        Y1, H7, H6, H5, H5, _, H3, H5, H6, 700, H6, 700, H7, H7, _, _, H7,
        Y2, Y3, H6, H5, H7, _, H3, H5,
        Y1, _, H7, _, H6, _, H5, _,
        H6, H5, H7, Y2, Y3, _, H3, H5,
        H6, H7, 0, H3, H2, H3, H2, 300, H6, H7, 0, H3, H2, H3, H2, 300,
        H6, H7, 0, H3, H2, H3, H2, 300, H5, 400, (H4 + 1), H5, (H4+1), 300, H3, H2,
        H6, H7, 0, H3, H2, H3, H2, 300, H6, H7, 0, H3, H2, H3, H2, 300,
        H6, H7, Y2, Y5, 0, (Y4 + 1), Y5, (Y4+1), Y3, 300, Y2, H7,
        H6, H7, 0, H3, H2, H3, H2, 300, H6, H7, 0, H3, H2, H3, H2, 300,
        H6, H7, 0, H3, H2, H3, H2, 300, H5, 400, (H4 + 1), H5, (H4+1), 300, H3, H2,
        H3, 0, H2, H3, 300, H5, 0, H3, H5, 300, H6, 0, H6, H7, Y2, Y5, H7, Y2, 300,
        Y5, 400, (Y4 + 1), Y5, (Y4+1), 300, Y3, Y2, Y3, _, Y3, Y5,
        500, H6, H7, 0, H3, H2, H3, H2, 300, H6, H7, 0, H3, H2, H3, H2, 300,
        H6, H7, 0, H3, H2, H3, H2, 300, H5, 400, (H4+1), H5, (H4+1), 300, H3, H2,
        H6, H7, 0, H3, H2, H3, H2, 300, H6, H7, 0, H3, H2, H3, H2, 300,
        H6, H7, Y2, Y5, 0, (Y4 + 1), Y5, (Y4+1), Y3, 300, Y2, H7,
        H6, H7, 0, H3, H2, H3, H2, 300, H6, H7, 0, H3, H2, H3, H2, 300,
        H6, H7, 0, H3, H2, H3, H2, 300, H5, 400, (H4 + 1), H5, (H4+1), 300, H3, H2,
        H6, 0, H7, Y2, Y3, Y2, H7, H6, 300,H3,H5,H6,H7,
        H3, 700, H3, 700, H2, H3, _, _, _,
        H3, 700, H3, 700, H2, H3, _, _, _,
    };
    for(auto i:th1)
    {
        if(i==0)
        {
            sleep=sta/2;
            continue;
        }
        if(i==300)
        {
            sleep=sta;
            continue;
        }
        if(i==700)
        {
            Sleep(sta/2);
            continue;
        }
        if(i==_)
        {
            Sleep(stb);
            continue;
        }
        if(i==400)
        {
            sleep=sta/3;
            continue;
        }
        if(i==500)
        {
            tmp=12;
            continue;
        }
        if(i==600)
        {
            tmp=0;
            continue;
        }
        if(i==800)
        {
            sleep=(sta*2)/3;
            continue;
        }

        voice=(gao<<16)+((i+tmp)<<8)+0x90;
        midiOutShortMsg(handle,voice);
        cout << ans << endl;
        ans++;
        Sleep(sleep);
    }
    midiOutClose(handle);
};

void TH2()
{
    int tmp=0;
    int th2[]=
    {
        M6,700,M6,700,M5,M6,700,M6,700,M5,M6,700,M6,700,M5,M6,_,H1,_, 
        M6,700,M6,700,M5,M6,700,M6,700,M5,
        M6,_,H4,_,H3,_,H4,750,
    };

    for(auto i:th2)
    {
        if(i==0)
        {
            sleep=sta/2;
            continue;
        }
        if(i==300)
        {
            sleep=sta;
            continue;
        }
        if(i==700)
        {
            Sleep(sta/2);
            continue;
        }
        if(i==_)
        {
            Sleep(stb);
            continue;
        }
        if(i==750)
        {
            Sleep(6000000);
            continue;
        }
        voice=(gao<<16)+((i+tmp)<<8)+0x91;
        midiOutShortMsg(handle,voice);
        Sleep(sleep);
    }
    midiOutClose(handle);
};

void TH3()
{
    int tmp=0;
    int th3[]=
    {
        M2,700,M2,700,M2,M2,700,M2,700,M2,M2,700,M2,700,M2, 
        M2,700,M2,700,M2,M2,700,M2,700,M2,M2,700,M2,700,M2,
        M2,_,M2,_,M1,_,M1,_,_,(L7 - 1),_,(L7 - 1),_,M1,_,M1,750,  
    };

    for(auto i:th3)
    {
        if(i==0)
        {
            sleep=sta/2;
            continue;
        }
        if(i==300)
        {
            sleep=sta;
            continue;
        }
        if(i==700)
        {
            Sleep(sta/2);
            continue;
        }
        if(i==_)
        {
            Sleep(stb);
            continue;
        }
        if(i==750)
        {
            Sleep(6000000);
            continue;
        }
        voice=(gao<<16)+((i+tmp)<<8)+0x92;
        midiOutShortMsg(handle,voice);
        Sleep(sleep);
    }
    midiOutClose(handle);
};

void TH4()
{
    int tmp=0;
    int th4[]=
    {
        L6,700,L6,700,L6,L6,700,L6,700,L6,L6,700,L6,700,L6,   
        L6,700,L6,700,L6,L6,700,L6,700,L6,L6,700,L6,700,L6,
        L6,_,L6,_,L5,_,L5,_,_,(L7 - 1),_,(L7 - 1),_,M1,_,M1, 
        _,M2,_,M2,_,M2,_,M2,
        _,(L7 - 1),_,(L7 - 1),_,M1,_,M1,  _,M2,_,M2,_,M2,_,M2,
        _,(L7 - 1),_,(L7 - 1),_,M1,_,M1, _,M2,_,M2,_,M2,_,M2,  
        _,(L7 - 1),_,(L7 - 1),_,M1,_,M1,  _,M2,_,M2,_,M2,_,M2, 
        _,(L7 - 1),_,(L7 - 1),_,M1,_,M1, _,M2,_,M2,_,M2,_,M2,
        _,(L7 - 1),_,(L7 - 1),_,M1,_,M1,

        _,M2,_,M2,_,M2,_,M2,
        _,(L7 - 1),_,(L7 - 1),_,M1,_,M1,
        _,M2,_,M2,_,M2,_,M2,
        _,(L7 - 1),_,(L7 - 1),_,M1,_,M1,
        _,M2,_,M2,_,M2,_,M2,
        _,(L7 - 1),_,(L7 - 1),_,M1,_,M1,
        _,M2,_,M2,_,M2,_,M2,
        _,(L7 - 1),_,(L7 - 1),_,M1,_,M1,
        _,M2,_,M2,_,M2,_,M2,750,
    };
    for(auto i:th4)
    {
        if(i==0)
        {
            sleep=sta/2;
            continue;
        }
        if(i==300)
        {
            sleep=sta;
            continue;
        }
        if(i==700)
        {
            Sleep(sta/2);
            continue;
        }
        if(i==_)
        {
            Sleep(stb);
            continue;
        }
        if(i==750)
        {
            Sleep(6000000);
            continue;
        }
        voice=(gao<<16)+((i+tmp)<<8)+0x93;
        midiOutShortMsg(handle,voice);
        Sleep(sleep);
    }
    midiOutClose(handle);
};

void TH5()
{
    int tmp=0;
    int th5[]=
    {
        L2,700,L2,700,L2,L2,700,L2,700,L2,L2,700,L2,700,L2, L2,700,L2,700,L2,L2,700,L2,700,L2,L2,700,L2,700,L2,
        L2,_,L2,_,L1,_,L1,_,  (X7 - 1),L4,(X7 - 1),L4,L1,L5,L1,L5, L2,L6,L2,L6,L2,L6,L2,L6,
        (X7 - 1),L4,(X7 - 1),L4,L1,L5,L1,L5,  L2,L6,L2,L6,L2,L6,L2,L6,
        (X7 - 1),L4,(X7 - 1),L4,L1,L5,L1,L5,  L2,L6,L2,L6,L2,L6,L2,L6,   
        (X7 - 1),L4,(X7 - 1),L4,L1,L5,L1,L5,  L2,L6,L2,L6,L2,L6,L2,L6,//重复
        (X7 - 1),L4,(X7 - 1),L4,L1,L5,L1,L5,  L2,L6,L2,L6,L2,L6,L2,L6,
        (X7 - 1),L4,(X7 - 1),L4,L1,L5,L1,L5,

        L2,L6,L2,L6,L2,L6,L2,L6,
        (X7 - 1),L4,(X7 - 1),L4,L1,L5,L1,L5,
        L2,L6,L2,L6,L2,L6,L2,L6,
        (X7 - 1),L4,(X7 - 1),L4,L1,L5,L1,L5,
        L2,L6,L2,L6,L2,L6,L2,L6,
        (X7 - 1),L4,(X7 - 1),L4,L1,L5,L1,L5,
        L2,L6,L2,L6,L2,L6,L2,L6,
        (X7 - 1),L4,(X7 - 1),L4,L1,L5,L1,L5,
        L2,L6,L2,L6,L2,L6,L2,L6,750,
    };
    for(auto i:th5)
    {
        if(i==0)
        {
            sleep=sta/2;
            continue;
        }
        if(i==300)
        {
            sleep=sta;
            continue;
        }
        if(i==700)
        {
            Sleep(sta/2);
            continue;
        }
        if(i==_)
        {
            Sleep(stb);
            continue;
        }
        if(i==750)
        {
            Sleep(6000000);
            continue;
        }
        voice=(gao<<16)+((i+tmp)<<8)+0x94;
        midiOutShortMsg(handle,voice);
        Sleep(sleep);
    }
    midiOutClose(handle);
};

int main()
{
    midiOutOpen(&handle,0,0,0,CALLBACK_NULL);
    thread t1(TH1);
    t1.detach();
    thread t2(TH2);
    t2.detach();
    thread t3(TH3);
    t3.detach();
    thread t4(TH4);
    t4.detach();
    thread t5(TH5);
    t5.detach();
    while(1);
    return 0;
}