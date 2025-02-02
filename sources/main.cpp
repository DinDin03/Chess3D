#include "raylib.h"
#include <cmath>

// Function to linearly interpolate between two points
Vector3 Lerp(Vector3 start, Vector3 end, float t) {
    return {
        start.x + (end.x - start.x) * t,
        start.y + (end.y - start.y) * t,
        start.z + (end.z - start.z) * t
    };
}

// Function to calculate the distance between two vectors
float Vector3Distance(Vector3 a, Vector3 b) {
    return sqrtf((b.x - a.x) * (b.x - a.x) +
                 (b.y - a.y) * (b.y - a.y) +
                 (b.z - a.z) * (b.z - a.z));
}

int main() {
    const int screenWidth = 1440;
    const int screenHeight = 1080;
    InitWindow(screenWidth, screenHeight, "Chess3D");

    // Camera setup
    Camera3D camera = { 0 };
    camera.position = { 15.0f, 7.0f, 3.5f };
    camera.target = { 3.5f, 0.0f, 3.5f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 endPosition = { 3.5f, 7.0f, 14.2f };
    float movementSpeed = 0.015f;
    float threshold = 0.01f;

    SetTargetFPS(144);

    while (!WindowShouldClose()) {
        if (Vector3Distance(camera.position, endPosition) > threshold) {
            camera.position = Lerp(camera.position, endPosition, movementSpeed);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        // Draw Chessboard
        for (int x = 0; x < 8; x++) {
            for (int z = 0; z < 8; z++) {
                Color color = ((x + z) % 2 == 0) ? DARKGRAY : LIGHTGRAY;
                DrawCube({ x + 0.5f, -0.1f, z + 0.5f }, 1.0f, 0.2f, 1.0f, color);
            }
        }

        // Draw Pieces as Cylinders (Temporary Placeholders)
        float pieceHeight = 1.0f;
        float pieceRadius = 0.3f;

        for (int i = 0; i < 8; i++) {
            // White Pawns
            DrawCylinder({ i + 0.5f, 0.5f, 6.5f }, pieceRadius, pieceRadius, pieceHeight, 12, WHITE);
            // Black Pawns
            DrawCylinder({ i + 0.5f, 0.5f, 1.5f }, pieceRadius, pieceRadius, pieceHeight, 12, BLACK);
        }

        // White King & Queen
        DrawCylinder({ 3.5f, 0.5f, 7.5f }, pieceRadius + 0.1f, pieceRadius, pieceHeight + 0.5f, 12, WHITE);
        DrawCylinder({ 4.5f, 0.5f, 7.5f }, pieceRadius + 0.1f, pieceRadius, pieceHeight + 0.5f, 12, WHITE);

        // Black King & Queen
        DrawCylinder({ 3.5f, 0.5f, 0.5f }, pieceRadius + 0.1f, pieceRadius, pieceHeight + 0.5f, 12, BLACK);
        DrawCylinder({ 4.5f, 0.5f, 0.5f }, pieceRadius + 0.1f, pieceRadius, pieceHeight + 0.5f, 12, BLACK);

        EndMode3D();
        DrawText("3D Chess Game", 10, 10, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
