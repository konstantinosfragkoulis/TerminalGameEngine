#ifndef ENGINE_H
#define ENGINE_H

typedef int bool;
#define true 1
#define false 0

#define NULL ((void *)0)

#define ARR_ROWS(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARR_COLS(arr) (sizeof(arr[0]) / sizeof(arr[0][0]))

/* Game Object */
/* Sprite Renderer */
typedef struct {
    int color;
    char **sprite;
    int rows, cols;
    int layer;
    /* float opacity; */
} SpriteRenderer;

/* RigidBody */
typedef struct {
    bool gravityEnabled;
    float gravity;
    char **collider;
    bool isTrigger;
    bool freezePosition;
    bool freezeRotation;
} RigidBody;

/* Core */
typedef struct {
    char *name;
    int x, y;
    SpriteRenderer *spriteRenderer;
    RigidBody *rigidBody;
} GameObject;



extern int termRows;
extern int termCols;

#define MAX_LAYERS 10

/* All GameObjects with a SpriteRenderer. They will be automatically drawn. */
extern GameObject **gameObjectsToDraw[MAX_LAYERS];
extern int layerElementCount[MAX_LAYERS];

/* inputManager.c */
extern void enableRawMode();
extern void disableRawMode();
extern char GetInput();

/* utils.c */
extern int cstrlen(const char *str);
extern void SetGameObjectName(GameObject *obj, const char *name);
extern void SetGameObjectSprite(GameObject *obj, int rows, int cols, char (*arr)[cols], int layer);
extern GameObject* NewGameObject(GameObject *obj, const char* name, const int x, const int y);
extern SpriteRenderer* NewSpriteRenderer(SpriteRenderer* renderer, const int color, int rows, int cols, char (*arr)[cols], int layer);
extern void AddSpriteRendererToGameObject(GameObject* obj, SpriteRenderer* renderer);

/* graphics.c */
extern void initFrameBuffer();
extern void Print(const char *str, int x, int y);
extern void DrawFrame();
extern void DrawGameObject(GameObject* obj);

/* initialize.c */
extern void initAll();

#endif