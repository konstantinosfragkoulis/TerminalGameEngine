#include <malloc.h>
#include <memory.h>

#include "engine.h"

int cstrlen(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        ++length;
    }
    return length;
}

void SetGameObjectName(GameObject *obj, const char *name) {
    free(obj->name);
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
        gameObjectsToDraw[layer][0] = obj;
        layerElementCount[layer] = 1;
    } else {
        layerElementCount[layer]++;
        const int newSize = (layerElementCount[layer] + 1) * sizeof(GameObject *);
        gameObjectsToDraw[layer] = (GameObject **)realloc(gameObjectsToDraw[layer], newSize); // Allocate more memory for 1 more GameObject
        gameObjectsToDraw[layer][layerElementCount[layer] - 1] = obj;
    }
}

GameObject* NewGameObject(GameObject *obj, const char* name, const int x, const int y) {

    obj->name = NULL;
    SetGameObjectName(obj, name);

    obj->x = x;
    obj->y = y;

    return obj;
}