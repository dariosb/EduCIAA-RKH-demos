/*
 * leds.h
 */
/**
 *  \file       leds.h
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
#ifndef __LEDS_H__
#define __LEDS_H__

/* ----------------------------- Include files ----------------------------- */
#include "sapi.h"  /* <= device handler header */

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/*
 * EduCIAA Leds map on "/dev/dio/out/0"
 */
#define LED0R_MASK  0x01    /* GPIO5[0]  */
#define LED0G_MASK  0x02    /* GPIO5[1]  */
#define LED0B_MASK  0x04    /* GPIO5[2]  */
#define LED1_MASK   0x08    /* GPIO0[14] */
#define LED2_MASK   0x10    /* GPIO1[11] */
#define LED3_MASK   0x20    /* GPIO1[12] */

typedef enum
{
    RGB_BLACK,
    RGB_WHITE,
    RGB_RED,
    RGB_LIME,
    RGB_BLUE,
    RGB_YELLOW,
    RGB_CYAN,
    RGB_MAGENTA
} RGB_COLOR_IDX;

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
void init_leds(void);
void set_led(uint8_t lmask, uint8_t st);
void set_rgb_led(RGB_COLOR_IDX idx);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
