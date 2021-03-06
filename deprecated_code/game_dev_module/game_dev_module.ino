// BRIAN SUMNER
// PHI HUYNH
// KAMIL ADYLOV
// UCDENVER CSCI 4287
// SPRING 2019
// LAZERBOY ENTERTAINMENT SYSTEM:
// LAZERTARGET DRIVER
// GAME DEVELOPMENT MODULE
<<<<<<< HEAD
// VERSION: ALPHA_01
=======
// VERSION: ALPHA_02
>>>>>>> worked on functions of general-purpose timer




// INCLUDES
#include <Arduino.h>

#include "talkie.h"
#include "vocab.h"

<<<<<<< HEAD



=======
>>>>>>> worked on functions of general-purpose timer
// CONSTANT DEFINITIONS
#define PIN_SPEAKER       3

#define PIN_LED_RED       13
#define PIN_LED_GREEN     13
#define PIN_LED_BLUE      13

#define PIN_GDM_LDR       14    // THIS IS ANALOG PIN A0

<<<<<<< HEAD
=======

#define PIN_SWITCH_BTN    2     // button for switching between two game mode. 

>>>>>>> worked on functions of general-purpose timer
#define LUX_THRESHOLD_GDM_LDR   512

#define LED_BLINK_DELAY   80
#define LED_BLINK_CYCLES  5

<<<<<<< HEAD



=======
#define TIMER_INTERVAL_MILLISECONDS   4
#define CPU_MHZ                       16
#define TIMER_PRESCALAR               1024



#define BTN_DEBOUNCE_TIME 50
#define NUMBER_OF_GP_TIMERS 8

// ------------------------------------------------------------------------------------------------------
>>>>>>> worked on functions of general-purpose timer
// VOICE OBJECT FOR SPEECH / AUDIO OUTPUT
Talkie voice;


<<<<<<< HEAD
=======
// TYPE DEFINITIONS
typedef struct timer32_t timer32_t;
struct timer32_t
{
  bool flag_isEnabled     : 1;
  uint32_t count          : 31;
  uint32_t maxCount       : 31;
  bool flag_doEvent       : 1;
};

// GLOBAL CONSTANTS
const double MAX_TIMER_ISR_COUNT = ((CPU_MHZ * 1000.0) / TIMER_PRESCALAR * TIMER_INTERVAL_MILLISECONDS) - 1;




// array of eight general purpose timer32_t records
volatile timer32_t timer_gps[8] = {0, 0, 31, 0};
>>>>>>> worked on functions of general-purpose timer


// FORWARD DECLARATIONS:

bool isTargetHit();     // RETURN TRUE IF THE TARGET HAS BEEN HIT

void blinkRedLED();     // BLINKS THE RED LED
void blinkGreenLED();   // BLINKS THE GREEN LED
void blinkBlueLED();    // BLINKS THE BLUE LED

<<<<<<< HEAD



