#include "transform.h"


Matrix4_f createProjectionMatrix(float fov, float aspect, float nearZ, float farZ)
{
    float FOV = degToRad(fov);
    float tanHalfFOV = tan(FOV / 2.0f);

    Matrix4_f projectionMatrix =
    {
      1 / (aspect * tanHalfFOV), 0.0f, 0.0f, 0.0f,
      0.0f, 1 / tanHalfFOV, 0.0f, 0.0f,
      0.0f, 0.0f, (farZ + nearZ) / (farZ - nearZ), (2 * farZ * nearZ) / (nearZ - farZ),
      0.0f, 0.0f, -1.0f, 0.0f
    };
    return projectionMatrix;
}

Matrix4_f createTranslationMatrix(float pos_x, float pos_y, float pos_z)
{
    Matrix4_f translationMatrix =
    {
      1.0f, 0.0f, 0.0f, pos_x,
      0.0f, 1.0f, 0.0f, pos_y,
      0.0f, 0.0f, 1.0f, pos_z,
      0.0f, 0.0f, 0.0f, 1.0f
    };
    return translationMatrix;
}

Matrix4_f createRotationMatrix(float rot_x, float rot_y, float rot_z)
{
    Matrix4_f rotationMatrix_x =
    {
        1, 0, 0, 0,
        0, cos(-degToRad(rot_x)), -sin(-degToRad(rot_x)), 0,
        0, sin(-degToRad(rot_x)), cos(-degToRad(rot_x)), 0,
        0, 0, 0, 1
    };

    Matrix4_f rotationMatrix_y =
    {
        cos(-degToRad(rot_y)), 0, sin(-degToRad(rot_y)), 0,
        0, 1, 0, 0,
        -sin(-degToRad(rot_y)), 0, cos(-degToRad(rot_y)), 0,
        0, 0, 0, 1
    };

    Matrix4_f rotationMatrix_z =
    {
        cos(-degToRad(rot_z)), -sin(-degToRad(rot_z)), 0, 0,
        sin(-degToRad(rot_z)), cos(-degToRad(rot_z)), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    Matrix4_f rotationMatrix = mat4x4(rotationMatrix_z, mat4x4(rotationMatrix_y, rotationMatrix_x));
    return rotationMatrix;
}

Matrix4_f createScaleMatrix(float scale_x, float scale_y, float scale_z)
{
    Matrix4_f scaleMatrix =
    {
      scale_x, 0.0f, 0.0f, 0.0f,
      0.0f, scale_y, 0.0f, 0.0f,
      0.0f, 0.0f, scale_z, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
    };
    return scaleMatrix;
}

Matrix4_f createLookAtMatrix(Vec3_f cameraPos, Vec3_f cameraTarget, Vec3_f up)
{
    Vec3_f cameraDirection = normalize_f(subVectors_f(cameraPos, cameraTarget));

    Vec3_f cameraRight = normalize_f(cross_f(up, cameraDirection));
    Vec3_f cameraUp = cross_f(cameraDirection, cameraRight);

    Matrix4_f lookAtRotationMatrix =
    {
        cameraRight.x, cameraRight.y, cameraRight.z, 0,
        cameraUp.x, cameraUp.y, cameraUp.z, 0,
        cameraDirection.x, cameraDirection.y, cameraDirection.z, 0,
        0, 0, 0, 1
    };

    Matrix4_f lookAtTranslationMatrix = createTranslationMatrix(-cameraPos.x, -cameraPos.y, -cameraPos.z);

    Matrix4_f lookAtMatrix = mat4x4(lookAtRotationMatrix, lookAtTranslationMatrix);
    return lookAtMatrix;
}

Matrix4_f createTransformationMatrix(float pos_x, float pos_y, float pos_z, 
    float rot_x, float rot_y, float rot_z, float s_x, float s_y, float s_z)
{
    Matrix4_f translationMatrix = createTranslationMatrix(pos_x, pos_y, pos_z);
    Matrix4_f rotationMatrix = createRotationMatrix(rot_x, rot_y, rot_z);
    Matrix4_f scaleMatrix = createScaleMatrix(s_x, s_y, s_z);

    Matrix4_f scale_rotate = mat4x4(rotationMatrix, scaleMatrix); // rotation * scale

    Matrix4_f scale_rotate_translate = mat4x4(translationMatrix, scale_rotate); // translation * rotation * scale

    Matrix4_f transformationMatrix = scale_rotate_translate;

    return transformationMatrix;
}

void applyMatrix_v(Vertex vertices[], int vertex_count, Matrix4_f matrix)
{
    for (int i = 0; i <= vertex_count - 1; i++)
    {
        Vec4_f vec4_converted = mat4_f(vertices[i].vertexCoordinates, matrix);
        vertices[i].vertexCoordinates = vec4_converted;
    }
}

void applyMatrix_e(Entity* entity, Matrix4_f matrix)
{
    for (int i = 0; i <= entity->vertexData.vertexCount - 1; i++)
    {
        entity->vertexData.vertexCoordinatesBuffer->modifiable[i] = mat4_f(entity->vertexData.vertexCoordinatesBuffer->readOnly[i], matrix);
    }
}

void transformToUnitSpace_v(Vertex vertices[], int vertex_count)
{
    for (int i = 0; i <= vertex_count - 1; i ++)
    {
        vertices[i].vertexCoordinates.x = (vertices[i].vertexCoordinates.x / pixelBuffer.width / 0.5f) - 1.0f;
        vertices[i].vertexCoordinates.y = (vertices[i].vertexCoordinates.y / pixelBuffer.height / 0.5f) - 1.0f;
        vertices[i].vertexCoordinates.z = (vertices[i].vertexCoordinates.z / 100.0f / 0.5f) - 1.0f;
    }
}

void transformToScreenSpace_v(Vertex vertices[], int vertex_count)
{
    for (int i = 0; i <= vertex_count - 1; i++)
    {
        vertices[i].vertexCoordinates.x = (vertices[i].vertexCoordinates.x + 1.0f) * 0.5f * pixelBuffer.width;
        vertices[i].vertexCoordinates.y = (vertices[i].vertexCoordinates.y + 1.0f) * 0.5f * pixelBuffer.height;
        vertices[i].vertexCoordinates.z = (vertices[i].vertexCoordinates.z + 1.0f) * 0.5f * 100.0f;
    }
}

void perspectiveDivide_v(Vertex vertices[], int vertex_count)
{
    for (int i = 0; i <= vertex_count - 1; i++)
    {
        vertices[i].vertexCoordinates.x = vertices[i].vertexCoordinates.x / vertices[i].vertexCoordinates.w;
        vertices[i].vertexCoordinates.y = vertices[i].vertexCoordinates.y / vertices[i].vertexCoordinates.w;
    }
}

void perspectiveDivide_e(Entity* entity)
{
    for (int i = 0; i <= entity->vertexData.vertexCount - 1; i++)
    {
        entity->vertexData.vertexCoordinatesBuffer->modifiable[i].x = entity->vertexData.vertexCoordinatesBuffer->modifiable[i].x / entity->vertexData.vertexCoordinatesBuffer->modifiable[i].w;
        entity->vertexData.vertexCoordinatesBuffer->modifiable[i].y = entity->vertexData.vertexCoordinatesBuffer->modifiable[i].y / entity->vertexData.vertexCoordinatesBuffer->modifiable[i].w;
        entity->vertexData.vertexCoordinatesBuffer->modifiable[i].z = entity->vertexData.vertexCoordinatesBuffer->modifiable[i].z / entity->vertexData.vertexCoordinatesBuffer->modifiable[i].w;
    }
}

void resetVertices_e(Entity* entity)
{
    for (int i = 0; i <= entity->vertexData.vertexCount - 1; i++)
    {
        entity->vertexData.vertexCoordinatesBuffer->modifiable[i] = entity->vertexData.vertexCoordinatesBuffer->readOnly[i];
    }
}

void transformToScreenSpace_e(Entity* entity)
{
    for (int i = 0; i <= entity->vertexData.vertexCount - 1; i++)
    {
        entity->vertexData.vertexCoordinatesBuffer->modifiable[i].x = (int)((entity->vertexData.vertexCoordinatesBuffer->modifiable[i].x + 1.0f) * 0.5f * pixelBuffer.width);
        entity->vertexData.vertexCoordinatesBuffer->modifiable[i].y = (int)((entity->vertexData.vertexCoordinatesBuffer->modifiable[i].y + 1.0f) * 0.5f * pixelBuffer.height);
        entity->vertexData.vertexCoordinatesBuffer->modifiable[i].z = (int)((entity->vertexData.vertexCoordinatesBuffer->modifiable[i].z + 1.0f) * 0.5f * 100.0f);
    }
}

void updateMatrix_e(Entity* entity)
{
    entity->transformationMatrix = createTransformationMatrix(entity->position.x, entity->position.y, entity->position.z,
        entity->rotation.x, entity->rotation.y, entity->rotation.z, entity->scale.x, entity->scale.y, entity->scale.z);
}