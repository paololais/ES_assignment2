/*
 * File:   timer.c
 * Author: paolo
 *
 * Created on March 4, 2025, 4:36 PM
 */


#include "xc.h"

void tmr_setup_period(int timer, int ms){
    if(ms > 200) return;
   
    long int Fcy = 72000000;
    
    if(timer == 1){
        PR1 = (int) ((Fcy / 256) * (ms / 1000.0));
    
        T1CONbits.TCS = 0;
        TMR1 = 0; // reset timer counter
        T1CONbits.TCKPS = 3; // prescaler 1:256
        IFS0bits.T1IF = 0;
        T1CONbits.TON = 1; // starts the timer!
    }
    
    else if(timer == 2){
        PR2 = (int) ((Fcy / 256) * (ms / 1000.0));

        T2CONbits.TCS = 0;
        TMR2 = 0; // reset timer counter
        T2CONbits.TCKPS = 3; // prescaler 1:256
        IFS0bits.T2IF = 0;
        T2CONbits.TON = 1; // starts the timer!
    }   
}

int tmr_wait_period(int timer){
    if (timer == 1){
        if(IFS0bits.T1IF == 0) return 0; 
         else if(IFS0bits.T1IF == 1){
             IFS0bits.T1IF = 0;
             return 1;
         }
    }
    else if(timer == 2){
        if(IFS0bits.T2IF == 0) return 0; 
         else if(IFS0bits.T2IF == 1){
             IFS0bits.T2IF = 0;
             return 1;
         }
    }
}