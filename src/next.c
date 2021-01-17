#include <stdlib.h>
#include <stdio.h>
#include "wifi.h"

void nextreg(char addr, char value) 
{
    outp(9275, addr);
    outp(9531, value);
}

void reset_esp()
{
    int k;
    printf("\r\nFlushing uart\r\n");
    nextreg(2, 128);

    for (k=0;k<100;k++) {
        __asm
        halt
        __endasm;
    } 

    nextreg(2, 0);
    
    for (k=0;k<100;k++) {
        __asm
        halt
        __endasm;
    } 


    for (k=0;k<12345;k++) uart_getc();

}