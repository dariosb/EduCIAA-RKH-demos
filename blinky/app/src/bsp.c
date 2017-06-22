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
#include "blinky.h"
#include "bsp.h"
#include "sapi.h"

RKH_THIS_MODULE

/* ----------------------------- Local macros ------------------------------ */
#ifdef DEBUG
#define reset_now()         __asm volatile ("bkpt 0x00FF\n")
#else
#define reset_now()         NVIC_SystemReset()
#endif

/* ------------------------------- Constants ------------------------------- */
#define TRC_COM_PORT        UART_USB
#define TRC_BAUD_RATE       115200
#define BSP_TICK_RATE_MS    (1000/RKH_CFG_FWK_TICK_RATE_HZ)
#define BSP_TS_RATE_HZ      BSP_TICK_RATE_MS

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_TS_T tstamp;

/* ----------------------- Local function prototypes ----------------------- */
static bool_t tickHook(void *p);

/* ---------------------------- Local functions ---------------------------- */
static bool_t
tickHook(void *p)
{
    ++tstamp;
    RKH_TIM_TICK();
}

/* ---------------------------- Global functions --------------------------- */
void
rkh_hook_timetick(void)
{
}

void
rkh_hook_start(void)
{
}

void
rkh_hook_exit(void)
{
    RKH_TRC_FLUSH();
}

void
rkh_hook_idle(void)
{
    RKH_ENA_INTERRUPT();
    RKH_TRC_FLUSH();
}

void
rkh_assert(RKHROM char * const file, int line)
{
    (void)line;

    RKH_DIS_INTERRUPT();
    RKH_TR_FWK_ASSERT((RKHROM char *)file, __LINE__);
    rkh_fwk_exit();
    reset_now();
}

#if RKH_CFG_TRC_EN == 1
void
rkh_trc_open(void)
{
    rkh_trc_init();
    uartConfig(TRC_COM_PORT, TRC_BAUD_RATE);
    RKH_TRC_SEND_CFG(BSP_TS_RATE_HZ);
}

void
rkh_trc_close(void)
{
}

RKH_TS_T
rkh_trc_getts(void)
{
    return tstamp;
}

void
rkh_trc_flush(void)
{
    rui8_t *blk;
    TRCQTY_T nbytes;
    RKH_SR_ALLOC();

    FOREVER
    {
        nbytes = 128;

        RKH_ENTER_CRITICAL_();
        blk = rkh_trc_get_block(&nbytes);
        RKH_EXIT_CRITICAL_();

        if ((blk != (rui8_t *)0))
        {
            while (nbytes--)
            {
                uartWriteByte(TRC_COM_PORT,*blk++);
            }
        }
        else
        {
            break;
        }
    }
}
#endif

void
bsp_init(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    boardConfig();

    tickConfig(BSP_TICK_RATE_MS, tickHook);

    gpioConfig(0, GPIO_ENABLE);

    gpioConfig(LED1, GPIO_OUTPUT);

    rkh_fwk_init();

    RKH_FILTER_ON_GROUP(RKH_TRC_ALL_GROUPS);
    RKH_FILTER_ON_EVENT(RKH_TRC_ALL_EVENTS);
    RKH_FILTER_OFF_EVENT(RKH_TE_TMR_TOUT);
    RKH_FILTER_OFF_EVENT(RKH_TE_SM_STATE);
    RKH_FILTER_OFF_SMA(blinky);
    RKH_FILTER_OFF_ALL_SIGNALS();

    RKH_TRC_OPEN();

    RKH_ENA_INTERRUPT();
}

void
bsp_ledOn(void)
{
    gpioWrite(LED1, ON);
}

void
bsp_ledOff(void)
{
    gpioWrite(LED1, OFF);
}

/* ------------------------------ End of file ------------------------------ */
