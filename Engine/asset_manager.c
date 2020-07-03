#include "asset_manager.h"

VertexCoordinatesBuffer* initVertexCoordinatesBuffer(int count)
{
    VertexCoordinatesBuffer* buffer;
    buffer = malloc(sizeof(VertexCoordinatesBuffer));

    buffer->readOnly = malloc(count * sizeof(Vec4_f));
    buffer->modifiable = malloc(count * sizeof(Vec4_f));

    int offset = 3;
    for (int i = 0; i <= count - 1; i++)
    {
        int index = i * offset;

        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        Vec4_f vector = { x, y, z, 1.0f };
        buffer->readOnly[i] = vector;
        buffer->modifiable[i] = vector;
    }

    return buffer;
}

void bindVertexCoordinatesBuffer(Entity* entity, float vertexCoordinates[], int count)
{
    deleteVertexCoordinatesBuffer(entity->vertexData.vertexCoordinatesBuffer);

    VertexCoordinatesBuffer* buffer;
    buffer = malloc(sizeof(VertexCoordinatesBuffer));

    buffer->readOnly = malloc(count * sizeof(Vec4_f));
    buffer->modifiable = malloc(count * sizeof(Vec4_f));

    int offset = 3;
    for (int i = 0; i <= count - 1; i++)
    {
        int index = i * offset;

        float x = vertexCoordinates[index];
        float y = vertexCoordinates[index + 1];
        float z = vertexCoordinates[index + 2];

        Vec4_f vector = { x, y, z, 1.0f };
        buffer->readOnly[i] = vector;
        buffer->modifiable[i] = vector;
    }

    entity->vertexData.vertexCoordinatesBuffer = buffer;
    entity->vertexData.vertexCount = count;

}

void deleteVertexCoordinatesBuffer(VertexCoordinatesBuffer* buffer)
{
    free(buffer->modifiable);
    free(buffer->readOnly);
    free(buffer);
}

ColorBuffer* initColorBuffer(int count)
{
    ColorBuffer* buffer;
    buffer = malloc(sizeof(ColorBuffer));

    buffer->readOnly = malloc(count * sizeof(Color));
    buffer->modifiable = malloc(count * sizeof(Color));

    int offset = 4;
    for (int i = 0; i <= count - 1; i++)
    {
        int index = i * offset;

        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 255.0f;

        Color vector = { r, g, b, a };
        buffer->readOnly[i] = vector;
        buffer->modifiable[i] = vector;
    }

    return buffer;
}

void bindColorBuffer(Entity* entity,  float colors[], int count)
{
    deleteColorBuffer(entity->vertexData.colorBuffer);

    ColorBuffer* buffer;
    buffer = malloc(sizeof(ColorBuffer));

    buffer->readOnly = malloc(count * sizeof(Color));
    buffer->modifiable = malloc(count * sizeof(Color));

    int offset = 4;
    for (int i = 0; i <= count - 1; i++)
    {
        int index = i * offset;

        float r = colors[index];
        float g = colors[index + 1];
        float b = colors[index + 2];
        float a = colors[index + 3];

        Color vector = { r, g, b, a };
        buffer->readOnly[i] = vector;
        buffer->modifiable[i] = vector;
    }

    entity->vertexData.colorBuffer = buffer;
}

void deleteColorBuffer(ColorBuffer* buffer)
{
    free(buffer->modifiable);
    free(buffer->readOnly);
    free(buffer);
}

IndexBuffer* initIndexBuffer(int count)
{
    IndexBuffer* buffer;
    buffer = malloc(sizeof(IndexBuffer));

    buffer->indices = malloc(count * sizeof(float));

    for (int i = 0; i <= count - 1; i++)
    {
        buffer->indices[i] = 0;
    }

    return buffer;
}

void bindIndexBuffer(Entity* entity, unsigned int indices[], int count)
{
    deleteIndexBuffer(entity->vertexData.indexBuffer);

    IndexBuffer* buffer;
    buffer = malloc(sizeof(IndexBuffer));

    buffer->indices = malloc(count * sizeof(float));

    for (int i = 0; i <= count - 1; i++)
    {
        buffer->indices[i] = indices[i];
    }

    entity->vertexData.indexBuffer = buffer;
    entity->vertexData.indexCount = count;
}

void deleteIndexBuffer(IndexBuffer* buffer)
{
    free(buffer->indices);
    free(buffer);
}

//////

Entity* createEntity()
{
    Entity* entity = malloc(sizeof(Entity));
    entity->vertexData.vertexCoordinatesBuffer = initVertexCoordinatesBuffer(1);
    entity->vertexData.colorBuffer = initColorBuffer(1);
    entity->vertexData.indexBuffer = initIndexBuffer(1);
    entity->vertexData.vertexCount = 1;
    entity->vertexData.indexCount = 1;

    entity->position = (Vec3_f){ 0.0f, 0.0f, -10.0f };
    entity->rotation = (Vec3_f){ 0.0f, 0.0f, 0.0f };
    entity->scale = (Vec3_f){ 1.0f, 1.0f, 1.0f };
    entity->transformationMatrix = createTransformationMatrix(entity->position.x, entity->position.y, entity->position.z,
        entity->rotation.x, entity->rotation.y, entity->rotation.z, entity->scale.x, entity->scale.y, entity->scale.z);

    entity->id = 0;

    return entity;
}

void deleteEntity(Entity* entity)
{
    free(entity->vertexData.vertexCoordinatesBuffer);
    free(entity->vertexData.indexBuffer);
    free(entity->vertexData.colorBuffer);
    free(entity);
}

void renderEntity(Entity* entity)
{
    updateMatrix_e(entity);
    // cull
    perspectiveDivide_e(entity);
    transformToScreenSpace_e(entity);
    drawEntity(entity);
}

Vertex createVertex(Entity* entity, int index)
{
    Vertex vertex;
    vertex.vertexCoordinates = entity->vertexData.vertexCoordinatesBuffer->modifiable[index];
    //vertex.textureCoordinates = entity->vertexData.textureCoordinatesBuffer->modifiable[index];
    //vertex.normalCoordinates = entity->vertexData.normalCoordinatesBuffer->modifiable[index];
    vertex.color = entity->vertexData.colorBuffer->modifiable[index];

    return vertex;
}

EntityList* createEntityList()
{
    EntityList* entityList = malloc(sizeof(EntityList));
    entityList->count = 0;
    entityList->entities = malloc(0);
    return entityList;
}

void deleteEntityListandContents(EntityList* entityList)
{
    for (int i = 0; i <= entityList->count - 1; i++)
    {
        deleteEntity(entityList->entities[i]);
    }
    free(entityList->entities);
    free(entityList);
}

void addEntity(EntityList* entityList, Entity* entity)
{
    entityList->count += 1;
    Entity** newEntities = malloc(entityList->count * sizeof(Entity*));
    for (int i = 0; i <= entityList->count - 1; i++)
    {
        newEntities[i] = entityList->entities[i];
    }
    newEntities[entityList->count - 1] = entity;
    free(entityList->entities);
    entityList->entities = newEntities;
}

// TODO - FIX
void removeEntity(EntityList* entityList, Entity* entity)
{
    entityList->count -= 1;
    Entity** newEntities = malloc((entityList->count) * sizeof(Entity*));
    int p = 0;
    for (int i = 0; i <= entityList->count - 1; i++)
    {
        if (entityList->entities[i] != entity)
        {
            newEntities[p] = entityList->entities[i];
        }
        p++;
    }
    free(entityList->entities);
    entityList->entities = newEntities;
    entityList->count -= 1;
}
