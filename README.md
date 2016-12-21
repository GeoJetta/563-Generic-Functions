# 563 Generic Functions

A library of functions for all of your needs! These should work with any robot, provided you modify them in a few key places.

##Editing the Libraries and Your Own Files
###Your Code
Here's what you need to change in your own code to use these libraries:
- Insert `#include` statements for every library
  - To do this, underneath the automatic `#include` statement created by the Competition Template (or above PreAuton or similar task), use `#include <file name>`. If the file is in a different spot than your main code, also use the file path like `include path/to/file/<file name>`. [![git1.png](https://s23.postimg.org/e7z521ee3/git1.png)](https://postimg.org/image/3xwq2soif/).

- Add in `startTask()`
  - Depending on where you want to use these functions, you can include them in PreAuton (for choosing autons with the LCD), Auton, or User Control sections
  - To start one of the tasks from the library, just use `startTask()` inside PreAuton, Auton, or User Control loops. Just make sure not to put them in the `while()` loop that's in User Control! [![git2.png](https://s27.postimg.org/spbrcvyo3/git2.png)](https://postimg.org/image/kjtpeqaf3/)

- Using Functions
  - Check out a function in the file and check what it asks for
  - Then use it like this: `<function name>(<stuff it asks for>);`

###In the Files
Here's what you need to change in the libraries before you use them:
-`lcd.c`
  - Make sure your LCD is plugged into UART 2.
  - On `line 46`, change `string_1`, `string_2`, etc. to the label you want to see on the LCD screen for each autonomous.
  - This isn't done yet!
-`movement_functions`
  - Change the number after `#define NUMBER_OF_DRIVE_MOTORS` to how many motors you have on your drive.
  - Change `leftMotorName` and `rightMotorName` after `#define MOTOR_WITH_LEFT_ENC` and `#define MOTOR_WITH_RIGHT_ENC` to the name of your motor the IME is on
  - Follow the instructions in this array:
```
tMotor driveMotors[NUMBER_OF_DRIVE_MOTORS] =
{
	
	/****************************************************************/
	/*	INSERT MOTOR NAMES HERE  									*/
	/*		Go in order from back to front, left to right			*/
	/*	EXAMPLE:													*/
	/*		leftBackMotor, leftMiddleMotor, leftFrontMotor			*/
	/*		rightBackMotor, rightMiddleMotor, rightFrontMotor		*/
	/*	USE THIS FORMATTING FOR ANY AND ALL DRIVE CONFIGURATIONS	*/
	/****************************************************************/
	
}
```
- `slew_rate`
  - For this task, the default values should be fine. If you want to tweak it, the number after `#define MOTOR_DEFAULT_SLEW_RATE` will change how fast your motor values change.
  - **Note:** This library can be used with anything else, because it runs in the background. Just make sure to test it with your robot to make sure there are no kinks!
