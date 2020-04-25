
#define BSP_KEY_MODULE

#include <bsp_key.h>

_TouchKey TouchKeyList[_Touchkey_number] = 
{
	{GPIO_ReadInputDataBit, BSP_KEY1_PORT, BSP_KEY1_PIN, Key_Up,   Key_Up,       500,  1, 0, 0},
};

_MultiTouchKey MultiTouchKeyList[_MultiTouchkey_number] = 
{
	{GPIO_ReadInputDataBit, BSP_KEY1_PORT, BSP_KEY1_PIN, GPIO_ReadInputDataBit, BSP_KEY5_PORT, BSP_KEY5_PIN, Key_Show_GUID, Key_SmartConfig, 2000, 0, 0, 0},
};

void BSP_Key_Start(void)
{
    uint8_t i = 0;
    
	for(i = 0;  i< _MultiTouchkey_number; i++)
	{
	   MultiTouchKeyList[i].Key_timer = g_dwTickCnt;
	}

	for(i = 0; i < _Touchkey_number; i++)
	{
	   TouchKeyList[i].Key_timer = g_dwTickCnt;
	}
}

void BSP_Key_Scan(void)
{
    unsigned int temp;
    unsigned char i = 0, j = 0;
    
    if(g_CurrentKey != Key_Null) 
        return;
    
    for(i = 0; i < _MultiTouchkey_number; i++)
    {
        if(    (Bit_RESET == MultiTouchKeyList[i].pkeyread(MultiTouchKeyList[i].portaddress, MultiTouchKeyList[i].portnumber))
            && (Bit_RESET == MultiTouchKeyList[i].pkeyread1(MultiTouchKeyList[i].portaddress1, MultiTouchKeyList[i].portnumber1)))
        {
            for(j = 0; j < _Touchkey_number; j++)
            {
                TouchKeyList[j].Key_timer = g_dwTickCnt;
            }
            
            if((MultiTouchKeyList[i].Key_lock_flag) == 0 || (MultiTouchKeyList[i].repeat_flag == 1))  
            {
                if(MultiTouchKeyList[i].Key_lock_flag)
                {
                    temp = 200;
                }
                else 
                {
                    temp = MultiTouchKeyList[i].longpresstime;
                }
                
                if((g_dwTickCnt - MultiTouchKeyList[i].Key_timer) > temp)
                {
                    g_CurrentKey = MultiTouchKeyList[i].Highkeyvalue;
                    MultiTouchKeyList[i].Key_lock_flag = 1;
                    MultiTouchKeyList[i].Key_timer = g_dwTickCnt;
                }   
            }
            else
            {
                MultiTouchKeyList[i].Key_timer = g_dwTickCnt;
            }
        }
        else 
        {
            if((g_dwTickCnt - MultiTouchKeyList[i].Key_timer) > 100)
            {
                g_CurrentKey = MultiTouchKeyList[i].Lowkeyvalue;
            }
            MultiTouchKeyList[i].Key_lock_flag = 0;
            MultiTouchKeyList[i].Key_timer = g_dwTickCnt;
        } 
    }

    for(i = 0; i < _Touchkey_number; i++)
    {
        if(Bit_RESET == TouchKeyList[i].pkeyread(TouchKeyList[i].portaddress, TouchKeyList[i].portnumber))
        {
            if((TouchKeyList[i].Key_lock_flag == 0) || (TouchKeyList[i].repeat_flag == 1))  
            {
                if(TouchKeyList[i].Key_lock_flag)
                {
                    temp = 200;
                }
                else 
                {
                    temp = TouchKeyList[i].longpresstime;
                }
                
                if((g_dwTickCnt - TouchKeyList[i].Key_timer) > temp)
                {
                    g_CurrentKey = TouchKeyList[i].Highkeyvalue;
                    TouchKeyList[i].Key_lock_flag = 1;
                    TouchKeyList[i].Key_timer = g_dwTickCnt;
                }   
            }
            else
            {
                TouchKeyList[i].Key_timer = g_dwTickCnt;
            }
        }
        else 
        {
            if((g_dwTickCnt - TouchKeyList[i].Key_timer) > 100)
            {
                g_CurrentKey = TouchKeyList[i].Lowkeyvalue;
            }
            TouchKeyList[i].Key_lock_flag = 0;
            TouchKeyList[i].Key_timer = g_dwTickCnt;
        } 
    }
}

void BSP_Key_Handler(void)
{
    uint8_t temp;
    uint8_t buf[4];

    if (g_CurrentKey != Key_Null)
    {
		temp = g_CurrentKey;
		g_CurrentKey = Key_Null;
        
	    switch(temp)
		{
            case Key_Up:
                break;
    }
}

