#include <io.h>
#include <delay.h>
#include <stdio.h>
#include <lcd.h>
#asm
.equ __lcd_port=0x1B  //PORTA
#endasm
//한바이트 통신

/*void putch(char data){
    //while(!(UCSR0A & 0x20));
    UDR0 = data;
}*/

/*char Getch(void){
    while(!(UCSR0A & 0x80));
    return UDR0;
}*/
void main(void){    
    
    lcd_init(16);
    lcd_gotoxy(1,0);
    lcd_puts("test USART0");
    
    EICRA = 0b00000010;
    EIMSK = 0b00000001;
    SREG = 0x80;
    
    UCSR0A = 0x00;
    UCSR0B = 0x10011000; //TXEN = 1, RXEN = 1
    UCSR0C = 0b00000110;
    UBRR0H = 0x00;
    UBRR0L = 103;
    
    lcd_gotoxy(0,1);
    
    while(1);
}
interrupt[USART0_RXC]void receive(void) {
    unsigned char ch;
    ch = UDR0;    
    lcd_gotoxy(0, 1);
    //lcd_puts("FUCK");
    lcd_putchar(ch);
}

interrupt[EXT_INT0]void ext_int0(void) { 
   if(!(UCSR0A & 0x80))
    UDR0 = 'B';       
}
