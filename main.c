#include "raylib.h"

#define BLUE_SQUARE \
    CLITERAL(Color) { 0, 178, 255, 255 }
#define RED_TRIANGLE \
    CLITERAL(Color) { 255, 0, 92, 255 }
#define YELLOW_CIRCLE \
    CLITERAL(Color) { 251, 230, 71, 255 }

//------------------------------------
// Types and Structures Definition
//------------------------------------

typedef enum GameScreen { LOGO,
                          TITLE,
                          GAMEPLAY } GameScreen;

typedef struct Square {
    Vector2 position;
    Vector2 size;
    Rectangle bounds;
} Square;

typedef struct Triangle {
    Vector2 v1;
    Vector2 v2;
    Vector2 v3;
    Rectangle bounds;
} Triangle;

typedef struct Circle {
    Vector2 position;
    int radius;
    Rectangle bounds;
} Circle;

//------------------------------------
// Program main entry point
//------------------------------------

int main() {
    //------------------------------------
    // Initialization
    //------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Shapes Game");

    Texture2D rayLogo = LoadTexture("resources/raylib_logo.png");
    Texture2D cpLogo = LoadTexture("resources/CuriosityPathGames_logo.png");

    GameScreen screen = LOGO;

    int framesCounter = 0;    // General purpose frames counter
    bool gamePaused = false;  // Game paused state toggle

    Square square = {0};
    Triangle triangle = {0};
    Circle circle = {0};

    square.position = (Vector2){screenWidth / 4, screenHeight / 4 + 220};
    square.size = (Vector2){100, 100};

    triangle.v1 = (Vector2){screenWidth / 4 + 50, screenHeight / 4};
    triangle.v2 = (Vector2){screenWidth / 4, screenHeight / 4 + 100};
    triangle.v3 = (Vector2){screenWidth / 4 + 100, screenHeight / 4 + 100};

    circle.position = (Vector2){screenWidth / 4 + 50, screenHeight / 4 + 500};
    circle.radius = 50;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        //------------------------------------
        // Update
        //------------------------------------

        switch (screen) {
            case LOGO: {
                // Update LOGO

                framesCounter++;

                if (framesCounter > 10) {
                    screen = TITLE;  // Change to TITLE screen after 3 seconds
                    framesCounter = 0;
                }

            } break;
            case TITLE: {
                // Update TITLE
                framesCounter++;

                screen = GAMEPLAY;

            } break;
            case GAMEPLAY: {
                // Update GAMEPLAY

                if (IsKeyPressed('P')) gamePaused = !gamePaused;  // Pause button logic

                if (!gamePaused) {
                    // gameplay stuff
                }

            } break;
            default:
                break;
        }

        //------------------------------------
        // Draw
        //------------------------------------
        BeginDrawing();

        ClearBackground(WHITE);

        switch (screen) {
            case LOGO: {
                ClearBackground(BLACK);

                if (framesCounter < 110) {
                    DrawText("Made with", screenWidth / 2 - 120, screenHeight / 2 - 200, 50, WHITE);
                    DrawTexture(rayLogo, screenWidth / 2 - rayLogo.width / 2, screenHeight / 2 - rayLogo.height / 2, WHITE);
                } else {
                    DrawTexture(cpLogo, screenWidth / 2 - cpLogo.width / 2, screenHeight / 2 - cpLogo.height / 2, WHITE);
                }
            } break;
            case TITLE: {
                DrawText("Press ENTER", screenWidth / 2 - 120, screenHeight / 2 - 200, 50, BLACK);
            } break;
            case GAMEPLAY: {
                DrawRectangle(square.position.x, square.position.y, square.size.x, square.size.y, BLUE_SQUARE);  // Draw player bar
                DrawCircle(circle.position.x, circle.position.y, circle.radius, YELLOW_CIRCLE);
                DrawTriangle(triangle.v1, triangle.v2, triangle.v3, RED_TRIANGLE);

                // Grid
                for (int i = 0; i < screenWidth / 100 + 1; i++) {
                    DrawLineV((Vector2){(float)100 * i, 0}, (Vector2){(float)100 * i, (float)screenHeight}, LIGHTGRAY);
                }

                for (int i = 0; i < screenHeight / 100 + 1; i++) {
                    DrawLineV((Vector2){0, (float)100 * i}, (Vector2){(float)screenWidth, (float)100 * i}, LIGHTGRAY);
                }

                DrawText("Hello World!", screenWidth / 2, screenHeight / 2, 24, LIGHTGRAY);

            } break;
            default:
                break;
        }

        EndDrawing();
    }

    //------------------------------------
    // De-Initialization
    //------------------------------------
    CloseWindow();

    return 0;
}