/*	Author: Mark Vincent
 *  Partner(s) Name: NA
 *	Lab Section: A01
 *	Assignment: Lab #5  Exercise #1
 *
 *  Google Drive Video Link:
 *  https://drive.google.com/file/d/1rMi3iAd8ppWNcBUiRZSEZBqAjrQENP1-/view
 *
 *	Exercise Description: 
 *  Build this program on the microcontroller and post video.
 *  
 *  Designing a fuel level sensor, PA3 - PA0 holds a
 *	value between 0 and 15 which will in turn, indicate which values of PC5 -
 *	PC0 to be 1. PC6 contains a low fuel light, which is 1 if 4 or less values
 *	of PC5 - PC0 are 1. 
 *
 *  Fuel Level 1 or 2   => PC5 is 1
 *  Fuel Level 3 or 4   => PC5 - PC4 is 1
 *  Fuel Level 5 or 6   => PC5 - PC3 is 1
 *  Fuel Level 7 to 9   => PC5 - PC2 is 1
 *  Fuel Level 10 to 12 => PC5 - PC1 is 1
 *  Fuel Level 13 to 15 => PC5 - PC0 is 1
 *
 *  Low Fuel Level at 4 or less => PC6 is 1
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    
    // Ports
    DDRA = 0x00; PORTA = 0xFF; // Configure PORTA as input
    DDRC = 0xFF; PORTC = 0x00; // Configure PORTC as output

    // Vars
    unsigned char tmpA = 0x00;
    unsigned char tmpC = 0x00;
    
    unsigned char lightLevel = 0x00;

    // Loop
    while (1) {
        
        // read input
        tmpA = ~PINA & 0x0F;
        
        // gather lightLevel
        lightLevel = tmpA & 0x0F;

        // begin setting light levels
        if (lightLevel >= 13) {
            // 1 on pins PC5 - PC0
            tmpC = 0x3F;

        } else if (lightLevel >= 10) {
            // 1 on pins PC5 - PC1
            tmpC = 0x3E;

        } else if (lightLevel >= 7)  {
            // 1 on pins PC5 - PC2
            tmpC = 0x3C;
            
        } else if (lightLevel >= 5)  {
            // 1 on pins PC5 - PC3
            tmpC = 0x38;

        } else if (lightLevel == 4)  {
            // 1 on pins PC5 - PC4 and PC6
            tmpC = 0x70;

        } else if (lightLevel >= 3)  {
            // 1 on pins PC5 - PC4 and PC6
            tmpC = 0x70;

        } else if (lightLevel > 0) {
            // 1 on pins PC5 and PC6
            tmpC = 0x60;

        } else {
            // fuel is empty, no lights except fuel light empty
            tmpC = 0x40;

        }
        
        // Writes to PORTC
        PORTC = tmpC;

        // Reset tmpC
        tmpC = 0x00;
    }

    return 1;
}
