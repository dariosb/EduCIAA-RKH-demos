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
leds_init(void)
{
    gpioConfig(LEDR, GPIO_OUTPUT);
    gpioConfig(LEDG, GPIO_OUTPUT);
    gpioConfig(LEDB, GPIO_OUTPUT);
}

void
leds_rgbSet(RGB_COLOR_IDX idx)
{
    gpioWrite(LEDR, rgb_colors[idx].r);
    gpioWrite(LEDG, rgb_colors[idx].g);
    gpioWrite(LEDB, rgb_colors[idx].b);
}

/* ------------------------------ End of file ------------------------------ */

