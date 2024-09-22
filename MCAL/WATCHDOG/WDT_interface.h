#ifndef WDT_INTERFACE_H
#define WDT_INTERFACE_H

#define Time_16_3_MS		0u
#define Time_32_5_MS        1u
#define Time_65_MS          2u
#define Time_0_13_S         3u
#define Time_0_26_S         4u
#define Time_0_52_S         5u
#define Time_1_S            6u
#define Time_2_1_S          7u

void WDT_voidSetTime(uint8 Copy_u8Time);

void WDT_voidEnable(void);

void WDT_voidDisable(void);

void WDT_voidReset(void);

#endif