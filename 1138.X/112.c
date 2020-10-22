
#include <pic16f887.h>
#include <xc.h>
#define _XTAL_FREQ 4000000
#define ADC 10
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

void main(void) {
    
    
    //OSCCONbits.SCS=0b00;
    ANSEL =0XFF;
    
    TRISA=1; //ENTRADA
    TRISD=0;
    TRISC=0;
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    ADCON1bits.ADFM=1;
    ADCON0=0b01000001;
    
    while(1)	//ciclo constante
    {
        //ADCON0bits.GO_nDONE=1;
        ADCON0bits.GO_DONE=1;
        while(ADCON0bits.GO_DONE==1);
        PORTD=ADRESL;
        PORTC=ADRESH;
    }
    return;
}
