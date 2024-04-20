//
// Created by James on 2024/4/20.
//
#include "delay.h"
#include "tim.h"

void delay_us(uint32_t xus){

    uint32_t Period = htim4.Init.Period;

    if (xus < Period){
//    ����1
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


//    ����2
//        __HAL_TIM_SET_COUNTER(&htim4, 0); //�Ѽ�������ֵ����Ϊ0
//        __HAL_TIM_ENABLE(&htim4); //��������
//        while (__HAL_TIM_GET_COUNTER(&htim4) < 10000); //ÿ����һ�Σ�����1us��ֱ��������ֵ����������Ҫ��ʱ��
//        __HAL_TIM_DISABLE(&htim4); //�رռ���
}

void delay_ms(uint32_t xms){
    delay_us(1000 * xms);
}
