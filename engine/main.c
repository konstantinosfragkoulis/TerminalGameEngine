#include <stdlib.h> // malloc
#include <string.h> // strcpy memcpy

#include "engine.h"
#include "../assets.h"

int main() {

    initAll();


    /* Player */
    GameObject player;

    SetGameObjectName(&player, "Player");
    
    player.x = termCols >> 1;
    player.y = termRows >> 1;
    
    SpriteRenderer playerRenderer;
    playerRenderer.color = (int) 0xFFFFFF; // white
    player.spriteRenderer = &playerRenderer;

    SetGameObjectSprite(&player, sizeof(playerSprite) / sizeof(playerSprite[0]), sizeof(playerSprite[0]) / sizeof(playerSprite[0][0]), playerSprite, 1);



    /* Enemy */
    GameObject enemy;
    SetGameObjectName(&enemy, "Enemy");

    enemy.x = 102;
    enemy.y = 10;

    SpriteRenderer enemyRenderer;
    enemyRenderer.color = (int) 0xFF0000; // red
    enemy.spriteRenderer = &enemyRenderer;

    SetGameObjectSprite(&enemy, sizeof(enemySprite) / sizeof(enemySprite[0]), sizeof(enemySprite[0]) / sizeof(enemySprite[0][0]), enemySprite, 0);
    


    /* Enemy2 */
    GameObject enemy2;
    SetGameObjectName(&enemy2, "Enemy2");

    enemy2.x = 10;
    enemy2.y = 10;

    SpriteRenderer enemyRenderer2;
    enemyRenderer2.color = (int) 0xFF0000; // red
    enemy2.spriteRenderer = &enemyRenderer2;

    SetGameObjectSprite(&enemy2, sizeof(enemySprite) / sizeof(enemySprite[0]), sizeof(enemySprite[0]) / sizeof(enemySprite[0][0]), enemySprite, 0);



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