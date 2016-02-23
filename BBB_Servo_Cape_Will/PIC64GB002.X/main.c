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
        Device            :  PIC24FJ64GB202
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
//===========================================================================
/*
                         Main application
 * 
 * 
 * 
 */
//Variables
//=======================================================================
int TimerVariable = 0;    //Increments every 100 ms see tmr1.c callback function 
int Timer2Variable = 0;   //Increments every 1 ms see tmr2.c callback function
int S1 = 1;               //Increments with every switch one press~State variable 
int TransmitComplete = 0;               //Increments with every switch two press 
int cycles; 
uint8_t LocalMemory[6]; 
int i = 0;  

//Functions
//=======================================================================
void debounce(int);      // Debounce function which waits multiples of 100 ms
void FastDebounce(int);  // Debounce function which waits multiples of 1 ms
void StateMaker(int);    // Blinker of LEDs to show state 
void MakeSelection(int);//Calls functions based on state 
void ResetMemory();
void grab();
void letGo();

//======================Preset Arm Positions
void setInitial();
void FaceHopper();
void setTo90();
//======================Preset Arm Functions 
void grabLow();
void grabMed();
void grabHigh();
void depositHopper();
//=====================Servo Movement Functions
void move1(int);
void move2(int);
void move3(int);
void move4(int);
void move5(int);
void changePosAll(int,int,int,int,int);
void increment1(int);
void increment2(int);
void increment3(int);
void increment4(int);
void increment5(int);
void scan();
//testing functions
void testAll();
void rangeTest();
       
////////////////////////////////////////////////////////////////////////////////
/// The ALMIGHTY MAIN function!!!!! ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    // initialize the device
    SYSTEM_Initialize();
    
    //Light show 
    debounce(2);
    PORTAbits.RA3 = 0;    //Led 4 
    debounce(5);
    PORTBbits.RB5 = 0;    //Led 3
    debounce(2);
    PORTBbits.RB7 = 0;    //Led 2
    debounce(1);
    
    debounce(1);
    
    ResetMemory();
    
    //setInitial();
    while (1) {
        //All mighty while loop
        
        //grabHigh();
        
        if(TransmitComplete){
            TransmitComplete = 0; 
            
            if(LocalMemory[0]== 0x00){
                LocalMemory[1] = 0x01;
                changePosAll(LocalMemory[1],LocalMemory[2],LocalMemory[3],LocalMemory[4],LocalMemory[5]);
                //ResetMemory();  
            }
            else if(LocalMemory[0] != 0x01){
                
                switch(LocalMemory[0]){
                    case 2: LocalMemory[1] = 0x01;
                        setInitial();
                        break;
                    case 3: LocalMemory[1] = 0x01;
                        FaceHopper();
                        break;
                    case 4: LocalMemory[1] = 0x01;
                        grabHigh();
                        break;
                    case 5: break;
                    case 6: break;
                            
                    
                }
                //ResetMemory();
            }
            
        }
        
        
           if(PORTAbits.RA0 == 1){        //S1 pressed
                S1++; 
                if(S1==10)
                                     //Overflow Condition~No State 9
                      S1 = 1; 
            
                debounce(500);
                StateMaker(S1);         //Set the LEDs 
        }
        
        
        
        
        //===============Heart beat <3 <3 <3
        PORTBbits.RB5 = 1;
        debounce(100);
        PORTBbits.RB5 = 0;
        debounce(50);
        
    }
    return -1;
}
// End main

/*
********************************************************************************
***  Functions *****************************************************************
********************************************************************************
 */


void ResetMemory(){
    
    int ResetIndex = 0; 
    
    while(ResetIndex<6)
        LocalMemory[ResetIndex++] = 0x01; 
    
    ResetIndex = 0;
}

void debounce(int cycles){
   TimerVariable = 0;
   while(TimerVariable <= cycles);
}

    
void FastDebounce(int cycles){  
    TimerVariable = 0;
    while(TimerVariable <= cycles); 
}

