#include <stdio.h>
#include "berni.h"
#include "console.h"
#include <time.h>
#include <stdbool.h>

#define LEER 0
#define GOLD 1
#define FALLE 2
#define SPIELER 3
#define FALLEN 12
#define X 0
#define Y 1

void initSpielfeld(int spielfeld[10][10], int spielerPos[2]);
void ausgabeSpielfeld(int spielfeld[10][10], int spielerPos[2]);
int checkPosition(int spielfeld[10][10], int spielerPos[2]);

bool gameover = false;
bool gewonnen = false;

int main() {
    initPrjct();
    clrscr();
    gotoxy(0, 0);
    setCursorType(0);
    srand(time(0));
    int spielfeld[10][10] = {LEER};
    int spielerPos[2] = {0};

    //Phase1: Initialisierung
    initSpielfeld(spielfeld, spielerPos);

    //Phase2: Spielschleife
    while (!gameover && !gewonnen) {

        if(kbhit()) {
            switch (getch()) {
                case UP:
                case 'W':
                case 'w': {if (--spielerPos[Y] < 0) spielerPos[Y] = 0;} break;
                case LEFT:
                case 'A':
                case 'a': {if (--spielerPos[X] < 0) spielerPos[X] = 0;} break;
                case DOWN:
                case 'S':
                case 's': {if (++spielerPos[Y] > 9) spielerPos[Y] = 9;} break;
                case RIGHT:
                case 'D':
                case 'd': {if (++spielerPos[X] > 9) spielerPos[X] = 9;} break;
                case ESC: return 0;
                default: break;
            }
        }

        ausgabeSpielfeld(spielfeld, spielerPos);
        checkPosition(spielfeld, spielerPos);
        // framebremse
        delay(100);
    }

    //Phase3: Beenden
    if (gameover) {
        clrscr();
        gotoxy(0,0);
        textcolor(RED);
        printf("VORBEI!\n");
        textcolor(WHITE);
        getch();
        gameover = false;
        main();
    } else if (gewonnen) {
        clrscr();
        gotoxy(0,0);
        textcolor(GREEN);
        printf("Glückwunsch, du hast das Gold gefunden!\n");
        textcolor(WHITE);
        getch();
        gewonnen = false;
        main();
    }

    getch();
    return 0;
}

void initSpielfeld(int spielfeld[10][10], int spielerPos[2]) {
    //Gold platzieren
    spielfeld[rand()%10][rand()%10] = GOLD;

    //Fallen platzieren
    for (int i = 0; i < FALLEN; ++i) {
        do {
            int x = rand()%10;
            int y = rand()%10;
            if (spielfeld[y][x] == LEER) {
                spielfeld[y][x] = FALLE;
                break;
            }
        } while(1);
    }

    //Spieler platzieren
    do {
        spielerPos[X] = rand()%10;
        spielerPos[Y] = rand()%10;
    } while(spielfeld[spielerPos[Y]][spielerPos[X]] != LEER);

}

void ausgabeSpielfeld(int spielfeld[10][10], int spielerPos[2]) {
    gotoxy(0,0);
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            if (i == 0 || i == 11 || j == 0 || j == 11) {
                printf("+");
            }
            else
                printf(" ");
        }
        printf("\n");
    }

    gotoxy(1,1);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            switch (spielfeld[i][j]) {
                case LEER: printf(" "); break;
                case GOLD:
                    textcolor(YELLOW);
                    printf("G");
                    textcolor(WHITE);
                    break;
                case FALLE:
                    textcolor(RED);
                    printf("F");
                    textcolor(WHITE);
                    break;
                default: break;
            }
        }
        printf("\n+");
        //feels fishy...
    }

    gotoxy(spielerPos[X]+1, spielerPos[Y]+1);
    textcolor(GREEN);
    printf("H");
    textcolor(WHITE);
}

int checkPosition(int spielfeld[10][10], int spielerPos[2]) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (spielfeld[spielerPos[Y]][spielerPos[X]] == FALLE) {
                gameover = true;
            } else if (spielfeld[spielerPos[Y]][spielerPos[X]] == GOLD) {
                gewonnen = true;
            }
        }
    }
}