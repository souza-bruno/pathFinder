#ifndef AGV_H_DEFINED
#define AGV_H_DEFINED

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f4xx_hal.h"

    void Error_Handler(void);

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

#ifdef __cplusplus
}
#endif

typedef enum
{
    AVG_OK = 0,
    AVG_ERROR,
} AVG_StatusTypedef;

//initAVG initializes all peripherals and low level stuff
void InitAVG(void);
//turnAngle will simply turn the avg the specified angle (in radians).
void TurnAngle(float radians);
//turnAngleGrap will turn the avg and look for a guide line inside the interval specified by
//(´radians´ - ´searchAngle´, ´radians´ + ´searchAngle´). Returns false if no guide line was found
//inside the interval, in which case the avg will make sure to turn exactly radians before returning
AVG_StatusTypedef TurnAngleGrab(float radians, float searchAngle);
//turn lines will spin while counting how many lines crossed the sensors, stoping once ´lines´ is
//reached. Returns false once a full rotation is completed but couldn't find sufficient guide lines,
//in which case the avg makes sure to stop at the initial angle
AVG_StatusTypedef TurnLines(int lines);
//followLine will attempt to follow the line that's currently between the sensors, returning true once
//a crossing has been reached. Return false means it was not possible to follow the path to its end,
//meaning the path is blocked. By default once a crossing is reached the agv will attempt to position
//itself right above the crossing by advancing the distance specified in `alignDistance`
AVG_StatusTypedef FollowLine();
//hardForward will attempt to advance the specified distance. If the path is block it'll wait until
//it's unblocked to be able to clear the specified distance
void HardForward(float distance);

#endif