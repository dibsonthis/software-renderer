#pragma once

#include "structures.h"
#include <malloc.h>

typedef struct VertexCoordinatesBuffer
{
    Vec4_f* readOnly;
    Vec4_f* modifiable;

} VertexCoordinatesBuffer;

typedef struct ColorBuffer
{
    Color* readOnly;
    Color* modifiable;

} ColorBuffer;

typedef struct IndexBuffer
{
    unsigned int* indices;

} IndexBuffer;

typedef struct VertexData
{
    VertexCoordinatesBuffer* vertexCoordinatesBuffer;
    IndexBuffer* indexBuffer;
    ColorBuffer* colorBuffer;
    int vertexCount;
    int indexCount;

} VertexData;

typedef struct Entity
{
    VertexData vertexData;
    Matrix4_f transformationMatrix;
    Vec3_f position;
    Vec3_f rotation;
    Vec3_f scale;
    unsigned int id;

} Entity;

typedef struct EntityList
{
    Entity** entities;
    int count;

} EntityList;

VertexCoordinatesBuffer* initVertexCoordinatesBuffer(int count);
void bindVertexCoordinatesBuffer(Entity* entity, float vertexCoordinates[], int count);
void deleteVertexCoordinatesBuffer(VertexCoordinatesBuffer* buffer);

ColorBuffer* initColorBuffer(int count);
void bindColorBuffer(Entity* entity, float colors[], int count);
void deleteColorBuffer(ColorBuffer* buffer);

IndexBuffer* initIndexBuffer(int count);
void bindIndexBuffer(Entity* entity, unsigned int indices[], int count);
void deleteIndexBuffer(IndexBuffer* buffer);

Entity* createEntity();
void deleteEntity(Entity* entity);
void renderEntity(Entity* entity);

Vertex createVertex(Entity* entity, int index);

// Forward Declarations
Matrix4_f createTransformationMatrix(float pos_x, float pos_y, float pos_z,
    float rot_x, float rot_y, float rot_z, float s_x, float s_y, float s_z);
void updateMatrix_e(Entity* entity);
void perspectiveDivide_e(Entity* entity);
void transformToScreenSpace_e(Entity* entity);
void drawEntity(Entity* entity);

EntityList* createEntityList();
void deleteEntityListandContents(EntityList* entityList);
void addEntity(EntityList* entityList, Entity* entity);
void removeEntity(EntityList* entityList, Entity* entity);