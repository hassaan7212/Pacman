#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
void maze();
void xy(int x, int y);
void cutp();
void printp();
char getCharAtxy(short int x, short int y);
int scores = 0;
int life = 3;
int x = 2, y = 1;
int g = 2, h = 18;
int g2 = 60, h2 = 1;
int g3 = 62, h3 = 18;
int g4 = 30, h4 = 10;
char gprev = ' ';
char gprev2 = ' ';
char gprev3 = ' ';
char gprev4 = ' ';
int gdirection = 1;
int gdirection2 = 1;
int gdirection3 = 1;
int gdirection4 = 1;
fstream highscore;
void fileto()
{
    highscore.open("pacmanscore.txt", ios::app);
    highscore << endl
              << scores;
    highscore.close();
}
void showscore()
{
    bool showhigh = true;
    int scoreslist;
    cout << "Scores: ";
    highscore.open("pacmanscore.txt", ios::in);
    // for (int i = 0; i < highscore.length(); i++)
    while (highscore >> scoreslist)
    {
        cout << endl
             << scoreslist;
        if (scores < scoreslist)
        {
            showhigh = false;
        }
    }
    highscore.close();
    if (showhigh)
    {
        cout << "----You have hit the high score----" << endl;
    }
}
char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize = {1, 1};
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}
void updatescoreandlives()
{
    xy(0, 20);
    cout << "Score = " << scores << "  Lives = " << life << "   ";
}
void score(char nextp)
{
    if (nextp == '.')
    {
        scores++;
    }
    else if (nextp == 'o')
    {
        scores += 5;
    }
    updatescoreandlives();
}
void moveGhost(int &g, int &h, char &gprev, int &gdirection)
{
    xy(g, h);
    cout << gprev;
    int G[4] = {-1, 0, 1, 0};
    int H[4] = {0, 1, 0, -1};
    int newg = g + G[gdirection];
    int newh = h + H[gdirection];
    char nextp = getCharAtxy(newg, newh);
    if (nextp == '#')
    {
        gdirection = (gdirection + 3) % 4;
        newg = g + G[gdirection];
        newh = h + H[gdirection];
        nextp = getCharAtxy(newg, newh);
    }
    if (nextp != '#')
    {
        gprev = nextp;
        g = newg;
        h = newh;
    }
    if (!(g == x && h == y))
    {
        xy(g, h);
        cout << "G";
    }
}
void updateg()
{
    moveGhost(g, h, gprev, gdirection);
    moveGhost(g2, h2, gprev2, gdirection2);
    moveGhost(g3, h3, gprev3, gdirection3);
    moveGhost(g4, h4, gprev4, gdirection4);
}
main()
{
    system("color 03");
    system("cls");
    maze();
    updatescoreandlives();
    while (true)
    {
        updateg();
        xy(x, y);
        cout << "p";
        Sleep(50);
        xy(x, y);
        cout << " ";
        if (GetAsyncKeyState(VK_RIGHT))
        {
            char nextp = getCharAtxy(x + 1, y);
            if (nextp == ' ' || nextp == '.' || nextp == 'o')
            {
                score(nextp);
                if (scores == 400)
                {
                    system("color 02");
                    cout << "\n....YOU WIN....\n....CONGRATULATIONS....";
                    break;
                }
                cutp();
                x = x + 1;
                printp();
            }
        }
        if (GetAsyncKeyState(VK_LEFT))
        {
            char nextp = getCharAtxy(x - 1, y);
            if (nextp == ' ' || nextp == '.' || nextp == 'o')
            {
                score(nextp);
                if (scores == 400)
                {
                    system("color 02");
                    cout << "\nYOU WIN\nCONGRATULATIONS";
                    break;
                }
                cutp();
                x = x - 1;
                printp();
            }
        }
        if (GetAsyncKeyState(VK_UP))
        {
            char nextp = getCharAtxy(x, y - 1);
            if (nextp == ' ' || nextp == '.' || nextp == 'o')
            {
                score(nextp);
                if (scores == 400)
                {
                    system("color 02");
                    cout << "\nYOU WIN\nCONGRATULATIONS";
                    break;
                }
                cutp();
                y = y - 1;
                printp();
            }
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            char nextp = getCharAtxy(x, y + 1);
            if (nextp == ' ' || nextp == '.' || nextp == 'o')
            {
                score(nextp);
                if (scores == 400)
                {
                    system("color 02");
                    cout << "\nYOU WIN\nCONGRATULATIONS";
                    break;
                }
                cutp();
                y = y + 1;
                printp();
            }
        }

        if ((x == g && y == h) || (x == g2 && y == h2) || (x == g3 && y == h3) || (x == g4 && y == h4))
        {
            system("color 04");
            Sleep(400);
            system("color 03");
            life--;
            updatescoreandlives();
            if (life == 0)
            {
                cout << "\nGAME OVER!" << endl;
                system("color 04");
                Sleep(1000);
                system("color 05");
                showscore();
                fileto();
                break;
            }
            /*if (scores == 400)
            {
                cout << "\nYOU WIN\nCONGRATULATIONS";
                break;
            }*/
            xy(x, y);
            cout << " ";
            xy(g, h);
            cout << gprev;
            xy(g2, h2);
            cout << gprev2;
            xy(g3, h3);
            cout << gprev3;
            xy(g4, h4);
            cout << gprev4;
            x = 2;
            y = 1;
        }
    }
    return 0;
}
void maze()
{
    cout << "#################################################################" << endl;
    cout << "##     ##........   ........o ## o.............o.............  ##" << endl;
    cout << "##     ##      ##     ####      .  ## oo######          ##  .  ##" << endl;
    cout << "##     ##             ##................  ..##     #######  .  ##" << endl;
    cout << "##     ##      ############### .. ### ..##.........o.........  ##" << endl;
    cout << "##      ##    ##      ##       .##### ..  ..    #########   #####" << endl;
    cout << "##        ####        ## ##### ...... ..##....  ##     ##   .  ##" << endl;
    cout << "#######                        .##### ..##....####     ##   .  ##" << endl;
    cout << "##      ............o......... .   ## .......................  ##" << endl;
    cout << "##     #########    #### ##### .   ## ..####  ......   #####o  ##" << endl;
    cout << "##     ##          .. ##    ## .   ## ..    ##..  ##        .  ##" << endl;
    cout << "##................... ##       .   ## oo    ##..  ##        .  ##" << endl;
    cout << "##..   ############.. ######## .##############.. ####  #### .####" << endl;
    cout << "##..   ##  ...............     ... ## o..............o..##     ##" << endl;
    cout << "##..   ##   ###### .. ##       o.. ##   #   ##      ....##  o  ##" << endl;
    cout << "##..   ######      .. ##########.. ###  ####         #####  .  ##" << endl;
    cout << "##..        #######..           ..                          .  ##" << endl;
    cout << "##..             ##.. o.....................o               .####" << endl;
    cout << "##..   o.........##..........o                          ### .  ##" << endl;
    cout << "#################################################################" << endl;
}

void xy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void cutp()
{
    xy(x, y);
    cout << " ";
    Sleep(10);
}
void printp()
{
    xy(x, y);
    cout << "p";
}
