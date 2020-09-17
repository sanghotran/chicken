/*
 * thread.h
 *
 *  Created on: Sep 17, 2020
 *      Author: Admin
 */

#ifndef INC_THREAD_H_
#define INC_THREAD_H_

#include "main.h"
#include "tim.h"
#include "gpio.h"

#define MaxThread 10

typedef void(*ThreadFunc_t)(char*);
typedef int ThreadId_t;
typedef enum
	{
		ThreadRepeat,
		ThreadSingleShot

	} ThreadType_t;
typedef struct
	{
		ThreadFunc_t ThreadFunc;
		int Period;
		int Count;
		ThreadType_t Type;
		char *Cxt;
	} Thread_t;

Thread_t Thread[MaxThread];

ThreadId_t RegisterThread(ThreadFunc_t, int, ThreadType_t, char*);
ThreadId_t UnRegisterThread(ThreadId_t );


void OneMsTimerInterrup();

void BlinkLed();
void BlinkBuzzer();






#endif /* INC_THREAD_H_ */
