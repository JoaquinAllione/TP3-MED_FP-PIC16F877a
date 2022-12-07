
#include "DISPLAY.h"
#include <xc.h>
#include "config.h"
#include <stdint.h>

#ifdef ANODE_DISPLAY

                                // GFEDCBA
unsigned char binvalue[10]= {   
                                0b11000000, 
                                0b11111001,
                                0b10100100,
                                0b10110000,
                                0b10011001,
                                0b10010010,
                                0b10000010,
                                0b11111000,
                                0b10000000,
                                0b10010000  
                            };
unsigned char hexvalue[10]= {0xC0, 0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

unsigned char binDigitIndicator[3]= {   
                                        0b00000001, 
                                        0b00000010,
                                        0b00000100,
                                    };
unsigned char hexDigitIndicator[3]= {0x01, 0x02,0x04};

#endif

#ifdef CATODE_DISPLAY

                                // GFEDCBA
unsigned char binvalue[10]= {   
                                ~0b11000000, 
                                ~0b11111001,
                                ~0b10100100,
                                ~0b10110000,
                                ~0b10011001,
                                ~0b10010010,
                                ~0b10000010,
                                ~0b11111000,
                                ~0b10000000,
                                ~0b10010000  
                            };

unsigned char binDigitIndicator[4]= {   
                                        ~0b00000001, 
                                        ~0b00000010,
                                        ~0b00000100,
                                        ~0b00001000
                                    };

#endif

void digitValue_set(DigitIndicator_enum dig, uint8_t value){

#ifdef ANODE_DISPLAY
    PORTD = 0x00;
#endif
    
#ifdef CATODE_DISPLAY
    PORTD = 0xFF;
#endif
    
    PORTC = binvalue[value];
    PORTD = binDigitIndicator[dig];
}

void DISPLAY_Init(void){
 
    TRISC = 0x00;
    
    //segmento DP
    TRISCbits.TRISC7 = 0; //pin como salida
    PORTCbits.RC7 = 1; //activo en bajo
    
    TRISD = 0x00;
    PORTD = 0x00;
    
    DISPLAY_SetNumber(0);
    
}

void DISPLAY_SetNumber(int num){
    uint8_t a,b,c;
    a = ((num/100)%10); // holds 100's digit
    b = ((num/10)%10);  // holds 10th digit
    c = (num%10);  // holds unit digit value   
    digitValue_set(FIRST_DIGIT, a);
    PORTCbits.RC7 = 0; //punto decimal en el primer digito
    __delay_ms(1);
    digitValue_set(SECOND_DIGIT, b);
    __delay_ms(1);
    digitValue_set(THIRD_DIGIT, c);
    __delay_ms(1);
}