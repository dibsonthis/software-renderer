#include "game.h"

float posSpeed = 0.01f;
float rotSpeed = 0.5f;
float sensitivity = 0.1f;
float yaw = -90.0f; float pitch = 0.0f;
Vec3_f cameraPos = { 0.0f, 0.0f, 10.0f };
int elemNumber = 0;

void handle_input(Input* input, float delta, EntityList* entityList)
{

	if (pressed(BUTTON_UP))
	{
		entityList->entities[0]->position.y += -posSpeed * delta;
	}
	if (pressed(BUTTON_DOWN))
	{
		entityList->entities[0]->position.y += posSpeed * delta;
	}
	if (pressed(BUTTON_LEFT))
	{
		entityList->entities[0]->position.x += -posSpeed * delta;
	}
	if (pressed(BUTTON_RIGHT))
	{
		entityList->entities[0]->position.x += posSpeed * delta;
	}
	if (pressed(BUTTON_W))
	{
		//entityList->entities[0]->rotation.x += -rotSpeed * delta;
	}
	if (pressed(BUTTON_S))
	{
		//entityList->entities[0]->rotation.x += rotSpeed * delta;
	}
	if (pressed(BUTTON_A))
	{
		//entityList->entities[0]->rotation.y += -rotSpeed * delta;
	}
	if (pressed(BUTTON_D))
	{
		//entityList->entities[0]->rotation.y += rotSpeed * delta;
	}
	if (pressed(BUTTON_L))
	{
		entityList->entities[0]->position.z += posSpeed * delta;
	}
	if (pressed(BUTTON_K))
	{
		entityList->entities[0]->position.z += -posSpeed * delta;
	}
	if (pressed(BUTTON_X))
	{
		addEntity(entityList, entityList->entities[0]);
		elemNumber += 1;
		printf("%d\n", elemNumber);
	}
}

void simulate_game(Input* input, float delta, EntityList* entityList)
{
	Color background = { 0, 0, 0, 255 };
	clearScreen(background);
	clearZBuffer();

	handle_input(input, delta, entityList);

	Matrix4_f projectionMatrix = createProjectionMatrix(45.0f, 1240.0f / 720.0f, 0.1f, 100.0f);

	float middle_x = pixelBuffer.width / 2, middle_y = pixelBuffer.height / 2;

	Vec3_f cameraTarget = { 0.0f, 0.0f, 0.0f };
	Vec3_f up = { 0.0f, 1.0f, 0.0f };

	float xoffset = input->mouse_x - middle_x;
	float yoffset = input->mouse_y - middle_y;

	SDL_ShowCursor(SDL_FALSE);
	SDL_WarpMouseGlobal(middle_x, middle_y);

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	Vec3_f cameraRotation;
	cameraRotation.x = cos(degToRad(yaw)) * cos(degToRad(pitch));
	cameraRotation.y = sin(degToRad(pitch));
	cameraRotation.z = sin(degToRad(yaw)) * cos(degToRad(pitch));

	Vec3_f cameraFront = normalize_f(cameraRotation);

	Vec3_f cameraDirection = addVectors_f(cameraPos, cameraFront);

	Matrix4_f viewMatrix = createLookAtMatrix(cameraPos, cameraDirection, up);

	Matrix4_f projectionViewMatrix = mat4x4(projectionMatrix, viewMatrix);

	for (int i = 0; i <= entityList->count - 1; i++)
	{
		applyMatrix_e(entityList->entities[i], mat4x4(projectionViewMatrix, entityList->entities[i]->transformationMatrix));
		renderEntity(entityList->entities[i]);
	}

	//for (int i = 0; i <= entityList->count - 1; i++)
	//{
	//	if (entityList->entities[i]->id == 2 || entityList->entities[i]->id == 3)
	//	{
	//		entityList->entities[i]->rotation.y += -rotSpeed * delta * 0.1f;
	//		if (entityList->entities[i]->rotation.y > 360) { entityList->entities[i]->rotation.y = 0; }
	//	}
	//}

	if (pressed(BUTTON_W))
	{
		cameraPos = addVectors_f(cameraPos, scalarMultiply_f(posSpeed * delta, cameraFront));
	}
	if (pressed(BUTTON_A))
	{
		cameraPos = subVectors_f(cameraPos, scalarMultiply_f(posSpeed * delta, normalize_f(cross_f(cameraFront, up))));
	}
	if (pressed(BUTTON_S))
	{
		cameraPos = subVectors_f(cameraPos, scalarMultiply_f(posSpeed * delta, cameraFront));
	}
	if (pressed(BUTTON_D))
	{
		cameraPos = addVectors_f(cameraPos, scalarMultiply_f(posSpeed * delta, normalize_f(cross_f(cameraFront, up))));
	}

}