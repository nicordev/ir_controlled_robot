// IR remote

#include "IRremote.h"

int receiverPin = 12;

const int BTN_NUM_0 = 0;
const int BTN_NUM_1 = 1;
const int BTN_NUM_2 = 2;
const int BTN_NUM_3 = 3;
const int BTN_NUM_4 = 4;
const int BTN_NUM_5 = 5;
const int BTN_NUM_6 = 6;
const int BTN_NUM_7 = 7;
const int BTN_NUM_8 = 8;
const int BTN_NUM_9 = 9;
const int BTN_POWER = 10;
const int BTN_VOL_PLUS = 11;
const int BTN_VOL_MINUS = 12;
const int BTN_UP = 13;
const int BTN_DOWN = 14;
const int BTN_PAUSE = 15;
const int BTN_BACK = 16;
const int BTN_FORWARD = 17;
const int BTN_STOP = 18;
const int BTN_EQ = 19;
const int BTN_REPT = 20;
const int BTN_UNKNOWN = 21;

/* Declare objects */
IRrecv irrecv(receiverPin);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/* Function */
// describing Remote IR codes
// takes action based on IR code received
int translateIR() 
{
  switch(results.value)
  {
	case 0xFD00FF: 
		Serial.println("POWER"); 
        return BTN_POWER;
	case 0xFD40BF: 
		Serial.println("FUNC/STOP");
        return BTN_STOP;
	case 0xFD807F: 
		Serial.println("VOL+");
        return BTN_VOL_PLUS;
	case 0xFD20DF: 
		Serial.println("FAST BACK");
        return BTN_BACK;  
	case 0xFDA05F: 
		Serial.println("PAUSE");
        return BTN_PAUSE;
	case 0xFD609F: 
		Serial.println("FAST FORWARD");
        return BTN_FORWARD;
	case 0xFD10EF: 
		Serial.println("DOWN");
        return BTN_DOWN;
	case 0xFD906F: 
		Serial.println("VOL-");
        return BTN_VOL_MINUS;
	case 0xFD50AF: 
		Serial.println("UP");
        return BTN_UP;
	default: 
		Serial.println("other button");
        return BTN_UNKNOWN;
  }
}

/**
 * Use of 2 DC motor and a L293D
 */

// Motor 1 (left)
const int PIN_ACTIVATE_1_2 = 9;
const int PIN_INPUT_1 = 10;
const int PIN_INPUT_2 = 11;

// Motor 2 (right)
const int PIN_ACTIVATE_3_4 = 3;
const int PIN_INPUT_3 = 4;
const int PIN_INPUT_4 = 5;

// Directions
const int MOVE_FORWARD = 0;
const int MOVE_BACKWARD = 1;
const int TURN_RIGHT = 2;
const int TURN_LEFT = 3;
const int STOP = 4;

/**
 * Initialize the pins of a motor
 */
void initMotor(int activationPin, int pin1, int pin2)
{
    pinMode(activationPin, OUTPUT);
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    // Enable the motor driver
    digitalWrite(activationPin, HIGH); 
}

/**
 * Run a motor either clockwise or counter-clockwise
 */
void runMotor(int pin1, int pin2, bool clockwise = true)
{
    if (clockwise) {
        // Run the motor clockwise
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
    } else {
        // Run the motor counter-clockwise
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, HIGH);
    }
}

/**
 * Stop a motor
 */
void stopMotor(int pin1, int pin2)
{
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
}

// Robot control

void move(int direction)
{
    switch (direction) {
        case MOVE_FORWARD:
            runMotor(PIN_INPUT_1, PIN_INPUT_2, false);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, true);
            break;
        case MOVE_BACKWARD:
            runMotor(PIN_INPUT_1, PIN_INPUT_2, true);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, false);
            break;
        case TURN_RIGHT:
            runMotor(PIN_INPUT_1, PIN_INPUT_2, false);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, false);
            break;
        case TURN_LEFT:
            runMotor(PIN_INPUT_1, PIN_INPUT_2, true);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, true);
            break;
        case STOP:
            stopMotor(PIN_INPUT_1, PIN_INPUT_2);
            stopMotor(PIN_INPUT_3, PIN_INPUT_4);
            break;
    }
}

// Main functions

void setup()   
{
    Serial.begin(9600);

    // Start the receiver
    irrecv.enableIRIn(); 

    // Initialize the motors
    initMotor(PIN_ACTIVATE_1_2, PIN_INPUT_1, PIN_INPUT_2);
    initMotor(PIN_ACTIVATE_3_4, PIN_INPUT_3, PIN_INPUT_4);
}

void loop()   
{
	// have we received an IR signal?
	if (irrecv.decode(&results)) {
		switch (translateIR())
        {
            case BTN_VOL_PLUS:
                move(MOVE_FORWARD);
                break;
            case BTN_VOL_MINUS:
                move(MOVE_BACKWARD);
                break;
            case BTN_FORWARD:
                move(TURN_RIGHT);
                break;
            case BTN_BACK:
                move(TURN_LEFT);
                break;
            case BTN_PAUSE:
                move(STOP);
                break;
            default:
                break;
        }
        delay(500);
		irrecv.resume(); // receive the next value
	}  
}
