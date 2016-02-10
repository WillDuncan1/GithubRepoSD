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
void MoveServo1_Degrees(int);        
void MoveServo2_Degrees(int);
void MoveServo3_Degrees(int);
void MoveServo4_Degrees(int);
void MoveServo5_Degrees(int);
void ResetMemory();
void SetTo90();
void SetTo180();
void SetTo0();
void Grab();
void LetGo();
void SetToInitial();
void TestServo1();       //State 1 function 
void TestServo2();       //State 2 function
void TestServo3();       //State 3 function
void TestServo4();       //State 4 function
void TestServo5();       //State 5 function
void TestServo6();       //State 6 function
void rangeTest();
void changePosAll(int,int,int,int,int);
void increment1(int);
void increment2(int);
void increment3(int);
void increment4(int);
void increment5(int);
void move2();
void testAll();

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
    PORTBbits.RB6 = 0;    //Led 1
    debounce(1);
    
    ResetMemory();
    
    while (1) {
        //All mighty while loop
        
        if(TransmitComplete){
            TransmitComplete = 0; 
            SetTo90();
            if(LocalMemory[0]== 0x01){
            MoveServo1_Degrees(LocalMemory[1]); 
            debounce(1);
            MoveServo4_Degrees(LocalMemory[4]);
            debounce(1);
            MoveServo3_Degrees(LocalMemory[3]);
            debounce(1);
            MoveServo2_Degrees(LocalMemory[2]);
            debounce(1);
            MoveServo5_Degrees(LocalMemory[5]);
            ResetMemory();  
            }
            else if(LocalMemory[0]== 0x02){
                
                switch(LocalMemory[1]){
                    case 1: 
                        break;
                    case 2: break;
                    case 3: break;
                    case 4: break;
                    case 5: break;
                            
                    
                }
            }
            
        }
                if(PORTAbits.RA0 == 1){        //S1 pressed
            S1++; 
            if(S1==10)
                                     //Overflow Condition~No State 9
                S1 = 1; 
            
            debounce(10);
            StateMaker(S1);         //Set the LEDs 
        }
        
        if(PORTAbits.RA2 == 1){          //S2 pressed 
            
            PORTBbits.RB6 = 1;        //Signifies selection with blinking of light
            debounce(5);
            PORTBbits.RB6 = 0;
            debounce(3); 
            PORTBbits.RB6 = 1;
            debounce(2);
            PORTBbits.RB6 = 0;
            debounce(1); 
            PORTBbits.RB6 = 1;
            
            MakeSelection(S1); 
            
            PORTBbits.RB6 = 1;        //Signifies end of selection with blinking of light
            debounce(5);
            PORTBbits.RB6 = 0;
            debounce(3); 
            PORTBbits.RB6 = 1;
            debounce(2);
            PORTBbits.RB6 = 0;
            debounce(1); 
            PORTBbits.RB6 = 1;
            debounce(1);
            PORTBbits.RB6 = 0;           
        }
    }
    return -1;
}

void debounce(int cycles){
   TimerVariable = 0;
   while(TimerVariable <= cycles);
}


void FastDebounce(int cycles){
    Timer2Variable = 0;
    while(Timer2Variable <= cycles); 
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
        case 1:  
                setInitial();
                debounce(1); 
                break;
        case 2: testAll();
                debounce(1);
                break;
        case 3: Grab();
                debounce(1);
                break;   
        case 4: LetGo();
                debounce(1);
                break;
        case 5: 
                debounce(1);
                break;
        case 6: 
                debounce(1);
                break;
        case 7: 
                debounce(1);
                break;
        case 8:  
                break;
        case 9: 
                break;
        
    }
}

void testAll() {
    changePosAll(0,160,0,180,180);
}



void moveAllTest() {
    MoveServo1_Degrees(0);
    MoveServo1_Degrees(180);
    MoveServo1_Degrees(0);

}

void move2() {
    int curPos = OC4R;
    OC4R = curPos + 0x6;
    FastDebounce(10);
   
}


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

