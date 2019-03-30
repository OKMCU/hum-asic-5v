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

#ifndef __HAL_ADC_H__
#define __HAL_ADC_H__

#include "stdint.h"

extern void hal_adc_init(void);
extern uint16_t hal_adc_read(void);

#endif /* __HAL_ADC_H__ */

