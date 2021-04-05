//
// OP-DITTO teensy-controller (c) 2021 by Operation Ditto Team
// 
// OP-DITTO teensy-controller is licensed under a
// Creative Commons Attribution-ShareAlike 4.0 International License.
// 
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
//

//
// Globals
//
int PSP_SERIAL_BAUD             = 4800;         // The baud (bytes per second) rate
int PSP_SERIAL_PIN_X            = 0;            // The pin responsible for the second analog X axis
int PSP_SERIAL_PIN_Y            = 1;            // The pin responsible for the second analog Y axis
int PSP_SERIAL_REQ_BOTH         = 2;            // The request byte for when a user wants to receive both axes
int PSP_SERIAL_REQ_IS_ACTIVE    = 3;            // Request byte for checking if serial is active

//
// Setup
// Called on initialization, set pins up and
// turn the LED on.
//
void setup()
{
    // Print that we're booted up
    Serial.println("Teensy Started!");

    // Set up our pin modes for the X and Y input axes
    pinMode(PSP_SERIAL_PIN_X, INPUT_PULLUP);
    pinMode(PSP_SERIAL_PIN_Y, INPUT_PULLUP);

    // Start with 4800baud (max for the PSP UART)
    Serial1.begin(PSP_SERIAL_BAUD);

    // Turn pin6 (LED) ON
    digialWrite(6, HIGH);
}

//
// Loop
// Executed ever 2ms, handle requests sent to
// the Teensy.
//
void loop()
{
    // Check for Requests
    int request = Serial1.read();

    // If we're requesting either axis, go ahead and shoot the analog state back
    if (request == PSP_SERIAL_PIN_X || request == PSP_SERIAL_PIN_Y) {
        Serial1.write(analogRead(request));
    }

    // If there's any sync issues, user will request both
    if (request == PSP_SERIAL_REQ_BOTH) {
        Serial1.write(analogRead(PSP_SERIAL_PIN_X));
        Serial1.write(analogRead(PSP_SERIAL_PIN_Y));
    }

    // Check if we're Active
    if (request == PSP_SERIAL_REQ_IS_ACTIVE) {
        Serial1.write(byte(1));
    }

    // Delay for 5 microseconds
    delayMicroseconds(5);
}
