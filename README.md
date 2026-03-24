# Maze Solving Robot (ELEC1601)

This project was developed as part of the ELEC1601 unit and involves building an autonomous maze-solving robot using Arduino. The robot navigates a maze using infrared (IR) sensors and a decision-making algorithm to detect and respond to obstacles in real time.

## Features

* Autonomous maze navigation using IR sensors
* Real-time obstacle detection (left, right, front)
* Dynamic path correction (left/right adjustments)
* 90-degree turns and U-turn capability
* Continuous environment scanning using frequency-based IR detection

## Technologies Used

* Arduino (C/C++)
* Servo motors for movement control
* Infrared (IR) sensors for distance detection
* Embedded systems programming

## How It Works

The robot uses three IR sensors (left, right, and front) to detect nearby obstacles. Each sensor scans across a range of frequencies (~38 kHz to 42 kHz) to improve detection reliability.

Based on sensor readings:

* The robot adjusts its path if it is too close to a wall
* Executes left or right 90° turns when openings are detected
* Performs a U-turn when no forward path is available
* Maintains forward motion with continuous micro-adjustments

The navigation logic is implemented using conditional decision-making in the main control loop, allowing the robot to react dynamically to the maze environment.

## Key Implementation Details

* Custom IR detection function using frequency sweeping for robust sensing
* Servo motor control using precise microsecond signals
* State tracking (e.g., `rightDone`, `leftDone`) to manage navigation decisions
* Logic to avoid repeated turns and improve path efficiency

## What I Learned

* Embedded systems programming with Arduino
* Sensor integration and signal processing
* Real-time decision-making in autonomous systems
* Debugging hardware-software interactions
* Control of motors using PWM signals

## Author

Your Name

