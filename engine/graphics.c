#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "engine.h"

char **fb;

int termRows;
int termCols;

void initFrameBuffer() {
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    termRows = ws.ws_row-1;
    termCols = ws.ws_col;

    /* Allocate memory for the Frame Buffer */
    fb = (char **)malloc(ws.ws_col * sizeof(char *));
    for (int i = 0; i < ws.ws_col; ++i) {
        fb[i] = (char *)malloc(ws.ws_row * sizeof(char));
    }

    for(int i = 0; i < ws.ws_col; ++i) {
        for(int j = 0; j < ws.ws_row; ++j) {
            fb[i][j] = ' ';
        }
    }

}

/* ENHANCEMENT - Ability to write vertical text */
/* Write text to the screen beginning at a specific point */
void Print(const char *str, int x, int y) {
    int strLen = cstrlen(str);

    for(int i = 0; i < strLen; ++i) {
        fb[x+i][y] = str[i];
    }
}

void DrawGameObject(GameObject* obj) {
    for (int i = 0; i < obj->spriteRenderer->cols; i++) {
        for (int j = 0; j < obj->spriteRenderer->rows; j++) {
            fb[obj->x+i][obj->y+j] = obj->spriteRenderer->sprite[j][i];
        }
    }
}

void DrawFrame() {
    for(int i = 0; i < termRows; ++i) {
        for(int j = 0; j < termCols; ++j) {
            printf("%c", fb[j][i]);
        }
        printf("\n");
    }
}