/* 
 * File:   DISPLAY.h
 * Author: Joaquin Allione
 *
 * Created on 21 de noviembre de 2022, 03:29
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#define ANODE_DISPLAY

typedef enum{
    FIRST_DIGIT = 0,
    SECOND_DIGIT,
    THIRD_DIGIT,
}DigitIndicator_enum;

void DISPLAY_Init(void);
void DISPLAY_SetNumber(int);

#endif	/* DISPLAY_H */

