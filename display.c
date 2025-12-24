#include <stdio.h>
#include <unistd.h>
#include "scroll.h"
#include "sense.h"

#define WHITE 0xFFFF
#define BLACK 0x0000

/* global framebuffer like in your examples */
pi_framebuffer_t *fb = NULL;

/* simple safe wrap to 0..7 */
int wrap8(int v) {
    int m = v % 8;
    if (m < 0) {
        m += 8;
    }
    return m;
}

void open_display(void) {
    if (fb == NULL) {
        fb = getFrameBuffer();
        if (fb) {
            clearFrameBuffer(fb, BLACK);
        } else {
            fprintf(stderr, "ERROR: getFrameBuffer() failed\n");
        }
    }
}

void close_display(void) {
    if (fb) {
        clearFrameBuffer(fb, BLACK);
        sleep(1);
        freeFrameBuffer(fb);
        fb = NULL;
    }
}

/*
  Draws letters 'A' and 'R' in the same pixel pattern
  you used in your monogram project. The letter is shifted
  by (xOffset, yOffset). Each pixel is wrapped into 0..7.
*/
void display_letter(char letter, int xOffset, int yOffset) {
    sense_fb_bitmap_t *bm;
    int x, y;

    if (fb == NULL) {
        fprintf(stderr, "Tried to draw to a non-existent frame buffer!\n");
        return;
    }

    bm = fb->bitmap;
    if (bm == NULL) {
        fprintf(stderr, "Failed to get bitmap\n");
        return;
    }

    /* erase previous frame */
    clearFrameBuffer(fb, BLACK);

    if (letter == 'A') {
        /* --- Your 'A' pattern, with wrapping + offsets --- */

        /* Top of A */
        x = wrap8(3 + xOffset); y = wrap8(0 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(4 + xOffset); y = wrap8(0 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(5 + xOffset); y = wrap8(0 + yOffset); bm->pixel[x][y] = WHITE;

        /* Diagonals */
        x = wrap8(2 + xOffset); y = wrap8(1 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(6 + xOffset); y = wrap8(1 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(1 + xOffset); y = wrap8(2 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(7 + xOffset); y = wrap8(2 + yOffset); bm->pixel[x][y] = WHITE;

        /* Middle bar */
        x = wrap8(2 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(3 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(4 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(5 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(6 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;

        /* Legs */
        x = wrap8(1 + xOffset); y = wrap8(4 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(7 + xOffset); y = wrap8(4 + yOffset); bm->pixel[x][y] = WHITE;

        x = wrap8(1 + xOffset); y = wrap8(5 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(7 + xOffset); y = wrap8(5 + yOffset); bm->pixel[x][y] = WHITE;

        x = wrap8(1 + xOffset); y = wrap8(6 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(7 + xOffset); y = wrap8(6 + yOffset); bm->pixel[x][y] = WHITE;

    } else if (letter == 'R') {
        /* --- Your 'R' pattern, with wrapping + offsets --- */

        /* Left vertical bar */
        x = wrap8(7 + xOffset); y = wrap8(0 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(7 + xOffset); y = wrap8(1 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(7 + xOffset); y = wrap8(2 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(7 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(7 + xOffset); y = wrap8(4 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(7 + xOffset); y = wrap8(5 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(7 + xOffset); y = wrap8(6 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(7 + xOffset); y = wrap8(7 + yOffset); bm->pixel[x][y] = WHITE;

        /* Top horizontal bar */
        x = wrap8(6 + xOffset); y = wrap8(0 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(5 + xOffset); y = wrap8(0 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(4 + xOffset); y = wrap8(0 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(3 + xOffset); y = wrap8(0 + yOffset); bm->pixel[x][y] = WHITE;

        /* Upper right vertical */
        x = wrap8(3 + xOffset); y = wrap8(1 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(3 + xOffset); y = wrap8(2 + yOffset); bm->pixel[x][y] = WHITE;

        /* Middle horizontal bar */
        x = wrap8(3 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(4 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(5 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(6 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;

        /* Diagonal leg */
        x = wrap8(5 + xOffset); y = wrap8(4 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(4 + xOffset); y = wrap8(5 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(3 + xOffset); y = wrap8(6 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(3 + xOffset); y = wrap8(7 + yOffset); bm->pixel[x][y] = WHITE;

    } else if (letter == '3') {
        /* Optional fallback if both initials were the same in main */
        /* Simple 3: three horizontal bars + right-side verticals */

        /* top */
        x = wrap8(3 + xOffset); y = wrap8(0 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(4 + xOffset); y = wrap8(0 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(5 + xOffset); y = wrap8(0 + yOffset); bm->pixel[x][y] = WHITE;

        /* upper right */
        x = wrap8(6 + xOffset); y = wrap8(1 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(6 + xOffset); y = wrap8(2 + yOffset); bm->pixel[x][y] = WHITE;

        /* middle */
        x = wrap8(3 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(4 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(5 + xOffset); y = wrap8(3 + yOffset); bm->pixel[x][y] = WHITE;

        /* lower right */
        x = wrap8(6 + xOffset); y = wrap8(4 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(6 + xOffset); y = wrap8(5 + yOffset); bm->pixel[x][y] = WHITE;

        /* bottom */
        x = wrap8(3 + xOffset); y = wrap8(6 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(4 + xOffset); y = wrap8(6 + yOffset); bm->pixel[x][y] = WHITE;
        x = wrap8(5 + xOffset); y = wrap8(6 + yOffset); bm->pixel[x][y] = WHITE;
    }
}

void clear_display(void) {
    if (fb) {
        clearFrameBuffer(fb, BLACK);
    }
}
