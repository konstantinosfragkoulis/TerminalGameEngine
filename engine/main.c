#include <stdlib.h> // malloc
#include <string.h> // strcpy memcpy

#include "engine.h"
#include "../assets.h"

int main() {

    initAll();


    GameObject player;

    SetGameObjectName(&player, "Player");
    
    player.x = termCols >> 1;
    player.y = termRows >> 1;
    
    /* Debug */
    Print(player.name, player.x, player.y);

    SpriteRenderer playerRenderer;
    playerRenderer.color = 0;
    player.spriteRenderer = &playerRenderer;

    SetGameObjectSprite(&player, sizeof(playerSprite) / sizeof(playerSprite[0]), sizeof(playerSprite[0]) / sizeof(playerSprite[0][0]), playerSprite);

    DrawGameObject(&player);
    

    DrawFrame();

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