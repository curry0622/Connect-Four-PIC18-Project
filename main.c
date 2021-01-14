#include "setting_hardaware/setting.h"
#include <stdlib.h>
#include "string.h"

#include <xc.h>
#include <PIC18F4520.h>
#include<stdio.h>
// using namespace std;

#pragma config OSC = INTIO67 // Oscillator Selection bits
#pragma config WDT = OFF     // Watchdog Timer Enable bit 
#pragma config PWRT = OFF    // Power-up Enable bit
//#pragma config BOREN = ON   // Brown-out Reset Enable bit
//#pragma config PBADEN = OFF     // Watchdog Timer Enable bit 
#pragma config LVP = OFF     // Low Voltage (single -supply) In-Circute Serial Pragramming Enable bit
#pragma config CPD = OFF     // Data EEPROM?Memory Code Protection bit (Data EEPROM code protection off)

void delay(unsigned int val);
void interrupt_initialize();
void input_output_initialize();
void show();    //show the current map on the LED
int judge();    //judge the situation if any player win or not
int update(); //get the top position from each column 
void win(int player);


int map[8][8]; //record the situation now 
int pos[8];
int nowpos; //the column player is locate now;
int turn=0; //turn bit decide the player moving now if player 1 turn =1 if player 2 turn = 2
int temp = 0;
int winflag = 0;

char str[20];

void main(void) 
{

//    while(1){
//        show();
//    }
    
    SYSTEM_Initialize() ;
        //initial
    interrupt_initialize();
    input_output_initialize();
    
    //player one first
    turn = 1;
    nowpos = 0;
//    int i=0, j =0;
    update();
    map[pos[nowpos]][nowpos] = 3;
    
    while(1) {
//        strcpy(str, GetString());
//        UART_Write_Text("11111111");
//        ClearBuffer();
        show();
        // TODO 
    }
    
    return;
    
}

void interrupt_initialize(){

//    ;set up external interrupt flag
    RCONbits.IPEN = 1;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.INT0IE = 1;
    INTCON3bits.INT1IE = 1;
    INTCON3bits.INT2IE = 1;
    
}

void input_output_initialize(){
    PORTB = 0x00;
    TRISB = 0x07; //setting input
    
    
    // TRISA
    // TRISAbits.TRISA0 = 0b0;
    TRISAbits.TRISA1 = 0b0;
    TRISAbits.TRISA2 = 0b0;
    TRISAbits.TRISA3 = 0b0;
    TRISAbits.TRISA4 = 0b0;
    TRISAbits.TRISA5 = 0b0;
    TRISAbits.TRISA6 = 0b0;
    TRISAbits.TRISA7 = 0b0;
	
	// TRISB
	TRISBbits.TRISB3 = 0b0;
	TRISBbits.TRISB4 = 0b0;
	TRISBbits.TRISB5 = 0b0;
    
    // TRISC
    TRISCbits.TRISC0 = 0b0;
    TRISCbits.TRISC1 = 0b0;
    TRISCbits.TRISC2 = 0b0;
    TRISCbits.TRISC3 = 0b0;
    TRISCbits.TRISC4 = 0b0;
    TRISCbits.TRISC5 = 0b0;
    // TRISCbits.TRISC6 = 0b0;
    // TRISCbits.TRISC7 = 0b0;
    
    // TRISD
    TRISDbits.TRISD0 = 0b0;
    TRISDbits.TRISD1 = 0b0;
    TRISDbits.TRISD2 = 0b0;
    TRISDbits.TRISD3 = 0b0;
    TRISDbits.TRISD4 = 0b0;
    TRISDbits.TRISD5 = 0b0;
    TRISDbits.TRISD6 = 0b0;
    TRISDbits.TRISD7 = 0b0;
    
    // TRISE
	TRISEbits.TRISE0 = 0b0;
}

void win(int player){
    int i =0;
    for(i = 0; i< 5 ; i++){
        map[i][0] = player;
        map[i][1] = player;
       
        map[i][3] = player;
        map[i][4] = player;
        
        map[i][6] = player;
        map[i][7] = player;
    }
    map[5][1] = player;
    map[5][2] = player;
    map[5][3] = player;
    map[5][4] = player;
    map[5][5] = player;
    map[5][6] = player;
    
    map[6][2] = player;
    map[6][3] = player;
    map[6][4] = player;
    map[6][5] = player;
}

