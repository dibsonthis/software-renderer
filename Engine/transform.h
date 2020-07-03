#pragma once

#include "memory_management.h"
#include "math_functions.h"
#include "structures.h"
#include "asset_manager.h"
#include <stdio.h>
#include <malloc.h>

extern Bufferi pixelBuffer;

// Matrix Transformations

Matrix4_f createTranslationMatrix(float pos_x, float pos_y, float pos_z);
Matrix4_f createRotationMatrix(float rot_x, float rot_y, float rot_z);
Matrix4_f createScaleMatrix(float scale_x, float scale_y, float scale_z);
Matrix4_f createLookAtMatrix(Vec3_f cameraPos, Vec3_f cameraTarget, Vec3_f up);
Matrix4_f createTransformationMatrix(float pos_x, float pos_y, float pos_z, float rot_x, float rot_y, float rot_z, float s_x, float s_y, float s_z);
Matrix4_f createProjectionMatrix(float fov, float aspect, float nearZ, float farZ);

void applyMatrix_v(Vertex vertices[], int vertex_count, Matrix4_f matrix);
void applyMatrix_e(Entity* entity, Matrix4_f matrix);
void transformToUnitSpace_v(Vertex vertices[], int vertex_count);
void transformToScreenSpace_v(Vertex vertices[], int vertex_count);
void perspectiveDivide_v(Vertex vertices[], int vertex_count);
void perspectiveDivide_e(Entity* entity);
void resetVertices_e(Entity* entity);
void transformToScreenSpace_e(Entity* entity);
void updateMatrix_e(Entity* entity);