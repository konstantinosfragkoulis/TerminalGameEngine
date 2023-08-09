#include <stdlib.h> // malloc
#include <string.h> // strcpy memcpy

#include "engine.h"
#include "../assets.h"

int main() {

    GameObject player;

    // malloc to make it mutable
    player.name = (char *)malloc(cstrlen("player") + 1); // +1 for the null terminator
    strcpy(player.name, "player");
    player.x = termCols >> 1;
    player.y = termRows >> 1;

    SpriteRenderer playerRenderer;
    playerRenderer.color = 0;
    playerRenderer.sprite = (char **)malloc(sizeof(char *) * 3);
    // Copy content from playerSprite to playerRenderer.sprite
    for (int i = 0; i < 3; i++) {
        playerRenderer.sprite[i] = (char *)malloc(5 * sizeof(char));
        memcpy(playerRenderer.sprite[i], playerSprite[i], 5);
    }

    player.spriteRenderer = &playerRenderer;

    initAll();

    DrawGameObject(&player);

    char c;
    int cnt = 0;
    while(1) {
        c = GetInput();

        if(c == 'q') break;
        
        if(c != '\0') {
            Print(&c, cnt, 0);
            //printf("%c\n", c);
            DrawFrame();
            ++cnt;
        }

    
    }

    return 0;
}