void show() {
    int i;
    for(i = 0; i < 8; i++) {
        _delay(400);
        // PORTA
        PORTBbits.RB3 = 0b0;
        PORTAbits.RA1 = 0b0;
        PORTAbits.RA2 = 0b0;
        PORTAbits.RA3 = 0b0;
        PORTAbits.RA4 = 0b0;
        PORTAbits.RA5 = 0b0;
        PORTAbits.RA6 = 0b0;
        PORTAbits.RA7 = 0b0;
        
        // PORTC
        PORTCbits.RC0 = 0b1;
        PORTCbits.RC1 = 0b1;
        PORTEbits.RE0 = 0b1;
        PORTCbits.RC3 = 0b1;
        PORTCbits.RC4 = 0b1;
        PORTCbits.RC5 = 0b1;
        PORTBbits.RB4 = 0b1;
        PORTBbits.RB5 = 0b1;

        // PORTD
        PORTDbits.RD0 = 0b1;
        PORTDbits.RD1 = 0b1;
        PORTDbits.RD2 = 0b1;
        PORTDbits.RD3 = 0b1;
        PORTDbits.RD4 = 0b1;
        PORTDbits.RD5 = 0b1;
        PORTDbits.RD6 = 0b1;
        PORTDbits.RD7 = 0b1;
        switch(i) {
            case 0:
                PORTBbits.RB3 = 0b1;
//                PORTAbits.RA1 = 0b0;
//                PORTAbits.RA2 = 0b0;
//                PORTAbits.RA3 = 0b0;
//                PORTAbits.RA4 = 0b0;
//                PORTAbits.RA5 = 0b0;
//                PORTAbits.RA6 = 0b0;
//                PORTAbits.RA7 = 0b0;
                
                if(map[i][0] == 0) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b1;
                } else if(map[i][0] == 1) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b0;
                } else if(map[i][0] == 2){
                    PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b1;
                } else {
					PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b0;
				}

                if(map[i][1] == 0) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b1;
                } else if(map[i][1] == 1) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b0;
                } else if(map[i][1] == 2) {
                    PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b1;
                } else {
					PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b0;
				}

                if(map[i][2] == 0) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b1;
                } else if(map[i][2] == 1) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b0;
                } else if(map[i][2] == 2) {
                    PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b1;
                } else {
					PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b0;
				}

                if(map[i][3] == 0) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b1;
                } else if(map[i][3] == 1) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b0;
                } else if(map[i][3] == 2) {
                    PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b1;
                } else {
					PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b0;
				}

                if(map[i][4] == 0) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b1;
                } else if(map[i][4] == 1) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b0;
                } else  if(map[i][4] == 2) {
                    PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b1;
                } else {
					PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b0;
				}

                if(map[i][5] == 0) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b1;
                } else if(map[i][5] == 1) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b0;
                } else if(map[i][5] == 2) {
                    PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b1;
                } else {
					PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b0;
				}

                if(map[i][6] == 0) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b1;
                } else if(map[i][6] == 1) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b0;
                } else if(map[i][6] == 2) {
                    PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b1;
                } else {
					PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b0;
				}

                if(map[i][7] == 0) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b1;
                } else if(map[i][7] == 1) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b0;
                } else if(map[i][7] == 2) {
                    PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b1;
                } else {
					PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b0;
				}
                
                break;
            
            case 1:
//                PORTBbits.RB3 = 0b0;
                PORTAbits.RA1 = 0b1;
