#include <stdlib.h> // malloc
#include <string.h> // strcpy memcpy

#include "engine.h"
#include "../assets.h"

int main() {

    initAll();


    /* Player */
    GameObject player = *(NewGameObject(&player, "Player", termCols >> 1, termRows >> 1));

    SpriteRenderer playerRenderer = *(NewSpriteRenderer(&playerRenderer, 0xFFFFFF, ARR_ROWS(playerSprite), ARR_COLS(playerSprite), playerSprite, 1));

    AddSpriteRendererToGameObject(&player, &playerRenderer);



    /* Enemy */
    GameObject enemy = *(NewGameObject(&enemy, "Enemy", 102, 10));
    SpriteRenderer enemyRenderer = *(NewSpriteRenderer(&enemyRenderer, 0xFF0000, ARR_ROWS(enemySprite), ARR_COLS(enemySprite), enemySprite, 0));
    AddSpriteRendererToGameObject(&enemy, &enemyRenderer);

    /* Enemy2 */
    GameObject enemy2 = *(NewGameObject(&enemy2, "Enemy2", 96, 10));
    SpriteRenderer enemyRenderer2 = *(NewSpriteRenderer(&enemyRenderer2, 0xFF0000, ARR_ROWS(enemySprite), ARR_COLS(enemySprite), enemySprite, 0));
    AddSpriteRendererToGameObject(&enemy2, &enemyRenderer2);

    /* Enemy3 */
    GameObject enemy3 = *(NewGameObject(&enemy3, "Enemy3", 90, 10));
    SpriteRenderer enemyRenderer3 = *(NewSpriteRenderer(&enemyRenderer3, 0xFF0000, ARR_ROWS(enemySprite), ARR_COLS(enemySprite), enemySprite, 0));
    AddSpriteRendererToGameObject(&enemy3, &enemyRenderer3);


    /* Draw first frame */
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

            DrawFrame();
        }

    
    }

    return 0;
}