void setInitial(){
    
    debounce(1);
    OC1R = 0xE0;
    debounce(1);
    OC2R = 0x2466;
    debounce(1);
    OC3R = 0xEF;
    debounce(1);
    OC4R = 0x500;
    debounce(1);
    OC5R = 0x475;
    debounce(1);   
}

void SetTo180() {
    OC1R = 0x495;       
    debounce(2);
    OC2R = 0x200;
    debounce(2);
    OC3R = 0x505;
    debounce(2);
    OC4R = 0x300;
    debounce(2);
    OC2R = 0x505;
    debounce(2);
    OC4R = 0x500;
    debounce(100);
}

void SetTo90(){
                      ///Actually sets to vertically straight not 90 for each servo 
    OC1R = 0xE0;       
    debounce(2);
    OC4R = 0x2F6;
    debounce(2);
    OC2R = 0x1FF;
    debounce(2);
    OC3R = 0x320;
    debounce(2);
    OC2R = 0x320;
    debounce(5);
}

void SetTo0(){
               //Sets all to 0 degrees 
    OC1R = 0xE0;
    debounce(2);
    OC4R = 0x150;
    debounce(2);
    OC2R = 0xE0;
    debounce(2);
    OC4R = 0xE0; 
    debounce(2);
    OC3R = 0xE0;
    debounce(2);
    OC2R = 0xE0;
    debounce(5);
}

void MoveServo1_Degrees(int degrees){
    int currentposition = OC1R;                    
    int desiredposition = 0xE0 + (degrees*0x5);     //5.272 calculated degree step       
       
    if(currentposition > desiredposition){           //moving negative angles
        while(currentposition > desiredposition ){
            currentposition--;
            OC1R = currentposition;
            FastDebounce(5);
        }
    }
    else if(currentposition < desiredposition){     // move positive direction
        while(currentposition < desiredposition ){
            currentposition++;
            OC1R = currentposition;
            FastDebounce(5);
        }        
    }
    OC1R = (int)desiredposition;
    FastDebounce(5);
}    
                       
void MoveServo2_Degrees(int degrees){
    int currentposition = OC2R;                    
    double desiredposition = 0x21A0 + (degrees*0x4);     //3.944 calculated degree step
       
    if(currentposition > desiredposition){           //moving negative angles
        while(currentposition > desiredposition ){
            currentposition--;
            OC2R = currentposition;
            FastDebounce(5);
        }
    }
    else if(currentposition < desiredposition){
        while(currentposition < desiredposition ){
            currentposition++;
            OC2R = currentposition;
            FastDebounce(5);
        }        
    }
    OC2R = (int)desiredposition;
}

void MoveServo3_Degrees(int degrees){
    int currentposition = OC3R;                    
    double desiredposition = 0xE0 + (degrees*0x6);     //5.867 calculated degree step 
       
    if(currentposition > desiredposition){           //moving negative angles
        while(currentposition > desiredposition ){
            currentposition--;
            OC3R = currentposition;
            FastDebounce(5);
        }
    }
    else if(currentposition < desiredposition){
        while(currentposition < desiredposition ){
            currentposition++;
            OC3R = currentposition;
            FastDebounce(5);
        }        
    }
    OC3R = (int)desiredposition;
}
void MoveServo4_Degrees(int degrees){
    int currentposition = OC4R;                    
    double desiredposition = 0xE0 + (degrees*0x6);     //5.8944 calculated degree step       
       
    if(currentposition > desiredposition){           //moving negative angles
        while(currentposition > desiredposition ){
            currentposition--;
            OC4R = currentposition;
            FastDebounce(5);
        }
    }
    else if(currentposition < desiredposition){
        while(currentposition < desiredposition ){
            currentposition++;
            OC4R = currentposition;
            FastDebounce(5);
        }        
    }
    OC4R = (int)desiredposition;
}