void StateMaker(S1){
    switch(S1){
        case 1:  PORTBbits.RB7 = 0;   
                 debounce(1);
                 PORTBbits.RB5 = 0;
                 debounce(1);
                 PORTAbits.RA1 = 1;
                 debounce(1); 
                 PORTAbits.RA3 = 0; 
                 break;
        case 2:  PORTAbits.RA1 = 0;
                 debounce(1);
                 PORTAbits.RA3 = 1; 
                 break;
        case 3:  PORTAbits.RA1 = 1;
                 debounce(1);
                 PORTAbits.RA3 = 1; 
                 break;   
        case 4:  PORTAbits.RA1 = 0;
                 debounce(1);
                 PORTAbits.RA3 = 0;
                 debounce(1);  
                 PORTBbits.RB7 = 1;
                 break;
        case 5:  PORTAbits.RA1 = 1;
                 debounce(1);
                 PORTAbits.RA3 = 0;
                 debounce(1);  
                 PORTBbits.RB7 = 1;
                 break;
        case 6:  PORTAbits.RA1 = 0;
                 debounce(1);
                 PORTAbits.RA3 = 1;
                 debounce(1);  
                 PORTBbits.RB7 = 1;
                 break;
        case 7:  PORTAbits.RA1 = 1; 
                 debounce(1);
                 break;
        case 8:  PORTAbits.RA1 = 0;
                 debounce(1); 
                 PORTAbits.RA3 = 0; 
                 debounce(1);
                 PORTBbits.RB7 = 0; 
                 debounce(1); 
                 PORTBbits.RB5 = 1; 
                 break;
        case 9:  PORTAbits.RA1 = 1;
                 debounce(1); 
                 PORTAbits.RA3 = 0; 
                 debounce(1);
                 PORTBbits.RB7 = 0; 
                 debounce(1); 
                 PORTBbits.RB5 = 1; 
                 break;
    }
}

void MakeSelection(S1){
    switch(S1){        
        case 1: depositHopper();
                FastDebounce(1); 
                break;
        case 2: setInitial();
                FastDebounce(1);
                break;
        case 3: grab();
                FastDebounce(1);
                break;   
        case 4: letGo();
                FastDebounce(1);
                break;
        case 5: 
                FastDebounce(1);
                break;
        case 6: 
                FastDebounce(1);
                break;
        case 7: 
                FastDebounce(1);
                break;
        case 8:  
                break;
        case 9: 
                break;
        
    }
}

void testAll() {
    changePosAll(0,160,0,180,0); // initial
    FastDebounce(1000);
    changePosAll(0,90,70,180,0);
    FastDebounce(1000);
    changePosAll(0,65,30,110,0);
    FastDebounce(1000);
    changePosAll(0,0,30,69,0);  // high tier
    FastDebounce(1000);
}
    
void scan() {
    
}

void depositHopper() {
    changePosAll(0,160,0,180,0); // initial
    FastDebounce(1000);
    changePosAll(180,160,0,180,0);
    FastDebounce(1000);
    changePosAll(180,90,40,180,0);
    FastDebounce(1);
}

void grabHigh() {
    
    changePosAll(0,160,0,180,0); // initial
    FastDebounce(1000);
    changePosAll(0,25,30,60,0);
    FastDebounce(5000);
    changePosAll(0,25,30,45,0);
    FastDebounce(100);
    changePosAll(0,45,45,45,0);
    
    /*
    changePosAll(0,90,70,180,0);
    FastDebounce(100);
    changePosAll(0,65,30,110,0);
    FastDebounce(1000);
    changePosAll(0,0,30,69,0);  // high height tier grab position
    FastDebounce(100);
    //grab();
    FastDebounce(100);
    //changePosAll(0,90,50,180,0);  //initial
    FastDebounce(100);
    //changePosAll(0,160,0,180,0);  //initial
    FastDebounce(1);*/
    setInitial();
}   

void grabMed() {
    changePosAll(0,160,0,180,0);  //initial
    FastDebounce(1000);
    changePosAll(0,90,70,180,0);
    FastDebounce(1000);
    changePosAll(0,10,74,130,0);  // medium height tier grab position
    FastDebounce(1000);
    grab();
    FastDebounce(1000);
    changePosAll(0,80,70,180,0);
    FastDebounce(1000);
    changePosAll(0,160,0,180,0);  //initial
    FastDebounce(1);
}

void grabLow() {
    changePosAll(0,160,0,180,0); //initial
    FastDebounce(1000);
    changePosAll(0,80,60,110,0);
    FastDebounce(1000);
    changePosAll(0,0,30,69,0);  // low  height tier grab position
    FastDebounce(1000);
    grab();
    FastDebounce(1000);
    changePosAll(0,90,65,100,0);
    FastDebounce(1000);
    changePosAll(0,160,0,180,0);  //initial
    FastDebounce(1);
}

void setInitial(){
    changePosAll(0,155,10,180,0);  //initial
    FastDebounce(1);
}

    
void FaceHopper(){
    changePosAll(180,155,10,180,0);
    FastDebounce(1);
}

void grab(){    
   /*while(OC6R >= 0x200){
        OC6R--;
        FastDebounce(1);
    }
    OC6R = 0x205;
    FastDebounce(1);*/
}
    
void letGo(){
    /*
    OC6R=0x455;
    FastDebounce(1);
    OC6R=0x450;*/
}  

void setTo90() {
    changePosAll(90,90,90,90,0);
    FastDebounce(1);
}


//=================================================================================

void changePosAll(int degree1, int degree2, int degree3, int degree4, int degree5) {
	int dStep1 = 0x6;
	int dStep2 = 0x5;
	int dStep3 = 0x6;
	int dStep4 = 0x6;
	int dStep5 = 0x6;
	
	int min1 = 0x100;
	int min2 = 0x21A0;
	int min3 = 0xEF;
	int min4 = 0xFF;
	int min5 = 0xFF;
	
    int max1 = 0x500;
    int max2 = 0x24C0;
    int max3 = 0x495;
    int max4 = 0x480;
    int max5 = 0x475;
    
	int intPos1 = OC1R;
	int intPos2 = OC2R;
	int intPos3 = OC3R;
	int intPos4 = OC4R;
	int intPos5 = OC5R;
	
    int newPos1 = min1 + degree1*dStep1;
	int newPos2 = min2 + degree2*dStep2;
	int newPos3 = min3 + degree3*dStep3;
	int newPos4 = min4 + degree4*dStep4;
	int newPos5 = min5 + degree5*dStep5;
    
    // make sure we don't exceed limits
    if (newPos1>max1) {
        newPos1=max1;
    }
    if (newPos2>max2) {
        newPos2=max2;
    }
    if (newPos3>max3) {
        newPos3=max3;
    }
    if (newPos4>max4) {
        newPos4=max4;
    }
    if (newPos5>max5) {
        newPos5=max5;
    }
    
	int delta1 = newPos1 - intPos1;
	int delta2 = newPos2 - intPos2;
	int delta3 = newPos3 - intPos3;
	int delta4 = newPos4 - intPos4;
	int delta5 = newPos5 - intPos5;
	
    // increment each servo to get to desired positions
    while((OC1R!=newPos1) || (OC2R!=newPos2) || (OC3R!=newPos3) || (OC4R!=newPos4) || (OC5R!=newPos5)) {
        if (OC1R != newPos1){
            increment1(delta1);
    	}
        if (OC2R != newPos2){
            increment2(delta2);
    	} 
        if (OC3R != newPos3){
            increment3(delta3);
    	} 
        if (OC4R != newPos4){
            increment4(delta4);
        } 
    	if (OC5R != newPos5){
        	increment5(delta5);
        }
    }
}
 