//                PORTAbits.RA2 = 0b0;
//                PORTAbits.RA3 = 0b0;
//                PORTAbits.RA4 = 0b0;
//                PORTAbits.RA5 = 0b0;
//                PORTAbits.RA6 = 0b0;
//                PORTAbits.RA7 = 0b0;
                
                if(map[i][0] == 0) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b1;
                } else if(map[i][0] == 1) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b0;
                } else if(map[i][0] == 2){
                    PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b1;
                } else {
					PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b0;
				}

                if(map[i][1] == 0) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b1;
                } else if(map[i][1] == 1) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b0;
                } else if(map[i][1] == 2) {
                    PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b1;
                } else {
					PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b0;
				}

                if(map[i][2] == 0) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b1;
                } else if(map[i][2] == 1) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b0;
                } else if(map[i][2] == 2) {
                    PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b1;
                } else {
					PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b0;
				}

                if(map[i][3] == 0) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b1;
                } else if(map[i][3] == 1) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b0;
                } else if(map[i][3] == 2) {
                    PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b1;
                } else {
					PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b0;
				}

                if(map[i][4] == 0) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b1;
                } else if(map[i][4] == 1) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b0;
                } else  if(map[i][4] == 2) {
                    PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b1;
                } else {
					PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b0;
				}

                if(map[i][5] == 0) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b1;
                } else if(map[i][5] == 1) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b0;
                } else if(map[i][5] == 2) {
                    PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b1;
                } else {
					PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b0;
				}

                if(map[i][6] == 0) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b1;
                } else if(map[i][6] == 1) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b0;
                } else if(map[i][6] == 2) {
                    PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b1;
                } else {
					PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b0;
				}

                if(map[i][7] == 0) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b1;
                } else if(map[i][7] == 1) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b0;
                } else if(map[i][7] == 2) {
                    PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b1;
                } else {
					PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b0;
				}
                
                break;
                
            case 2:
//                PORTBbits.RB3 = 0b0;
//                PORTAbits.RA1 = 0b0;
                PORTAbits.RA2 = 0b1;
//                PORTAbits.RA3 = 0b0;
//                PORTAbits.RA4 = 0b0;
//                PORTAbits.RA5 = 0b0;
//                PORTAbits.RA6 = 0b0;
//                PORTAbits.RA7 = 0b0;
                
                if(map[i][0] == 0) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b1;
                } else if(map[i][0] == 1) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b0;
                } else if(map[i][0] == 2){
                    PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b1;
                } else {
					PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b0;
				}

                if(map[i][1] == 0) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b1;
                } else if(map[i][1] == 1) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b0;
                } else if(map[i][1] == 2) {
                    PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b1;
                } else {
					PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b0;
				}

                if(map[i][2] == 0) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b1;
                } else if(map[i][2] == 1) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b0;
                } else if(map[i][2] == 2) {
                    PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b1;
                } else {
					PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b0;
				}

                if(map[i][3] == 0) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b1;
                } else if(map[i][3] == 1) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b0;
                } else if(map[i][3] == 2) {
                    PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b1;
                } else {
					PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b0;
				}

                if(map[i][4] == 0) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b1;
                } else if(map[i][4] == 1) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b0;
                } else  if(map[i][4] == 2) {
                    PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b1;
                } else {
					PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b0;
				}

                if(map[i][5] == 0) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b1;
                } else if(map[i][5] == 1) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b0;
                } else if(map[i][5] == 2) {
                    PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b1;
                } else {
					PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b0;
				}

                if(map[i][6] == 0) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b1;
                } else if(map[i][6] == 1) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b0;
                } else if(map[i][6] == 2) {
                    PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b1;
                } else {
					PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b0;
				}

                if(map[i][7] == 0) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b1;
                } else if(map[i][7] == 1) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b0;
                } else if(map[i][7] == 2) {
                    PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b1;
                } else {
					PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b0;
				}
                
                break;
                
            case 3:
//                PORTBbits.RB3 = 0b0;
//                PORTAbits.RA1 = 0b0;
//                PORTAbits.RA2 = 0b0;
                PORTAbits.RA3 = 0b1;
//                PORTAbits.RA4 = 0b0;
//                PORTAbits.RA5 = 0b0;
//                PORTAbits.RA6 = 0b0;
//                PORTAbits.RA7 = 0b0;
                
                if(map[i][0] == 0) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b1;
                } else if(map[i][0] == 1) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b0;
                } else if(map[i][0] == 2){
                    PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b1;
                } else {
					PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b0;
				}

                if(map[i][1] == 0) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b1;
                } else if(map[i][1] == 1) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b0;
                } else if(map[i][1] == 2) {
                    PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b1;
                } else {
					PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b0;
				}

                if(map[i][2] == 0) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b1;
                } else if(map[i][2] == 1) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b0;
                } else if(map[i][2] == 2) {
                    PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b1;
                } else {
					PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b0;
				}

                if(map[i][3] == 0) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b1;
                } else if(map[i][3] == 1) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b0;
                } else if(map[i][3] == 2) {
                    PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b1;
                } else {
					PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b0;
				}

                if(map[i][4] == 0) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b1;
                } else if(map[i][4] == 1) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b0;
                } else  if(map[i][4] == 2) {
                    PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b1;
                } else {
					PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b0;
				}

                if(map[i][5] == 0) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b1;
                } else if(map[i][5] == 1) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b0;
                } else if(map[i][5] == 2) {
                    PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b1;
                } else {
					PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b0;
				}

                if(map[i][6] == 0) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b1;
                } else if(map[i][6] == 1) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b0;
                } else if(map[i][6] == 2) {
                    PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b1;
                } else {
					PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b0;
				}

                if(map[i][7] == 0) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b1;
                } else if(map[i][7] == 1) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b0;
                } else if(map[i][7] == 2) {
                    PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b1;
                } else {
					PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b0;
				}
                
                break;
                
            case 4:
//                PORTBbits.RB3 = 0b0;
//                PORTAbits.RA1 = 0b0;
//                PORTAbits.RA2 = 0b0;
//                PORTAbits.RA3 = 0b0;
                PORTAbits.RA4 = 0b1;
//                PORTAbits.RA5 = 0b0;
//                PORTAbits.RA6 = 0b0;
//                PORTAbits.RA7 = 0b0;
                
                if(map[i][0] == 0) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b1;
                } else if(map[i][0] == 1) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b0;
                } else if(map[i][0] == 2){
                    PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b1;
                } else {
					PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b0;
				}

                if(map[i][1] == 0) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b1;
                } else if(map[i][1] == 1) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b0;
                } else if(map[i][1] == 2) {
                    PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b1;
                } else {
					PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b0;
				}

                if(map[i][2] == 0) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b1;
                } else if(map[i][2] == 1) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b0;
                } else if(map[i][2] == 2) {
                    PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b1;
                } else {
					PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b0;
				}

                if(map[i][3] == 0) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b1;
                } else if(map[i][3] == 1) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b0;
                } else if(map[i][3] == 2) {
                    PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b1;
                } else {
					PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b0;
				}

                if(map[i][4] == 0) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b1;
                } else if(map[i][4] == 1) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b0;
                } else  if(map[i][4] == 2) {
                    PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b1;
                } else {
					PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b0;
				}

                if(map[i][5] == 0) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b1;
                } else if(map[i][5] == 1) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b0;
                } else if(map[i][5] == 2) {
                    PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b1;
                } else {
					PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b0;
				}

                if(map[i][6] == 0) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b1;
                } else if(map[i][6] == 1) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b0;
                } else if(map[i][6] == 2) {
                    PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b1;
                } else {
					PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b0;
				}

                if(map[i][7] == 0) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b1;
                } else if(map[i][7] == 1) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b0;
                } else if(map[i][7] == 2) {
                    PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b1;
                } else {
					PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b0;
				}
                
                break;
                
            case 5:
//                PORTBbits.RB3 = 0b0;
//                PORTAbits.RA1 = 0b0;
//                PORTAbits.RA2 = 0b0;
//                PORTAbits.RA3 = 0b0;
//                PORTAbits.RA4 = 0b0;
                PORTAbits.RA5 = 0b1;
//                PORTAbits.RA6 = 0b0;
//                PORTAbits.RA7 = 0b0;
                
                if(map[i][0] == 0) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b1;
                } else if(map[i][0] == 1) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b0;
                } else if(map[i][0] == 2){
                    PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b1;
                } else {
					PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b0;
				}

                if(map[i][1] == 0) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b1;
                } else if(map[i][1] == 1) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b0;
                } else if(map[i][1] == 2) {
                    PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b1;
                } else {
					PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b0;
				}

                if(map[i][2] == 0) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b1;
                } else if(map[i][2] == 1) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b0;
                } else if(map[i][2] == 2) {
                    PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b1;
                } else {
					PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b0;
				}

                if(map[i][3] == 0) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b1;
                } else if(map[i][3] == 1) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b0;
                } else if(map[i][3] == 2) {
                    PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b1;
                } else {
					PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b0;
				}

                if(map[i][4] == 0) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b1;
                } else if(map[i][4] == 1) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b0;
                } else  if(map[i][4] == 2) {
                    PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b1;
                } else {
					PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b0;
				}

                if(map[i][5] == 0) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b1;
                } else if(map[i][5] == 1) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b0;
                } else if(map[i][5] == 2) {
                    PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b1;
                } else {
					PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b0;
				}

                if(map[i][6] == 0) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b1;
                } else if(map[i][6] == 1) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b0;
                } else if(map[i][6] == 2) {
                    PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b1;
                } else {
					PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b0;
				}

                if(map[i][7] == 0) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b1;
                } else if(map[i][7] == 1) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b0;
                } else if(map[i][7] == 2) {
                    PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b1;
                } else {
					PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b0;
				}
                
                break;
                
            case 6:
