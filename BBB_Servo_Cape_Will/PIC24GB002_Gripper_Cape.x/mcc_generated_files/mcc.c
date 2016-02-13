/**
  @Generated MPLAB® Code Configurator Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using MPLAB® Code Configurator

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC24FJ64GB002
        Driver Version    :  1.02
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

// Configuration bits: selected in the GUI

// CONFIG4
#pragma config DSWDTPS = DSWDTPSF    // DSWDT Postscale Select->1:2,147,483,648 (25.7 days)
#pragma config DSWDTOSC = LPRC    // Deep Sleep Watchdog Timer Oscillator Select->DSWDT uses Low Power RC Oscillator (LPRC)
#pragma config DSBOREN = ON    // Deep Sleep BOR Enable bit->BOR enabled in Deep Sleep
#pragma config RTCOSC = SOSC    // RTCC Reference Oscillator  Select->RTCC uses Secondary Oscillator (SOSC)
#pragma config DSWDTEN = ON    // Deep Sleep Watchdog Timer->DSWDT enabled

// CONFIG3
#pragma config WPDIS = WPDIS    // Segment Write Protection Disable->Segmented code protection disabled
#pragma config WPFP = WPFP63    // Write Protection Flash Page Segment Boundary->Highest Page (same as page 42)
#pragma config WUTSEL = LEG    // Voltage Regulator Wake-up Time Select->Default regulator start-up time used
#pragma config WPEND = WPENDMEM    // Segment Write Protection End Page Select->Write Protect from WPFP to the last page of memory
#pragma config WPCFG = WPCFGDIS    // Write Protect Configuration Page Select->Last page and Flash Configuration words are unprotected
#pragma config SOSCSEL = IO    // Secondary Oscillator Pin Mode Select->SOSC pins have digital I/O functions (RA4, RB4)

// CONFIG2
#pragma config IESO = ON    // Internal External Switchover->IESO mode (Two-Speed Start-up) enabled
#pragma config IOL1WAY = ON    // IOLOCK One-Way Set Enable->Once set, the IOLOCK bit cannot be cleared
#pragma config FNOSC = FRC    // Initial Oscillator Select->Fast RC Oscillator (FRC)
#pragma config PLL96MHZ = ON    // 96MHz PLL Startup Select->96 MHz PLL Startup is enabled automatically on start-up
#pragma config PLLDIV = DIV12    // USB 96 MHz PLL Prescaler Select->Oscillator input divided by 12 (48 MHz input)
#pragma config I2C1SEL = PRI    // I2C1 Pin Select bit->Use default SCL1/SDA1 pins for I2C1 
#pragma config POSCMOD = NONE    // Primary Oscillator Select->Primary Oscillator disabled
#pragma config OSCIOFNC = ON    // OSCO Pin Configuration->OSCO pin functions as port I/O (RA3)
#pragma config FCKSM = CSDCMD    // Clock Switching and Fail-Safe Clock Monitor->Sw Disabled, Mon Disabled

// CONFIG1
#pragma config WDTPS = PS32768    // Watchdog Timer Postscaler->1:32,768
#pragma config ICS = PGx1    // Emulator Pin Placement Select bits->Emulator functions are shared with PGEC1/PGED1
#pragma config FWPSA = PR128    // WDT Prescaler->Prescaler ratio of 1:128
#pragma config WINDIS = OFF    // Windowed WDT->Standard Watchdog Timer enabled,(Windowed-mode is disabled)
#pragma config GWRP = OFF    // General Segment Write Protect->Writes to program memory are allowed
#pragma config GCP = OFF    // General Segment Code Protect->Code protection is disabled
#pragma config FWDTEN = ON    // Watchdog Timer->Watchdog Timer is enabled
#pragma config JTAGEN = OFF    // JTAG Port Enable->JTAG port is disabled

#include "mcc.h"

void SYSTEM_Initialize(void) {
    OSCILLATOR_Initialize();
    PIN_MANAGER_Initialize();
    INTERRUPT_Initialize();
    I2C2_Initialize();
    OC1_Initialize();
    TMR1_Initialize();
    TMR2_Initialize();
}

void OSCILLATOR_Initialize(void) {
    // DOZEN disabled; DOZE 1:8; CPDIV 1:1; RCDIV FRC/1; ROI disabled; 
    CLKDIV = 0x3000;
    // Set the secondary oscillator

}

/**
 End of File
 */