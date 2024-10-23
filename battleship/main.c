#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "console.h"
#include "fsst.h"

int main() {
    initConsole();
    system("chcp 65001");
    system("title Battleship");
    srand(time(0));

    clrscr();

    setCursorType(OFF);

    int **spielfeld = (int **)malloc(ROWS * sizeof(int *));
    speicher(OPEN, spielfeld);

    fillArray(spielfeld);
    spielfeldAusgabe(spielfeld, ROWS, COLS);
    spielfeldInit(spielfeld, ROWS, COLS);
    placeBoat(spielfeld, ROWS, COLS);

    while (!gameover) {
        if(kbhit()) {
            switch (getch()) {
                case SPACE:
                    spielfeldInit(spielfeld, ROWS, COLS);
                    placeBoat(spielfeld, ROWS, COLS);
                    break;
                case ESCAPE:
                    gameover = true;
                    break;
                default: break;
            }
        }

        spielfeldAusgabe(spielfeld, ROWS, COLS);
        delay(75);
    }

    speicher(CLOSE, spielfeld);
    closeConsole();

    return EXIT_SUCCESS;
}

void fillArray(int **array) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            array[i][j] = 0;
}

void speicher(int c, int **array) {
    if (c == OPEN) {
        for (int i = 0; i < ROWS; i++)
            array[i] = (int *)malloc(COLS * sizeof(int));
    } else if (c == CLOSE) {
        for (int i = 0; i < ROWS; i++)
            free(array[i]);
        free(array);
    }
}

void spielfeldInit(int **array, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            array[i][j] = WATER;

    textcolor(GRAY);
    for (int i = 0; i < COLS; i++) {
        gotoxy(ROWS * 2, i);
        printf("║ %c", A + i);
    }

    for (int i = 0; i < ROWS; i++) {
        gotoxy(i * 2, COLS);
        printf("══");
    }
    for (int i = 0; i < ROWS; i++) {
        gotoxy(i * 2, COLS + 1);
        printf("%d", i + 1);
    }
    gotoxy(ROWS * 2,COLS);
    printf("╝");
    textcolor(WHITE);
}

void spielfeldAusgabe(int **array, int rows, int cols) {
    gotoxy(0,0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (array[i][j] == WATER) {
                textcolor(CYAN);
                printf("██");
            } else if (array[i][j] == BOAT) {
                textcolor(GRAY);
                printf("██");
            }
            textcolor(WHITE);
        }
        printf("\n");
    }
}

void placeBoat(int **array, int rows, int cols) {
    int boatCounts[] = {1, 2, 3, 4};  // Anzahl der Boote: 1x 4er, 2x 3er, 3x 2er, 4x 1er
    int boatSizes[] = {VIER, DREI, ZWEI, EINS};  // Längen der Boote

    for (int b = 0; b < 4; b++) {  // Für jeden Bootstyp
        int boatCount = boatCounts[b];
        int boatLength = boatSizes[b];

        for (int i = 0; i < boatCount; i++) {
            int x, y, valid, horizontal;

            do {
                valid = 1;
                horizontal = rand() % 2;  // 0 = vertikal, 1 = horizontal
                x = rand() % (horizontal ? (cols - boatLength + 1) : cols);
                y = rand() % (horizontal ? rows : (rows - boatLength + 1));

                // Überprüfen, ob die gesamte Bootslänge und Umgebung frei ist
                for (int j = 0; j < boatLength; j++) {
                    int checkX = x + (horizontal ? j : 0);
                    int checkY = y + (horizontal ? 0 : j);

                    if (array[checkY][checkX] != WATER ||
                        (checkY > 0 && array[checkY - 1][checkX] != WATER) ||        // oben
                        (checkY < rows - 1 && array[checkY + 1][checkX] != WATER) ||  // unten
                        (checkX > 0 && array[checkY][checkX - 1] != WATER) ||         // links
                        (checkX < cols - 1 && array[checkY][checkX + 1] != WATER)) {  // rechts
                        valid = 0;
                        break;
                        }
                }
            } while (!valid);

            // Boot platzieren
            for (int j = 0; j < boatLength; j++) {
                int placeX = x + (horizontal ? j : 0);
                int placeY = y + (horizontal ? 0 : j);
                array[placeY][placeX] = BOAT;
            }
        }
    }
}

void placeBoatManually(int **array, int rows, int cols, int type) {
    int x = 0, y = 0, valid = 0;

    if (type == EINS) {
        do {
            x = rand() % rows;
            y = rand() % cols;
            if (array[y][x] == WATER &&
                (y == 0 || array[y - 1][x] == WATER) &&
                (y == rows - 1 || array[y + 1][x] == WATER) &&
                (x == 0 || array[y][x - 1] == WATER) &&
                (x == cols - 1 || array[y][x + 1] == WATER)) {
                valid = 1;
            }
        } while (!valid);
        array[y][x] = BOAT;
    }
}