/******************************************************************************

 @file  app_event_main.c

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/

/**************************************************************************************************
 * INCLUDES
 **************************************************************************************************/
#include "osal.h"
#include "hal.h"
#include "app.h"

#include "main.h"

#include "stdstr.h"
#include "stringx.h"
/**************************************************************************************************
 * TYPE DEFINES
 **************************************************************************************************/

 /**************************************************************************************************
 * LOCAL API DECLARATION
 **************************************************************************************************/

/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/

/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/

extern void app_event_main_por( void )
{
#if APP_CLI_EN > 0
    hal_cli_print_str( "\r\nThis is OSAL demo project on Nuvoton 8051 series MCU.\r\n" );
    hal_cli_print_str( "Power on reset.\r\n" );

    hal_cli_print_str( "Free-OSAL Version " );
    hal_cli_print_str( OSAL_VERSION );
    hal_cli_print_str( "\r\n" );
    
    hal_cli_print_str( "Firmware Version " );
    hal_cli_print_str( FIRMWARE_VER );
    hal_cli_print_str( "\r\n" );

    hal_cli_print_str( "Hardware Version " );
    hal_cli_print_str( HARDWARE_VER );
    hal_cli_print_str( "\r\n" );
#endif

    app_info.sys_state = SYS_STATE_SCAN_FREQ;
    app_info.adc_value = 0;
    app_info.water_state = WATER_STATE_UNKNOWN;

    osal_event_set( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_RESET );
    osal_event_set( TASK_ID_APP_WATERDET, TASK_EVT_APP_WATERDET_RESET );
    osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_IDLE );

    //hal_mist_set_pwr( 3 );
    hal_mcu_hsi_trim_set( 0 );
    hal_mist_set_pwr( 3 );
    hal_mist_on();
}


extern void app_event_main_app_exception( void )
{
#if (APP_CLI_EN > 0)
    hal_cli_print_str( "ERROR! " );
    hal_cli_print_str( "APP EXCEPTION!\r\n" );
#endif
}

extern void app_event_main_hal_exception( void )
{
#if (APP_CLI_EN > 0)
    hal_cli_print_str( "ERROR! " );
    hal_cli_print_str( "HAL EXCEPTION!\r\n" );
#endif
}

extern void app_event_main_osal_exception( void )
{
#if (APP_CLI_EN > 0)
    hal_cli_print_str( "ERROR! " );
    hal_cli_print_str( "OSAL_EXCEPTION!\r\n" );
#endif
}

extern void app_event_main_water_state_update( void )
{
    switch ( app_info.water_state )
    {
        case WATER_STATE_UNKNOWN:
            hal_mist_on();
        break;

        case WATER_STATE_NONE:
            hal_nowater_pin_low();
            hal_mist_off();

            if( app_info.sys_state == SYS_STATE_SCAN_FREQ )
            {
                osal_event_set( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_RESET );
            }

            if( app_info.sys_state == SYS_STATE_NORMAL_WORKING )
            {
                osal_event_set( TASK_ID_APP_WATERDET, TASK_EVT_APP_WATERDET_RESET );
            }
            
            osal_timer_event_create( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_NO_WATER_TIMEOUT, 5000 );
        break;

        case WATER_STATE_EXIST:
            hal_nowater_pin_high();
        break;
    }
}

extern void app_event_main_no_water_timeout( void )
{
    app_info.water_state = WATER_STATE_UNKNOWN;
    osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_WATER_STATE_UPD );
}

extern void app_event_main_idle( void )
{

    if( app_info.water_state != WATER_STATE_NONE )
    {
        app_info.adc_value = hal_adc_read();
        
        switch ( app_info.sys_state )
        {
            case SYS_STATE_SCAN_FREQ:
            {
                #if APP_FHOP_EN > 0
                osal_event_set( TASK_ID_APP_FHOP, TASK_EVT_APP_FHOP_UPDATE );
                #endif
            }
            break;
            
            case SYS_STATE_NORMAL_WORKING:
            {
                #if APP_WATERDET_EN > 0
                osal_event_set( TASK_ID_APP_WATERDET, TASK_EVT_APP_WATERDET_UPDATE );
                #endif
            }
            break;
        }
    }
    
    osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_IDLE );
}

/**************************************************************************************************
**************************************************************************************************/

