#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "raylib.h"
#include <vector>
#include <string>

using namespace std;

// Define Circle struct
struct Circle {
    Vector2 position;
    float radius;
    Color color;
    int id;

    void draw(){
        DrawCircleV(position, radius, color);
    }

    void drawWithAnnotation() {
        draw();
        DrawText(TextFormat("%d", id), position.x - 30, position.y - 30, 15, BLACK);
    }

    int getID(){
        return id;
    }
};

// Define Square struct
struct Square {
    Vector2 position;
    float size;
    Color color;
    int id;

    void draw() {
        Vector2 drawPosition = position;
        drawPosition.x = drawPosition.x - size / 2.0;
        drawPosition.y = drawPosition.y - size / 2.0;
        DrawRectangleV(drawPosition, (Vector2){size, size}, color);
    }

    void drawWithAnnotation() {
        draw();
        DrawText(TextFormat("%d", id), position.x - 30, position.y - 30, 15, BLACK);
    }

     int getID(){
        return id;
    }
};

#endif // GEOMETRY_H
