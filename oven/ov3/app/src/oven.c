/**
 *  \file       oven.c
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
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhfwk_dynevt.h"
#include "oven.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ======================== States and pseudostates ======================== */
RKH_CREATE_BASIC_STATE(opened, door_open, NULL,  RKH_ROOT, NULL);
RKH_CREATE_TRANS_TABLE(opened)
    RKH_TRREG(CLOSE,   NULL,   NULL,   &closed),
RKH_END_TRANS_TABLE

RKH_CREATE_COMP_STATE(closed, NULL, NULL,  RKH_ROOT, &ready, &close_hist);
RKH_CREATE_TRANS_TABLE(closed)
    RKH_TRREG(OPEN,    NULL,   NULL,   &opened),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(ready, cook_ready, NULL,  &closed, NULL);
RKH_CREATE_TRANS_TABLE(ready)
    RKH_TRREG(START,   NULL,   NULL,   &cooking),
RKH_END_TRANS_TABLE

RKH_CREATE_BASIC_STATE(cooking, cook_start, cook_stop,  &closed, NULL);
RKH_CREATE_TRANS_TABLE(cooking)
    RKH_TRINT(START,   NULL,   cook_restart),
    RKH_TRREG(TMREVT,  NULL,   NULL,   &ready),
RKH_END_TRANS_TABLE

/* ---------------------------- Local data types --------------------------- */
struct Oven
{
    RKH_SMA_T sma;  /* base structure */
    RKH_TMR_T timer;
};

/* ---------------------------- Global variables --------------------------- */
/* ============================= Active object ============================= */
RKH_SMA_CREATE(Oven, oven, 0, HCAL, &opened, oven_init, NULL);
RKH_SMA_DEF_PTR(oven);

/* ---------------------------- Local variables ---------------------------- */
/*
 *  Declare and allocate the 'e_tout' event.
 *  The 'e_tout' event with TIMEOUT signal never changes, so it can be
 *  statically allocated just once by means of RKH_ROM_STATIC_EVENT() macro.
 */
static RKH_ROM_STATIC_EVENT(e_tout, TMREVT);

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
/* ============================ Initial action ============================= */
void
oven_init(Oven *const me)
{
    bsp_ovenInit();

    /* send objects to trazer */
    RKH_TR_FWK_AO(me);
    RKH_TR_FWK_STATE(me, &closed);
    RKH_TR_FWK_STATE(me, &opened);
    RKH_TR_FWK_STATE(me, &ready);
    RKH_TR_FWK_STATE(me, &cooking);
    RKH_TR_FWK_OBJ(&me->timer);
    RKH_TR_FWK_FUN(&oven_init);
    RKH_TR_FWK_FUN(&cook_start);
    RKH_TR_FWK_FUN(&cook_stop);
    RKH_TR_FWK_FUN(&door_open);
    RKH_TR_FWK_FUN(&cook_ready);
    RKH_TR_FWK_FUN(&cook_restart);

    /* send signals to trazer */
    RKH_TR_FWK_SIG(OPEN);
    RKH_TR_FWK_SIG(CLOSE);
    RKH_TR_FWK_SIG(START);
    RKH_TR_FWK_SIG(TMREVT);
    RKH_TR_FWK_SIG(TERM);

    RKH_TMR_INIT(&me->timer, &e_tout, NULL);
}

/* ============================ Effect actions ============================= */
void
cook_restart(Oven *const me, RKH_EVT_T *pe)
{
    (void)pe;

    RKH_TMR_ONESHOT(&me->timer, RKH_UPCAST(RKH_SMA_T, me), COOK_TIME);
}

/* ============================= Entry actions ============================= */
void
door_open(Oven *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    bsp_doorOpen();
}

void
cook_ready(Oven *const me, RKH_EVT_T *pe)
{
    (void)me;
    (void)pe;

    bsp_emitterReady();
}

void
cook_start(Oven *const me, RKH_EVT_T *pe)
{
    (void)pe;

    RKH_TMR_ONESHOT(&me->timer, RKH_UPCAST(RKH_SMA_T, me), COOK_TIME);
    bsp_emitterOn();
}

/* ============================= Exit actions ============================== */
void
cook_stop(Oven *const me, RKH_EVT_T *pe)
{
    (void)pe;

    rkh_tmr_stop(&me->timer);
    bsp_emitterOff();
}

/* ================================ Guards ================================= */
/* ------------------------------ End of file ------------------------------ */
