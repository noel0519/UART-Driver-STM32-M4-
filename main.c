#include<stdint.h>
#include<stdio.h>
#include "main.h"



void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);


uint32_t current_task = 0;

void enable_processor_faults();

void init_systick_timer(uint32_t tick_hz);
__attribute__ ((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack);

void init_tasks_stack(void);

void update_next_task(void);

__attribute__((naked)) void switch_sp_to_psp();

uint32_t pSP_of_tasks[MAX_TASKS] = {T1_STACK_START,T2_STACK_START,T3_STACK_START,T4_STACK_START};

uint32_t task_handlers[MAX_TASKS];

int main(){

	enable_processor_faults();

	init_scheduler_stack(SCHED_STACK_START);

	task_handlers[0] = (uint32_t)task1_handler;
	task_handlers[1] = (uint32_t)task2_handler;
	task_handlers[2] = (uint32_t)task3_handler;
	task_handlers[3] = (uint32_t)task4_handler;



	init_tasks_stack();

	init_systick_timer(TICK_HZ);
    switch_sp_to_psp();

    task1_handler();
	for(;;);
}

void task1_handler(void){
	while(1){
		printf("Task1");
	}
}

void task2_handler(void){
	while(1){
		printf("Task2");
	}
}

void task3_handler(void){
	while(1){
		printf("Task3");
	}
}

void task4_handler(void){
	while(1){
		printf("Task4");
	}
}


void init_systick_timer(uint32_t tick_hz){

	uint32_t *psRVR = (uint32_t *)0xE000E014;
	uint32_t *psCSR = (uint32_t *)0xE000E010;


	uint32_t count_value = SYSTICK_TIM_CLK/tick_hz - 1;

	*psRVR &= ~(0x00FFFFFFFF);


	*psRVR |= count_value;

	*psCSR |= (1 << 1); //Enables Systick exceptin request
	*psCSR |= (1 << 2);
	*psCSR |= (1 << 0);
}

__attribute__((naked)) void init_scheduler_stack(uint32_t sched_top_of_stack){

	__asm volatile("MSR MSP , %0": :"r"(sched_top_of_stack) : );
	__asm volatile("BX LR");

}



void init_tasks_stack(void){

	uint32_t *pPSP;

	for(int i =0; i < MAX_TASKS; i++){

		pPSP = (uint32_t *) pSP_of_tasks[i];
		pPSP--;
		*pPSP = DUMMY_XPSR;

		pPSP--;
	    *pPSP = task_handlers[i];


	    pPSP--;
	    *pPSP = 0xFFFFFFFD;

	    for(int j = 0; j<13;j++){
	    	pPSP--;
	        *pPSP = 0 ;

	    }

	    pSP_of_tasks[i]  = (uint32_t)pPSP;










	}

}

void enable_processor_faults(){

	uint32_t *pSHCSR = (uint32_t*)0xE000ED24;

	*pSHCSR |= (1<<16);
	*pSHCSR |= (1<<17);
	*pSHCSR |= (1<<18);


}

uint32_t get_psp_value(){

	return pSP_of_tasks[current_task];

}


void save_psp_value(uint32_t current_stack_addr){
	pSP_of_tasks[current_task] = current_stack_addr;
}

void update_next_task(void){

	current_task++;
	current_task %= MAX_TASKS;
}


__attribute__((naked)) void switch_sp_to_psp(){


	__asm volatile("PUSH {LR}");
	__asm volatile("BL get_psp_value");

	__asm volatile("MSR PSP,R0");
	__asm volatile("POP {LR}");

	__asm volatile("MOV R0,#0X02");
	__asm volatile("MSR CONTROL,R0");

	__asm volatile("ISB");
	__asm volatile("BX LR");

}

__attribute__((naked)) void SysTick_Handler(void){

	__asm volatile("MRS R0,PSP");
	__asm volatile("STMDB R0! , {R4-R11}");
	__asm volatile("BL save_psp_value");

	__asm volatile("BL update_next_task");

	__asm volatile("PUSH {LR}");

	__asm volatile("BL get_psp_value");

	__asm volatile("LDMIA R0!, {R4-R11}");


	__asm volatile("MSR PSP,R0");

	__asm volatile("POP {LR}");

	__asm volatile("BX LR");

}

void HardFault_Handler(void)
{
	printf("Hard fault \n");
    while (1)
    {

    }
}

void MemManage_Handler(void)
{
	printf("MemManage fault \n");
    while (1)
    {

    }
}


void BusFault_Handler(void)
{
	printf("Bus fault \n");
    while (1)
    {

    }
}
