//
// OP-DITTO teensy-controller (c) 2021 by Operation Ditto Team
// 
// OP-DITTO teensy-controller is licensed under a
// Creative Commons Attribution-ShareAlike 4.0 International License.
// 
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
//
#include <HardwareSerial.h>

//
// Globals
//
int PSP_SERIAL_BAUD             = 4800;         // The baud (bytes per second) rate
int PSP_SERIAL_PIN_X            = 0;            // The pin responsible for the second analog X axis
int PSP_SERIAL_PIN_Y            = 1;            // The pin responsible for the second analog Y axis
int PSP_SERIAL_REQ_BOTH         = 2;            // The request byte for when a user wants to receive both axes
int PSP_SERIAL_REQ_IS_ACTIVE    = 3;            // Request byte for checking if serial is active

// TODO: Investigate why this is so.. weird
int ANALOG_X_MAXIMUM            = 750;
int ANALOG_X_MINIMUM            = 128;
int ANALOG_Y_MAXIMUM            = 861;
int ANALOG_Y_MINIMUM            = 265;

void boot_text()
{
  Serial.println("=================================================");
  Serial.println(" ___________      ______ _____ _____ _____ _____ ");
  Serial.println("|  _  | ___ \\     |  _  \\_   _|_   _|_   _|  _  |");
  Serial.println("| | | | |_/ /_____| | | | | |   | |   | | | | | |");
  Serial.println("| | | |  __/______| | | | | |   | |   | | | | | |");
  Serial.println("\\ \\_/ / |         | |/ / _| |_  | |   | | \\ \\_/ /");
  Serial.println(" \\___/\\_|         |___/  \\___/  \\_/   \\_/  \\___/ ");
  Serial.println("=================================================");
}

//
// Setup
// Called on initialization, set up pins and turn
// the LED on.
//
void setup()
{
    // Epic Boot Text
    boot_text();

    // Set up our pin modes for the X and Y input axes
    pinMode(PSP_SERIAL_PIN_X, INPUT_PULLUP);
    pinMode(PSP_SERIAL_PIN_Y, INPUT_PULLUP);

    // Start with 4800baud (max for the PSP UART)
    Serial1.begin(PSP_SERIAL_BAUD);

    // Turn pin6 (LED) ON
    digitalWrite(6, HIGH);
}

//
// Loop
// Executed every 5mis, handle UART requests
// sent to the Teensy and do analog conversions.
//
void loop()
{
    // Grab the X Axis
    int analog_x = analogRead(PSP_SERIAL_PIN_X);
    analog_x = map(analog_x, ANALOG_X_MINIMUM, ANALOG_X_MAXIMUM, 0, 255);

    if (analog_x > 255) analog_x = 255;
    if (analog_x < 0) analog_x = 0;

    byte analog_x_byte = byte(analog_x); // put it in byte form for later

    // Grab the Y Axis
    int analog_y = analogRead(PSP_SERIAL_PIN_Y);
    analog_y = map(analog_y, ANALOG_Y_MINIMUM, ANALOG_Y_MAXIMUM, 0, 255);

    if (analog_y > 255) analog_y = 255;
    if (analog_y < 0) analog_y = 0;

    byte analog_y_byte = byte(analog_y); // put it in byte form for later

    Serial.println(analog_x_byte);
    Serial.println(analog_y_byte);

    // Delay for 5 microseconds
    delayMicroseconds(500);
}