//                PORTBbits.RB3 = 0b0;
//                PORTAbits.RA1 = 0b0;
//                PORTAbits.RA2 = 0b0;
//                PORTAbits.RA3 = 0b0;
//                PORTAbits.RA4 = 0b0;
//                PORTAbits.RA5 = 0b0;
                PORTAbits.RA6 = 0b1;
//                PORTAbits.RA7 = 0b0;
                
                if(map[i][0] == 0) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b1;
                } else if(map[i][0] == 1) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b0;
                } else if(map[i][0] == 2){
                    PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b1;
                } else {
					PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b0;
				}

                if(map[i][1] == 0) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b1;
                } else if(map[i][1] == 1) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b0;
                } else if(map[i][1] == 2) {
                    PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b1;
                } else {
					PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b0;
				}

                if(map[i][2] == 0) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b1;
                } else if(map[i][2] == 1) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b0;
                } else if(map[i][2] == 2) {
                    PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b1;
                } else {
					PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b0;
				}

                if(map[i][3] == 0) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b1;
                } else if(map[i][3] == 1) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b0;
                } else if(map[i][3] == 2) {
                    PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b1;
                } else {
					PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b0;
				}

                if(map[i][4] == 0) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b1;
                } else if(map[i][4] == 1) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b0;
                } else  if(map[i][4] == 2) {
                    PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b1;
                } else {
					PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b0;
				}

                if(map[i][5] == 0) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b1;
                } else if(map[i][5] == 1) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b0;
                } else if(map[i][5] == 2) {
                    PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b1;
                } else {
					PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b0;
				}

                if(map[i][6] == 0) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b1;
                } else if(map[i][6] == 1) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b0;
                } else if(map[i][6] == 2) {
                    PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b1;
                } else {
					PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b0;
				}

                if(map[i][7] == 0) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b1;
                } else if(map[i][7] == 1) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b0;
                } else if(map[i][7] == 2) {
                    PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b1;
                } else {
					PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b0;
				}
                
                break;
                
            case 7:
//                PORTBbits.RB3 = 0b0;
//                PORTAbits.RA1 = 0b0;
//                PORTAbits.RA2 = 0b0;
//                PORTAbits.RA3 = 0b0;
//                PORTAbits.RA4 = 0b0;
//                PORTAbits.RA5 = 0b0;
//                PORTAbits.RA6 = 0b0;
                PORTAbits.RA7 = 0b1;
                
                if(map[i][0] == 0) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b1;
                } else if(map[i][0] == 1) {
                    PORTCbits.RC0 = 0b1;
                    PORTDbits.RD0 = 0b0;
                } else if(map[i][0] == 2){
                    PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b1;
                } else {
					PORTCbits.RC0 = 0b0;
                    PORTDbits.RD0 = 0b0;
				}

                if(map[i][1] == 0) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b1;
                } else if(map[i][1] == 1) {
                    PORTCbits.RC1 = 0b1;
                    PORTDbits.RD1 = 0b0;
                } else if(map[i][1] == 2) {
                    PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b1;
                } else {
					PORTCbits.RC1 = 0b0;
                    PORTDbits.RD1 = 0b0;
				}

                if(map[i][2] == 0) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b1;
                } else if(map[i][2] == 1) {
                    PORTEbits.RE0 = 0b1;
                    PORTDbits.RD2 = 0b0;
                } else if(map[i][2] == 2) {
                    PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b1;
                } else {
					PORTEbits.RE0 = 0b0;
                    PORTDbits.RD2 = 0b0;
				}

                if(map[i][3] == 0) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b1;
                } else if(map[i][3] == 1) {
                    PORTCbits.RC3 = 0b1;
                    PORTDbits.RD3 = 0b0;
                } else if(map[i][3] == 2) {
                    PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b1;
                } else {
					PORTCbits.RC3 = 0b0;
                    PORTDbits.RD3 = 0b0;
				}

                if(map[i][4] == 0) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b1;
                } else if(map[i][4] == 1) {
                    PORTCbits.RC4 = 0b1;
                    PORTDbits.RD4 = 0b0;
                } else  if(map[i][4] == 2) {
                    PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b1;
                } else {
					PORTCbits.RC4 = 0b0;
                    PORTDbits.RD4 = 0b0;
				}

                if(map[i][5] == 0) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b1;
                } else if(map[i][5] == 1) {
                    PORTCbits.RC5 = 0b1;
                    PORTDbits.RD5 = 0b0;
                } else if(map[i][5] == 2) {
                    PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b1;
                } else {
					PORTCbits.RC5 = 0b0;
                    PORTDbits.RD5 = 0b0;
				}

                if(map[i][6] == 0) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b1;
                } else if(map[i][6] == 1) {
                    PORTBbits.RB4 = 0b1;
                    PORTDbits.RD6 = 0b0;
                } else if(map[i][6] == 2) {
                    PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b1;
                } else {
					PORTBbits.RB4 = 0b0;
                    PORTDbits.RD6 = 0b0;
				}

                if(map[i][7] == 0) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b1;
                } else if(map[i][7] == 1) {
                    PORTBbits.RB5 = 0b1;
                    PORTDbits.RD7 = 0b0;
                } else if(map[i][7] == 2) {
                    PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b1;
                } else {
					PORTBbits.RB5 = 0b0;
                    PORTDbits.RD7 = 0b0;
				}
                
                break;
            
        }
    }
}

