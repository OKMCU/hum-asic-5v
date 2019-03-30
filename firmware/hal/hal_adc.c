/**
  ******************************************************************************
  * @file    hal_adc.h
  * @author  SUN Wentao
  * @version V0.0.1
  * @date    24-MAR-2019
  * @brief   
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 OKMCU</center></h2>
  *
  * Licensed under OKMCU Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.okmcu.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

#include "osal.h"
#include "spl.h"

#include "hal_config.h"
#include "hal_assert.h"
#include "hal_adc.h"

#include "main.h"

#if HAL_ADC_EN > 0

extern void hal_adc_init(void)
{
    
    
}

extern uint16_t hal_adc_read(void)
{
    uint16_t chadc, bgadc;
    uint32_t u32tmp;
    
    bgadc = spl_adc_read( SPL_ADC_CH_BANDGAP );
    chadc = spl_adc_read( SPL_ADC_CH_5 );
    
    u32tmp = spl_adc_get_bandgap();
    u32tmp *= chadc;
    u32tmp *= 3; // *3072
    u32tmp >>= 2;// /4096
    u32tmp /= bgadc;
    if( u32tmp > UINT16_MAX )
        return UINT16_MAX;
    
    return (uint16_t)u32tmp;
}

#endif /* HAL_ADC_EN > 0 */

