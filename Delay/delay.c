//
// Created by James on 2024/4/20.
//
#include "delay.h"
#include "tim.h"

void delay_us(uint32_t xus){

    uint32_t Period = htim4.Init.Period;

    if (xus < Period){
//    方法1
        htim4.Instance->CNT = 0;
        HAL_TIM_Base_Start(&htim4);
        while (htim4.Instance->CNT < xus);
        HAL_TIM_Base_Stop(&htim4);
    } else{
        Period = 60000;
        uint32_t cycle_for_delay = xus / Period;
        uint32_t remain_us = xus % Period;
        for (uint32_t i = 0; i < cycle_for_delay; i++){
            htim4.Instance->CNT = 0;
            HAL_TIM_Base_Start(&htim4);
            while (htim4.Instance->CNT < Period);
            HAL_TIM_Base_Stop(&htim4);
        }
        htim4.Instance->CNT = 0;
        HAL_TIM_Base_Start(&htim4);
        while (htim4.Instance->CNT < remain_us);
        HAL_TIM_Base_Stop(&htim4);
    }


//    方法2
//        __HAL_TIM_SET_COUNTER(&htim4, 0); //把计数器的值设置为0
//        __HAL_TIM_ENABLE(&htim4); //开启计数
//        while (__HAL_TIM_GET_COUNTER(&htim4) < 10000); //每计数一次，就是1us，直到计数器值等于我们需要的时间
//        __HAL_TIM_DISABLE(&htim4); //关闭计数
}

void delay_ms(uint32_t xms){
    delay_us(1000 * xms);
}
