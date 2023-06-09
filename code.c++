#pragma config(Sensor, in3,    line,           sensorLineFollower)
#pragma config(Sensor, dgtl8,  solanoid,       sensorDigitalOut)
#pragma config(Sensor, dgtl12, button,         sensorTouch)
#pragma config(Motor,  port3,           myMotor,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           servo,         tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// GLOBAL VARIABLES //
bool debounce = false;
bool buttonPress = false;

// MAIN PROGRAM //
void sort() { // Sorts marbles based on sensor's readings
	if (SensorValue(line) < 1400) { // White
		setServo(servo, 90);
	}
	if (SensorValue(line) > 1400 && SensorValue(line) < 2650) { // Metal (dark)
		setServo(servo, 0);
	}
	if (SensorValue(line) > 2650) { // Clear
		setServo(servo, -90);
	}
}

task main() {
	// Reset all values and calibrate sensors
	buttonPress = false;
	SensorValue(solanoid) = 0;
	SensorValue(line) = 0;
	stopMotor(myMotor);
	while (true) {
		if (SensorValue(button) == 1 && buttonPress == false) {
			buttonPress = true;
		}
		if (buttonPress == true && debounce == false) { // Machine starts on button press
			debounce = true; // Debounce necessary, else loop repeats instantaneously
			startMotor(myMotor, 15);
			wait(0.535);
			stopMotor(myMotor);
			wait(2.1); // Allow sensor 2.1 seconds to sense marble
			sort();
			SensorValue(solanoid) = 1;
			wait(0.3);
			SensorValue(solanoid) = 0;
			SensorValue(line) = 0;
			debounce = false;
		}
	}
}


