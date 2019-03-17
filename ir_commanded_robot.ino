// IR remote

#include "IRremote.h"

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11

typedef enum RemoteBtn RemoteBtn;
enum RemoteBtn {
    NUM_0,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    POWER,
    VOL_PLUS,
    VOL_MINUS,
    UP,
    DOWN,
    PAUSE,
    BACK,
    FORWARD,
    STOP,
    EQ,
    REPT,
    UNKNOWN
};

/* Declare objects */
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/* Function */
// describing Remote IR codes
// takes action based on IR code received
void translateIRElegoo() 
{
  switch(results.value)
  {
	case 0xFFA25D: 
		Serial.println("POWER"); 
        return RemoteBtn.POWER;
	case 0xFFE21D: 
		Serial.println("FUNC/STOP");
        return RemoteBtn.STOP;
	case 0xFF629D: 
		Serial.println("VOL+");
        return RemoteBtn.VOL_PLUS;
	case 0xFF22DD: 
		Serial.println("FAST BACK");
        return RemoteBtn.BACK;  
	case 0xFF02FD: 
		Serial.println("PAUSE");
        return RemoteBtn.PAUSE;
	case 0xFFC23D: 
		Serial.println("FAST FORWARD");
        return RemoteBtn.FORWARD;
	case 0xFFE01F: 
		Serial.println("DOWN");
        return RemoteBtn.DOWN;
	case 0xFFA857: 
		Serial.println("VOL-");
        return RemoteBtn.VOL_MINUS;
	case 0xFF906F: 
		Serial.println("UP");
        return RemoteBtn.UP;
	case 0xFF9867: 
		Serial.println("EQ");
        return RemoteBtn.EQ;
	case 0xFFB04F: 
		Serial.println("ST/REPT");
        return RemoteBtn.REPT;
	case 0xFF6897: 
		Serial.println("0");
        return RemoteBtn.NUM_0;
	case 0xFF30CF: 
		Serial.println("1");    
		return RemoteBtn.NUM_1;
	case 0xFF18E7: 
		Serial.println("2");    
		return RemoteBtn.NUM_2;
	case 0xFF7A85: 
		Serial.println("3");    
		return RemoteBtn.NUM_3;
	case 0xFF10EF: 
		Serial.println("4");    
		return RemoteBtn.NUM_4;
	case 0xFF38C7: 
		Serial.println("5");    
		return RemoteBtn.NUM_5;
	case 0xFF5AA5: 
		Serial.println("6");    
		return RemoteBtn.NUM_6;
	case 0xFF42BD: 
		Serial.println("7");    
		return RemoteBtn.NUM_7;
	case 0xFF4AB5: 
		Serial.println("8");    
		return RemoteBtn.NUM_8;
	case 0xFF52AD:
		Serial.println("9");
		return RemoteBtn.NUM_9;
	default: 
		Serial.println("other button");
        return RemoteBtn.UNKNOWN;
  }
}

void translateIRTinkerCad() 
{
  switch(results.value)
  {
	case 16580863: 
		Serial.println("POWER"); 
		return RemoteBtn.POWER;
	case 16597183: 
		Serial.println("FUNC/STOP"); 
		return RemoteBtn.STOP;
	case 16613503:
		Serial.println("VOL+"); 
		return RemoteBtn.VOL_PLUS;
	case 16589023: 
		Serial.println("FAST BACK");    
		return RemoteBtn.BACK;
	case 16621663: 
		Serial.println("PAUSE");    
		return RemoteBtn.PAUSE;
	case 16605343: 
		Serial.println("FAST FORWARD");   
		return RemoteBtn.FORWARD;
	case 16584943: 
		Serial.println("DOWN");   
		return RemoteBtn.DOWN;
	case 16617583: 
		Serial.println("VOL-");    
		return RemoteBtn.VOL_MINUS;
	case 16601263: 
		Serial.println("UP");    
		return RemoteBtn.UP;
	case 16625743: 
		Serial.println("EQ");    
		return RemoteBtn.EQ;
	case 16609423: 
		Serial.println("ST/REPT");    
		return RemoteBtn.REPT;
	case 16593103: 
		Serial.println("0");    
		return RemoteBtn.NUM_0;
	case 16582903: 
		Serial.println("1");    
		return RemoteBtn.NUM_1;
	case 16615543: 
		Serial.println("2");    
		return RemoteBtn.NUM_2;
	case 16599223: 
		Serial.println("3");    
		return RemoteBtn.NUM_3;
	case 16591063: 
		Serial.println("4");    
		return RemoteBtn.NUM_4;
	case 16623703: 
		Serial.println("5");    
		return RemoteBtn.NUM_5;
	case 16607383: 
		Serial.println("6");    
		return RemoteBtn.NUM_6;
	case 16586983: 
		Serial.println("7");    
		return RemoteBtn.NUM_7;
	case 16619623: 
		Serial.println("8");    
		return RemoteBtn.NUM_8;
	case 16603303:
		Serial.println("9");
		return RemoteBtn.NUM_9;
	default: 
		Serial.println("other button");
        return RemoteBtn.UNKNOWN;
  }
}

int translateIR(bool elegoo = false)
{
    if (elegoo) {
        return translateIRElegoo();
    }
    return translateIRTinkerCad();
}

/**
 * Use of 2 DC motor and a L293D
 */

// Motor 1 (left)
const int PIN_ACTIVATE_1_2 = 8;
const int PIN_INPUT_1 = 9;
const int PIN_INPUT_2 = 10;

// Motor 2 (right)
const int PIN_ACTIVATE_3_4 = 2;
const int PIN_INPUT_3 = 3;
const int PIN_INPUT_4 = 4;

enum Directions {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    TURN_RIGHT,
    TURN_LEFT,
    STOP
};

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
        case Directions.MOVE_FORWARD:
            runMotor(PIN_INPUT_1, PIN_INPUT_2, false);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, true);
            break;
        case Directions.MOVE_BACKWARD:
            runMotor(PIN_INPUT_1, PIN_INPUT_2, true);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, false);
            break;
        case Directions.TURN_RIGHT:
            runMotor(PIN_INPUT_1, PIN_INPUT_2, false);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, false);
            break;
        case Directions.TURN_LEFT:
            runMotor(PIN_INPUT_1, PIN_INPUT_2, true);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, true);
            break;
        case Directions.STOP:
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
		switch (translateIR(false))
        {
            case RemoteBtn.VOL_PLUS:
                move(Directions.MOVE_FORWARD);
                break;
            case RemoteBtn.VOL_MINUS:
                move(Directions.MOVE_BACKWARD);
                break;
            case RemoteBtn.FORWARD:
                move(Directions.TURN_RIGHT);
                break;
            case RemoteBtn.BACK:
                move(Directions.TURN_LEFT);
                break;
            case RemoteBtn.PAUSE:
                move(Directions.STOP);
                break;
            default:
                break;
        }
        delay(500);
		irrecv.resume(); // receive the next value
	}  
}
