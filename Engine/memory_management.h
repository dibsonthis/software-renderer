#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <uchar.h>

typedef struct Bufferi
{
    uint32_t* elements;
    int width;
    int height;

} Bufferi;

typedef struct Bufferf
{
    float* elements;
    int width;
    int height;

} Bufferf;