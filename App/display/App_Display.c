#include "App_Display.h"
#include "Com_Datapool.h"

static uint32_t nowtime;
static char str[100];

void App_Display_Start(void)
{
  initRingBuffer();		// Initialize serial RX ring buffer
	HAL_UART_Receive_IT(&TJC_UART, RxBuffer, 1);	// Enable UART RX interrupt
	nowtime = HAL_GetTick();
	debug_printf("触摸屏初始化完成");

}
void App_Display_Show(void)
{
    if (HAL_GetTick() - nowtime >= 1000)
		{
			nowtime = HAL_GetTick();

			sprintf(str, "page1.adc1_ch0.val=%d", AdcBuf[0]);
			tjc_send_string(str);
			debug_printf("adc1_ch0=%d",AdcBuf[0]);
			
			sprintf(str, "page1.adc1_ch1.val=%d", AdcBuf[1]);
			tjc_send_string(str);
			debug_printf("adc1_ch1=%d",AdcBuf[1]);
		}
}