int judge(){
    int check_count=0;
    int i, j;
    
    //check row
    for( i=0; i<8; i++){
        check_count = 0;
        for( j=0; j<8;j++){
            if(turn ==1){
                if(map[i][j] == 1){
                    check_count++;
                }
                else {
                	check_count=0;
				}
				if(check_count == 4){
					break;
				}
            }
            else if(turn == 2) {
                if(map[i][j]==2){
                    check_count++;
                }
                else {
                	check_count=0;
				}
				if(check_count == 4){
					break;
				}
            }
        }
        if(check_count == 4) {

            if(turn == 1)
                return 1;
            else if(turn == 2)
                return 2;
        }
    }
    
	//   check column
	for( j=0; j<8; j++){
        check_count = 0;
        for( i=0; i<8;i++){
            if(turn ==1){
                if(map[i][j] == 1){
                    check_count++;
                }
                else {
                	check_count=0;
				}
				if(check_count == 4){
					break;
				}
            }
            else if(turn == 2) {
                if(map[i][j]==2){
                    check_count++;
                }
                else {
                	check_count=0;
				}
				if(check_count == 4){
					break;
				}
            }
        }
        if(check_count == 4) {

            if(turn == 1)
                return 1;
            else if(turn == 2)
                return 2;
        }
    }
    
	//check slash line '\'
	for( i=0, j=0; i<5; i++){
		check_count = 0;

			int k, l;
			for(k = i, l= j; k<8&&l<8; k++, l++){
				if(map[k][l] == turn){
					check_count++;
				}
				else {
					check_count = 0;
				}
				if(check_count == 4)
					break;
			}

			if(check_count == 4) {

	            if(turn == 1)
	                return 1;
	            else if(turn == 2)
	                return 2;
        	}

	}
	for( i=0, j=1; j<5; j++){
		check_count = 0;

			int k, l;
			for(k = i, l= j; k<8&&l<8; k++, l++){
				if(map[k][l] == turn){
					check_count++;
				}
				else {
					check_count = 0;
				}
				if(check_count == 4)
					break;
			}
			if(check_count == 4) {
	            if(turn == 1)
	                return 1;
	            else if(turn == 2)
	                return 2;
        	}

	}
	
	//check slash line '/'
	for( i=0, j=3; j<8; j++){
		check_count = 0;
			int k, l;
			for(k = i, l = j;k<8&&l>-1;l--,k++){
				if(map[k][l] == turn){
					check_count++;
				}
				else {
					check_count = 0;
				}
				if(check_count == 4)
					break;
			}
			if(check_count == 4) {
	            if(turn == 1)
	                return 1;
	            else if(turn == 2)
	                return 2;
        	}

	}
	for( i=1, j=7; i<5; i++){
		check_count = 0;
			int k, l;
			for(k = i, l = j;k<8&&l>-1;l--,k++){
				if(map[k][l] == turn){
					check_count++;
				}
				else {
					check_count = 0;
				}
				if(check_count == 4)
					break;
			}
			if(check_count == 4) {
	            if(turn == 1)
	                return 1;
	            else if(turn == 2)
	                return 2;
        	}
			

	}
	
	check_count=0;
	//check if the game finished
	for(i=0; i<8; i++){
		for(j=0;j<8; j++){
			if(map[i][j]!=0){
				check_count++;
			}
		}
	}
	if(check_count == 64){
		return 4;
	}
	return 0;
}

