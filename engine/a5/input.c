
#include "allegro5.h"

ALLEGRO_KEYBOARD_STATE keystate;
u16 input_previous;
u16 input_current;

void input_update()
{
	// Record previous state
	input_previous = input_current;

	al_get_keyboard_state(&keystate);
	input_current = 
		  (al_key_down(&keystate, ALLEGRO_KEY_UP) ? DPAD_Up : INPUT_NONE )
		| (al_key_down(&keystate, ALLEGRO_KEY_DOWN) ? DPAD_Down : INPUT_NONE )
		| (al_key_down(&keystate, ALLEGRO_KEY_LEFT) ? DPAD_Left : INPUT_NONE )
		| (al_key_down(&keystate, ALLEGRO_KEY_RIGHT) ? DPAD_Right : INPUT_NONE )
		| (al_key_down(&keystate, ALLEGRO_KEY_X) ? BUTTON_A : INPUT_NONE )
		| (al_key_down(&keystate, ALLEGRO_KEY_Z) ? BUTTON_B : INPUT_NONE )
		| (al_key_down(&keystate, ALLEGRO_KEY_BACKSPACE) ? BUTTON_Select : INPUT_NONE )
		| (al_key_down(&keystate, ALLEGRO_KEY_ENTER) ? BUTTON_Start : INPUT_NONE )
		| (al_key_down(&keystate, ALLEGRO_KEY_S) ? BUTTON_R : INPUT_NONE )
		| (al_key_down(&keystate, ALLEGRO_KEY_A) ? BUTTON_L : INPUT_NONE )
		| (al_key_down(&keystate, ALLEGRO_KEY_TAB) ? BUTTON_SUPER : INPUT_NONE )
		| (al_key_down(&keystate, ALLEGRO_KEY_ESCAPE) ? BUTTON_QUIT : INPUT_NONE );

	// Support joystick map
	if(al_get_num_joysticks() > 0)
	{
		ALLEGRO_JOYSTICK_STATE joystate;
		al_get_joystick_state(al_get_joystick(0), &joystate);
		// TODO Convert joystick state to button
	}

}

u16 input_button_pressed(ControllerInput Button)
{
	return (((input_current & Button) != 0 && (input_previous & Button) == 0) ? Button : 0);
}

u16 input_button_held(ControllerInput Button)
{
	return (input_current & Button);
}

u16 input_button_released(ControllerInput Button)
{
	return (((input_previous & Button) != 0 && (input_current & Button) == 0) ? Button : 0);
}
