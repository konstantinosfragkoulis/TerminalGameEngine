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

void SetGameObjectSprite(GameObject *obj, int rows, int cols, char (*arr)[cols], int layer) {
    
    obj->spriteRenderer->sprite = (char **)malloc(sizeof(char *) * rows);
    for (int i = 0; i < rows; ++i) {
        obj->spriteRenderer->sprite[i] = (char *)malloc(cols * sizeof(char));
        memcpy(obj->spriteRenderer->sprite[i], arr[i], cols);
    }

    obj->spriteRenderer->rows = rows;
    obj->spriteRenderer->cols = cols;

    obj->spriteRenderer->layer = layer;

    if(gameObjectsToDraw[layer][0] == NULL) { // This layer is empty
        gameObjectsToDraw[layer] = (GameObject **)malloc(sizeof(GameObject *) * 2); // Allocate memory for 1 GameObject
        gameObjectsToDraw[layer][0] = obj;
        gameObjectsToDraw[layer][1] = NULL;
    } else {
        const int newSize = sizeof(gameObjectsToDraw[layer]) + sizeof(GameObject *);
        gameObjectsToDraw[layer] = (GameObject **)realloc(gameObjectsToDraw[layer], newSize); // Allocate more memory for 1 more GameObject
        gameObjectsToDraw[layer][newSize / sizeof(GameObject *) - 1] = obj;
        gameObjectsToDraw[layer][newSize / sizeof(GameObject *)] = NULL;
    }
}