//******************************************************************************\\
//                                                                              \\
//                               b e r n i i i i                                \\
//                                                                              \\
//                                  windows                                     \\
//                                                                              \\
//                                                               BERNI FEB 2024 \\
//******************************************************************************\\


// I N C L U D E S
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "berni.h"
#include "console.h"


// V A R I A B L E N
int x, y;


// F u n k t i o n e n :
//---------------------

//  G O T O   T O P
void goTop() {
    gotoxy(0, 0);
}


//  I N I T   P R O J E C T
void initPrjct() {
    initConsole();
    system("title Dungeon Crawler");
    SetConsoleOutputCP(CP_UTF8);
    setCursorType(1);
    goTop();
    clrscr();
    textcolor(H_WHITE);
}

//  R E S E T   C O L O R
void rc(int color) {
    switch(color) {
        case W:
            textcolor(H_WHITE);
            break;
        case B:
            textcolor(BLACK);
            break;
        default: break;
    }
}

//  G E T   C U R R.   P O S.
void getpos() {
    getxy(&x, &y);
}

//  Z E N T R I E R U N G
void align(int align) {
    switch(align) {
        case CENTER:
            gotoxy(50, y+1);
            break;
        case LINKS:
            gotoxy(0, y+1);
            break;
        case RECHTS:
            gotoxy(79, y+1);
        default: break;
    }
}

//  E N D   P R O G R A M
void end() {
    closeConsole();
}

// T I T E L
void title(const char* text) {
    getpos();
    align(CENTER);
    printf("%s\n", text);
}

// Z E I L E N U M B R U C H
void br() {
    printf("\n\n");
}