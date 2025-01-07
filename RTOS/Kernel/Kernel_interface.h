#ifndef KERNEL_INTERFACE_H
#define KERNEL_INTERFACE_H

uint8 Kernel_u8CreateTask(uint8 Copy_u8Priority , uint16 Copy_u16Priodicity , void(*Copy_pvTaskHandler)(void));

void Kernel_voidStartSchduler(void);

#endif