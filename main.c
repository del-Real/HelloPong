#include "raylib.h"

#define PLAYER_LIFES 5

//------------------------------------
// Types and Structures Definition
//------------------------------------

typedef enum GameScreen {
    LOGO,
    TITLE,
    GAMEPLAY
} GameScreen;

typedef struct Player {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    Rectangle bounds;
    int lifes;
} Player;

// Ball structure
typedef struct Ball {
    Vector2 position;
    Vector2 speed;
    float radius;
    bool active;
} Ball;

//------------------------------------
// Program main entry point
//------------------------------------

int main() {
    //------------------------------------
    // Initialization
    //------------------------------------
    const int screenWidth = 750;
    const int screenHeight = 750;

    InitWindow(screenWidth, screenHeight, "Shapes Game");

    Texture2D rayLogo = LoadTexture("resources/raylib_logo.png");
    Texture2D cpLogo = LoadTexture("resources/CuriosityPathGames_logo.png");

    GameScreen screen = LOGO;

    int framesCounter = 0;    // General purpose frames counter
    bool gamePaused = false;  // Game paused state toggle

    Player player1 = {0};
    Player player2 = {0};
    Ball ball = {0};

    player1.position = (Vector2){screenWidth / 2, screenHeight * 7 / 8};
    player1.speed = (Vector2){8.0f, 0.0f};
    player1.size = (Vector2){100, 24};
    player1.lifes = PLAYER_LIFES;

    player2.position = (Vector2){screenWidth / 2, screenHeight * 5 / 8};
    player2.speed = (Vector2){8.0f, 0.0f};
    player2.size = (Vector2){100, 24};
    player2.lifes = PLAYER_LIFES;

    ball.radius = 10.0f;
    ball.active = false;
    ball.position = (Vector2){player1.position.x + player1.size.x / 2, player1.position.y - ball.radius * 2};
    ball.speed = (Vector2){4.0f, 4.0f};

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

                if (framesCounter > 1) {
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
                DrawLineV((Vector2){(float)100 * i, 0}, (Vector2){(float)100 * i, (float)screenHeight}, LIGHTGRAY);
                DrawRectangle(square.position.x, square.position.y, square.size.x, square.size.y, BLUE_SQUARE);
                DrawRectangle(square.position.x, square.position.y, square.size.x, square.size.y, BLUE_SQUARE);

                DrawCircle(circle.position.x, circle.position.y, circle.radius, YELLOW_CIRCLE);

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