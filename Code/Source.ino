// ==========================================
// GLOBAL CONSTANTS & VARIABLES
// ==========================================

// IO pins assignments
const int LED_PIN = 13;         // Digital Pin
const int SWITCH_PIN = 2;       // Interrupt Pin
const int TEMP_SENSOR_PIN = 0;  // Analog Pin

// Temperature sensor scan interval in milliseconds
const int TEMP_SENSOR_INTERVAL = 3000;

// The timestamp (in milliseconds) of the last temperature sensor scan
long prevTempTimestamp = 0;

// LED state
int ledState = 0;

// ==========================================
// ARDUINO FUNCTIONS
// ==========================================

/**
 * Arduino setup function, needed to initialize things up.
 * To be called only once at the beginning.
 */
void setup() {
    // ...

    // Configure serial port data rate
    Serial.begin(9600);

    // Setup pins modes
    pinMode(LED_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT);
    pinMode(TEMP_SENSOR_PIN, INPUT);

    // Attach the switch interrupt handler (ISR)
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), switchHandler, RISING);

    // ...
}

/**
 * Arduino loop function. To be called indefinitely.
 */
void loop() {
    // ...

    scanTemperature();

    // ...
}

/**
 * The interrupt service routine of the switch.
 * To be called during the rising edge of the switch.
 * (i.e. from LOW to HIGH)
 */
void switchHandler() {
    // Toggle the state of the LED
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    // Send info messages through serial monitor
    Serial.println("Pressed");
    Serial.println(ledState ? "LED ON" : "LED OFF");
}

/**
 * Reads the temperature sensor value every fixed interval
 * of time (3 seconds), and send the temperature (in Celsius degree)
 * to the serial monitor.
 */
void scanTemperature() {
    long currentMillis = millis();

    // Return if the interval didn't pass yet
    if (currentMillis - prevTempTimestamp < TEMP_SENSOR_INTERVAL) {
        return;
    }

    // Update the temperature scan timestamp
    prevTempTimestamp = currentMillis;

    // Scan temperature sensor value (10-bits value)
    // Minimum value: 0
    // Maximum value: 1023
    int sensorValue = analogRead(TEMP_SENSOR_PIN);

    // Map the read sensor value into voltage value (milli volts)
    // 0    value       ->  0       milli volts
    // 1023 value       ->  5000    milli volts
    double voltage = sensorValue * (5000.0 / 1023);

    // Map voltage (in milli volts) into temperature Celsius degree
    // 0    milli volts ->  -50     degree Celsius
    // 5000 milli volts ->  450     degree Celsius
    double temperature = (voltage - 500.0) / 10.0;

    // Send the temperature value to the serial monitor
    Serial.print("Temperature (Celsius): ");
    Serial.println(temperature);
}