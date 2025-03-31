#include "module_sel.h"

void  Led1_sel(void){
    // HAL_Delay(1000);
    HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);


}

void Led2_sel(void){
    // HAL_Delay(1000);
    HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN);
}

// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
//     if(GPIO_Pin == KEY1_PIN){
//         Led1_sel();
//     }
//     else if(GPIO_Pin == KEY2_PIN){
//         Led2_sel();
//     }

// }