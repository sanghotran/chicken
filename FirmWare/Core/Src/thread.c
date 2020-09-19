/*
 * thread.c
 *
 *  Created on: Sep 17, 2020
 *      Author: Admin
 */


#include "thread.h"

int i;

ThreadId_t RegisterThread(ThreadFunc_t ThreadFunc, int PeriodMs, ThreadType_t Type, char* Context)
{
	for( i = 0; i < MaxThread; i++)
	{
		if(Thread[i].ThreadFunc == NULL)
		{
			Thread[i].ThreadFunc = ThreadFunc;
			Thread[i].Period = PeriodMs;
			Thread[i].Count = PeriodMs;
			Thread[i].Type = Type;
			Thread[i].Cxt = Context;
			return i;
		}
	}
	return -1;
}

ThreadId_t UnRegisterThread(ThreadId_t ProcId)
{
	if(Thread[ProcId].ThreadFunc != NULL)
	{
		Thread[ProcId].ThreadFunc = NULL;
		return 1;
	}
	else return 0;
}

void OneMsTimerInterrup()
{
	for(i = 0; i < MaxThread; i++)
	{
		if(Thread[i].ThreadFunc != 0)
		{
			Thread[i].Count--;
			if(Thread[i].Count == 0)
			{
				Thread[i].ThreadFunc(Thread[i].Cxt);
				if(Thread[i].Type == ThreadRepeat)
				{
					Thread[i].Count = Thread[i].Period;
				}
				else if(Thread[i].Type = ThreadSingleShot)
				{
					Thread[i].ThreadFunc = NULL;
				}
			}
		}
	}

}

void BlinkLed()
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}


void BlinkBuzzer()
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim -> Instance == htim1.Instance )
	{
		OneMsTimerInterrup();
	}
}

