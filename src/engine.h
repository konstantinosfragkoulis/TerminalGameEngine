#ifndef ENGINE_H
#define ENGINE_H

typedef int bool;
#define true 1
#define false 0

/* Game Object */
/* Sprite Renderer */
typedef struct {
    int color;
    char **sprite;
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

/* inputManager.c */
extern void enableRawMode();
extern void disableRawMode();
extern char GetInput();

/* utils.c */
extern int cstrlen(const char *str);

/* graphics.c */
extern void initFrameBuffer();
extern void Print(const char *str, int x, int y);
extern void DrawFrame();
extern void DrawGameObject(GameObject* obj);

/* initialize.c */
extern void initAll();

#endif