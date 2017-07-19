/*
 *  \file       oven.h
 *  \brief      Example application.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2016.03.17  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Darío Baliña  dariosb@gmail.com
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __OVEN_H__
#define __OVEN_H__

/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
#define COOK_TIME       RKH_TIME_SEC(5)     /* Cook cycle duration time */

/* -------------------------------- Constants ------------------------------ */
/* ================================ Signals ================================ */
typedef enum ov_sigs_t
{
    OPEN,   /* door is open  */
    CLOSE,  /* door is close */
    START,  /* start button pressed */
    TMREVT, /* timer expired */
    TERM,   /* to close application in x86 */
} OV_SIGS_T;

/* ======================== Declares active object ========================= */
RKH_SMA_DCLR(oven);

/* =================== Declares states and pseudostates ==================== */
RKH_DCLR_BASIC_STATE opened, ready, cooking;
RKH_DCLR_COMP_STATE closed;
RKH_DCLR_SHIST_STATE close_hist;

/* ------------------------------- Data types ------------------------------ */
typedef struct Oven Oven;

/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
/* ============================ Initial action ============================= */
void oven_init(Oven *const me);

/* ============================ Effect actions ============================= */
void cook_restart(Oven *const me, RKH_EVT_T *pe);

/* ============================= Entry actions ============================= */
void door_open(Oven *const me, RKH_EVT_T *pe);
void cook_ready(Oven *const me, RKH_EVT_T *pe);
void cook_start(Oven *const me, RKH_EVT_T *pe);

/* ============================= Exit actions ============================== */
void cook_stop(Oven *const me, RKH_EVT_T *pe);

/* ================================ Guards ================================= */

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */

