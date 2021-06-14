/*
 * File:   newmain.c
 * Author: Diego Avellaneda
 *
 * Created on 14 de junio de 2021, 15:09
 */


#pragma config FOSC = LP       // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-Up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF       // GP3/MCLR pin function select (GP3/MCLR pin function is MCLR)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#include <xc.h>

# define _XTAL_FREQ 4000000

int count=0;

void __interrupt() isr(){

    if( PIR1bits.TMR1IF){
        
        
        count++;
        if(count==5){
        //T1CONbits.TMR1ON=0;//Disable timer
        GP0=1;
        __delay_ms(2000);
        GP0=0;
        count=0;
        
        PIR1bits.TMR1IF=0;
        //T1CONbits.TMR1ON=1;//Enable timer
        SLEEP();
        
        }
    

    
    }
    
}

void main(void) {
    
    // ---------------------Registros limpios ----------------------------------
    
    INTCON=0x00;
    T1CON=0x00;//Limpiar el t1
    PIE1=0x00; // Limpiar el registro
    
    // ---------------------Definir los registros ----------------------------------
    
    //Registro INTCON para el manejo de las interrupciones 
    INTCONbits.GIE=1;// habilitar las interrupciones Globales
    INTCONbits.PEIE=1;// Habilitar las interrupciones perifericas. 
     // ---------------------Comparators off ----------------------------------
    //CMCONbits.CM0=1;
    //CMCONbits.CM1=1;
    //CMCONbits.CM2=1;
    
    // ---------------------GPIO ----------------------------------
    //TRISIO=0x00;
    TRISIO0=0;//Puerto como salida
    
    TRISIObits.TRISIO4=0;// como entrada digital
    TRISIObits.TRISIO5=0;//como entrada digital 
    ANSEL=0x00;
    CMCON=0x07;
    
    
    T1CONbits.TMR1ON=1;//Enable timer
    PIE1bits.TMR1IE=1;/// activar el PIE
    PIR1bits.TMR1IF=0;
    GP0=0;
    
    T1CONbits.T1OSCEN=1;// LP oscilator enable
    
    T1CONbits.T1CKPS1=T1CONbits.T1CKPS0=1;
    T1CONbits.TMR1CS=1;// 1 External 0 Internal ESTO ES LO QUE GENERA CONFLICTO EN 1
    
    T1CONbits.nT1SYNC=1;// 1 No sincronizar con externo 0 si sincronizar con externo
    
   
   
    
    SLEEP();
    while(1);
    
    //return;
}
