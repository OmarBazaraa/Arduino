# About
I have always been interested in embedded system development, so I am looking forward to get accepted in this internship to
 - Gain more experience regarding embedded systems
 - Extend my connection network

I am also looking forward to have a chance to participate in a real life projects, not just "proof-of-concept" projects.

## Previous Experience
I have participated (in a team of 4 members) in developing a CNC machine that can solve the famous Android Flow game, and can draw images.

And here you can find a trailer video of our machine...

### Trailer Video:
[![IMAGE ALT TEXT](http://img.youtube.com/vi/A8BskRCSG7A/0.jpg)](http://www.youtube.com/watch?v=A8BskRCSG7A "CNC Machine")

And for more information you can visit our project's repository on GitHub from [here](https://github.com/OmarBazaraa/CNC-Machine).

### Used languages, platforms, ..etc.
In this project we did use lots of platforms together to build the system.

We used:

#### C++
We used C++ to develop the computer-side algorithms for solving the Flow game, and for converting an image into a drawing-instructions that the CNC Machine can handle.

#### OpenCV
We used OpenCV as an image processing framework to
- Extract the state of the game from the taken screenshot.
- Detect the position of the "Next Level" button after the game is solved.
- Do thresholding and some pre-processing on the image before running painter algorithm.

#### Android (ADB)
We used Android Debug Bridge (ADB) to automatically
- Get phone screen size and resolution to adjust the machine movement.
- Capture screenshots from the phone.
- Press the "Next Level" button on the given screen position.
- Get the foreground activity regularly to check if the game has been suspended or still running.

#### Arduino (C)
We used Arduino to
- Control the motors and the sensors on the CNC machine
- Execute the instructions received from the Java controller program.
- Protect the CNC against some faults that might occur.

#### Java (Processing)
We used Java to manages and controls all the previously mentioned platforms and programs.

It allows the user to select one of the following tasks:

- Solve flow game.
- Paint photo on paper.
- Play piano from the keyboard.
- Calibrate the CNC manually.

This controller program is designed in an expandable way. All the logic to communicate and configure the CNC is encapsulated in `CNCTask` class. So we can simply add new tasks by just extending `CNCTask` class and implementing few methods without the need to deal with the underlying logic for communicating with the Arduino.

### What I have done in this project

- Participated in developing and structuring the Arduino-side program.
- Developed the flow solver algorithm in C++.
- Developed the painter algorithm in C++.
- Designed the software structure of the Java controller program that gives orders to the Arduino.
- Supported and collaborated the hardware sub-team to handle multiple possible faults
	- CNC Machine out of range faults.
	- Phone not in position.
	- Flow game activity moved to the background.
	- Phone disconnected.
	- Power-off.
