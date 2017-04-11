/*************************************
*2017/04/12                          *
*Multiplexer Counter                 *
**************************************
*Used IC                             *
-------------------------------------*
*decoder/demultiplexer - 74HC139     *
*octal transparent latch = 74LS373   *
*not gate - 74LS04P                  *
-------------------------------------*
**************************************/

#include <io.h>
#include <delay.h>
unsigned char FND[] = {0xc0,0xf9,0xa4,0x30,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char LEDL=0x01;
unsigned char LEDR=0x80;
void out(char addr, char data){
    PORTE = addr;
    PORTA = data;
    PORTE &= 0xfb;
    PORTE |= 0x04;
}

void main(void){
    int a;
    int b =0;
    DDRA = 0xff;
    DDRE = 0xff;
    while(1){
        for(a=0;a<7;a++)
        {
            out(0x00, LEDL<<a);
            delay_ms(500);
        }
        //When seven LEDs Turn on
        out(0x01, FND[b]);
        //FND count
        b++;
        delay_ms(500);
    }
}