int update(){
    int i, j;
    for(i=0; i<8;i++){
        for (j=0; j<8; j++){
            if(map[j][i] == 0) {
                pos[i] = j;
            }
        }
    }
}


// old version: 
// void interrupt high_priority Hi_ISR(void)
void __interrupt(high_priority) Hi_ISR(void)
{
    if(PIR1bits.CCP1IF == 1) {
        RC2 ^= 1;
        PIR1bits.CCP1IF = 0;
        TMR3 = 0;
    }
    //ours
    if(INTCONbits.INT0IF == 1){
        //button blue //right button
//        PORTAbits.RA0 = 1;
        temp = nowpos;
        map[pos[nowpos]][nowpos] = 0;
        nowpos++;
        while(1){
            if(map[0][nowpos] != 0){
                nowpos++;
            }
            if(nowpos > 7 || map[0][nowpos] == 0){
                break;
            }
        }
        if(nowpos > 7 ){
            nowpos = temp;
        }
        update();
        map[pos[nowpos]][nowpos] = 3;
                
        INTCONbits.INT0IF = 0;
    }
    if(INTCON3bits.INT1IF == 1){
        //button grey // confirm button
//        PORTAbits.RA1 = 1;
        map[pos[nowpos]][nowpos] = turn;
        
        nowpos = 0;
        while(1){
            if(map[0][nowpos] != 0){
                nowpos++;
            }
            else {
                break;
            }
        }
        update();
        map[pos[nowpos]][nowpos]=3;
        int outcome = judge();
        if(outcome == 1){
            int i=0, j =0;
            for(i=0; i<8; i++){
                for(j=0; j<8; j++){
                    map[i][j]=0;
                }
            }
            int k=0;
            for(k = 0; k <30; k++){
                win(1);
                show();
                _delay(20000);
                for(i=0; i<8; i++){
                    for(j=0; j<8; j++){
                        map[i][j]=0;
                    }
                }
                show();
                UART_Write_Text("  \n");
            }
            UART_Write_Text(" player");
            UART_Write_Text(" one win  ");
            UART_Write_Text("   ");
            //show the win picture and reset the game;
            winflag =1;
            turn = 2;
            nowpos = 0;
            update();
            map[pos[nowpos]][nowpos] = 3;
            
        }
        else if(outcome == 2){
            int i=0, j =0;
            for(i=0; i<8; i++){
                for(j=0; j<8; j++){
                    map[i][j]=0;
                }
            }
            int k=0;
            for(k = 0; k <30; k++){
                win(2);
                show();
                _delay(2000);
                for(i=0; i<8; i++){
                    for(j=0; j<8; j++){
                        map[i][j]=0; 
                    }
                }
                show();
                UART_Write_Text("  \n");
            }
            UART_Write_Text(" player");
            UART_Write_Text(" two win  ");
            UART_Write_Text("   ");
            //show the win picture and reset the game;
            winflag =2;
            nowpos = 0;
            update();
            map[pos[nowpos]][nowpos] = 3;
        }
        else if(outcome == 4){
            int i=0, j =0;
            for(i=0; i<8; i++){
                for(j=0; j<8; j++){
                    map[i][j]=0;
                }
            }
            nowpos = 0;
            update();
            map[pos[nowpos]][nowpos] = 3;
        }
       
        if(turn ==1){
            turn = 2;
        }
        else {
            turn = 1;
        }
        INTCON3bits.INT1IF = 0;

    }
    if(INTCON3bits.INT2IF == 1){
        //button yellow //left button
//        PORTAbits.RA2 = 1;
        temp = nowpos;
        map[pos[nowpos]][nowpos] = 0;
        nowpos--;
        while(1){
            if(map[0][nowpos] != 0){
                nowpos--;
            }
            if(nowpos < 0 || map[0][nowpos] == 0){
                break;
            }
        }
        if(nowpos < 0){
            nowpos = temp;
        }
        update();
        map[pos[nowpos]][nowpos] = 3;
        INTCON3bits.INT2IF = 0;
    }
    
    show(); // show the result 
    return ;
}







