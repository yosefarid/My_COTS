#ifndef WDT_REGISTER_H
#define WDT_REGISTER_H

#define WDTCR			*((volatile uint8*)0x41)
#define WDTCR_WDTOE		4u
#define WDTCR_WDE		3u

#endif