void MoveServo5_Degrees(int degrees){
    int currentposition = OC5R;                    
    double desiredposition = 0xE0 + (degrees*0x6);     //5.867 is calculated degree step       
       
    if(currentposition > desiredposition){           //moving negative angles
        while(currentposition > desiredposition ){
            currentposition--;
            OC5R = currentposition;
            FastDebounce(5);
        }
    }
    else if(currentposition < desiredposition){
        while(currentposition < desiredposition ){
            currentposition++;
            OC5R = currentposition;
            FastDebounce(5);
        }        
    }
    OC5R = (int)desiredposition;
}


void Grab(){    
    while(OC6R >= 0x230){
        OC6R--;
        FastDebounce(1);
    }
    OC6R = 0x235;
}
    
void LetGo(){
    OC6R=0x490;
}  

void ResetMemory(){
    
    int ResetIndex = 0; 
    
    while(ResetIndex<6)
        LocalMemory[ResetIndex++] = 0x01; 
    
    ResetIndex = 0;
}

//=================================================================================


void changePosAll(int degree1, int degree2, int degree3, int degree4, int degree5) {
	int dStep1 = 0x6;
	int dStep2 = 0x5;
	int dStep3 = 0x6;
	int dStep4 = 0x6;
	int dStep5 = 0x6;
	
	int min1 = 0xE0;
	int min2 = 0x21A0;
	int min3 = 0xEF;
	int min4 = 0xE0;
	int min5 = 0xE0;
	
    int max1 = 0x495;
    int max2 = 0x2466;
    int max3 = 0x500;
    int max4 = 0x500;
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
    } else if (newPos2>max2) {
        newPos2=max2;
    } else if (newPos3>max3) {
        newPos3=max3;
    } else if (newPos4>max4) {
        newPos4=max4;
    } else if (newPos5>max5) {
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
//          delayMS(1);
    	} else 
        if (OC2R != newPos2){
            increment2(delta2);
//          delayMS(1);
    	} else 
        if (OC3R != newPos3){
            increment3(delta3);
//          delayMS(1);
    	} else 
        if (OC4R != newPos4){
            increment4(delta4);
//          delayMS(1);
        } else 
    	if (OC5R != newPos5){
        	increment5(delta5);
//          delayMS(1);
        }
    }
}
 
void increment1( int delta) {
	int step1 = 1;	
    int curPos = OC1R;
	// negative delta
	if (delta < 0) {
		OC1R = curPos-step1;
        FastDebounce(1);
	} else {
	// positive delta
		OC1R = curPos+step1;
        FastDebounce(1);
	}
}

void increment2(int delta) {
	int step2 = 1;
    int curPos = OC2R;
	// negative delta
	if (delta < 0) {
		OC2R = curPos-step2;
        FastDebounce(1);
	} else {
	// positive delta
		OC2R = curPos+step2;
        FastDebounce(1);
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

void TestServo1(){
    MoveServo1_Degrees(0);
    debounce(100);
    MoveServo1_Degrees(180);
    debounce(100);
    MoveServo1_Degrees(90);
    
}

void TestServo2(){
    MoveServo2_Degrees(0);
    debounce(100);
    MoveServo2_Degrees(180);
    debounce(100);
    MoveServo2_Degrees(90);
    
}

void TestServo3(){
    MoveServo3_Degrees(0);
    debounce(100);
    MoveServo3_Degrees(180);
    debounce(100);
    MoveServo3_Degrees(90);
    
}

void TestServo4(){
    MoveServo4_Degrees(0);
    debounce(100);
    MoveServo4_Degrees(180);
    debounce(100);
    MoveServo4_Degrees(90);
    
}

void TestServo5(){
    OC5R = 0x110;  
    while(OC5R <= 0x465){
        OC5R += 0x01; 
        FastDebounce(5); 
    }
}

void TestServo6(){
    
    OC6R = 0x400;
    while(OC6R >= 0x275){
        OC6R -= 0x01; 
        FastDebounce(8); 
    }
}


/*
 End of File
 */