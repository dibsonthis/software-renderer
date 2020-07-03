#pragma once

#include "memory_management.h"
#include "structures.h"
#include "math_functions.h"
#include "asset_manager.h"

// Constants

static const float Z_FAR = -1000.0f;
static const float Z_NEAR = 0.0f;

// Buffers

extern Bufferi pixelBuffer;
extern Bufferf zBuffer;

// Helper Functions

Color interpolate_rgba(Color col1, Color col2, float percentage);

// Buffer Functions

void clearScreen(Color color);
void clearZBuffer();

// Pixel Functions

int getBuffPos(int x, int y);
Color getPixel(int x, int y);
void drawPixel(int x, int y, float z, Color color);

// Drawing Functions

void drawLine_v(Vertex v1, Vertex v2);
void drawTriangle_v(Vertex v1, Vertex v2, Vertex v3);
void drawTriangle_t(Triangle t);

void drawEntity(Entity* entity);

// Rasterization Functions