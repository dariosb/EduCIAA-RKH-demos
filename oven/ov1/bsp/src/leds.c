/**
 *  \file       leds.c
 *
 *  \brief      Simple Leds control for EduCIAA
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2015.10.24  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "leds.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_COLOR_ST;

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static int32_t fd_leds;
static const RGB_COLOR_ST rgb_colors[] =
{
    {0, 0, 0},                                           /* black   */
    {1, 1, 1},                                           /* white   */
    {1, 0, 0},                                           /* red     */
    {0, 1, 0},                                           /* lime    */
    {0, 0, 1},                                           /* blue    */
    {1, 1, 0},                                           /* yellow  */
    {0, 1, 1},                                           /* cyan    */
    {1, 0, 1}                                            /* magenta */
};

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
init_leds(void)
{
//    fd_leds = ciaaPOSIX_open("/dev/dio/out/0", ciaaPOSIX_O_RDWR);
}

void
set_led(uint8_t lmask, uint8_t st)
{
    uint8_t outputs;

    /* set output on */
//    ciaaPOSIX_read(fd_leds, &outputs, 1);

    if (st)
    {
        outputs |= lmask;
    }
    else
    {
        outputs &= ~lmask;
    }

//    ciaaPOSIX_write(fd_leds, &outputs, 1);
}

void
set_rgb_led(RGB_COLOR_IDX idx)
{
    set_led(LED0R_MASK, rgb_colors[idx].r);
    set_led(LED0G_MASK, rgb_colors[idx].g);
    set_led(LED0B_MASK, rgb_colors[idx].b);
}

/* ------------------------------ End of file ------------------------------ */

