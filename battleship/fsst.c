//
// Feichtinger Bernhard
// 15.10.2024
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fsst.h"
#include "console.h"

//
// Array Funktionen
//

void bubbleSort(int array[], int length) {
    int zwSpeicher;

    for (int i = 1; i < length; i++) {
        for (int j = 0; j < length - i; j++) {
            if (array[j] > array[j + 1]) {
                zwSpeicher = array[j];
                array[j] = array[j + 1];
                array[j + 1] = zwSpeicher;
            }
        }
    }
}

void shuffleArray(int array[], int size) {
    srand(time(0));
    for (int i = 0; i < size - 1; i++) {
        int zWert = i + rand() / (RAND_MAX / (size - i) + 1);
        int temp = array[zWert];
        array[zWert] = array[i];
        array[i] = temp;
    }
}

//
// Allgemeine Funktionen
//

void start() {
    initConsole();
    setCursorType(CURSOR);
    SetConsoleOutputCP(CP_UTF8);
}

void printPtrChar(int *prtChar) {
    int charLength = strlen(prtChar);

    for (int i = 0; i < charLength; ++i) {
        printf("%c", *prtChar);
        prtChar++;
    }
}

void asciiZeichen(int minZahl, int maxZahl) {
    int nummmer = 0;
    for (int i = minZahl; i < maxZahl; i++) {
        printf("%d - %d: %c\n", nummmer++, i, i);
    }
}