#include "TIMER.h"
#include <xc.h>

void TIMER1_Config(void){
    
    INTCONbits.GIE = 1; //interrupciones globales activadas
    INTCONbits.PEIE = 1; //int de perifericos activadas
    PIE1bits.TMR1IE = 1; //int de TIMER1 activadas
    PIR1bits.TMR1IF = 0; //limpia la flag de TIMER1
    T1CONbits.TMR1CS = 0; //clock interno Fosc/4
    T1CONbits.T1CKPS = 0b11; //prescaler (ver pag. 59 del manual)
    
    /* PRESCALER 
     * 11 ---> 1:8 (PS_Value = 8 en este caso)
     * 10 ---> 1:4
     * 01 ---> 1:2
     * 00 ---> 1:1
    */
    
    T1CONbits.T1INSYNC = 1; //sin sincronizacion (ver diagrama de bloques pag. 60)
    T1CONbits.TMR1ON = 1; //TIMER1 activado
    
    TMR1 = TMR1_Value;
    
    /* TMP1 Value 
     *                  T*Fosc
     * TMP1 = 65536 - ----------
     *                4*PS_Value
    */
    
}

void TIMER1_SetValue(int value){
    if (value <= 65535) TMR1 = value;
}
