#include "include/edf_sorting.h"

Task tasks_sorted[PERIODIC_TASK_COUNT];

// --------compare function used in qsort (quick_sort)--------------
int compare_tasks(const void *a, const void *b) {
    const Task *task_a = (const Task *)a;
    const Task *task_b = (const Task *)b;

    return task_a->sorting_task_deadline - task_b->sorting_task_deadline;
}

//-----task deadline sorting and new priority assignment function------
void ComputeTaskPriority()
{
    //deadline assignment
	for(iter = 0; iter < PERIODIC_TASK_COUNT; iter++)
	{
		tasks_sorted[iter].sorting_task_num = iter + 1;  
		tasks_sorted[iter].sorting_task_deadline = upd_deadline[iter];
	}

    size_t num_tasks = sizeof(tasks_sorted) / sizeof(tasks_sorted[0]);

    //deadline sorting with quicksort algorithm
    qsort(tasks_sorted, num_tasks, sizeof(Task), compare_tasks);

	//Earliest deadline task assigned highest priority 6
	if( tasks_sorted[0].sorting_task_num == 1 )
		vTaskPrioritySet( xHandle1, 6);
	else if( tasks_sorted[0].sorting_task_num == 2 )
		vTaskPrioritySet( xHandle2, 6);
	else if( tasks_sorted[0].sorting_task_num == 3 && PERIODIC_TASK_COUNT > 2 )
		vTaskPrioritySet( xHandle3, 6);
	else if( tasks_sorted[0].sorting_task_num == 4 && PERIODIC_TASK_COUNT > 3 )
		vTaskPrioritySet( xHandle4, 6);

	//Second Earliest deadline task assigned second highest priority 5
	if( tasks_sorted[1].sorting_task_num == 1 )
		vTaskPrioritySet( xHandle1, 5);
	else if( tasks_sorted[1].sorting_task_num == 2 )
		vTaskPrioritySet( xHandle2, 5);
	else if( tasks_sorted[1].sorting_task_num == 3 && PERIODIC_TASK_COUNT > 2)
		vTaskPrioritySet( xHandle3, 5);
	else if( tasks_sorted[1].sorting_task_num == 4 && PERIODIC_TASK_COUNT > 3)
		vTaskPrioritySet( xHandle4, 5);

	//Third Earliest deadline task assigned third highest priority 4
	if( tasks_sorted[2].sorting_task_num == 1 && PERIODIC_TASK_COUNT > 2)
		vTaskPrioritySet( xHandle1, 4);
	else if( tasks_sorted[2].sorting_task_num == 2 && PERIODIC_TASK_COUNT > 2)
		vTaskPrioritySet( xHandle2, 4);
	else if( tasks_sorted[2].sorting_task_num == 3 && PERIODIC_TASK_COUNT > 2)
		vTaskPrioritySet( xHandle3, 4);
	else if( tasks_sorted[2].sorting_task_num == 4 && PERIODIC_TASK_COUNT > 3)
		vTaskPrioritySet( xHandle4, 4);

	//Longest deadline task assigned least priority 3
	if( tasks_sorted[3].sorting_task_num == 1 && PERIODIC_TASK_COUNT > 3 )
		vTaskPrioritySet( xHandle1, 3);
	else if( tasks_sorted[3].sorting_task_num == 2  && PERIODIC_TASK_COUNT > 3)
		vTaskPrioritySet( xHandle2, 3);
	else if( tasks_sorted[3].sorting_task_num == 3 && PERIODIC_TASK_COUNT > 3)
		vTaskPrioritySet( xHandle3, 3);
	else if( tasks_sorted[3].sorting_task_num == 4 && PERIODIC_TASK_COUNT > 3)
		vTaskPrioritySet( xHandle4, 3);
}