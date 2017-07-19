/**
 *  \file       main.c
 *  \brief      Oven demo. 
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
#include "rkhfwk_sched.h"
#include "rkhtrc.h"
#include "bsp.h"
#include "oven.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
#define QSTO_SIZE           4

/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static RKH_EVT_T *qsto[QSTO_SIZE];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
int
main(int argc, char *argv[])
{
    bsp_init(argc, argv);

    RKH_SMA_ACTIVATE(oven, qsto, QSTO_SIZE, 0, 0);

    rkh_fwk_enter();

    RKH_TRC_CLOSE();

    return 0;
}

/* ------------------------------ End of file ------------------------------ */
