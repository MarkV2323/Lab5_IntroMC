/*	Author: Mark Vincent II
 *  Partner(s) Name: 
 *	Lab Section: A01
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description:
 *
 *  Youtube Video Link:
 *  https://youtu.be/nU9n1uqZhfA
 *
 *  I need to build a festive light show for our LEDs on the breadboard.
 *  Using A0 to cycle through modes.
 *  Use B0 - B5 for the LEDs.
 *  
 *  Mode 1: Rainbow: 2 LEDS start at B0 and B1, move 1 by 1 to B5 then wrap
 *  back around and continue
 *
 *  Mode 2: Even Odd: Even LEDs start lit, Odd off, alternate between the two.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


// States ie, {Start, Init, ... etc}
enum States{start, init, onMode1, onMode2} state;

// Global Vars
unsigned char tmpA = 0x00;
unsigned char tmpB = 0x00;

enum Flags{mode1R, mode1P, mode2R, mode2P} flag;

// Mode1 Function
// Mode2 Function
void count(double amount) {
    for(double i = 0; i < amount; i++) {
        // nothing to do here
    }
}

// tick function
void tick() {
    
    // READ INPUT (must inverse for pull up mode on MC)
    tmpA = ~PINA & 0x01;

    // Transitions
    switch(state) {
        case start:
            state = init;
            break;
        case init:
            state = onMode1;
            flag = mode1R;
            break;
        case onMode1:
            // Checks if should move to onMode2
            if ((tmpA == 0x01) & (flag == mode1R)) {
                // transition
                state = onMode2;
                flag = mode2P;
            } 
            else if (tmpA == 0x00) {
                // stay in mode1
                state = onMode1;
                flag = mode1R;
            } else {
                // stay in mode1
                state = onMode1;
            }
            break;
        case onMode2:
            // Checks if should move to onMode1
            if ((tmpA == 0x01) & (flag == mode2R)) {
                // transition
                state = onMode1;
                flag = mode1P;
            } 
            else if (tmpA == 0x00) {
                // stay in mode2
                state = onMode2;
                flag = mode2R;
            } else {
                // stay in mode2
                state = onMode2;
            }
            break;
        default:
            state = start;
            break;
    }

    // Actions
    switch(state) {
        case start:
            break;
        case init:
            // Sets output to 1F and writes.
            tmpB = 0x00;
            PORTB = tmpB;
            break;
        case onMode1:
            // does a rainbow effect on LEDs
            for (int i = 0; i < 6; i++) {
               // shift left 1
               tmpB = tmpB << 1;
               // sets tmpB to bbbb bbb1
               tmpB = tmpB | 0x01;
               // writes to PORTB
               PORTB = tmpB;
               count(1000);
            }

            for (int i = 0; i < 6; i++) {
                // shift lef 1
                tmpB = tmpB << 1;
                // writes to PORTB
                PORTB = tmpB;
                count(1000);
            }

           break;
        case onMode2:
            // Lights up evens
            tmpB = 0x15;
            PORTB = tmpB;
            count(10000);
            // Lights up odds
            tmpB = 0x2A;
            PORTB = tmpB;
            count(10000);
           break;
        default:
            break;
    }

}

// Main Function
int main(void) {
    
    // PORTS
    DDRA = 0x00; PORTA = 0xFF; // Configure PORTA as input
    DDRB = 0xFF; PORTB = 0x00; // Configure PORTB as output

    // init output, all 6 LEDs with light up.
    tmpB = 0x3F;

    // init state
    state = start; 
    
    // Loop
    while (1) {
        tick();
    }

    return 1;
}
