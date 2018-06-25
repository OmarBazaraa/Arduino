# Embedded Systems Development Task
Simple Arduino program for XIOT internship filtration.

## About the System
The system has one input <i><b>switch</b></i> (push button) that controls a <i><b>LED</b></i>.<br>
Whenever the switch is pressed:
- The LED changes its state (from ON to OFF or vice versa).
- A serial holding the current state of the LED is sent to the serial monitor.

The system also has an analog <i><b>temperature sensor</b></i>.<br>
The temperature degree (in Celsius) is read every 3 seconds and is sent to the serial monitor.

## System Components
#### Ardunio
A microcontroller that controls and manages the system.

#### Switch
A simple ON/OFF push button connected to an <i><b>interrupt</b></i> input pin of the Arduino.<br>
Whenever the switch is pressed (during the rising edge), the Arduino automatically calls the interrupt-service routine (ISR) attached with that pin.

#### LED
A simple digital LED that toggle its state when pressing the switch.<br>
Connected to a digital output pin of the Arduino.

#### Temperature Sensor
An analog temperature sensor connected to one of the Arduino's analog pins with the following specifications:
- 0 volts correspond to -50 °C
- 5 volts correspond to 450 °C

The analog value is converted to a 10-bit digital value though the Analog-to-Digital converter (ADC) of the microcontroller.
- Minimum value: 0
- Maximum value: 2^10 - 1 = 1023

To convert from the digital sensor value to the actual voltage we will use the following mapping function:<br>
`voltage_value (in milliVolts) = digital_value * (5000 / 1023)`

To convert from the voltage value to the actual temperature Celsius degree we will use this simple mapping function:<br>
`temp_degree (in Celsius) = (voltage_value (in milliVolts) - 500) / 10`

## How to Use?
* Clone this repository.
* Get the system components and connect them as described above.
* Change the pins constant numbers in the code to match your actual connection.
* Make sure to install Arduino-IDE.
* Burn the code on the Arduino chip through the IDE.
* Run the system and keep watching the serial monitor.
