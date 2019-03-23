// Buttons

const int FORWARD_PIN_BTN = 9;
const int BACKWARD_PIN_BTN = 10;
const int LEFT_PIN_BTN = 11;
const int RIGHT_PIN_BTN = 12;

void initButton(int buttonBin)
{
	pinMode(buttonBin, INPUT_PULLUP);
}

/**
 * Use of 2 DC motor and a L293D
 */

// Motor 1 (left)
const int PIN_ACTIVATE_1_2 = 5;
const int PIN_INPUT_1 = 6;
const int PIN_INPUT_2 = 7;

// Motor 2 (right)
const int PIN_ACTIVATE_3_4 = 2;
const int PIN_INPUT_3 = 3;
const int PIN_INPUT_4 = 4;

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
			Serial.println("Forward");
            runMotor(PIN_INPUT_1, PIN_INPUT_2, false);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, true);
            break;
        case MOVE_BACKWARD:
			Serial.println("Backward");
            runMotor(PIN_INPUT_1, PIN_INPUT_2, true);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, false);
            break;
        case TURN_RIGHT:
			Serial.println("Right");
            runMotor(PIN_INPUT_1, PIN_INPUT_2, false);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, false);
            break;
        case TURN_LEFT:
			Serial.println("Left");
            runMotor(PIN_INPUT_1, PIN_INPUT_2, true);
            runMotor(PIN_INPUT_3, PIN_INPUT_4, true);
            break;
        case STOP:
			Serial.println("Stop");
            stopMotor(PIN_INPUT_1, PIN_INPUT_2);
            stopMotor(PIN_INPUT_3, PIN_INPUT_4);
            break;
    }
}

// Main functions

void setup()   
{
    Serial.begin(9600);

    // Initialize the buttons
	initButton(FORWARD_PIN_BTN);
	initButton(BACKWARD_PIN_BTN);
	initButton(LEFT_PIN_BTN);
	initButton(RIGHT_PIN_BTN);

    // Initialize the motors
    initMotor(PIN_ACTIVATE_1_2, PIN_INPUT_1, PIN_INPUT_2);
    initMotor(PIN_ACTIVATE_3_4, PIN_INPUT_3, PIN_INPUT_4);
}

void loop()   
{
	if (!digitalRead(FORWARD_PIN_BTN)) {
		move(MOVE_FORWARD);
	} else if (!digitalRead(BACKWARD_PIN_BTN)) {
		move(MOVE_BACKWARD);
	} else if (!digitalRead(LEFT_PIN_BTN)) {
		move(TURN_LEFT);
	} else if (!digitalRead(RIGHT_PIN_BTN)) {
		move(TURN_RIGHT);
	} else {
		move(STOP);
	}
	delay(500);
}
