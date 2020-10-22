PROCESSOR 16F887                    //Selecion de nuestro pic a utilizar
    #include <xc.inc>
   
    CONFIG FOSC=INTRC_NOCLKOUT        //Configuracion de nuestros fuses
    CONFIG WDTE=OFF
    CONFIG PWRTE=ON
    CONFIG MCLRE=ON
    CONFIG CP=OFF
    CONFIG CPD=OFF
    CONFIG BOREN=OFF
    CONFIG IESO=OFF
    CONFIG FCMEN=OFF
    CONFIG LVP=OFF
    CONFIG DEBUG=ON
     
    CONFIG BOR4V=BOR40V          
    CONFIG WRT=OFF

PSECT resetVec,class=CODE,delta=2           //Nuestra seccion de reset hubicada en la direccion 0h
resetVec:
goto main

PSECT code                               //seccion de codigo de nuestro delay como son solamente microsegundos se opto por uno sencillo
 delay:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    return
        
PSECT main,class=CODE,delta=2        //Seccion principal del codigo hubicada en la direccion 20h
main:   
     BANKSEL OSCCON             //Configuracion de los registros correspondientes         
    MOVLW 0X64
    MOVWF OSCCON
BANKSEL ANSEL
   movlw 0xFF
   movwf ANSEL
   BANKSEL PORTD
   CLRF PORTA
   CLRF PORTD
   clrf PORTC
   BANKSEL TRISA
   movlw  0xFF
   movwf TRISA
   CLRF TRISD
   clrf TRISC
   BANKSEL ADCON0                   //Activacion del modulo ADC
   MOVLW 0b01000001
   movwf ADCON0
   BANKSEL ADCON1
   movlw 0b10000000
   movwf ADCON1
   loop:
   call delay
   BANKSEL ADCON0
   BSF ADCON0,1	                 
   C:
   BTFSC ADCON0,1                   //Verificacion de finalizaion de la conversion ADC
   goto C
   BANKSEL ADRESH                 
   BANKSEL ADRESL
   MOVF ADRESL,0                
   BANKSEL PORTD
   movwf PORTD                     //Los resultados de nuestra conversion son mandados al puerto d para poder visualizar dicha conversion
   goto loop
  
END