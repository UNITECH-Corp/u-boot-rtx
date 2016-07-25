/*
 * efm32.c - driver for EFM32 MCU
 *
 * Copyright (c) 2014 Retronix Technology Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <common.h>
#include <i2c.h>

void disable_efm32_watchdog( )
{
	unsigned char const ubSentBuf[8] = { 5 , 0x8E , 0 , 0 , 0x93 } ;
	unsigned char ubRecvBuf[8] = { 0 } ;
	unsigned int iBus = i2c_get_bus_num() ;
		
	if ( i2c_set_bus_num( CONFIG_MCU_WDOG_BUS ) ) 
	{
		printf("unable to set i2c bus\n");
	}
	else
	{
		if ( !i2c_probe( 0xc ) )
		{
			
			if ( i2c_write( 0xc , 0x00 , 0 , (uint8_t *)ubSentBuf , 5 ) ) 
			{
				
				printf("%s:i2c_write:error\n", __func__);
			}
			else
			{
				if ( i2c_read( 0xc , 0x0 , 0 , ubRecvBuf , 3 ) ) 
				{
					printf("%s:i2c_read:error\n", __func__);
				}
				else
				{
					printf("[%02X][%02X][%02X]\n",ubRecvBuf[0],ubRecvBuf[1],ubRecvBuf[2]);
				}
			}
			
		}
		else
		{
			printf("unable to probe efm32\n");
		}
	}
	
	/* reset the i2c bus */
	i2c_set_bus_num( iBus ) ;
}


void vEFM32_SetTimeout( )
{
	unsigned char buf[4] = { 0 } ;
	unsigned int bus = i2c_get_bus_num() ;
		
	if ( i2c_set_bus_num( 1 ) ) 
	{
		printf("unable to set i2c bus\n");
	}
	else
	{
		if ( !i2c_probe( 0xc ) )
		{
			buf[0] = 0x00 ;
			if ( i2c_read( 0xc , 0xEB0000 , 3 , buf , 1 ) ) 
			//if ( i2c_read( 0xc , 0xEB01FF , 3 , buf , 1 ) ) 
			{
				printf("%s:i2c_write:error\n", __func__);
			}
			
		}
		else
		{
			printf("unable to probe efm32\n");
		}
	}
	/* reset the i2c bus */
	i2c_set_bus_num(bus);
}

