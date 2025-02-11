#include "include/edf_task.h"

uint32_t iter = 0;
uint8_t current_task_sout = 0;
uint32_t event_sout = 0;
uint8_t current_task_sin = 0; 
uint32_t event_sin = 0;
uint32_t counter = 0;

const TickType_t period[PERIODIC_TASK_COUNT]= {PERIOD};
const TickType_t phase[PERIODIC_TASK_COUNT] = {PHASE};
const TickType_t deadline[PERIODIC_TASK_COUNT] = {DEADLINE};

TickType_t upd_deadline[PERIODIC_TASK_COUNT];
TickType_t xLastWakeTime[PERIODIC_TASK_COUNT]; 
uint32_t start_time[PERIODIC_TASK_COUNT], end_time[PERIODIC_TASK_COUNT];
uint16_t task_instance[PERIODIC_TASK_COUNT];

TaskHandle_t xHandle1;
TaskHandle_t xHandle2;
TaskHandle_t xHandle3;
TaskHandle_t xHandle4;
TaskHandle_t xHandle_aper;

// -------------------Tasks -------------------------------------
// -------------------Periodic Task 1 ---------------------------
void task1(void *pvParameters)
{
	TaskData_t *pxTaskData = (TaskData_t *)pvParameters;	//Periodic task 1 parameters
	task_log[counter] = 1;

	xLastWakeTime[TASK1] = xTaskGetTickCount();  		// Initialize the xLastWakeTime variable with the current time.
	start_time[TASK1] =  pxTaskData->task_phase;		//task instance start time

	while(1)
	{
		task_instance[TASK1]++;				

		crude_delay();	//crude delay or add your computation here

		task_update(TASK1, pxTaskData->task_deadline, pxTaskData->task_period);		

		if (counter >= LOG_TIME)						//log time end
		{
			if ( xHandle2 != NULL && eTaskGetState(xHandle2) != eDeleted)
				vTaskSuspend( xHandle2 );		//suspension of periodic tasks
			if ( xHandle3 != NULL && eTaskGetState(xHandle3) != eDeleted)
				vTaskSuspend( xHandle3 );
			if ( xHandle4 != NULL && eTaskGetState(xHandle4) != eDeleted)
				vTaskSuspend( xHandle4 );
            
			vTaskSuspend( xHandle_aper );
    		xTaskCreate(task_print, "task_print", 2048, NULL, 3, NULL);			//creation of print task

			if ( xHandle1 != NULL && eTaskGetState(xHandle1) != eDeleted)
				vTaskSuspend( xHandle1 );
		}

		task_delay(TASK1, pxTaskData->task_phase, pxTaskData->task_period);
	}
}

// -------------------Periodic Task 2 ---------------------------
void task2(void *pvParameters)
{
	TaskData_t *pxTaskData = (TaskData_t *)pvParameters;

	task_log[counter] = 2;

	xLastWakeTime[TASK2] = xTaskGetTickCount(); 	// Initialize the xLastWakeTime variable with the current time.
	start_time[TASK2] =   pxTaskData->task_phase;

	while(1)
	{
		task_instance[TASK2]++;

		crude_delay();	

		task_update(TASK2, pxTaskData->task_deadline, pxTaskData->task_period);							

		if (counter >= LOG_TIME )
		{
			if ( xHandle1 != NULL && eTaskGetState(xHandle1) != eDeleted)
				vTaskSuspend( xHandle1 );
			if ( xHandle3 != NULL && eTaskGetState(xHandle3) != eDeleted)
				vTaskSuspend( xHandle3 );
			if ( xHandle4 != NULL && eTaskGetState(xHandle4) != eDeleted)
				vTaskSuspend( xHandle4 );

			vTaskSuspend( xHandle_aper );
    		xTaskCreate(task_print, "task_print", 2048, NULL, 3, NULL);

			if ( xHandle2 != NULL && eTaskGetState(xHandle2) != eDeleted)
				vTaskSuspend( xHandle2 );
		}

		task_delay(TASK2, pxTaskData->task_phase, pxTaskData->task_period);
	}
}

// -------------------Periodic Task 3 ---------------------------
void task3(void *pvParameters)
{
	TaskData_t *pxTaskData = (TaskData_t *)pvParameters;

	task_log[counter] = 3;

	xLastWakeTime[TASK3] = xTaskGetTickCount(); 	
	start_time[TASK3] =   pxTaskData->task_phase;

	while(1)
	{
		task_instance[TASK3]++;

		crude_delay();	
											
		task_update(TASK3, pxTaskData->task_deadline, pxTaskData->task_period);

		if (counter >= LOG_TIME )
		{
			if ( xHandle1 != NULL && eTaskGetState(xHandle1) != eDeleted)
				vTaskSuspend( xHandle1 );
			if ( xHandle2 != NULL && eTaskGetState(xHandle2) != eDeleted)
				vTaskSuspend( xHandle2 );
			if ( xHandle4 != NULL && eTaskGetState(xHandle4) != eDeleted)
				vTaskSuspend( xHandle4 );
			
			vTaskSuspend( xHandle_aper );
    		xTaskCreate(task_print, "task_print", 2048, NULL, 3, NULL);

			if ( xHandle3 != NULL && eTaskGetState(xHandle3) != eDeleted)
				vTaskSuspend( xHandle3 );
		}

		task_delay(TASK3, pxTaskData->task_phase, pxTaskData->task_period);
	}
}

