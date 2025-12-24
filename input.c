#include <stdio.h>
#include "scroll.h"
#include "sense.h"

pi_joystick_t *joystick = NULL;

void open_input(void) {
    joystick = getJoystickDevice();
    if (joystick == NULL) {
        printf("Could not open joystick device.\n");
    }
}

void close_input(void) {
    if (joystick != NULL) {
        freeJoystick(joystick);
        joystick = NULL;
    }
}

void check_input(void (*callback)(unsigned int), int delay) {
    if (joystick == NULL) {
        return;
    }
    pollJoystick(joystick, callback, delay);
}
