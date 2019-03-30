/**
  ******************************************************************************
  * @file    hal_fan.c
  * @author  SUN Wentao
  * @version V0.0.1
  * @date    20-SEP-2017
  * @brief   
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 OKMCU</center></h2>
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
#include "hal_fan.h"

#include "main.h"

#if HAL_FAN_EN > 0

extern void hal_fan_init(void)
{
    spl_gpio_write_pin( SPL_GPIO_PIN_P15, 0 );
    SPL_GPIO_SET_MODE_P15_QUASI();
}
extern void hal_fan_on(void)
{
    spl_gpio_write_pin( SPL_GPIO_PIN_P15, 1 );
}
extern void hal_fan_off(void)
{
    spl_gpio_write_pin( SPL_GPIO_PIN_P15, 0 );
}


#endif /* HAL_FAN_EN > 0 */

