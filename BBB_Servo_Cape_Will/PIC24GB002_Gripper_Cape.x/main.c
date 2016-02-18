/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC24FJ64GB002
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.24
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#include "mcc_generated_files/mcc.h"
//==================================================Functions

void debounce(int cycles);
void grab();
void letGo();
void ResetMemory();

//================================================Global Variables

int TimerVariable = 0; 
int TransmitComplete = 0;               //Increments with every switch two press 
int cycles; 
uint8_t LocalMemory[6]; 
int i = 0;  


//=======================================Start Main ===============
int main(void) {
    // initialize the device
    SYSTEM_Initialize();

    while (1) {
        // Add your application code
        
        if(TransmitComplete){
            TransmitComplete = 0; 
            switch(LocalMemory[0]){
                    case 5: grab();
                        break;
                    case 6: letGo();
                        break;
            }
            ResetMemory();
        }
        
        
        if(PORTAbits.RA2 == 1){
            grab();
            debounce(50);
        }
        if(PORTAbits.RA0 == 1){
            letGo();
            debounce(50);
        }
        //=============================Heart Beat <3 <3 <3 
        PORTAbits.RA1 = 1; 
        debounce(3);
        PORTAbits.RA3 = 1;
        debounce(3);
        PORTAbits.RA1 = 0;
        debounce(1);
        PORTBbits.RB7 = 1;
        debounce(3);
        PORTAbits.RA3 = 0; 
        debounce(3);
        PORTBbits.RB5 = 1;
        debounce(3);
        PORTBbits.RB7 = 0;
        debounce(3);
        PORTBbits.RB5 = 0;
    }

    return -1;
}

//=====================================End Main ===================

void letGo(){
    
    while(OC1R < 0x450){
        OC1R+= 0x10; 
        debounce(1);
    }
}
void grab(){
    
    while(OC1R > 0x140){
        OC1R-= 0x10;
        debounce(1);
    }
    OC1R = 0x150; 
}

void ResetMemory(){
    
    int ResetIndex = 0; 
    while(ResetIndex<6)
        LocalMemory[ResetIndex++] = 0x01; 
    ResetIndex = 0;
}

void debounce(int cycles){
    
    TimerVariable = 0;
    while (TimerVariable < cycles);
}
/**
 End of File
 */