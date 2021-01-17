#include "wifi.h"

#include <stdlib.h>
#include <stdio.h>

void uart_init()
{
    __asm
    ld hl, table
    ld bc, 9275
    ld a, 17
    out (c),a
    ld bc, 9531
    in a,(c)	
    ld e,a
    rlc e		
    ld d, 0 
    add hl,de

    ld e, (hl)
    inc hl
    ld d, (hl)
    ex de, hl
    
    ld bc, UART_Sel
    ld a, $20 
    out (c), a

    ld bc, UART_SetBaud
    ld a, l
    AND $7f	
    out (c), a
    ld a, h
    rl l		
    rla		
    or $80	
    out (c), a
    jr exit
table:
    defw 243,248,256,260,269,278,286,234
exit:
    __endasm;
}

int uart_getc()
{
    if ((inp(UART_GetStatus) & UART_DATA_READY) == 0) return -1;

    return inp(UART_RxD);
}

int uart_readb()
{
    char c = -1;
    while(c == -1) {
        if (getk() == 17) 
            return -1;

        c=uart_getc();
    }

    return c;
}

void uart_putc(unsigned char c)
{
    while ((inp(UART_GetStatus) & UART_TX_BUSY) != 0);

    outp(UART_TxD, c);
}

void uart_write(char *what)
{
    char c;
    for (c=0;what[c]!=0;c++)
        uart_putc(what[c]);
}

int ok_err_cmd(char *cmd)
{
    char c;
    uart_write(cmd);

    uart_putc(13);
    uart_putc(10);

    while(1) {
        c = uart_readb();
        
        if (c == -1) return 0;

        if (c == 'O') 
            if (uart_readb() == 'K') {
                while (uart_readb() != 10);
                return 1;
            }

        if (c == 'E')
            if (uart_readb() == 'R')
                if (uart_readb() == 'R') {
                    while (uart_readb() != 10);
                    return 0;
                }
        
                if (c == 'E')

        if (uart_readb() == 'F')
            if (uart_readb() == 'A')
                if (uart_readb() == 'I')  {
                while (uart_readb() != 10);
                return 0;
            }
    }
}

int wifi_connect(char *host, char *port) {
    char connstring[256];
    char c;

    if (ok_err_cmd("AT+CIPMUX=0") && ok_err_cmd("AT+CIPMODE=1")) {
        printf("\r\nWifi inited\r\n");
    } else {
        printf("\r\nWifi init error!\r\n");
        
        return 0;
    }
    sprintf(connstring, "AT+CIPSTART=\"TCP\",\"%s\",%s", host, port);

    if (!ok_err_cmd(connstring)) {
        printf("\r\nCan't connect to %s:%s\r\n", host,port);
        
        return 0;
    }

    uart_write("AT+CIPSEND\r\n");

    return 1;
}