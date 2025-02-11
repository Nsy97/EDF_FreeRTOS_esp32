/*
	EDF Scheduling algorithm implementation

	EDF priority assignment is done in Switched_OUT trace macro

	Logging is done in both traceTASK_INCREMENT_TICK macro &&
		event based (Switched_IN & Switched_OUT) trace macros

	Program to model Periodic tasks and Aperiodic task
	Enter the parameters of Periodic tasks in #define macros below ) and run them by EDF scheduing algorithm.
	Can generate 2 to 4 Periodic tasks and 1 Aperiodic Task

	Task parameters are defined in the edf_main.h file with #define macros

	menuconfig = Set Component config > FreeRTOS > CONFIG_FREERTOS_UNICORE to [yes]
	INCLUDE_xTaskGetIdleTaskHandle must be set to 1
	#define INCLUDE_eTaskGetState 1  in FreeRTOS.h file
	#define INCLUDE_vTaskPrioritySet 1  in FreeRTOS.h file

	Add your computation replacing crude_delay() in edf_task.c 

	Sorting is done using qsort inbuilt C function ( quick_sort).
	vTaskPrioritySet is used to reassign task priorities.

	Flash instruction for expressif esp32
	idf.py build
	idf.py -p COM4 flash
	idf.py -p COM4 monitor

	The program logs the scheduling events upto the variable LOG_TIME

	Run the python script "Plotting_chart(ms).py" to view the scheduling graph
*/

#include "include/edf_main.h"
#include "include/edf_logging.h"
#include "include/edf_sorting.h"
#include "include/edf_task.h"

// -------------------app_main ---------------------------
void app_main(void)
{
    printf("Start \n");

	for(iter = 0; iter < PERIODIC_TASK_COUNT; iter++)
	{
		upd_deadline[iter] = phase[iter] + deadline[iter];
	}

	//Periodic task scheduler and aperiodic task with lower priority than periodic tasks
	xTaskCreate(vTaskScheduler, "Scheduler", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	#ifdef APERIODIC
		xTaskCreate(aperiodic_task, "Aperiodic_task", configMINIMAL_STACK_SIZE+1000, NULL, 1, &xHandle_aper);
	#endif
}

