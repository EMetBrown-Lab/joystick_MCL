# Joystick Control for MadCity Labs Microcontroller

This project provides code to control a microcontroller from MadCity Labs using a joystick. It is compatible with devices having the serial numbers: **RM21 Classic MCL-uS2671** and **LP200: MCLS04446**.

## Getting Started

You can directly use the application from the [Releases](#) section. If the pre-built application does not work, you can compile the code yourself using the provided `Makefile`.

## Features

- **Precise Displacement Control**: Adjust the stage movement precisely by specifying how far the stage should move with each button press.
- **Continuous Movement**: Keep the stage moving as long as the button is held down. The stage stops moving when you release the button.
- **Stop Movement**: Press the stop button to immediately halt the stage.

## Menu Options

- **Reset Axis**: Set the axis coordinates to `(0, 0, 0)`.
- **Go Home**: Quickly move to the `(0, 0, 0)` position using a fast 3-axis motion.
- **Reset Axis**: Perform a full range of motion to return to the center of the stage.

## Screenshot

<img src="screenshot.png" width="250">
