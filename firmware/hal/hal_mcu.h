/******************************************************************************

 @file  hal_mcu.h

 @brief Describe the purpose and contents of the file.

 Group: 
 Target Device: 

 ******************************************************************************

 ******************************************************************************
 Release Name: 
 Release Date: 
 *****************************************************************************/

#ifndef __HAL_MCU_H__
#define __HAL_MCU_H__

#include "stdint.h"
#include "hal_config.h"
/* ------------------------------------------------------------------------------------------------
 * CONSTANTS
 * ------------------------------------------------------------------------------------------------
 */
#if HAL_MCU_HSI_TRIM_EN > 0
#define HAL_MCU_TRIM_MIN       -20      //about 18000kHz - 10*40kHz/10 = 17600kHz
#define HAL_MCU_TRIM_MAX       20       //about 18000kHz + 20*40kHz/10 = 18800kHz
#endif //HAL_MCU_TRIM_EN > 0

/* ------------------------------------------------------------------------------------------------
 *                                           Macros
 * ------------------------------------------------------------------------------------------------
 */

/* ------------------------------------------------------------------------------------------------
 *                                          Prototypes
 * ------------------------------------------------------------------------------------------------
 */

/**************************************************************************************************
 */

/**************************************************************************************************
 *                                        FUNCTIONS - API
 **************************************************************************************************/

extern void hal_mcu_init( void );
#if HAL_MCU_RESET_EN > 0
extern void hal_mcu_reset( void );
#endif //HAL_MCU_DELAYUS_EN > 0
#if HAL_MCU_DELAYUS_EN > 0
extern void hal_mcu_delayus( uint32_t us);
#endif //HAL_MCU_DELAYUS_EN > 0
#if HAL_MCU_HSI_TRIM_EN > 0
extern int8_t hal_mcu_hsi_trim_set( int8_t trim );
extern int8_t hal_mcu_hsi_trim_get( void );
#endif //HAL_MCU_TRIM_EN > 0

#endif

