#include "SDL.h"
#include "event_handling.h"
#include "memory_management.h"
#include "renderer.h"
#include "game.h"
#include "asset_manager.h"

char running = 1;

Bufferi pixelBuffer;
Bufferf zBuffer;

Input input = { 0 };

int main(int argc, char* argv[])
{
	int WIDTH = 1240;
	int HEIGHT = 720;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Something", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_SetWindowResizable(window, 1);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture* screen_texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
		WIDTH, HEIGHT);
	pixelBuffer.elements = malloc(WIDTH * HEIGHT * sizeof(uint32_t));
	pixelBuffer.height = HEIGHT;
	pixelBuffer.width = WIDTH;
	zBuffer.elements = malloc(WIDTH * HEIGHT * sizeof(uint32_t));
	zBuffer.height = HEIGHT;
	zBuffer.width = WIDTH;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0.16f;

	int cube_indices[] =
	{
		// front
		0, 1, 2,
		2, 3, 0,
		// back
		4, 5, 6,
		6, 7, 4,
		// right
		1, 5, 6,
		6, 2, 1,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	float cube_vertices[] =
	{
		-1.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,
		 0.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,

		-1.0f, -1.0f,  -1.0f,
		 0.0f, -1.0f,  -1.0f,
		 0.0f,  0.0f,  -1.0f,
		-1.0f,  0.0f,  -1.0f
	};

	float cube_colors[] =
	{
		255, 0, 0, 255,
		0, 255, 0, 255,
		0, 0, 255, 255,
		255, 255, 255, 255,

		255, 255, 0, 255,
		0, 255, 255, 255,
		255, 0, 255, 255,
		255, 0, 0, 255
	};

	Entity* entity = createEntity();
	entity->id = 1;
	bindVertexCoordinatesBuffer(entity, cube_vertices, 8);
	bindIndexBuffer(entity, cube_indices, 36);
	bindColorBuffer(entity, cube_colors, 8);

	Entity* entity_2 = createEntity();
	entity_2->id = 2;
	bindVertexCoordinatesBuffer(entity_2, cube_vertices, 8);
	bindIndexBuffer(entity_2, cube_indices, 36);
	bindColorBuffer(entity_2, cube_colors, 8);
	entity_2->position = (Vec3_f){ 10.0f, 0.5f, -10.0f };
	entity_2->rotation = (Vec3_f){ 0.0f, 45.0f, -45.0f };
	updateMatrix_e(entity_2);

	Entity* entity_3 = createEntity();
	entity_3->id = 3;
	bindVertexCoordinatesBuffer(entity_3, cube_vertices, 8);
	bindIndexBuffer(entity_3, cube_indices, 36);
	bindColorBuffer(entity_3, cube_colors, 8);
	entity_3->position = (Vec3_f){ -10.0f, -0.5f, -10.0f };
	entity_3->rotation = (Vec3_f){ 45.0f, 90.0f, 45.0f };
	entity_3->scale = (Vec3_f){ 1.2f, 1.2f, 1.2f };
	updateMatrix_e(entity_3);

	Entity* entity_4 = createEntity();
	entity_4->id = 4;
	bindVertexCoordinatesBuffer(entity_4, cube_vertices, 8);
	bindIndexBuffer(entity_4, cube_indices, 36);
	bindColorBuffer(entity_4, cube_colors, 8);
	entity_4->position = (Vec3_f){ -20.0f, -1.0f, -10.0f };
	entity_4->rotation = (Vec3_f){ 45.0f, 90.0f, 45.0f };
	entity_4->scale = (Vec3_f){ 1.0f, 1.0f, 0.2f };
	updateMatrix_e(entity_4);

	EntityList* entityList = createEntityList();
	addEntity(entityList, entity);
	addEntity(entityList, entity_2);
	addEntity(entityList, entity_3);
	addEntity(entityList, entity_4);

	while (running)
	{
		LAST = NOW;

		handle_window_events();

		int mouseX, mouseY;
		SDL_GetGlobalMouseState(&mouseX, &mouseY);
		input.mouse_x = mouseX;
		input.mouse_y = mouseY;

		simulate_game(&input, deltaTime, entityList);

		SDL_UpdateTexture(screen_texture, NULL, pixelBuffer.elements, pixelBuffer.width * sizeof(uint32_t));
		SDL_RenderCopy(renderer, screen_texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
	}

	return 0;
}