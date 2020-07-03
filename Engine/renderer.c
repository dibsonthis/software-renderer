#include "renderer.h"

// Helper Functions

Color interpolate_rgba(Color col1, Color col2, float percentage)
{
    float r, g, b, a;

    r = linearInterpolate_f(col1.r, col2.r, percentage);
    g = linearInterpolate_f(col1.g, col2.g, percentage);
    b = linearInterpolate_f(col1.b, col2.b, percentage);
    a = linearInterpolate_f(col1.a, col2.a, percentage);

    Color result = { r, g, b, a };
    return result;
}

// Buffer Functions

void clearScreen(Color color)
{
    int rgba = ((color.r & 0x0ff) << 24) | ((color.g & 0x0ff) << 16) | ((color.b & 0x0ff) << 8) | (color.a & 0x0ff);
    for (int x = 0; x <= pixelBuffer.width; x++)
    {
        for (int y = 0; y <= pixelBuffer.height - 1; y++)
        { pixelBuffer.elements[x + y * pixelBuffer.width] = rgba; }
    }
}

void clearZBuffer()
{
    for (int x = 0; x <= zBuffer.width; x++)
    {
        for (int y = 0; y <= zBuffer.height - 1; y++)
        { zBuffer.elements[x + y * zBuffer.width] = Z_FAR; }
    }
}

// Pixel Functions

int getBuffPos(int x, int y)
{
    return x + y * pixelBuffer.width;
}

Color getPixel(int x, int y)
{
    x = clamp_i(x, 0, pixelBuffer.width);
    y = clamp_i(y, 0, pixelBuffer.height - 1);

    int index = getBuffPos(x, y);
    int pixel = pixelBuffer.elements[index];

    int r = ((pixel >> 24) & 0x0ff);
    int g = ((pixel >> 16) & 0x0ff);
    int b = ((pixel >> 8) & 0x0ff); 
    int a = ((pixel) & 0x0ff);      

    Color pixelColor = { r, g, b, a };
    return pixelColor;
}

void drawPixel(int x, int y, float z, Color color)
{
   /* x = clamp_i(x, 0, pixelBuffer.width);
    y = clamp_i(y, 0, pixelBuffer.height - 1);*/

    int rgba = ((color.r & 0x0ff) << 24) | ((color.g & 0x0ff) << 16) | ((color.b & 0x0ff) << 8) | (color.a & 0x0ff);
    int index = getBuffPos(x, y);

    // TODO: Change to RGBA blending

    if (x < 0 || x > pixelBuffer.width - 1)
    {
        return;
    }
    if (y < 0 || y > pixelBuffer.height - 1)
    {
        return;
    }

    if (z >= zBuffer.elements[index])
    {
        pixelBuffer.elements[index] = rgba;
        zBuffer.elements[index] = z;
    }
}

// Drawing Functions

void drawLine_v(Vertex v1, Vertex v2)
{
    float x = v2.vertexCoordinates.x - v1.vertexCoordinates.x;
    float y = v2.vertexCoordinates.y - v1.vertexCoordinates.y;
    float z = v2.vertexCoordinates.z - v1.vertexCoordinates.z;

    float x_offset = x / y;
    float y_offset = y / x;
    float z_offset_x = z / x;
    float z_offset_y = z / y;

    if (x >= 0)
    {
        for (int i = 0; i <= x; i++)
        {
            int x_pos = v1.vertexCoordinates.x + i;
            int y_pos = v1.vertexCoordinates.y + (y_offset * i);
            float z_pos = v1.vertexCoordinates.z + (z_offset_x * i);
            float percentage = (i / x);
            Color interpolated_color = interpolate_rgba(v1.color, v2.color, percentage);
            drawPixel(x_pos, y_pos, z_pos, interpolated_color);
        }
    }
    else
    {
        for (int i = 0; i >= x; i--)
        {
            int x_pos = v1.vertexCoordinates.x + i;
            int y_pos = v1.vertexCoordinates.y + (y_offset * i);
            float z_pos = v1.vertexCoordinates.z + (z_offset_x * i);
            float percentage = (i / x);
            Color interpolated_color = interpolate_rgba(v1.color, v2.color, percentage);
            drawPixel(x_pos, y_pos, z_pos, interpolated_color);
        }
    }
    if (y >= 0)
    {
        for (int i = 0; i <= y; i++)
        {
            int y_pos = v1.vertexCoordinates.y + i;
            int x_pos = v1.vertexCoordinates.x + (x_offset * i);
            float z_pos = v1.vertexCoordinates.z + (z_offset_y * i);
            float percentage = (i / y);
            Color interpolated_color = interpolate_rgba(v1.color, v2.color, percentage);
            drawPixel(x_pos, y_pos, z_pos, interpolated_color);
        }
    }
    else
    {
        for (int i = 0; i >= y; i--)
        {
            int y_pos = v1.vertexCoordinates.y + i;
            int x_pos = v1.vertexCoordinates.x + (x_offset * i);
            float z_pos = v1.vertexCoordinates.z + (z_offset_y * i);
            float percentage = (i / y);
            Color interpolated_color = interpolate_rgba(v1.color, v2.color, percentage);
            drawPixel(x_pos, y_pos, z_pos, interpolated_color);
        }
    }
}

void drawTriangle_v(Vertex v1, Vertex v2, Vertex v3)
{
    drawLine_v(v1, v2);
    drawLine_v(v2, v3);
    drawLine_v(v3, v1);
}

void drawTriangle_t(Triangle t)
{
    drawLine_v(t.v1, t.v2);
    drawLine_v(t.v2, t.v3);
    drawLine_v(t.v3, t.v1);
}

void drawEntity(Entity* entity)
{

    for (int i = 0; i <= entity->vertexData.indexCount - 3; i += 3)
    {
        int v1_index = entity->vertexData.indexBuffer->indices[i];
        int v2_index = entity->vertexData.indexBuffer->indices[i + 1];
        int v3_index = entity->vertexData.indexBuffer->indices[i + 2];

        Vec4_f v1 = entity->vertexData.vertexCoordinatesBuffer->modifiable[v1_index];
        Vec4_f v2 = entity->vertexData.vertexCoordinatesBuffer->modifiable[v2_index];
        Vec4_f v3 = entity->vertexData.vertexCoordinatesBuffer->modifiable[v3_index];

        Vertex vertex_1 = createVertex(entity, v1_index);
        Vertex vertex_2 = createVertex(entity, v2_index);
        Vertex vertex_3 = createVertex(entity, v3_index);

        if (vertex_1.vertexCoordinates.w < 1.0f || vertex_2.vertexCoordinates.w < 1.0f || vertex_3.vertexCoordinates.w < 1.0f)
        {
            return;
        }
        else
        {
            drawLine_v(vertex_1, vertex_2);
            drawLine_v(vertex_2, vertex_3);
            drawLine_v(vertex_3, vertex_1);
        }

    }
}

// Rasterization Functions