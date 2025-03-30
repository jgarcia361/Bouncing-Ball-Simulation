#include "raylib.h"
#include <string>
#include <ctime>

int main() {
    int screenWidth = 1000;
    int screenHeight = 800;
    SetRandomSeed((unsigned int)time(NULL)); // Setting seed to randomize velocity values

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN); // Allows the window to be resized during runtime
    InitWindow(screenWidth, screenHeight, "Bouncing Ball Simulation"); // Creating window

    const int FPS30 = 30; // 30 FPS cap
    const int FPS60 = 60; // 60 FPS cap
    const int FPS144 = 144; // 144 FPS cap
    const int FPSUnlimited = 0; // 0 FPS cap (unlimited frames)
    int currentTargetFPS = FPS60; // Default FPS cap set to 60

    SetTargetFPS(currentTargetFPS); // Setting FPS cap

    int minVelocity = -500; // Min velocity for randomized velocity range
    int maxVelocity = 500; // Max velocity for randomized velocity range
    Vector2 ballPosition = { screenWidth / 2.0f, screenHeight / 2.0f };
    Vector2 ballVelocity = { (float)GetRandomValue(minVelocity, maxVelocity), (float)GetRandomValue(minVelocity, maxVelocity) };
    const float ballRadius = 10.0f;
    const float ballDiameter = ballRadius * 2;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE)) { // Pressing "1" caps the FPS to 30
            currentTargetFPS = FPS30;
            SetTargetFPS(currentTargetFPS);
        }
        else if (IsKeyPressed(KEY_TWO)) { // Pressing "2" caps the FPS to 60
            currentTargetFPS = FPS60;
            SetTargetFPS(currentTargetFPS);
        }
        else if (IsKeyPressed(KEY_THREE)) { // Pressing "3" caps the FPS to 144
            currentTargetFPS = FPS144;
            SetTargetFPS(currentTargetFPS);
        }
        else if (IsKeyPressed(KEY_FOUR)) { // Pressing "4" uncaps the FPS (unlimited frames)
            currentTargetFPS = FPSUnlimited;
            SetTargetFPS(currentTargetFPS);
        }
        else if (IsKeyPressed(KEY_UP)) { // Pressing "UP" increases FPS cap by 5
            currentTargetFPS += 5;
            SetTargetFPS(currentTargetFPS);
        }
        else if (IsKeyPressed(KEY_DOWN)) { // Pressing "DOWN" decreases FPS cap by 5 (lowest is 5 FPS cap)
            currentTargetFPS -= 5;
            if (currentTargetFPS < 5)
                currentTargetFPS = 10;
            SetTargetFPS(currentTargetFPS);
        }

        float deltaTime = GetFrameTime(); // Frame independent timing
        if (deltaTime > 0.1f) {
            deltaTime = 0.1f;
        }
        screenWidth = GetScreenWidth(); // Updating screen width
        screenHeight = GetScreenHeight(); // Updating screen height

        ballPosition.x += ballVelocity.x * deltaTime; // Updating the ball's x position 
        ballPosition.y += ballVelocity.y * deltaTime; // Updating the ball's y position

        // Handles ball collision with the sides of the window (left and right sides) 
        if ((ballPosition.x + ballRadius < ballDiameter && ballVelocity.x < 0) ||
            (ballPosition.x + ballRadius > screenWidth && ballVelocity.x > 0)) {
            ballVelocity.x *= -1;
        }
        // Handles ball collision with the top and bottom of the window
        if ((ballPosition.y + ballRadius < ballDiameter && ballVelocity.y < 0) ||
            (ballPosition.y + ballRadius > screenHeight && ballVelocity.y > 0)) {
            ballVelocity.y *= -1;
        }

        // ==========Beginning of drawing scene==========
        BeginDrawing();
        ClearBackground(BLACK);

        // Drawing circle on the screen
        DrawCircleV(ballPosition, ballRadius, WHITE);

        // Displaying debug information
        DrawText(TextFormat("Current Target FPS: %d", currentTargetFPS), 20, 20, 18, GREEN);
        DrawText(TextFormat("FPS: %d", GetFPS()), 20, 40, 18, GREEN);
        DrawText(TextFormat("Frame Time: %.3f ms", GetFrameTime() * 1000), 20, 60, 18, GREEN);
        DrawText(TextFormat("Elapsed Time: %.3f sec", GetTime()), 20, 80, 18, GREEN);

        if (deltaTime >= 0.1f) {
            DrawText("Large delta time detected!", 20, 100, 18, RED);
        }

        EndDrawing();
        // ==========End of drawing scene==========
    }

    CloseWindow();
    return 0;
}
