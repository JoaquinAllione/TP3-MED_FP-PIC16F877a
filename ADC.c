#include "ADC.h"
#include <xc.h>

void ADC_Config(void){
    
    TRISAbits.TRISA0 = 1; //pin RA0 configurado como entrada
    
    INTCONbits.GIE = 1; //int globales activadas
    INTCONbits.PEIE = 1; //int de perifericos activadas
    PIE1bits.ADIE = 1; //int por conversion completa del ADC
    PIR1bits.ADIF = 0; //limpia la flag del conversor ADC
    
    ADCON0bits.ADCS0 = 0; //seleccion de frecuencia de clock (ver pag. 129 del manual)
    ADCON0bits.ADCS1 = 0;
    ADCON1bits.ADCS2 = 0; //Fosc/2
    ADCON0bits.CHS = 0b000; //seleccion de canal (AN0)
    ADCON1bits.ADFM = 1; //ajuste de datos a derecha
    
    ADCON1bits.PCFG = 0b0001; //ver pag. 130 del manual del pic
      
    ADCON0bits.ADON = 1; //modulo ADC activado
    
}

void ADC_StartConv(void){
    ADCON0bits.GO_nDONE = 1; //lanza conversion
}
