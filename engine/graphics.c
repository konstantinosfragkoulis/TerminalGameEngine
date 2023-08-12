#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <malloc.h>

#include "engine.h"

char **fb;
int **colors;

int termRows;
int termCols;

void initFrameBuffer() {
    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    termRows = ws.ws_row-1;
    termCols = ws.ws_col;

    /* Allocate memory and Initialize the Frame Buffer and ColorBuffer */
    fb = (char **)malloc(ws.ws_col * sizeof(char *));
    colors = (int **)malloc(ws.ws_col * sizeof(int *));
    for (int i = 0; i < ws.ws_col; ++i) {
        fb[i] = (char *)malloc(ws.ws_row * sizeof(char));
        colors[i] = (int *)malloc(ws.ws_row * sizeof(int));

        for(int j = 0; j < ws.ws_row; ++j) {
            fb[i][j] = ' ';
            colors[i][j] = (int) 0xFFFFFF; // white
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

/* All GameObjects with a SpriteRenderer that used SetGameObjectSprite() are automatically drawn. */
/* ***Use only if you know what you are doing** */
void DrawGameObject(GameObject* obj) {
    for (int i = 0; i < obj->spriteRenderer->cols; i++) {
        for (int j = 0; j < obj->spriteRenderer->rows; j++) {
            if(obj->x+i >= 0 && obj->x+i <= termCols-obj->spriteRenderer->cols && obj->y+j >= 0 && obj->y+j <= termRows-obj->spriteRenderer->rows && obj->spriteRenderer->sprite[j][i] != ' ') {
                fb[obj->x+i][obj->y+j] = obj->spriteRenderer->sprite[j][i];
                colors[obj->x+i][obj->y+j] = obj->spriteRenderer->color;
            }
        }
    }
}

void DrawFrame() {

    /* Automatically draw all GameObjects with a SpriteRenderer */
    for(int i = 0; i < MAX_LAYERS; ++i) {
        for (int j = 0; gameObjectsToDraw[i][j] != NULL; ++j) {
            DrawGameObject(gameObjectsToDraw[i][j]);
        }
    }

    for(int i = 0; i < termRows; ++i) {
        for(int j = 0; j < termCols; ++j) {
            if(colors[j][i] == (int)0xFF0000) { // red
                printf("\033[31m%c\033[0m", fb[j][i]);
            } else if(colors[j][i] == (int)0xFFFFFF) { // white
                printf("\033[97m%c\033[0m", fb[j][i]);
            } else if(colors[j][i] == (int)0x0000FF) { // blue
                printf("\033[34m%c\033[0m", fb[j][i]);
            }

            /* Reset FrameBuffer and ColorBuffer */
            fb[j][i] = ' ';
            colors[j][i] = (int) 0xFFFFFF; // white
        }
        printf("\n");
    }
}
