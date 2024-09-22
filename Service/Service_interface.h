#ifndef SERVICE_INTERFACE_H
#define SERVICE_INTERFACE_H

/**
 * Macros for Schedule_MS condition
 */
#define ONCE		1u
#define periodic	2u

/**
 * @brief Sets the PWM signal parameters for Timer 1 Channel A.
 *
 * This function configures Timer 1 in Fast PWM mode using ICR1 as the top value. It calculates
 * the compare match values for generating a PWM signal based on the provided period and on-time
 * values. The function automatically handles scaling and initialization of the timer with a prescaler
 * of 8. The PWM signal is generated with a resolution of 2000 ticks per millisecond.
 *
 * @param[in] Copy_u16PeriodTime_MS The desired period time of the PWM signal in milliseconds.
 * @param[in] Copy_u16OnTime_MS The desired on-time (high time) of the PWM signal in milliseconds.
 *
 * This function works directly for periods less than or equal to 32ms (due to the timer overflow limit).
 * For longer periods, overflow handling would be necessary, but this version assumes the period
 * and on-time are within the range.
 *
 * Example usage:
 * @code
 * PWM_voidSet(20, 10); // Set a 20ms period and 10ms on-time for a 50% duty cycle
 * @endcode
 */
void PWM_voidSet(uint16 Copy_u16PeriodTime_MS , uint16 Copy_u16OnTime_MS);

/**
 * @brief Measure the period and on-time of a PWM signal.
 *
 * This function initializes Timer1 in normal mode with input capture functionality to measure the
 * period and on-time of a PWM signal in microseconds. The function sets up an interrupt service
 * routine to capture the rising and falling edges of the PWM signal.
 *
 * @param[out] Copy_pu16PeriodTime_MS Pointer to store the measured period time in microseconds.
 * @param[out] Copy_pu16OnTime_MS Pointer to store the measured on-time in microseconds.
 *
 * @return uint8 Returns error state: OK if the measurement is successful, or NULL_PTR_ERR if any input pointer is NULL.
 */
uint8 PWM_u8Get(uint16* Copy_pu16PeriodTime_MS , uint16* Copy_pu16OnTime_MS);

/**
 * @brief Schedules a task to run after a specified delay in milliseconds.
 *
 * This function sets up Timer0 in CTC mode with a compare match interrupt to execute a user-defined task
 * after a specified time in milliseconds. The task can be scheduled to run once or periodically.
 *
 * @param[in] Copy_u16Time_MS The delay time in milliseconds before the task is executed.
 * @param[in] Copy_u8Condition Condition specifying if the task is one-time or periodic.
 *             Use 'periodic' for repeated execution or 'one_time' for single execution.
 * @param[in] Copy_pvPtrFunc Pointer to the function to be executed when the time expires.
 *
 * @return uint8 Returns error state: OK if the task is scheduled successfully, or NULL_PTR_ERR if the function pointer is NULL.
 */
uint8 Schedule_MS(uint16 Copy_u16Time_MS , uint8 Copy_u8Condition ,  void(*Copy_pvPtrFunc)(void));

#endif