void increment1( int delta) {
	int step1 = 1;	
    int curPos = OC1R;
	// negative delta
	if (delta < 0) {
		OC1R = curPos-step1;
        FastDebounce(3);
	} else {
	// positive delta
		OC1R = curPos+step1;
        FastDebounce(3);
	}
}

void increment2(int delta) {
	int step2 = 1;
    int curPos = OC2R;
	// negative delta
	if (delta < 0) {
		OC2R = curPos-step2;
        FastDebounce(2);
	} else {
	// positive delta
		OC2R = curPos+step2;
        FastDebounce(2);
	}
}

void increment3(int delta) {
	int step3 = 1;
    int curPos = OC3R;
	// negative delta
	if (delta < 0) {
		OC3R = curPos-step3;
        FastDebounce(1);
	} else {
	// positive delta
		OC3R = curPos+step3;
        FastDebounce(1);
	}
}

void increment4(int delta) {
	int step4 = 1;
    int curPos = OC4R;
	// negative delta
	if (delta < 0) {
		OC4R = curPos-step4;
        FastDebounce(1);
	} else {
	// positive delta
		OC4R = curPos+step4;
        FastDebounce(1);
	}
}

void increment5(int delta) {
	int step5 = 1;
    int curPos = OC5R;
	// negative delta
	if (delta < 0) {
		OC5R = curPos-step5;
        FastDebounce(1);
	} else {
	// positive delta
		OC5R = curPos+step5;
        FastDebounce(1);
	}
}


void move1(int degree1) {
   	int dStep = 0x6;
   	int min = 0xE5;
    int max = 0x495;
   	int intPos = OC1R;
    int newPos = min + degree1*dStep;
    // don't exceed range
    if (newPos>max) {
        newPos=max;
    }
   	int delta = newPos - intPos;
    // change position
    while (OC1R != newPos){
            increment1(delta);
    }
}

void move2(int degree2) {
    int dStep = 0x5;
   	int min = 0x21A0;
    int max = 0x2466;
   	int intPos = OC2R;
    int newPos = min + degree2*dStep;
    // don't exceed range
    if (newPos>max) {
        newPos=max;
    }
   	int delta = newPos - intPos;
    // change position
    while (OC2R != newPos){
            increment2(delta);
    }
}

void move3(int degree3) {
    int dStep = 0x6;
   	int min = 0xEF;
    int max = 0x495;
   	int intPos = OC3R;
    int newPos = min + degree3*dStep;
    // don't exceed range
    if (newPos>max) {
        newPos=max;
    }
   	int delta = newPos - intPos;
    // change position
    while (OC3R != newPos){
            increment3(delta);
    }
}

void move4(int degree4) {
    int dStep = 0x6;
   	int min = 0xE0;
    int max = 0x495;
   	int intPos = OC4R;
    int newPos = min + degree4*dStep;
    // don't exceed range
    if (newPos>max) {
        newPos=max;
    }
   	int delta = newPos - intPos;
    // change position
    while (OC4R != newPos){
            increment4(delta);
    }
}

void move5(int degree5) {
    int dStep = 0x6;
   	int min = 0xFF;
    int max = 0x475;
   	int intPos = OC5R;
    int newPos = min + degree5*dStep;
    // don't exceed range
    if (newPos>max) {
        newPos=max;
    }
   	int delta = newPos - intPos;
    // change position
    while (OC5R != newPos){
            increment5(delta);
    }
}

/*
 ******************************************************************************
 */


void rangeTest() {
    int step = 1;
    int intPos =    0xE0;
    int finalPos =  0x495;
    int end = 0x490;
    OC1R = intPos;     
    FastDebounce(1);
    // positive rotation
    while(OC1R < finalPos){
        OC1R += step;
        FastDebounce(20);
    }
    // negative rotation
    while(OC1R > intPos) {
        OC1R -= step;
        FastDebounce(20);
    }
    // positive rotation
    while(OC1R < end) {
        OC1R += step;
        FastDebounce(30);
    }    
}


/*
 End of File
 */