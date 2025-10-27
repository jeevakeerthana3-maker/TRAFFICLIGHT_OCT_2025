/*
 * File:   TRAFFIC_LIGHT.c
 * Author: SINGAPORE
 *
 * Created on October 10, 2025, 12:29 PM
 */
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
int count=0;
void delay(long unsigned int t)
{
    while(t--);
}
void enable()
{
    RE1=1;
    delay(1000);
    RE1=0;
    delay(1000);
}
void lcd(char rs,char data)
{
  RE0=rs;
  PORTD=data;
  enable();
  
}
void string(char *ptr)
{
  while(*ptr)
  {
      lcd(1,*ptr++);
  }
}
void timer(float limit)
{
    count=0;
   while(count<2 *limit)
   {
       if(TMR1IF==1)
       {
           count++;
           TMR1=3035;
           TMR1IF=0;
       }
    
   }
      
}
void main(void)
{
    PORTA=PORTB=PORTC=PORTD=PORTE=0X00;
    TRISA=TRISB=TRISC=TRISD=TRISE=ANSEL=ANSELH=0X00;
    T1CON=0X31;
    TMR1=3035;
    int i,a,b;
    int arr[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
    lcd(0,0X38);
    lcd(0,0X0E);
    while(1)
    {
        RB0=1;
        string("Stop");
        for(i=10;i>0;i--)
        {
            a=i/10;
            b=i%10;
        RA4=0;RA5=1;
        PORTC=arr[a];
        timer(0.5);
        RA5=0;RA4=1;
        PORTC=arr[b];
        timer(0.5);
        }
        
        RB0=0;
        lcd(0,0X01);
 
         RB1=1;
         string("Go");
          for(i=10;i>0;i--)
          {
              
              a=i/10;
              b=i%10;
        RA4=0; RA5=1;
        PORTC=arr[a];
        timer(0.5);
        RA5=0; RA4=1;
        PORTC=arr[b];
        timer(0.5);
         }
         
         RB1=0;
         lcd(0,0X01);
          RB2=1;
         string("Wait");
        for(i=5;i>0;i--)
        {
            
            a=i/10;
            b=i%10;
        RA4=0;RA5=1;
        PORTC=arr[a];
        timer(0.5);
        RA5=0;RA4=1;
        PORTC=arr[b];
        timer(0.5);
        }
         RB2=0;
         lcd(0,0X01);
        } 
   
    return;

}

