#pragma once

#include "engine_io.h"
#include "renderer.h"
#include "transform.h"
#include "SDL.h"

void handle_input(Input* input, float delta, EntityList* entityList);
void simulate_game(Input* input, float delta, EntityList* entityList);

// Fwd Declatations
