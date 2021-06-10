/*
 * File:   main.c
 * Author: Diego Avellaneda Torres
 *
 * Created on 5 de mayo de 2021, 20:47
 */
// PIC12F675 Configuration Bit Settings

// CONFIG
//#pragma config FOSC = LP        // Oscillator Selection bits (LP oscillator: Low power crystal on GP4/OSC2/CLKOUT and GP5/OSC1/CLKIN)
#pragma config FOSC = INTRCCLK  // Oscillator Selection bits (INTOSC oscillator: CLKOUT function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // GP3/MCLR pin function select (GP3/MCLR pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
# define _XTAL_FREQ 4000000
//# define _XTAL_FREQ 32000
int count=0;
//Defino una funcion para cuando suceda la interrupcion. 
void __interrupt() isr(){
    //Cuando el timmer overflow enra en el if
    //if(INTCONbits.TMR0IF){
      //  INTCONbits.TMR0IF=0;// Vuelvo a bajar la bandera.
        //count++;
        //if(count==5){
            //GP0=~GP0;
        //}
        //GP0=1;
        //__delay_ms(2000);
        //GP0=0;
    //}

    if( PIR1bits.TMR1IF){
        
        PIR1bits.TMR1IF=0;
        count++;
        if(count==5){
        GP0=1;
        __delay_ms(2000);
        GP0=0;
        count=0;
        }
       

    
    }
    
}


void main() {
    INTCON=0x00;
    T1CON=0x00;//Limpiar el t1
    PIE1=0x00; // Limpiar el registro
    //Definir el Pin GPIO 0 como salida 
    
    TRISIO0=0;
    GP0=0;
    
    //Registro INTCON para el manejo de las interrupciones 
    INTCONbits.GIE=1;// habilitar las interrupciones Globales
    INTCONbits.PEIE=1;// Habilitar las interrupciones perifericas. 
    
    GP0=1;
    __delay_ms(2000);
    GP0=0;
    
    //INTCONbits.TMR0IE=1;//Enable timeer interrupt
    //INTCONbits.TMR0IF=0;// Clear timer overflow flag
    
    //OPTION_REGbits.T0CS=0;//internal instruction clycle clock
    //OPTION_REGbits.T0SE=0;//edge seleccion
    
    //OPTION_REGbits.PSA=0;//prescaler assigned to timer 0 
    //Colocamos el preescaler para 1:256
    //OPTION_REGbits.PS0=1;
    //OPTION_REGbits.PS1=1;
    //OPTION_REGbits.PS2=1;
    
    //SLEEP();
    
    // ---------------------Todo lo de arriba aplica para el timer 0 ----------------------------------
    // ---------------------TIMER1 ----------------------------------

    T1CONbits.TMR1ON=1;//Enable timer
    PIE1bits.TMR1IE=1;/// activar el PIE
    PIR1bits.TMR1IF=0;
    TMR1H=0x22;
    TMR1L=0x00;
    //T1CONbits.TMR1CS=0;// Cuenta los pulsos del oscilador interno
    //T1CONbits.T1CKPS1=T1CONbits.T1CKPS0=1;
    //T1CONbits.T1OSCEN=1;// LP oscilator enable
    //T1CONbits.nT1SYNC=1;
    //SLEEP();
    while(1);
    
    //return;
}
