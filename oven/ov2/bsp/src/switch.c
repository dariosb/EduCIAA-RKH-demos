/**
 *  \file       switch.c
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
/* ----------------------------- Include files ----------------------------- */
#include "switch.h"
#include "sapi.h"
#include "bsp.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
typedef struct
{
	unsigned char state;
	bool_t (*rawsw)(void);
	ruint debsw;
	ruint filter;
}SWITCH_ST;

/* ---------------------------- Global variables --------------------------- */
/* ----------------------- Local function prototypes ----------------------- */
static bool_t rawStart( void );
static bool_t rawStop( void );
static bool_t rawDoor( void );

/* ---------------------------- Local variables ---------------------------- */
static SWITCH_ST switchs[SWITCHS_NUM] = 
{
	{ 0, rawStart,	SW_RELEASE, SW_PRESS },
	{ 0, rawStop,	SW_RELEASE, SW_PRESS },
	{ 0, rawDoor,	SW_RELEASE, SW_PRESS|SW_RELEASE },
};

/* ---------------------------- Local functions ---------------------------- */
static
bool_t
rawStart( void )
{
    return gpioRead(TEC1);
}

static
bool_t
rawStop( void )
{
    return gpioRead(TEC2);
}
	
static
bool_t
rawDoor( void )
{
    return gpioRead(TEC3);
}

/* ---------------------------- Global functions --------------------------- */
void
switch_init( void )
{
    gpioConfig(TEC1, GPIO_INPUT);
    gpioConfig(TEC2, GPIO_INPUT);
    gpioConfig(TEC3, GPIO_INPUT);
}

void
switch_tick( void )
{
	SWITCH_ST *p;
	ruint s;

	for( s = 0, p = switchs; p < &switchs[SWITCHS_NUM]; ++p, ++s ) 
	{
		p->state = (p->state<<1) | !(p->rawsw()); 
		if( (p->state == 0xFF) && (p->debsw != SW_PRESS) )
		{
			p->debsw = SW_PRESS;
			if( p->filter & SW_PRESS )
				bsp_publishSwitchEvt( s, SW_PRESS );
		}
		else if( ( p->state == 0x00 ) && (p->debsw != SW_RELEASE) )
		{
			p->debsw = SW_RELEASE;
			if( p->filter & SW_RELEASE )
				bsp_publishSwitchEvt( s, SW_RELEASE );
		}
	}
}

ruint
switch_getState( ruint who )
{
	return switchs[who].debsw;
}

/* ------------------------------ End of file ------------------------------ */
