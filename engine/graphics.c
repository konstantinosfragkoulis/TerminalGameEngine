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

/* All GameObjects with a SpriteRenderer that used SetGameObjectSprite() are automatically drawn. */
/* ***Use only if you know what you are doing** */
void DrawGameObject(GameObject* obj) {
    for (int i = 0; i < obj->spriteRenderer->cols; i++) {
        for (int j = 0; j < obj->spriteRenderer->rows; j++) {
            if(obj->x+i >= 0 && obj->x+i <= termCols-obj->spriteRenderer->cols && obj->y+j >= 0 && obj->y+j <= termRows-obj->spriteRenderer->rows && obj->spriteRenderer->sprite[j][i] != ' ') {
                fb[obj->x+i][obj->y+j] = obj->spriteRenderer->sprite[j][i];
            }
        }
    }
}

void DrawFrame() {

    /* Automatically draw all GameObjects with a SpriteRenderer */
    for(int i = 0; i < MAX_LAYERS; ++i) {
        //for(int j = 0; j < sizeof(gameObjectsToDraw[i])/sizeof(GameObject *); ++j) {
        //    DrawGameObject(gameObjectsToDraw[i][j]);
        //}
        GameObject **objectsInLayer = gameObjectsToDraw[i];
        for (int j = 0; objectsInLayer[j] != NULL; ++j) {
            DrawGameObject(objectsInLayer[j]);
        }
    }

    for(int i = 0; i < termRows; ++i) {
        for(int j = 0; j < termCols; ++j) {
            printf("%c", fb[j][i]);
            fb[j][i] = ' ';
        }
        printf("\n");
    }
}