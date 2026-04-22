#include "Com_Debug.h"
 
UART_RxTypeDef Uart1Rx = {{0}, 0, 0};  // 为UART1初始化结构体
 
// 重定向c库函数printf到huart1
int fputc(int ch, FILE *f) {
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
  return ch;
}
