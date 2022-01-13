# Lab 3
## Assignment 1
```c
volatile int* E; 
void labinit( void )
{
  E = (volatile int*)0xbf886100; //TRISE sets either input or output on E
  *E &= ~0xff;

  E = (volatile int*) 0xbf886110; //PORTE reads and writes data to E
  *E = 0;
  TRISD |= 0x07f0;
  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  //ADDRESS PORTD = 0xbf8860d0
  
  int btns = getbtns();
  int sw = getsw();

  if (btns & 1) {
    mytime = (sw << 4) | (mytime & 0xff0f);
  }
  if (btns & 2) {
    mytime = (sw << 8) | (mytime & 0xf0ff);
  }
  if (btns & 4) {
    mytime = (sw << 12) | (mytime & 0x0fff);
  }
  
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  *E += 0x1;
  display_image(96, icon);
}
```
```c
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw( void ){
    int value = PORTD;
    return (value >> 8) & 0x000F;
}

int getbtns( void ){
    int value = PORTD;
    return (value >> 5) & 0x0007;
}
```
### Questions for Assignment 1 

The following questions aim to help you check that you understand the code well. At the examination, the teacher may choose to ask questions which are not on this list. 

1. Test pressing BTN3 and BTN2 at the same time. What happens? Why? 

Answer: When both buttons are pressed, mytime is updated on both the minute and the 10th second place. It happens because the code that was written is designed to update the minute when BTN3 is pressed and to update the 10th second place when BTN2 is pressed.

2. Three device-registers for input/output control are TRISE, TRISESET, and TRISECLR. Their functions are related. How? What are the differences? 

Answer: TRISECLR: Write clears selected bits in TRISE, read yields undefined value
TRISESET: Write sets selected bits in TRISE, read yields undefined value
TRISE: Is used to define the direction of port or pin.

3. In the generated assembly code, in which MIPS register will the return values from functions getbtns and getsw be placed in. You should be able to answer this question without debugging the generated assembly code. 

Answer: The return values will be places in register $v0

4. In this exercise, we explained which bits that should be used in Port D and Port E. How can you find this information in the PIC32 and ChipKIT manuals? Be prepared to demonstrate how to find this information in the manuals. Advice: check the lecture slides from lecture 5 for ideas.

Answer: https://reference.digilentinc.com/_media/chipkit_shield_basic_io_shield:chipkit_basic_io_shield_rm.pdf Kolla vilken input/output du vill använda på pin nummer
http://ww1.microchip.com/downloads/en/DeviceDoc/chipKIT-Uno32-RevC_rm.pdf
Kolla vilket port dens pin nummer korresponderar till. 
RF1 = TRISEF, PORTF, bit 1
RB11 = TRISEB, PORTB, bit 11

## Assignment 2
```c
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define TMR2PERIOD ((80000000 / 256) / 10) //1 second / 10 = 100ms

int mytime = 0x5957;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
volatile int* E; 
void labinit( void )
{
  E = (volatile int*)0xbf886100;
  *E &= ~0xff;

  E = (volatile int*) 0xbf886110;
  *E = 0;
  TRISD |= 0x07F0;


    T2CONSET = 0x70; //Sets prescaling to 1:256 
    PR2 = TMR2PERIOD; //Set timeperiod
    TMR2 = 0; //Timer starts at 0
    T2CONSET = 0x8000; //Start the timer by setting msb to 1
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  //ADDRESS PORTD = 0xbf8860d0
  
  int btns = getbtns();
  int sw = getsw();

  if (btns & 1) {
        mytime = (sw << 4) | (mytime & 0xff0f);
    }
    if (btns & 2) {
        mytime = (sw << 8) | (mytime & 0xf0ff);
    }
    if (btns & 4) {
        mytime = (sw << 12) | (mytime & 0x0fff);
    }

  if (IFS(0) & 0x100) { //Checking if ninth bit is equal to one
        // Reset all event flags.
        IFS(0) = 0;     
        timeoutcount++; 

        if (timeoutcount == 10) {

           time2string( textstring, mytime );
           display_string( 3, textstring );
           display_update();
           tick( &mytime );
           display_image(96, icon);
           *E += 0x1;
           timeoutcount = 0;       
        }
    }       
}
```

### Questions for Assignment 2 
The following questions aim to help you check that you understand the code well. At the examination, the teacher may choose to ask questions which are not on this list.
 
1. When the time-out event-flag is a "1", how does your code reset it to "0"? 

Answer: The time-out event flag is reset to “0” by IFS(0) = 0

2. What would happen if the time-out event-flag was not reset to "0" by your code? Why? 

Answer: If the event flag IFS(0) isn't reseted to 0 it wouldn't need to reach PR2 which in this case is 100ms.

3. Which device-register (or registers) must be written to define the time between time-out events? Describe the function of that register (or of those registers).

Answer: To define the time between time-out events the registers PR2 and T2CONSET are defined. PR2: The period of which the timer is supposed to interrupt
T2CONSET: Is the function that sets the definition of T2CON and is defined with prescaling and either “ON” or “OFF”.

4. If you press BTN3 quickly, does the time update reliably? Why, or why not? If not, would that be easy to change? If so, how?

Answer: The time does not update reliably because the program does not have enough time to sense that the button is pressed. The only way to change the button reliability is to make sure that the tick function is outside of the timer.

## Assignment 3
```c
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define TMR2PERIOD ((80000000 / 256) / 10)

int mytime = 0x5957;
int prime = 1234567;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  if(IFS(0) & 0x100){

    IFS(0) = 0;
    timeoutcount++;

    if(timeoutcount == 10){
      time2string(textstring, mytime);
      display_string(3, textstring);
      display_update();
      tick(&mytime);
      timeoutcount = 0;
    }
  }
}

/* Lab-specific initialization goes here */
volatile int* E; 
void labinit( void )
{
  E = (volatile int*)0xbf886100;
  *E &= ~0xff;

  E = (volatile int*) 0xbf886110;
  *E = 0;
  TRISD |= 0x07F0; //0xF80F

  T2CONSET = 0x70;
  PR2 = TMR2PERIOD;
  TMR2 = 0;
  T2CONSET = 0x8000;

  IPCSET(2) = 0b100;
  IECSET(0) = 0x100;
  enable_interrupt();
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update();  
}

// Is placed in labwork.S
.global enable_interrupt
enable_interrupt:
	ei
	jr $ra
	nop
```

### Questions for Assignment 3
1. When the time-out event-flag is a "1", how does your code reset it to "0"?

Answer: The time-out event flag is reset to “0” by IFS(0) = 0

2. What would happen if the time-out event-flag was not reset to "0" by your code? Why?

Answer: If the event flag IFS(0) isn't reseted to 0 it wouldn't need to reach PR2 which in this case is 100ms. Because the clock will increase as fast as possible it won't be able to print out prime numbers.

3. From which part of the code is the function user_isr called? Why is it called from there?

Answer: The function user_isr is called in the file vector.S. By calling the function user_isr nearly all registers are pushed to the stack. Then the function is called. After the function is called and executed we pop the values back again.

4. Why are registers saved before the call to user_isr? Why are only some registers saved?

Answer: Before we call the function user_isr we save all the callers because the function user_isr should be able to use these registers. We only save the at, v, a and t registers because those are the registers that might be used in user_isr. Because these variables might be used in the function primenumbers and therefore we pop and push. We dont save the register S because it's already saved.
