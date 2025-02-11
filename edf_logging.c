#include "include/edf_logging.h"

uint8_t task_log[LOG_TIME];
uint32_t user_usec_sout[100][2];
uint32_t user_usec_sin[100][2];

// -------------------Log Print function ---------------------------
void logprint(void)
{
	//ESP_LOGI("TASK_PRINT", "index, Tickcount , Tasks \n");
	printf("Tickcount, Tasks \n");

	for (iter = 0; iter <= LOG_TIME ; iter++)
	{
		if(task_log[iter] == 0)	
		{
			//ESP_LOGI("TASK_PRINT", "%lu, %lu, Idle \n", iter, iter);
			printf("%lu, Idle \n",iter);
		}			
			
		else if(task_log[iter] == 6)
		{
			//ESP_LOGI("TASK_PRINT", "%lu, %lu, Aper \n", iter, iter);
			printf("%lu, Aper \n",iter);
		}
			
		else
		{
			//ESP_LOGI("TASK_PRINT", "%lu, %lu, %u \n", iter, iter, task_log[iter]);
			printf("%lu, %u\n",iter,task_log[iter]);
		}
			
	}
}

// ---------Switched IN trace macro log function ---------------
void sin_log(void)
{
	user_usec_sin[event_sin][0] = current_task_sin;
	user_usec_sin[event_sin][1] = (esp_timer_get_time()/1000);
	event_sin++;
}

// ---------Switched OUT trace macro log function ---------------
void sout_log(void)
{
	user_usec_sout[event_sout][0] = current_task_sout;
	user_usec_sout[event_sout][1] = (esp_timer_get_time()/1000);
	event_sout++;
}