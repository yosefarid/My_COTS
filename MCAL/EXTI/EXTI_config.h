#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H

/*configure the sense ctrl options for INT0 channel, Options:
 * 																1- EXTI_LOW_LEVEL
 * 																2- EXTI_ON_CHANGE
 * 																3- EXTI_FALLING_EDGE
 * 																4- EXTI_RISING_EDGE
 * 	*/
#define INT0_SENSE_CTRL											EXTI_FALLING_EDGE


/*configure the sense ctrl options for INT1 channel, Options:
 * 																1- EXTI_LOW_LEVEL
 * 																2- EXTI_ON_CHANGE
 * 																3- EXTI_FALLING_EDGE
 * 																4- EXTI_RISING_EDGE
 * 	*/
#define INT1_SENSE_CTRL											EXTI_FALLING_EDGE


/*configure the sense ctrl options for INT2 channel, Options:
 * 																1- EXTI_FALLING_EDGE
 * 																2- EXTI_RISING_EDGE
 * 	*/
#define INT2_SENSE_CTRL											EXTI_FALLING_EDGE


/*configure the initial state options for INT0 channel, Options:
 * 																1- ENABLED
 * 																2- DISABLED
 * 	*/
#define INT0_INIT_STATE											ENABLED


/*configure the initial state options for INT1 channel, Options:
 * 																1- ENABLED
 * 																2- DISABLED
 * 	*/
#define INT1_INIT_STATE											ENABLED


/*configure the initial state options for INT2 channel, Options:
 * 																1- ENABLED
 * 																2- DISABLED
 * 	*/
#define INT2_INIT_STATE											DISABLED

#endif
