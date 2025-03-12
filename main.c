/*
 * File:   main.c
 * Author: paolo
 *
 * Created on March 4, 2025, 4:36 PM
 */


#include "xc.h"
#include "timer.h"

//int i = 0;

void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt(){
  IFS0bits.T2IF = 0; 
  IEC0bits.T2IE = 0;
  T2CONbits.TON = 0; 
  IEC1bits.INT1IE = 1;

  if (PORTEbits.RE9 == 1) {
   //toggle led
    LATGbits.LATG9 = !LATGbits.LATG9;

  }

}
void __attribute__((__interrupt__, __auto_psv__)) _INT1Interrupt(){
  IFS1bits.INT1IF = 0;
  IEC0bits.T2IE = 1;
  tmr_setup_period(TIMER2, 10);
}

/*void __attribute__((__interrupt__, __auto_psv__)) _T2Interrupt() {
    IFS0bits.T2IF = 0; // reset interrupt flag
    i = i + 1;
    if (i == 5) {
        LATGbits.LATG9 = 1;
    } else if (i == 10) {
        i = 0;
        LATGbits.LATG9 = 0;
    }
}
*/

/*
int main(void) {
    // initialization code
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0 = 0;

    TRISGbits.TRISG9 = 0;
    LATGbits.LATG9 = 0;

    tmr_setup_period(TIMER1, 200);
    tmr_setup_period(TIMER2, 100);
    int status = 0;

    //IEC0bits.T1IE = 1;

    while (1) {
        if (status == 0) {
            LATAbits.LATA0 = 1;
            status = 1;
        } else {
            LATAbits.LATA0 = 0;
            status = 0;
        }
        //IFS0bits.INT0IF = 1;
        tmr_wait_period(TIMER1);
    }
    return 0;
}
*/

//ESERCIZIO 1 ASSIGNMENT2
/* void __attribute__((__interrupt__, __auto_psv__)) _INT1Interrupt() {
  IFS1bits.INT1IF = 0; // reset interrupt flag
  
}
*/

int main(void) {
    // initialization code
    ANSELA = ANSELB = ANSELC = ANSELD = ANSELE = ANSELG = 0x0000;
    TRISAbits.TRISA0 = 0;
    LATAbits.LATA0 = 0;
    
    TRISGbits.TRISG9 = 0;
    LATGbits.LATG9 = 0;
    //setting left botton T2 as input
    TRISEbits.TRISE8 = 1;
    
    RPINR0bits.INT1R = 0x58;
    INTCON2bits.GIE = 1;
    IFS1bits.INT1IF = 0;
    IEC1bits.INT1IE = 1;
      
    tmr_setup_period(TIMER1, 200);
    
    volatile int status = 0;
  
    while (1) {
        
        if(status == 0){
            LATAbits.LATA0 = 1;
            status = 1;
        } else{
            LATAbits.LATA0 = 0;
            status = 0;
        }
        
        //LATAbits.LATA0 = status; // Accendi/spegni il LED1 su RA0
        //status = !status;
        
        tmr_wait_period(TIMER1);
    }
    return 0;
}