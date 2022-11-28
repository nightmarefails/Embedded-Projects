/*  Creation Crate Mood Lamp
This lamp smoothly cycles through a colour spectrum.
It only turns on when its surroundings are dark.
*/

int pulseSpeed = 5; //  This value controls how fast the mood lamp runs. You can replace this with any whole number.

//  These are the pins we are using with the UNO R3 (Arduino-compatible). You can see the numbers on the board itself.
int ldrPin = 0;    // LDR in Analog Input 0 to read the surrounding light.
int redLed = 11;   // red LED in Digital Pin 11.
int greenLed = 10; // green LED in Digital Pin 10.
int blueLed = 9;   // blue LED in DIgital Pin 9.
int ambientLight;  // This variable stores the value of the light in the room.
int power = 150;   // This variable controls the brightness of the lamp (2-255).
float RGB[3];      // This is an ‘array’. It holds 3 values: RGB[0], RGB[1], and RGB[2], used to store the values of the Red, Blue, and Green LEDs.
float CommonMathVariable = 180 / PI;

void setup()
{
    Serial.begin(9600); // This sets the communication speed for the Serial Monitor, which can be used for testing.
    // These tell the UNO R3 that data is sent OUT of these pins to the LEDs.
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(blueLed, OUTPUT);

    //  This sets all the outputs (LEDs) to low (as in off), so that they do not turn on during startup.
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
}

/* Main Loop
This part of the program is a ‘loop’. It
repeats itself over and over again, making a small change in the
brightness of the LEDs each time - this creates a smooth transition in
colour. */

void loop()
{

    for (float x = 0; x < PI; x = x + 0.00001)
    {
        RGB[0] = power * abs(sin(x * (CommonMathVariable)));                  // Red LED.
        RGB[1] = power * abs(sin((x + PI / 3) * (CommonMathVariable)));       // Green LED.
        RGB[2] = power * abs(sin((x + (2 * PI) / 3) * (CommonMathVariable))); // Blue LED.

        ambientLight = analogRead(ldrPin); // This reads the light in the room and stores it as a number.
        Serial.print("Ambient Light Reading: ");
        Serial.println(ambientLight); // We can print the value of the ldr to the Serial Monitor for testing


        if (ambientLight > 500)
        {
            // These ‘analogWrite’ statements will send the values calculated above to the LEDs.
            analogWrite(redLed, RGB[0]);
            analogWrite(greenLed, RGB[1]);
            analogWrite(blueLed, RGB[2]);
        } 
        else
        {
            digitalWrite(redLed, LOW);
            digitalWrite(greenLed, LOW);
            digitalWrite(blueLed, LOW);
        }

        for (int i = 0; i < 3; i++)
        {
            if (RGB[i] < 1)
            {
                delay(20 * pulseSpeed);
            }
            else if (RGB[i] < 5)
            {
                delay(10 * pulseSpeed);
            }
            else if (RGB[i] < 10)
            {
                delay(2 * pulseSpeed);
            }
            else if (RGB[i] < 100)
            {
                delay(1 * pulseSpeed);
            }
            // This blank ‘else statement’ is a fail-safe mechanism. It instructs the program to do nothing if the conditions above do not activate. This prevents the program from generating errors when calculating delays.
            else
            {
            }
        }
        delay(10);
    }
}