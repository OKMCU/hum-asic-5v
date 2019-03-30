/******************************************************************************

 @file  app_task_fhop.c

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

#if APP_FHOP_EN > 0
/**************************************************************************************************
 * TYPES
 **************************************************************************************************/

/**************************************************************************************************
 * CONSTANTS
 **************************************************************************************************/
#define FREQ_MAX        ((uint8_t)((int8_t)HAL_MCU_TRIM_MAX-(int8_t)HAL_MCU_TRIM_MIN)+1)
#define FREQ_OFFSET     5
#define SAMPLE_CNT_MAX  150
#define FHOP_NO_WATER_HI_THRESHOLD      3000
#define FHOP_NO_WATER_LO_THRESHOLD      0
#define FUZZY_SCALE     3
/**************************************************************************************************
 * LOCAL FUNCTION DECLARATION
 **************************************************************************************************/
static void app_task_fhop_handle_update( void );
/**************************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************************/
static uint8_t sample_cnt;
static uint32_t freq_index[FREQ_MAX];

static uint8_t find_fuzzy_peak( const uint32_t *p_value, uint8_t len, uint32_t *p_fuzzy_peak )
{
    uint8_t i;
    uint8_t j;
    uint8_t peak_idx;
    uint32_t peak_val;
    uint32_t peak_fuzzy;
    
    peak_val = 0;
    peak_idx = 0;
    for( i = (FUZZY_SCALE/2); i < (len-(FUZZY_SCALE/2)); i++ )
    {
        peak_fuzzy = 0;
        for( j = i - FUZZY_SCALE/2; j<=(i+FUZZY_SCALE/2); j++ )
        {
            peak_fuzzy += p_value[j];
        }

        if( peak_fuzzy >= peak_val )
        {
            peak_val = peak_fuzzy;
            peak_idx = i;
        }
    }

    if( p_fuzzy_peak )
    {
        *p_fuzzy_peak = peak_val / FUZZY_SCALE;
    }
    
    return peak_idx;
}

extern void app_task_fhop_init( void )
{
    uint8_t i;
    
    for( i = 0; i < FREQ_MAX; i++ )
    {
        freq_index[i] = 0;
    }
    sample_cnt = 0;
}


static void app_task_fhop_reset( void )
{
    app_task_fhop_init();
    hal_mcu_hsi_trim_set( HAL_MCU_TRIM_MIN );
    hal_mist_set_pwr( 2 );
    //hal_mist_on();
}

extern void app_task_fhop ( uint8_t task_id, uint8_t event_id )
{
    task_id = task_id;
    
    switch (event_id)
    {
        case TASK_EVT_APP_FHOP_RESET:
        {
            app_task_fhop_reset();
        }
        break;
        
        case TASK_EVT_APP_FHOP_UPDATE:
        {
            app_task_fhop_handle_update();
        }
        break;
        
        default:
            APP_ASSERT_FORCED();
        break;
    }
}

static void app_task_fhop_handle_update( void )
{
    int8_t trim;
    uint8_t i;
    uint8_t peak_idx;
    uint32_t peak_val;

    trim = hal_mcu_hsi_trim_get();
    i = (uint8_t)(trim - (int8_t)HAL_MCU_TRIM_MIN);
    
    freq_index[i] += app_info.adc_value;
    sample_cnt++;
    if( sample_cnt == SAMPLE_CNT_MAX )
    {
        sample_cnt = 0;
        if( trim < HAL_MCU_TRIM_MAX )
        {
            trim++;
            hal_mcu_hsi_trim_set( trim );
        }
        else
        {
            peak_idx = find_fuzzy_peak( freq_index, FREQ_MAX, &peak_val );

            if(  peak_val < (uint32_t)((uint32_t)FHOP_NO_WATER_HI_THRESHOLD*(uint32_t)SAMPLE_CNT_MAX)
              && peak_val > (uint32_t)((uint32_t)FHOP_NO_WATER_LO_THRESHOLD*(uint32_t)SAMPLE_CNT_MAX) )
            {
                trim = (int8_t)peak_idx + (int8_t)(HAL_MCU_TRIM_MIN) - (int8_t)FREQ_OFFSET;   
                trim = 0;
                hal_mcu_hsi_trim_set( trim );
                hal_mist_set_pwr( 3 );
                
                app_info.sys_state = SYS_STATE_NORMAL_WORKING;
                app_info.water_state = WATER_STATE_EXIST;
                osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_WATER_STATE_UPD );
            }
            else
            {
                app_info.water_state = WATER_STATE_NONE;
                osal_event_set( TASK_ID_APP_MAIN, TASK_EVT_APP_MAIN_WATER_STATE_UPD );
            }
        }
    }
    
    
}


#endif
/**************************************************************************************************
**************************************************************************************************/

