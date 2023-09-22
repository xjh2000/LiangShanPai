//
// Created by xjh on 2023/9/22.
//

#include "tools.h"
#include "stm32f4xx_hal.h"


void delay_us(uint32_t u_delay) {
    uint32_t start_val, tick_n, delay_n, wait_n;

    start_val = SysTick->VAL;
    tick_n = HAL_GetTick();
    // sys_clock = 168000;  // SystemCoreClock / (1000U / uwTickFreq);
    delay_n = u_delay * 180; // sys_clock / 1000 * u_delay;
    // this maybe have a bug when wait_n never equal SysTick->VAL
    if (delay_n > start_val) {
        while (HAL_GetTick() == tick_n) {
        }
        wait_n = 180000 - (delay_n - start_val);
        while (wait_n < SysTick->VAL) {}
    } else {
        wait_n = start_val - delay_n;
        while (wait_n < SysTick->VAL && HAL_GetTick() == tick_n) {
        }
    }
}