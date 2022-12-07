/*
 * File:   main.c
 * Author: Joaquin Allione
 *
 * Created on 21 de noviembre de 2022, 00:37
 */


#include "config.h"
#include <stdint.h>
#include <math.h>
#include "ADC.h"
#include "TIMER.h"
#include "DISPLAY.h"

uint16_t ADC_Value = 0;

#define pi 3.141592
#define RC 5 //pal. por Seg.   (rapidez de conversion)
#define Tconv 1000/RC //mSeg.  (tiempo de conversion)

void main(void) {
    
    //para el DISPLAY
    DISPLAY_Init();
    
    //para el SIGNO
    TRISBbits.TRISB0 = 1; //pin como entrada
    
    TRISBbits.TRISB2 = 0; //pin como salida (indicador de signo de phi)
    PORTBbits.RB2 = 0;
    
    TRISBbits.TRISB1 = 0; //pin como salida (indicador de signo de phi)
    PORTBbits.RB1 = 0;
    
    //para el ADC
    ADC_Config();
    
    //para el TIMER1
    TIMER1_Config();
    
    ADC_StartConv();
    
    while(1){
        DISPLAY_SetNumber(round((50*pi*ADC_Value)/1023.0));
    }
}

int t = 0;

void __interrupt() ADC_TIMER1_ISR(void){
    
    if(PIR1bits.ADIF == 1){
        PIR1bits.ADIF = 0; //limpia la flag
        ADC_Value = ADRESH;
        ADC_Value = ADC_Value<<8;
        ADC_Value = ADC_Value + ADRESL;
    }
    
    if (PIR1bits.TMR1IF == 1){
        PIR1bits.TMR1IF = 0; //limpia la flag de TIMER1
        TIMER1_SetValue(TMR1_Value); //para 1mSeg
        t++;
        if (t >= Tconv){
            t = 0;
            ADC_StartConv();
            PORTBbits.RB1 = PORTBbits.RB0;  
            PORTBbits.RB2 = !PORTBbits.RB0;
        }
        
    }
    
}
