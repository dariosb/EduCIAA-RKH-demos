/*
 * switch.c
 *
 * Minimal debouncing switch handler.
 * hardware access.
 *
 */

#include "switch.h"
#include "sapi.h"
#include "bsp.h"

#define CIAA_SW1_MSK    1
#define CIAA_SW2_MSK    2
#define CIAA_SW3_MSK    4
#define CIAA_SW4_MSK    8

static int32_t fd_in;
static uint8_t inputs;
static ruint rawStart( void );
static ruint rawStop( void );
static ruint rawDoor( void );

static SWITCH_ST switchs[SWITCHS_NUM] = 
{
	{ 0, rawStart,	SW_RELEASE, SW_PRESS },
	{ 0, rawStop,	SW_RELEASE, SW_PRESS },
	{ 0, rawDoor,	SW_RELEASE, SW_PRESS|SW_RELEASE },
};

static
ruint
rawStart( void )
{
    //ciaaPOSIX_read(fd_in, &inputs, 1);
	return inputs & CIAA_SW1_MSK;
}

static
ruint
rawStop( void )
{
    //ciaaPOSIX_read(fd_in, &inputs, 1);
	return inputs & CIAA_SW2_MSK;
}
	
static
ruint
rawDoor( void )
{
    //ciaaPOSIX_read(fd_in, &inputs, 1);
	return inputs & CIAA_SW3_MSK;
}

void
init_switch( void )
{
    //fd_in = ciaaPOSIX_open("/dev/dio/in/0", ciaaPOSIX_O_RDWR);
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
get_switch_state( ruint who )
{
	return switchs[who].debsw;
}
