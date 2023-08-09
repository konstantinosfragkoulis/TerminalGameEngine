#include <stdlib.h> // malloc
#include <string.h> // memcpy strcpy

#include "engine.h"

int cstrlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        ++length;
    }
    return length;
}

void SetGameObjectName(GameObject *obj, const char *name) {
    obj->name = (char *)malloc(cstrlen(name) + 1);
    strcpy(obj->name, name);
}

void SetGameObjectSprite(GameObject *obj, int rows, int cols, char (*arr)[cols]) {
    
    obj->spriteRenderer->sprite = (char **)malloc(sizeof(char *) * rows);
    for (int i = 0; i < rows; ++i) {
        obj->spriteRenderer->sprite[i] = (char *)malloc(cols * sizeof(char));
        memcpy(obj->spriteRenderer->sprite[i], arr[i], cols);
    }

    obj->spriteRenderer->rows = rows;
    obj->spriteRenderer->cols = cols;
}