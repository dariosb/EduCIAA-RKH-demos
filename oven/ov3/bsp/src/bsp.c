/*
 *  --------------------------------------------------------------------------
 *
 *                                Framework RKH
 *                                -------------
 *
 *            State-machine framework for reactive embedded systems
 *
 *                      Copyright (C) 2010 Leandro Francucci.
 *          All rights reserved. Protected by international copyright laws.
 *
 *
 *  RKH is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any
 *  later version.
 *
 *  RKH is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with RKH, see copying.txt file.
 *
 *  Contact information:
 *  RKH web site:   http://sourceforge.net/projects/rkh-reactivesys/
 *  e-mail:         francuccilea@gmail.com
 *  ---------------------------------------------------------------------------
 */

/**
 *  \file       bsp.c
 *  \brief      BSP for Cortex-M3 EDU-CIAA LPC4337 ARM-GCC
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2017.06.23  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Baliña       dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhfwk_sched.h"
#include "rkhfwk_dynevt.h"
#include "oven.h"
#include "bsp.h"
#include "leds.h"
#include "switch.h"
#include "sapi.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_TS_T tstamp;

#if defined(RKH_USE_TRC_SENDER)
static rui8_t door;
static rui8_t panel;
#endif

static RKH_ROM_STATIC_EVENT(e_start, START);
static RKH_ROM_STATIC_EVENT(e_open, OPEN);
static RKH_ROM_STATIC_EVENT(e_close, CLOSE);
static RKH_ROM_STATIC_EVENT(e_term, TERM);
#if (__STOP_BUTTON__ == RKH_ENABLED)
static RKH_ROM_STATIC_EVENT(e_stop, STOP);
#endif

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
bsp_timeTick(void)
{
    ++tstamp;
    switch_tick();
}

RKH_TS_T
rkh_trc_getts(void)
{
    return tstamp;
}

void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    boardConfig();

    rkh_fwk_init();

    RKH_FILTER_ON_GROUP(RKH_TRC_ALL_GROUPS);
    RKH_FILTER_ON_EVENT(RKH_TRC_ALL_EVENTS);
    RKH_FILTER_OFF_EVENT(RKH_TE_TMR_TOUT);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_SMA(oven);
    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();

#if defined(RKH_USE_TRC_SENDER)
    RKH_TR_FWK_OBJ(&panel);
    RKH_TR_FWK_OBJ(&door);
#endif

    RKH_ENA_INTERRUPT();
}

void
bsp_ovenInit(void)
{
    leds_init();
    switch_init();
}

void
bsp_publishSwitchEvt(ruint s, ruint debsw)
{
    switch (s)
    {
        case START_SW:
            RKH_SMA_POST_FIFO(oven, &e_start, &panel);
            break;

#if (__STOP_BUTTON__ == RKH_ENABLED)
        case STOP_SW:
            RKH_SMA_POST_FIFO(oven, &e_stop, &panel);
            break;
#endif

        case DOOR_SW:
            if (debsw == SW_PRESS)
            {
                RKH_SMA_POST_FIFO(oven, &e_close, &door);
            }
            else
            {
                RKH_SMA_POST_FIFO(oven, &e_open, &door);
            }
            break;
    }
}

void
bsp_emitterOn(void)
{
    leds_rgbSet(RGB_RED);
}

void
bsp_emitterOff(void)
{
    leds_rgbSet(RGB_BLACK);
}

void
bsp_doorOpen(void)
{
    leds_rgbSet(RGB_BLACK);
}

void
bsp_emitterReady(void)
{
    leds_rgbSet(RGB_LIME);
}

void
bsp_emitterPause(void)
{
    leds_rgbSet(RGB_YELLOW);
}

void
bsp_emitterContinue(void)
{
    leds_rgbSet(RGB_RED);
}


/* ------------------------------ End of file ------------------------------ */
