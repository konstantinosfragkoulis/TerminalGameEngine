#include <stdlib.h> // malloc
#include <string.h> // strcpy memcpy

#include "engine.h"
#include "../assets.h"

int main() {

    initAll();


    /* Player */
    GameObject player = *(NewGameObject(&player, "Player", termCols >> 1, termRows >> 1));

    SpriteRenderer playerRenderer;
    playerRenderer.color = (int) 0xFFFFFF; // white
    player.spriteRenderer = &playerRenderer;

    SetGameObjectSprite(&player, ARR_ROWS(playerSprite), ARR_COLS(playerSprite), playerSprite, 1);



    /* Enemy */
    GameObject enemy = *(NewGameObject(&enemy, "Enemy", 102, 10));

    SpriteRenderer enemyRenderer;
    enemyRenderer.color = (int) 0xFF0000; // red
    enemy.spriteRenderer = &enemyRenderer;

    SetGameObjectSprite(&enemy, ARR_ROWS(enemySprite), ARR_COLS(enemySprite), enemySprite, 0);
    


    /* Enemy2 */
    GameObject enemy2 = *(NewGameObject(&enemy2, "Enemy2", 96, 10));

    SpriteRenderer enemyRenderer2;
    enemyRenderer2.color = (int) 0xFF0000; // red
    enemy2.spriteRenderer = &enemyRenderer2;

    SetGameObjectSprite(&enemy2, ARR_ROWS(enemySprite), ARR_COLS(enemySprite), enemySprite, 0);



    /* Enemy3 */
    GameObject enemy3 = *(NewGameObject(&enemy3, "Enemy3", 90, 10));

    SpriteRenderer enemyRenderer3;
    enemyRenderer3.color = (int) 0xFF0000; // red
    enemy3.spriteRenderer = &enemyRenderer3;

    SetGameObjectSprite(&enemy3, ARR_ROWS(enemySprite), ARR_COLS(enemySprite), enemySprite, 0);



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