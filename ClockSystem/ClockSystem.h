#ifndef CLOCKSYSTEM_CLOCKSYSTEM_H_
#define CLOCKSYSTEM_CLOCKSYSTEM_H_

extern int twoMinuteFlag;
extern int twoSecondFlag;
extern int tenSecondFlag;
extern int updateHeader;

void Setup_Clocks(void);
void SysTick_Init(void);
void SysTick_delay(uint32_t delay_ms);
void Timer32_Init(void);
void T32_INT1_IRQHandler(void);

#endif /* CLOCKSYSTEM_CLOCKSYSTEM_H_ */