// PROGRAM INITIALIZATION
void setup() 
{

    Serial.begin(115200);
    Serial.println("INITIALIZING TARGET");

    // SET UP PIN MODES
    pinMode(PIN_SPEAKER, OUTPUT);

    voice.say(spINTRO);

    Serial.println("FINISHED INITIALIZING TARGET");

=======
bool isRoomTooBright();  // RETURN TRUE IF ROOM IS TOO BRIGHT FOR PLAYING THE GAME

void timer_start(int timerNumber);                              // sets enabled flag for gp timer
void timer_stop(int timerNumber);                               // clears enabled flag for gp timer
void timer_setCount(int timerNumber, uint32_t count );          // sets count
void timer_setMaxCount(int timerNumber, uint32_t maxCount);    // sets maxCount
void timer_setDoEvent(int timerNumber);                        // sets doEvent flag
void timer_clearDoEvent(int timerNumber);                     // clears doEvent flag
bool timer_isActive(int timerNumber);                         // returns true if timer is enabled and greater than 0



volatile timer32_t timer_btnDebounce = {0, 0, BTN_DEBOUNCE_TIME , 0};

volatile bool flag_isBtnPressed = false;
volatile bool flag_isBtnEnabled = true;


// PROGRAM INITIALIZATION
void setup()
{

  Serial.begin(115200);
  Serial.println("INITIALIZING TARGET");

  // SET UP PIN MODES
  pinMode(PIN_SPEAKER, OUTPUT);
  pinMode(PIN_SWITCH_BTN, INPUT_PULLUP);                 // D2 input mode with pull-up resistor

  // attach an interrupt on int0 and call ISR_BTN_PRESSED() when triggered
  attachInterrupt(digitalPinToInterrupt(PIN_SWITCH_BTN), ISR_BTN_PRESSED, FALLING);


  // CLEAR TIMER/COUNTER REGISTERS
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2  = 0;

  // SET MAX TIMER COUNTER
  OCR2A = MAX_TIMER_ISR_COUNT;

  // CLEAR TIMER ON COMPARE MATCH
  TCCR2B |= (1 << WGM12);

  // SET CS12 AND CS10 TO USE PRESCALAR 1024
  TCCR2B |= (1 << CS12);
  TCCR2B |= (1 << CS10);

  // ENBABLE TIMER COMPARE INTERRUPT
  TIMSK2 |= (1 << OCIE2A);

  // ENABLE INTERRUPTS
  sei();

  voice.say(spINTRO);

  Serial.println("FINISHED INITIALIZING TARGET");
  flag_isBtnPressed = false;
>>>>>>> worked on functions of general-purpose timer
}




// MAIN PROGRAM LOOP
<<<<<<< HEAD
void loop() 
{

=======
void loop()
{

  if (flag_isBtnPressed) {
    Serial.println("Push pressed.. ");
    flag_isBtnPressed = false;
  }

  if (timer_btnDebounce.flag_doEvent)  {

    if (digitalRead(PIN_SWITCH_BTN) == LOW) {
      timer_clearDoEvent(&timer_btnDebounce);
      timer_setCount(&timer_btnDebounce, BTN_DEBOUNCE_TIME);
      flag_isBtnEnabled = true;
    }
  }



>>>>>>> worked on functions of general-purpose timer
  if (isTargetHit())
  {
    // INDICATE HIT OCCURRED


    // OUTPUT SPEECH FOR HIT EVENT
    // NOTE: USE 'false' ARGUMENT FOR NON-BLOCKING SPEECH
<<<<<<< HEAD
    voice.say(spHIT, false); 
    // voice.say(spGREAT2, false); 
=======
    voice.say(spHIT, false);
    // voice.say(spGREAT2, false);
>>>>>>> worked on functions of general-purpose timer


    // OUTPUT MESSAGE TO SERIAL CONSOLE
    Serial.println("HIT");


    // BLINK LED
<<<<<<< HEAD
    blinkGreenLED(); 


  // END IF
  }


// END LOOP
}





// NOTE:  NONE OF THE FUNCTIONS BELOW NEED TO BE MODIFIED
// NOTE:  PARAMETERS FOR THE FUNCTIONS BELOW ARE DEFINED BY CONSTANTS AT TOP OF FILE
=======
    blinkGreenLED();


    // END IF
  }


}

// activates debounce timer once the push button is pressed
void ISR_BTN_PRESSED() {

  if (flag_isBtnEnabled) {
    flag_isBtnEnabled = false;

    flag_isBtnPressed = true;

    timer_btnDebounce.flag_isEnabled = true;
  }
}


// INTERRUPT SERVICE ROUTINE FOR TIMER1
ISR(TIMER2_COMPA_vect)
{

  if (timer_btnDebounce.flag_isEnabled) {

    if (timer_btnDebounce.count <= 0) {
      timer_btnDebounce.flag_isEnabled = false;
      timer_btnDebounce.flag_doEvent = true;
    }
    else
      --timer_btnDebounce.count;
  }


}