// -------------------Periodic Task 4 ---------------------------
void task4(void *pvParameters)
{
	TaskData_t *pxTaskData = (TaskData_t *)pvParameters;

	task_log[counter] = 4;

	xLastWakeTime[TASK4] = xTaskGetTickCount(); 	
	start_time[TASK4] =  pxTaskData->task_phase;

	while(1)
	{
		task_instance[TASK4]++;

		crude_delay();		
		
		task_update(TASK4, pxTaskData->task_deadline, pxTaskData->task_period);

		if (counter >= LOG_TIME )
		{
			if ( xHandle2 != NULL && eTaskGetState(xHandle2) != eDeleted)
				vTaskSuspend( xHandle2 );
			if ( xHandle3 != NULL && eTaskGetState(xHandle3) != eDeleted)
				vTaskSuspend( xHandle3 );
			if ( xHandle1 != NULL && eTaskGetState(xHandle1) != eDeleted)
				vTaskSuspend( xHandle1 );
			
			vTaskSuspend( xHandle_aper );
            xTaskCreate(task_print, "task_print", 2048, NULL, 3, NULL);

			if ( xHandle4 != NULL && eTaskGetState(xHandle4) != eDeleted)
				vTaskSuspend( xHandle4 );
		}
		task_delay(TASK4, pxTaskData->task_phase, pxTaskData->task_period);
	}
}

// -------------------Print Task ---------------------------
void task_print(void *pvParameters)
{
	printf("  \n");
	printf(" Task log: \n");
	printf("  \n");
	logprint();		//print function
	vTaskSuspend( NULL);
}

// ------------Periodic scheduler task --------------------
void vTaskScheduler(void *pvParameters)
{
 	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	TaskData_t xTaskData1 = { period[TASK1] , phase[TASK1], deadline[TASK1] };		//task input parameters
	TaskData_t xTaskData2 = { period[TASK2] , phase[TASK2], deadline[TASK2] };
	TaskData_t xTaskData3 = { period[TASK3] , phase[TASK3], deadline[TASK3] };
	TaskData_t xTaskData4 = { period[TASK4] , phase[TASK4], deadline[TASK4] };

	//delay for initial task phases
	if(PERIODIC_TASK_COUNT > 0)
	{
		if(phase[TASK1] != 0)
    		vTaskDelayUntil(&xLastWakeTime, phase[TASK1]+1);
    	xTaskCreate(task1, "Task1", 4096, (void *)&xTaskData1, 3, &xHandle1);
	}

 	if(PERIODIC_TASK_COUNT > 1)
	{
		if(phase[TASK2] != 0)
    		vTaskDelayUntil(&xLastWakeTime, (phase[TASK2]-phase[TASK1]));
    	xTaskCreate(task2, "Task2", 4096, (void *)&xTaskData2, 3, &xHandle2);
	}

 	if(PERIODIC_TASK_COUNT > 2)
	{
		if(phase[TASK3] != 0)
    		vTaskDelayUntil(&xLastWakeTime, (phase[TASK3]-phase[TASK2]));
    	xTaskCreate(task3, "Task3", 4096, (void *)&xTaskData3, 3, &xHandle3);
	}

 	if(PERIODIC_TASK_COUNT > 3)
	{
		if(phase[TASK4] != 0)
    		vTaskDelayUntil(&xLastWakeTime, (phase[TASK4]-phase[TASK3]));
    	xTaskCreate(task4, "Task4", 4096, (void *)&xTaskData4, 3, &xHandle4);
	}
    vTaskDelete(NULL);		
}

// -------------------Aperiodic Task ---------------------------
void aperiodic_task(void *pvParameters)
{
  while(1)
  {
       // Crude delay
        for (int iter = 0; iter < DELAY; iter++)
        {
            __asm__ __volatile__("NOP");
        }
  }
}

// ---------------- Task update function ---------------------------
void task_update(uint8_t task_num, uint16_t task_deadline, uint16_t task_period) 
{
	printf(" Periodic Task %u - %u instance\n", task_num+1, task_instance[task_num]);

    end_time[task_num] = xTaskGetTickCount();

    printf(" Periodic Task %u - start time = %lu, end time = %lu \n", task_num, start_time[task_num],end_time[task_num]);

	if((end_time[task_num] - start_time[task_num]) > task_deadline)
	{
		printf(" Time overflow occurred in Task %u, start time = %lu, end time = %lu, deadline = %lu \n", task_num+1, start_time[task_num],
					end_time[task_num],(start_time[task_num] + task_deadline));			//overflow check
	}

	start_time[task_num] =  start_time[task_num] + task_period;			
	upd_deadline[task_num] += task_period; 
}

// ---------------- crude delay function ---------------------------
void crude_delay()
{

	/*
	ets_delay_us(10000);
	ets_delay_us(10000);
	ets_delay_us(10000);
	*/
	
	for(iter = 0; iter < (DELAY/1000); iter++)
	{
		ets_delay_us(1000);
	}
}	

// ---------------- task delay for periodic tasks ---------------------------
void task_delay(uint8_t task_num, uint16_t task_phase, uint16_t task_period) {
	if(task_instance[task_num] == 1)			//if arrival time is delayed, delay adjustment
	{
		if (task_period - (xLastWakeTime[task_num] - task_phase) > 0)
		{
			vTaskDelayUntil( &xLastWakeTime[task_num], task_period -
						(xLastWakeTime[task_num] - task_phase)); }
		else if ( (int) (task_period - (xLastWakeTime[task_num] - task_phase)) < 0) {
			vTaskDelayUntil( &xLastWakeTime[task_num], task_period +
						(xLastWakeTime[task_num] - task_phase)); }
		else
			vTaskDelayUntil( &xLastWakeTime[task_num], task_period);
	}
	else
	{
		vTaskDelayUntil( &xLastWakeTime[task_num], task_period ); 
	}
}