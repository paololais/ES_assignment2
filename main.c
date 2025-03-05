/*
 * File:   main.c
 * Author: paolo
 *
 * Created on March 4, 2025, 4:36 PM
 */


#include "xc.h"
#include "timer.h"

int i = 0;

void __attribute__((__interrupt__, __auto_psv__)) _INT0Interrupt() {
  IFS0bits.INT0IF = 0; // reset interrupt flag
  i = i + 1;
        if (i == 2){
            LATGbits.LATG9 = 1;
        }
        else if (i == 5){
            i = 0;
            LATGbits.LATG9 = 0;
        }
}


int main(void) {
    // initialization code
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0 = 0;
    
    TRISGbits.TRISG9 = 0;
    LATGbits.LATG9 = 0;
    
    tmr_setup_period(TIMER1, 200);
    int status = 0;
    
    IEC0bits.INT0IE = 1;
 
    while (1) {
        if(status == 0){
            LATAbits.LATA0 = 1;
            status = 1;
        } else{
            LATAbits.LATA0 = 0;
            status = 0;
        }
        IFS0bits.INT0IF = 1;
        tmr_wait_period(TIMER1);
    }
    return 0;
}
