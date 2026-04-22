#ifndef __COM_DEBUG_H
#define __COM_DEBUG_H

#include "usart.h"
#include "string.h"
#include "stdio.h"

#define debug_printf printf

 
#define RX_BUFFER_SIZE 256
 
typedef struct {
    uint8_t RxBuffer[RX_BUFFER_SIZE];
    uint8_t RxData;
    uint16_t RxDataCnt;
}UART_RxTypeDef;
 
extern UART_RxTypeDef Uart1Rx;   // 为UART1声明外部结构体变量
 

#endif
