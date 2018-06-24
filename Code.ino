// ==========================================
// GLOBAL CONSTANTS & VARIABLES
// ==========================================

// IO pins assignments
const int LED_PIN = 13;
const int SWITCH_PIN = 2;
const int TEMP_SENSOR_PIN = 0;

// Temperature sensor scan interval in milliseconds
const int TEMP_SENSOR_INTERVAL_MILLIS = 3000;

// The timestamp in milliseconds of the last temperature sensor scan
long prevTempTimestamp = 0;

// Flag to indicate whether "pressed" is sent to the serial monitor or not
bool pressedSent = false;

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
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), switchHandler, CHANGE);

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
 * To be called whenever the state of the switch is changed
 * (i.e. from LOW to HIGH or vice versa).
 */
void switchHandler() {
    // Read the state of the switch (ON or OFF)
    int state = digitalRead(SWITCH_PIN);

    // Reflect the switch state to the LED
    digitalWrite(LED_PIN, state);

    // Send LED state through serial port
    Serial.println(state ? "LED ON" : "LED OFF");

    // Send switch pressed message only the first time the switch is changed
    if (!pressedSent) {
        Serial.println("Pressed");
        pressedSent = true;
    }
}

/**
 * Reads the temperature sensor value every fixed interval
 * of time (3 seconds), and send the temperature (in Celsius degree)
 * to the serial monitor.
 */
void scanTemperature() {
    long currentMillis = millis();

    // Return if the interval didn't pass yet
    if (currentMillis - prevTempTimestamp < TEMP_SENSOR_INTERVAL_MILLIS) {
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