#ifndef EDF_MAIN_H
#define EDF_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include <rom/ets_sys.h>
#include "esp_timer.h"
#include "esp_log.h"                // Using esp32 logging library

// -------------------Task parameters macros (in ticks) ---------------------------

#define PERIODIC_TASK_COUNT 2	    // Enter the number of Periodic Tasks

#define PERIOD 10, 8, 18, 17		// Enter the Periods of Periodic Tasks [1, 2, 3, 4]

#define PHASE 0, 0, 0, 0		    // Enter the phases of Periodic Tasks (ascending order only) [1, 2, 3, 4]

#define DEADLINE 7, 5, 9, 11		// Enter the Deadlines realtive to phases of Periodic Tasks [1, 2, 3, 4]

#define LOG_TIME 100		        //Enter log time

#define APERIODIC 1			        //Define here to enable aperiodic task

#define DELAY 30000		    		// Enter crude delay (or) computation delay for tasks.

#define PRINT_TASK_TAG "TASK_PRINT"	// Log print task

// -------------------Global variables ---------------------------
extern uint8_t current_task_sout;
extern uint32_t event_sout;
extern uint8_t current_task_sin; 
extern uint32_t event_sin;
extern uint32_t counter;
extern uint32_t iter;

extern uint8_t task_log[LOG_TIME];
extern uint32_t user_usec_sout[100][2];
extern uint32_t user_usec_sin[100][2];

extern const TickType_t period[PERIODIC_TASK_COUNT];
extern const TickType_t phase[PERIODIC_TASK_COUNT];
extern const TickType_t deadline[PERIODIC_TASK_COUNT];
extern TickType_t upd_deadline[PERIODIC_TASK_COUNT];

extern TickType_t xLastWakeTime[PERIODIC_TASK_COUNT]; 
extern uint32_t start_time[PERIODIC_TASK_COUNT], end_time[PERIODIC_TASK_COUNT];
extern uint16_t task_instance[PERIODIC_TASK_COUNT];

enum Task_Num {
	TASK1,
	TASK2,
	TASK3,
	TASK4
};

// -------------------Task handles  ---------------------------
extern TaskHandle_t xHandle1;
extern TaskHandle_t xHandle2;
extern TaskHandle_t xHandle3;
extern TaskHandle_t xHandle4;
extern TaskHandle_t xHandle_aper;

#endif