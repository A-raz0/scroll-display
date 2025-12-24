#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include "scroll.h"

int running = 1;

int vx = 0;
int vy = 0;

float xf = 0.0f;
float yf = 0.0f;

char letters[2] = { 'A', 'R' };
int letter_index = 0;

int clamp(int v, int lo, int hi) {    //to keep within range
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

void handler(unsigned int code) {
    if (code == KEY_LEFT) {
        vy = clamp(vy - 1, -10, 10);
    } else if (code == KEY_RIGHT) {
        vy = clamp(vy + 1, -10, 10);
    } else if (code == KEY_UP) {
        vx = clamp(vx - 1, -10, 10);
    } else if (code == KEY_DOWN) {
        vx = clamp(vx + 1, -10, 10);
    } else if (code == KEY_ENTER) {
        letter_index++;
        if (letter_index >= 2) {
            running = 0;
        }
    }
}

int main(void) {
    if (letters[0] == letters[1]) {
        letters[1] = '3';
    }

    open_display();
    open_input();

    display_letter(letters[letter_index], 0, 0);

    const float dt = 0.05f;
    while (running) {
        check_input(handler, 10);

        xf += vx * dt;
        yf += vy * dt;

        if (xf >= 8.0f) xf -= 8.0f;
        if (xf <  0.0f) xf += 8.0f;
        if (yf >= 8.0f) yf -= 8.0f;
        if (yf <  0.0f) yf += 8.0f;

        display_letter(letters[letter_index], (int)xf, (int)yf);

        usleep((useconds_t)(dt * 1000000.0f));
    }

    clear_display();
    close_input();
    close_display();
    return 0;
}
