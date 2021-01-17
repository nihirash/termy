
#pragma output noprotectmsdos
#pragma output nofileio

#include "wifi.h"
#include "next.h"
#include <stdlib.h>
#include <stdio.h>

void main(int argc, char *argv[])
{
    if (argc < 3) {
        printf("Usage:\n%s host port\n", argv[0]);
        
        return;
    }

    int c, k;
    uart_init();
    printf("Uart inited\r\n");
    printf("CTRL-Q for exit\r\n");

    if (wifi_connect(argv[1], argv[2]))
        for (;k!=17;) {
            for (c = uart_getc(); c != -1 ; c = uart_getc()) 
                if (c != -1) printf("%c", c);
            
            k = getk();
            if (k) {
                uart_putc(k);
                if (k==13) 
                    uart_putc(10);
                while(getk() == k);
            }
        }
    reset_esp();
    
    return ;
}

