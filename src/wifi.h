#ifndef WIFI_H
#define WIFI_H

#define UART_RxD 0x143B
#define UART_TxD 0x133B
#define UART_Sel 0x153B

#define UART_SetBaud UART_RxD
#define UART_GetStatus UART_TxD

#define UART_TX_BUSY 2
#define UART_DATA_READY 1

void uart_init();

int  uart_getc();
void uart_putc(unsigned char c);
void uart_write(char *what);

int wifi_connect(char *host, char *port);

#endif