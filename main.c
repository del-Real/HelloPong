#include "raylib.h"
#define BGRAY \
    CLITERAL(Color) { 25, 25, 25, 255 }

#define MAX_SCORE 9

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
    int score;
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
    const int screenWidth = 1080;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Hello Pong");

    Texture2D rayLogo = LoadTexture("resources/raylib_logo.png");
    Texture2D cpLogo = LoadTexture("resources/CuriosityPathGames_logo.png");

    GameScreen screen = LOGO;

    int framesCounter = 0;    // General purpose frames counter
    bool gamePaused = false;  // Game paused state toggle
    bool debugMode = false;

    Player player1 = {0};
    Player player2 = {0};
    Ball ball = {0};

    player1.position = (Vector2){screenWidth / 2 - (screenWidth / 2.2f), screenHeight / 2 - 50};
    player1.speed = (Vector2){15.0f, 0.0f};
    player1.size = (Vector2){20, 100};
    player1.score = 0;

    player2.position = (Vector2){screenWidth / 2 + (screenWidth / 2.2f), screenHeight / 2 - 50};
    player2.speed = (Vector2){15.0f, 0.0f};
    player2.size = (Vector2){20, 100};
    player2.score = 0;

    int randX, randY;
    // Generate random values for the range -10 to -5 and -5 to 10
    if (GetRandomValue(0, 1) == 0) {
        randX = GetRandomValue(-10, -5);
    } else {
        randX = GetRandomValue(5, 10);
    }
    if (GetRandomValue(0, 1) == 0) {
        randY = GetRandomValue(-10, -5);
    } else {
        randY = GetRandomValue(5, 10);
    }
    ball.speed = (Vector2){randX, randY};

    ball.radius = 10.0f;
    ball.active = true;
    ball.position = (Vector2){screenWidth / 2, screenHeight / 2};
    ball.speed = (Vector2){randX, randY};

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

                if (framesCounter > 200) {  // default value: 200
                    screen = TITLE;         // Change to TITLE screen after 3 seconds
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

                // Pause game option
                if (IsKeyPressed('P')) {
                    gamePaused = !gamePaused;
                }

                // Reset ball option
                if (IsKeyPressed('R')) {
                    ball.position = (Vector2){screenWidth / 2, screenHeight / 2};
                    int randX, randY;
                    // Generate random values for the range -10 to -5 and -5 to 10
                    if (GetRandomValue(0, 1) == 0) {
                        randX = GetRandomValue(-10, -5);
                    } else {
                        randX = GetRandomValue(5, 10);
                    }
                    if (GetRandomValue(0, 1) == 0) {
                        randY = GetRandomValue(-10, -5);
                    } else {
                        randY = GetRandomValue(5, 10);
                    }
                    ball.speed = (Vector2){randX, randY};
                }

                if (!gamePaused) {
                    // Players movement logic
                    if (IsKeyDown(KEY_W)) player1.position.y -= player1.speed.x;
                    if (IsKeyDown(KEY_S)) player1.position.y += player1.speed.x;

                    if (IsKeyDown(KEY_UP)) player2.position.y -= player2.speed.x;
                    if (IsKeyDown(KEY_DOWN)) player2.position.y += player2.speed.x;

                    // Players movement limits
                    if ((player1.position.y) <= 0) player1.position.y = 0;
                    if ((player1.position.y + player1.size.y) >= screenHeight) player1.position.y = screenHeight - player1.size.y;

                    if ((player2.position.y) <= 0) player2.position.y = 0;
                    if ((player2.position.y + player2.size.y) >= screenHeight) player2.position.y = screenHeight - player2.size.y;

                    // Players box colliders
                    player1.bounds = (Rectangle){player1.position.x, player1.position.y, player1.size.x, player1.size.y};
                    player2.bounds = (Rectangle){player2.position.x, player2.position.y, player2.size.x, player2.size.y};

                    if (ball.active) {
                        // Ball movement logic
                        ball.position.x += ball.speed.x;
                        ball.position.y += ball.speed.y;

                        // Collision logic: ball vs screen-limits
                        if ((ball.position.y - ball.radius) <= 0) ball.speed.y *= -1;             // roof collider
                        if ((ball.position.y + ball.radius) >= screenHeight) ball.speed.y *= -1;  // floor collider

                        // Collision logic: ball vs player
                        if (CheckCollisionCircleRec(ball.position, ball.radius, player1.bounds)) {
                            ball.speed.x *= -1;
                            ball.speed.y = (ball.position.x - (player1.position.x + player1.size.x / 2)) / player1.size.x * randX;
                        }

                        if (CheckCollisionCircleRec(ball.position, ball.radius, player2.bounds)) {
                            ball.speed.x *= -1;
                            ball.speed.y = (ball.position.x - (player2.position.x + player2.size.x / 2)) / player2.size.x * randX;
                        }

                        // Player 1 win condition
                        if ((ball.position.x + ball.radius) >= screenWidth) {
                            ball.speed = (Vector2){0, 0};
                            ball.active = false;
                            player1.score++;
                        }

                        // Player 2 win condition
                        if ((ball.position.x - ball.radius) <= 0) {
                            ball.speed = (Vector2){0, 0};
                            ball.active = false;
                            player2.score++;
                        }

                        if (player1.score > MAX_SCORE || player2.score > MAX_SCORE) {
                            player1.score = 0;
                            player2.score = 0;
                        }

                    } else {
                        ball.position = (Vector2){screenWidth / 2, screenHeight / 2};
                        ball.active = true;

                        int randX, randY;
                        // Generate random values for the range -10 to -5 and -5 to 10
                        if (GetRandomValue(0, 1) == 0) {
                            randX = GetRandomValue(-10, -5);
                        } else {
                            randX = GetRandomValue(5, 10);
                        }
                        if (GetRandomValue(0, 1) == 0) {
                            randY = GetRandomValue(-10, -5);
                        } else {
                            randY = GetRandomValue(5, 10);
                        }
                        ball.speed = (Vector2){randX, randY};
                    }

                    DrawText(TextFormat("%i", player1.score), screenWidth / 2 - 50, 50, 52, WHITE);
                    DrawText(TextFormat("%i", player2.score), screenWidth / 2 + 25, 50, 52, WHITE);
                } else {
                    DrawText("GAME PAUSED", screenWidth / 2 - 160, screenHeight / 2, 52, WHITE);
                }

            } break;
            default:
                break;
        }

        //------------------------------------
        // Draw
        //------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        switch (screen) {
            case LOGO: {
                if (framesCounter < 100) {
                    DrawTexture(cpLogo, screenWidth / 2 - cpLogo.width / 2, screenHeight / 2 - cpLogo.height / 2, WHITE);
                } else {
                    DrawText("Made with", screenWidth / 2 - 120, screenHeight / 2 - 200, 50, WHITE);
                    DrawTexture(rayLogo, screenWidth / 2 - rayLogo.width / 2, screenHeight / 2 - rayLogo.height / 2, WHITE);
                }
            } break;

            case TITLE: {
                // DrawText("Press ENTER", screenWidth / 2 - 120, screenHeight / 2 - 200, 50, BLACK);
            } break;

            case GAMEPLAY: {
                ClearBackground(BGRAY);
                DrawLineV((Vector2){(float)screenWidth / 2, 0}, (Vector2){(float)screenWidth / 2, (float)screenHeight}, LIGHTGRAY);

                DrawRectangle(player1.position.x, player1.position.y, player1.size.x, player1.size.y, RAYWHITE);
                DrawRectangle(player2.position.x, player2.position.y, player2.size.x, player2.size.y, RAYWHITE);

                DrawCircleV(ball.position, ball.radius, WHITE);

                // DEBUG MODE
                if (IsKeyPressed(KEY_TAB)) {
                    debugMode = !debugMode;
                }

                // Ball position
                char xPos[20], yPos[20];
                sprintf(xPos, "%.0f", ball.position.x);
                sprintf(yPos, "%.0f", ball.position.y);

                char ballPos[20];
                strcpy(ballPos, "");
                strcat(ballPos, xPos);
                strcat(ballPos, ", ");
                strcat(ballPos, yPos);

                if (debugMode) {
                    DrawLine(screenWidth / 2, screenHeight / 2, ball.position.x, ball.position.y, GREEN);
                    DrawLine(ball.position.x, ball.position.y, ball.speed.x * screenWidth, ball.speed.y * screenHeight, RED);

                    DrawText("DEBUG MODE", screenWidth / 2 - 115, 10, 32, WHITE);
                    DrawText(ballPos, ball.position.x + 25, ball.position.y + 25, 22, WHITE);
                }

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