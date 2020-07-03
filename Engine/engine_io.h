#pragma once

#include <stdint.h>
#include <uchar.h>

typedef struct Button
{
	char32_t is_down;
	char32_t changed;

} Button;

enum Keys {

	BUTTON_LEFT, BUTTON_RIGHT, BUTTON_UP, BUTTON_DOWN,
	BUTTON_SPACE, BUTTON_PLUS, BUTTON_MINUS, BUTTON_SHIFT,
	BUTTON_A, BUTTON_B, BUTTON_C, BUTTON_D, BUTTON_E,
	BUTTON_F, BUTTON_G, BUTTON_H, BUTTON_I, BUTTON_J,
	BUTTON_K, BUTTON_L, BUTTON_M, BUTTON_N, BUTTON_O,
	BUTTON_P, BUTTON_Q, BUTTON_R, BUTTON_S, BUTTON_T,
	BUTTON_U, BUTTON_V, BUTTON_W, BUTTON_X, BUTTON_Y,
	BUTTON_Z,

	BUTTON_COUNT

};

typedef struct Input
{
	int mouse_x;
	int mouse_y;

	Button buttons[BUTTON_COUNT];

} Input;

#define pressed(b) (input->buttons[b].is_down)