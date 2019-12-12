/**
 * Use of a DC motor and a L293D
 */

const int PIN_ACTIVATE_3_4 = 2;
const int PIN_INPUT_3 = 3;
const int PIN_INPUT_4 = 4;


void setup()
{
    pinMode(PIN_ACTIVATE_3_4, OUTPUT);
    pinMode(PIN_INPUT_3, OUTPUT);
    pinMode(PIN_INPUT_4, OUTPUT);

    // Enable the motor driver
    digitalWrite(PIN_ACTIVATE_3_4, HIGH); 
}

void loop()
{
    // Run the motor clockwise
    digitalWrite(PIN_INPUT_3, HIGH);
    digitalWrite(PIN_INPUT_4, LOW);
    delay(2000);
    
    // Run the motor counter-clockwise
    digitalWrite(PIN_INPUT_3, LOW);
    digitalWrite(PIN_INPUT_4, HIGH);
    delay(2000);
}