
#include "gba.h"

u16 input_previous = 0;
u16 input_current = 0;

void input_update()
{
    input_previous = input_current;
    input_current = (u16)(~REG_KEYINPUT) & 0x03ff;
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
