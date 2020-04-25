
#ifndef  BSP_KEY_PRESENT
#define  BSP_KEY_PRESENT

#ifdef   BSP_KEY_MODULE
#define  BSP_KEY_EXT
#else
#define  BSP_KEY_EXT  extern
#endif

#define BSP_KEY1_RCC                    RCC_AHB1Periph_GPIOE
#define BSP_KEY1_PORT                   GPIOE
#define BSP_KEY1_PIN                    GPIO_Pin_7

typedef enum
{
	Key_Null = 0,
    Key_Up,
    Key_CF,
}KEY_VALUE_E;

#define _Touchkey_number                8

typedef struct
{
    uint8_t (*pkeyread)(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
    GPIO_TypeDef *      portaddress;
    uint16_t            portnumber;
    const unsigned char Lowkeyvalue;
    const unsigned char Highkeyvalue;
    const unsigned long longpresstime;
    const unsigned char repeat_flag;
    unsigned char       Key_lock_flag;
    unsigned long       Key_timer;
}_TouchKey;

typedef struct
{
    uint8_t (*pkeyread1)(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
    GPIO_TypeDef *      portaddress1;
    uint16_t            portnumber1;

    uint8_t (*pkeyread2)(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
    GPIO_TypeDef *      portaddress2;
    uint16_t            portnumber2;

    const unsigned char Lowkeyvalue;
    const unsigned char Highkeyvalue;
    const unsigned long longpresstime;
    const unsigned char repeat_flag;
    unsigned char       Key_lock_flag;
    unsigned long       Key_timer;
}_MultiTouchKey;

#define _MultiTouchkey_number 3

BSP_KEY_EXT unsigned char g_CurrentKey;

#endif

