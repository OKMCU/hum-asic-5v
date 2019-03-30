/******************************************************************************

 @file  main.h

 @brief 

 Group: 
 Target Device: 

 ******************************************************************************
 

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/

#ifndef __MAIN_H__
#define __MAIN_H__

#define TASK_ID_HAL_DRIVER_BASIC            0
#define TASK_ID_APP_CLI                     1
#define TASK_ID_APP_FHOP                    2
#define TASK_ID_APP_WATERDET                3
#define TASK_ID_APP_MAIN                    4

#define TASK_EVT_APP_CLI_RX_CHAR            1
#define TASK_EVT_APP_CLI_RX_OVF             2

#define TASK_EVT_APP_FHOP_RESET             0 
#define TASK_EVT_APP_FHOP_UPDATE            1

#define TASK_EVT_APP_WATERDET_UPDATE        0
#define TASK_EVT_APP_WATERDET_RESET         1

#define TASK_EVT_APP_MAIN_POR               1
#define TASK_EVT_APP_MAIN_APP_EXCEPTION     2
#define TASK_EVT_APP_MAIN_HAL_EXCEPTION     3
#define TASK_EVT_APP_MAIN_OSAL_EXCEPTION    4
#define TASK_EVT_APP_MAIN_WATER_STATE_UPD   5
#define TASK_EVT_APP_MAIN_NO_WATER_TIMEOUT  6
#define TASK_EVT_APP_MAIN_IDLE              7



#define TASK_EVT_HAL_DRIVER_BASIC_CLI_RXNE       1
//#define TASK_EVT_HAL_DRIVER_BASIC_CLI_TXE        2

/**************************************************************************************************
 *                                        FUNCTIONS - API
 **************************************************************************************************/

#endif

