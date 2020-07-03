#include "event_handling.h"

void handle_window_events()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) exit(0);
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				input.buttons[BUTTON_UP].is_down = 1;
				break;
			case SDLK_DOWN:
				input.buttons[BUTTON_DOWN].is_down = 1;
				break;
			case SDLK_LEFT:
				input.buttons[BUTTON_LEFT].is_down = 1;
				break;
			case SDLK_RIGHT:
				input.buttons[BUTTON_RIGHT].is_down = 1;
				break;
			case SDLK_a:
				input.buttons[BUTTON_A].is_down = 1;
				break;
			case SDLK_b:
				input.buttons[BUTTON_B].is_down = 1;
				break;
			case SDLK_c:
				input.buttons[BUTTON_C].is_down = 1;
				break;
			case SDLK_d:
				input.buttons[BUTTON_D].is_down = 1;
				break;
			case SDLK_e:
				input.buttons[BUTTON_E].is_down = 1;
				break;
			case SDLK_f:
				input.buttons[BUTTON_F].is_down = 1;
				break;
			case SDLK_g:
				input.buttons[BUTTON_G].is_down = 1;
				break;
			case SDLK_h:
				input.buttons[BUTTON_H].is_down = 1;
				break;
			case SDLK_i:
				input.buttons[BUTTON_I].is_down = 1;
				break;
			case SDLK_j:
				input.buttons[BUTTON_J].is_down = 1;
				break;
			case SDLK_k:
				input.buttons[BUTTON_K].is_down = 1;
				break;
			case SDLK_l:
				input.buttons[BUTTON_L].is_down = 1;
				break;
			case SDLK_m:
				input.buttons[BUTTON_M].is_down = 1;
				break;
			case SDLK_n:
				input.buttons[BUTTON_N].is_down = 1;
				break;
			case SDLK_o:
				input.buttons[BUTTON_O].is_down = 1;
				break;
			case SDLK_p:
				input.buttons[BUTTON_P].is_down = 1;
				break;
			case SDLK_q:
				input.buttons[BUTTON_Q].is_down = 1;
				break;
			case SDLK_r:
				input.buttons[BUTTON_R].is_down = 1;
				break;
			case SDLK_s:
				input.buttons[BUTTON_S].is_down = 1;
				break;
			case SDLK_t:
				input.buttons[BUTTON_T].is_down = 1;
				break;
			case SDLK_u:
				input.buttons[BUTTON_U].is_down = 1;
				break;
			case SDLK_v:
				input.buttons[BUTTON_V].is_down = 1;
				break;
			case SDLK_w:
				input.buttons[BUTTON_W].is_down = 1;
				break;
			case SDLK_x:
				input.buttons[BUTTON_X].is_down = 1;
				break;
			case SDLK_y:
				input.buttons[BUTTON_Y].is_down = 1;
				break;
			case SDLK_z:
				input.buttons[BUTTON_Z].is_down = 1;
				break;
			case SDLK_ESCAPE:
				running = 0;
				exit(0);
			}

		}
		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				input.buttons[BUTTON_UP].is_down = 0;
				break;
			case SDLK_DOWN:
				input.buttons[BUTTON_DOWN].is_down = 0;
				break;
			case SDLK_LEFT:
				input.buttons[BUTTON_LEFT].is_down = 0;
				break;
			case SDLK_RIGHT:
				input.buttons[BUTTON_RIGHT].is_down = 0;
				break;
			case SDLK_a:
				input.buttons[BUTTON_A].is_down = 0;
				break;
			case SDLK_b:
				input.buttons[BUTTON_B].is_down = 0;
				break;
			case SDLK_c:
				input.buttons[BUTTON_C].is_down = 0;
				break;
			case SDLK_d:
				input.buttons[BUTTON_D].is_down = 0;
				break;
			case SDLK_e:
				input.buttons[BUTTON_E].is_down = 0;
				break;
			case SDLK_f:
				input.buttons[BUTTON_F].is_down = 0;
				break;
			case SDLK_g:
				input.buttons[BUTTON_G].is_down = 0;
				break;
			case SDLK_h:
				input.buttons[BUTTON_H].is_down = 0;
				break;
			case SDLK_i:
				input.buttons[BUTTON_I].is_down = 0;
				break;
			case SDLK_j:
				input.buttons[BUTTON_J].is_down = 0;
				break;
			case SDLK_k:
				input.buttons[BUTTON_K].is_down = 0;
				break;
			case SDLK_l:
				input.buttons[BUTTON_L].is_down = 0;
				break;
			case SDLK_m:
				input.buttons[BUTTON_M].is_down = 0;
				break;
			case SDLK_n:
				input.buttons[BUTTON_N].is_down = 0;
				break;
			case SDLK_o:
				input.buttons[BUTTON_O].is_down = 0;
				break;
			case SDLK_p:
				input.buttons[BUTTON_P].is_down = 0;
				break;
			case SDLK_q:
				input.buttons[BUTTON_Q].is_down = 0;
				break;
			case SDLK_r:
				input.buttons[BUTTON_R].is_down = 0;
				break;
			case SDLK_s:
				input.buttons[BUTTON_S].is_down = 0;
				break;
			case SDLK_t:
				input.buttons[BUTTON_T].is_down = 0;
				break;
			case SDLK_u:
				input.buttons[BUTTON_U].is_down = 0;
				break;
			case SDLK_v:
				input.buttons[BUTTON_V].is_down = 0;
				break;
			case SDLK_w:
				input.buttons[BUTTON_W].is_down = 0;
				break;
			case SDLK_x:
				input.buttons[BUTTON_X].is_down = 0;
				break;
			case SDLK_y:
				input.buttons[BUTTON_Y].is_down = 0;
				break;
			case SDLK_z:
				input.buttons[BUTTON_Z].is_down = 0;
				break;
			}

		}
	}
}