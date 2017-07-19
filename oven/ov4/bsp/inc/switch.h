/**
 *  \file       switch.h
 *
 *  \brief      Minimal debouncing switch handler.
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
#ifndef __SWITCH_H__
#define __SWITCH_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#define SW_FLT_MSK	(SW_RELEASE|SW_PRESS)

/* -------------------------------- Constants ------------------------------ */
enum
{
	SW_RELEASE = 0x01,
	SW_PRESS = 0x02
};

enum
{
	START_SW,
	STOP_SW,
	DOOR_SW,
	SWITCHS_NUM
};

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
void switch_init( void );
void switch_tick( void );
ruint switch_getState( ruint who );

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
