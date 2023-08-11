#include <malloc.h>
#include <string.h> // strcpy memcpy
#include <unistd.h>

#include "engine.h"
#include "../assets.h"

#define IMmidp (__INT_MAX__ >> 1)
#define IMmidn (-__INT_MAX__ >> 1)

int main() {

    initAll();


    /* Player */
    GameObject *player = NewGameObject("Player", termCols >> 1, termRows >> 1);
    SpriteRenderer *playerRenderer = NewSpriteRenderer(0xFFFFFF, ARR_ROWS(playerSprite), ARR_COLS(playerSprite), playerSprite, 1);
    AddSpriteRendererToGameObject(player, playerRenderer);



    /* Enemy */
    GameObject *enemy = NewGameObject("Enemy", 102, 10);
    SpriteRenderer *enemyRenderer = NewSpriteRenderer(0xFF0000, ARR_ROWS(enemySprite), ARR_COLS(enemySprite), enemySprite, 0);
    AddSpriteRendererToGameObject(enemy, enemyRenderer);

    /* Enemy2 */
    GameObject *enemy2 = NewGameObject("Enemy2", 96, 10);
    SpriteRenderer *enemyRenderer2 = NewSpriteRenderer(0xFF0000, ARR_ROWS(enemySprite), ARR_COLS(enemySprite), enemySprite, 0);
    AddSpriteRendererToGameObject(enemy2, enemyRenderer2);

    /* Enemy3 */
    GameObject *enemy3 = NewGameObject("Enemy3", 90, 10);
    SpriteRenderer *enemyRenderer3 = NewSpriteRenderer(0xFF0000, ARR_ROWS(enemySprite), ARR_COLS(enemySprite), enemySprite, 0);
    AddSpriteRendererToGameObject(enemy3, enemyRenderer3);


    /* Draw first frame */
    DrawFrame();

    GameObject **bullets = NULL;
    int bulletCount = 0;

    char c;
    while(1) {

        c = GetInput();

        if(c == 'q') break;
        
        if(c != '\0') {

            if(c == 'a') {
                player->x--;
            } else if(c == 'd') {
                player->x++;
            } else if(c == 'w') {
                player->y--;
            } else if(c == 's') {
                player->y++;
            } else if(c == ' ') {
                if(bulletCount == 0) {
                    bullets = (GameObject **)malloc(sizeof(GameObject *));
                    ++bulletCount;
                } else {
                    ++bulletCount;
                    bullets = (GameObject **)realloc(bullets, bulletCount * sizeof(GameObject *));
                }

                /* Find a way to add new bullets every time to bullets[] not the same */
                //GameObject *bullet = NewGameObject("Bullet", player->x+(player->spriteRenderer->cols >> 1), player->y-1);
                bullets[bulletCount-1] = NewGameObject("Bullet", player->x+(player->spriteRenderer->cols >> 1), player->y-1);
                SpriteRenderer *bulletRenderer = NewSpriteRenderer(0x0000FF, ARR_ROWS(bulletSprite), ARR_COLS(bulletSprite), bulletSprite, 2);
                
                AddSpriteRendererToGameObject(bullets[bulletCount-1], bulletRenderer);

            }

            DrawFrame();

            for(int i = 0; i < bulletCount; ++i) {
                /* Remove bullet from bullets[] */
                /* Remove bullet from GameObjectsToDraw[] */
                //if(bullets[i].y < 0) bullets[i] = NULL;
                bullets[i]->y--;
            }
        }

        
    }

    return 0;
}