// sets enabled flag for gp timer
void timer_start(timer32_t *timerNumber) {
  timerNumber->flag_isEnabled = true;

}

// clears enabled flag for gp timer
void timer_stop(timer32_t *timerNumber) {
  timerNumber->flag_isEnabled = false;

}

// sets count
void timer_setCount(timer32_t *timerNumber, uint32_t count) {
  timerNumber->count = count;
}

// sets maxCount
void timer_setMaxCount(timer32_t *timerNumber, uint32_t maxCount) {
  timerNumber->maxCount = maxCount;
}

// sets doEvent flag
void timer_setDoEvent(timer32_t *timerNumber) {
  timerNumber->flag_doEvent = true;
}

void timer_setDoEvent(int timerNumber) {
  timerArray[timerNumber].flag_doEvent = true;
}


// clears doEvent flag
void timer_clearDoEvent(int *timerNumber) {
  timerNumber->flag_doEvent = false;
}

// returns true if timer is enabled and greater than 0
bool timer_isActive(int timerNumber) {

  if (timer_gps[timerNumber].flag_isEnabled && timer_gps[timerNumber].count > 0)
    return true;

  else return false;

}

>>>>>>> worked on functions of general-purpose timer


// RETURN TRUE IF THE TARGET HAS BEEN HIT
bool isTargetHit()
{
  bool result = false;

  // READ ANALOG PIN 6 TIMES TO EMULATE FULL PROTOTYPE TIMING
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }
  if (analogRead(PIN_GDM_LDR) >= LUX_THRESHOLD_GDM_LDR)
  {
    result = true;
  }

  return result;
}


// BLINKS THE RED LED
<<<<<<< HEAD
void blinkRedLED() 
{
     // BLINK LED
    for (int i = 0; i < LED_BLINK_CYCLES; ++i)
    {
      digitalWrite(PIN_LED_RED, HIGH);
      delay(LED_BLINK_DELAY);
      digitalWrite(PIN_LED_RED, LOW);
      delay(LED_BLINK_DELAY);
    }
}

// BLINKS THE GREEN LED
void blinkGreenLED() 
{
     // BLINK LED
    for (int i = 0; i < LED_BLINK_CYCLES; ++i)
    {
      digitalWrite(PIN_LED_RED, HIGH);
      delay(LED_BLINK_DELAY);
      digitalWrite(PIN_LED_RED, LOW);
      delay(LED_BLINK_DELAY);
    }
}

// BLINKS THE BLUE LED
void blinkBlueLED() 
{
     // BLINK LED
    for (int i = 0; i < LED_BLINK_CYCLES; ++i)
    {
      digitalWrite(PIN_LED_RED, HIGH);
      delay(LED_BLINK_DELAY);
      digitalWrite(PIN_LED_RED, LOW);
      delay(LED_BLINK_DELAY);
    }
=======
void blinkRedLED()
{
  // BLINK LED
  for (int i = 0; i < LED_BLINK_CYCLES; ++i)
  {
    digitalWrite(PIN_LED_RED, HIGH);
    delay(LED_BLINK_DELAY);
    digitalWrite(PIN_LED_RED, LOW);
    delay(LED_BLINK_DELAY);
  }
}

// BLINKS THE GREEN LED
void blinkGreenLED()
{
  // BLINK LED
  for (int i = 0; i < LED_BLINK_CYCLES; ++i)
  {
    digitalWrite(PIN_LED_RED, HIGH);
    delay(LED_BLINK_DELAY);
    digitalWrite(PIN_LED_RED, LOW);
    delay(LED_BLINK_DELAY);
  }
}

// BLINKS THE BLUE LED
void blinkBlueLED()
{
  // BLINK LED
  for (int i = 0; i < LED_BLINK_CYCLES; ++i)
  {
    digitalWrite(PIN_LED_RED, HIGH);
    delay(LED_BLINK_DELAY);
    digitalWrite(PIN_LED_RED, LOW);
    delay(LED_BLINK_DELAY);
  }
>>>>>>> worked on functions of general-purpose timer
}
