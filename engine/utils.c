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

/* ***Depricated** - Use NewSpriteRenderer() and AddSpriteRendererToGameObject()*/
void SetGameObjectSprite(GameObject *obj, int rows, int cols, char (*arr)[cols], int layer) {
    
    obj->spriteRenderer->sprite = (char **)malloc(sizeof(char *) * rows);
    for (int i = 0; i < rows; ++i) {
        obj->spriteRenderer->sprite[i] = (char *)malloc(cols * sizeof(char));
        memcpy(obj->spriteRenderer->sprite[i], arr[i], cols);
    }

    obj->spriteRenderer->rows = rows;
    obj->spriteRenderer->cols = cols;

    obj->spriteRenderer->layer = layer;

    /* Add GameObject with SpriteRenderer to GameObject list to automatically render them each frame */
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

GameObject* NewGameObject(const char* name, const int x, const int y) {

    GameObject *obj = (GameObject*)malloc(sizeof(GameObject));

    obj->name = NULL;
    SetGameObjectName(obj, name);

    obj->x = x;
    obj->y = y;

    return obj;
}

SpriteRenderer* NewSpriteRenderer(const int color, int rows, int cols, char (*arr)[cols], int layer) {

    SpriteRenderer* renderer = (SpriteRenderer*)malloc(sizeof(SpriteRenderer));

    renderer->sprite = (char **)malloc(sizeof(char *) * rows);
    for (int i = 0; i < rows; ++i) {
        renderer->sprite[i] = (char *)malloc(cols * sizeof(char));
        memcpy(renderer->sprite[i], arr[i], cols);
    }

    renderer->color = (int) color;
    renderer->rows = rows;
    renderer->cols = cols;
    renderer->layer = layer;

    return renderer;
}

void AddSpriteRendererToGameObject(GameObject* obj, SpriteRenderer* renderer) {
    obj->spriteRenderer = renderer;

    /* Add GameObject with SpriteRenderer to GameObject list to automatically render them each frame */
    if(gameObjectsToDraw[renderer->layer][0] == NULL) { // This layer is empty
        gameObjectsToDraw[renderer->layer][0] = obj;
        layerElementCount[renderer->layer] = 1;
    } else {
        layerElementCount[renderer->layer]++;
        const int newSize = (layerElementCount[renderer->layer] + 1) * sizeof(GameObject *);
        gameObjectsToDraw[renderer->layer] = (GameObject **)realloc(gameObjectsToDraw[renderer->layer], newSize); // Allocate more memory for 1 more GameObject
        gameObjectsToDraw[renderer->layer][layerElementCount[renderer->layer] - 1] = obj;
    }
}