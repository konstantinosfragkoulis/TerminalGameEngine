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
    
    SpriteRenderer playerRenderer;
    playerRenderer.color = 0;
    player.spriteRenderer = &playerRenderer;

    SetGameObjectSprite(&player, sizeof(playerSprite) / sizeof(playerSprite[0]), sizeof(playerSprite[0]) / sizeof(playerSprite[0][0]), playerSprite);

    DrawGameObject(&player);
    

    DrawFrame();

    char c;
    while(1) {
        c = GetInput();

        if(c == 'q') break;
        
        if(c != '\0') {

            if(c == 'a') {
                player.x--;
            } else if(c == 'd') {
                player.x++;
            } else if(c == 'w') {
                player.y--;
            } else if(c == 's') {
                player.y++;
            }

            DrawGameObject(&player);

            DrawFrame();
        }

    
    }

    return 0;
}