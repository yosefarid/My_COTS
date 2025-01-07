#ifndef KERNEL_PRIVATE_H
#define KERNEL_PRIVATE_H

typedef struct
{
	uint16 Periodicity;
	void(*TaskHandler)(void);
}TASK_t;

#endif