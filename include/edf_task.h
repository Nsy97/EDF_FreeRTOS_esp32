#ifndef EDF_TASK_H
#define EDF_TASK_H

#include "edf_main.h"
#include "edf_logging.h"

// -------------------Struct Declarations ---------------------------
typedef struct {			       
    uint16_t task_period;
    uint16_t task_phase;
    uint16_t task_deadline;
} TaskData_t;

typedef struct {
	uint8_t sorting_task_num;
	uint16_t sorting_task_deadline;
} Task;

// -------------------Task functions ---------------------------
void task1(void *pvParameters);
void task2(void *pvParameters);
void task3(void *pvParameters);
void task4(void *pvParameters);
void task_print(void *pvParameters);
void vTaskScheduler(void *pvParameters);
void aperiodic_task(void *pvParameters);

// ------------------- functions ---------------------------
void task_update(uint8_t task_num, uint16_t task_deadline, uint16_t task_period);
void task_delay(uint8_t task_num, uint16_t task_phase, uint16_t task_period);
void crude_delay(void);

#endif