#include <stdlib.h> // malloc

#include "engine.h"

GameObject **gameObjectsToDraw[MAX_LAYERS];
int layerElementCount[MAX_LAYERS];

void initAll() {

    enableRawMode();
    
    initFrameBuffer();

    for(int i = 0; i < MAX_LAYERS; ++i) {
        gameObjectsToDraw[i] = (GameObject **)malloc(sizeof(GameObject *));
        gameObjectsToDraw[i][0] = NULL;
        layerElementCount[i] = 0;
    }


}