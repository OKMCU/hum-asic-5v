/******************************************************************************

 @file  app_info.h

 @brief Describe the purpose and contents of the file.

 Group: 
 Target Device: 

 ******************************************************************************

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/

#ifndef __APP_INFO_H__
#define __APP_INFO_H__

#include "app_config.h"
#include "stdint.h"


typedef struct app_info_t {

    uint16_t adc_value;
    uint8_t sys_state;
    uint8_t water_state;
} APP_INFO_t;
/* ------------------------------------------------------------------------------------------------
 *                                           CONSTANTS
 * ------------------------------------------------------------------------------------------------
 */

#define SYS_STATE_SCAN_FREQ         0
#define SYS_STATE_NORMAL_WORKING    1

#define WATER_STATE_UNKNOWN         0
#define WATER_STATE_NONE            1
#define WATER_STATE_EXIST           2

/* ------------------------------------------------------------------------------------------------
 *                                            MACROS
 * ------------------------------------------------------------------------------------------------
 */

/* ------------------------------------------------------------------------------------------------
 *                                          Prototypes
 * ------------------------------------------------------------------------------------------------
 */

/**************************************************************************************************
 */
extern APP_INFO_t app_info;

/**************************************************************************************************
 *                                        FUNCTIONS - API
 **************************************************************************************************/

#endif

