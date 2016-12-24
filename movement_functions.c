/**********************************************************************
/* Author:  Titan Robotics Club
/*
/* FUNCTION LIBRARY:  Movement Functions  (TRC_FL_Movement_Functions.c)
/*
/* USAGE:
/*  These functions are meant for use with any robot with the following:
/*  - 4 motor drive  (2 left side, 2 right side, sides are from the perspective of the robot)
/*  - Integrated Encoders must be installed on "leftDriveMotor" and "rightDriveMotor" (changed to correct name)
/*
/* FUNCTION DEFINITIONS:
/*  void setDriveMotorPower (int motorPower, char rightOrLeft)
/*  void driveStraight (int motorPower, int maxEncoderValue)
/*  void swingTurn (int motorPower, int maxEncoderValue, char leftOrRight)
/*  void pointTurn (int motorPower, int maxEncoderValue, char leftOrRight)
/*
/* VERSION HISTORY:
/*  11.22.2014 - Created (jrushing)
/*  11.05.2015 - Revised to make motor name changes easier
/*
/**********************************************************************/
 
//Number of motors on drive
#define NUMBER_OF_DRIVE_MOTORS 4
//Replace with names of motors that have encoders
#define MOTOR_WITH_LEFT_ENC leftMotorName
#define MOTOR_WITH_RIGHT_ENC rightMotorName

//WARNING: ONLY WORKS WITH EVEN NUMBERS OF MOTORS
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
 
// Set constant values for motor and turn functions
enum
{
	//each of these is the same as using #define, it just sets the first to 0, second to 1, etc.
	RIGHTSIDE, 
	LEFTSIDE,
	ALL

}
 
 
//++++++++++++++++++++++| function: SET DRIVE MOTOR POWER |++++++++++++++++++++++++++++++++++++
void setDriveMotorPower (int motorPower, int motors)
{
	
	int motorIndex;
	
    // Set power for RIGHTSIDE side drive motors
    if (motors == RIGHTSIDE) {
        //For the last half of the motors (right side), set them to motorPower
		//Subtract one because arrays start at 0
		for (motorIndex = NUMBER_OF_DRIVE_MOTORS; motorIndex > (NUMBER_OF_DRIVE_MOTORS/2)-1; motorIndex--)
		{
			motor[driveMotors[motorIndex]] = motorPower;
		}
 
    // Set power for LEFTSIDE side drive motors
    } else if (motors == LEFTSIDE) {
        //For the first half of the motors (left side), set them to motorPower
		for (motorIndex = 0; motorIndex < (NUMBER_OF_DRIVE_MOTORS/2); motorIndex++)
		{
			motor[driveMotors[motorIndex]] = motorPower;
		}
 
    // Set power for ALL drive motors
    } else if (motors == ALL) {
        //Go through all of the motors and set them to motorPower
		for (motorIndex = 0; motorIndex < NUMBER_OF_DRIVE_MOTORS; motorIndex++)
		{
			motor[driveMotors[motorIndex]] = motorPower;
		}
    }
 
}
 
 
//++++++++++++++++++++++++++| function: DRIVE STRAIGHT |++++++++++++++++++++++++++++++++++++
// Use + motorPower for moving forward
// Use - motorPower for moving backward
void driveStraight (int motorPower, int maxEncoderValue)
{
    int stopMotor = 0;
    int absMaxEncoderValue = abs(maxEncoderValue);
    int encoderValue = 0;
 
    // Reset the encoders
    nMotorEncoder[MOTOR_WITH_LEFT_ENC] = 0;
    nMotorEncoder[MOTOR_WITH_RIGHT_ENC] = 0;
 
    // Start the motors
    setDriveMotorPower(motorPower, RIGHTSIDE);
    setDriveMotorPower(motorPower, LEFTSIDE);
 
    // Keep driving straight until the absMaxEncoderValue is reached
    while (encoderValue < absMaxEncoderValue) {
 
    // If leftEncoderValue == rightEncoderValue, set motors to same power
        if (nMotorEncoder[MOTOR_WITH_LEFT_ENC] == nMotorEncoder[MOTOR_WITH_RIGHT_ENC]) { //
                setDriveMotorPower(motorPower, RIGHTSIDE);
                setDriveMotorPower(motorPower, LEFTSIDE);
        }
        if (motorPower > 0) {  // Forward
            // If the left motor is moving faster, decrease power by 15%
            if (nMotorEncoder[MOTOR_WITH_LEFT_ENC] > nMotorEncoder[MOTOR_WITH_RIGHT_ENC]) {
                setDriveMotorPower(motorPower, RIGHTSIDE);
                setDriveMotorPower(motorPower*.85, LEFTSIDE);
            }
            // If the right motor is moving faster, decrease power by 15%
            if (nMotorEncoder[MOTOR_WITH_LEFT_ENC] < nMotorEncoder[MOTOR_WITH_RIGHT_ENC]) {
                setDriveMotorPower(motorPower*.85, RIGHTSIDE);
                setDriveMotorPower(motorPower, LEFTSIDE);
            }
        } else {  // Reverse
            // If the left motor is moving faster, decrease power by 15%
            if (nMotorEncoder[MOTOR_WITH_LEFT_ENC] < nMotorEncoder[MOTOR_WITH_RIGHT_ENC]) {
                setDriveMotorPower(motorPower, RIGHTSIDE);
                setDriveMotorPower(motorPower*.85, LEFTSIDE);
            }
            // If the right motor is moving faster, decrease power by 15%
            if (nMotorEncoder[MOTOR_WITH_LEFT_ENC] > nMotorEncoder[MOTOR_WITH_RIGHT_ENC]) {
                setDriveMotorPower(motorPower*.85, RIGHTSIDE);
                setDriveMotorPower(motorPower, LEFTSIDE);
            }
        }
 
        // Reset encoder value for loop test
        encoderValue = abs(nMotorEncoder[MOTOR_WITH_LEFT_ENC]);
 
    } // End WHILE loop
 
    // Stop motors
    setDriveMotorPower(stopMotor, RIGHTSIDE);
    setDriveMotorPower(stopMotor, LEFTSIDE);
}
 
 
 
//++++++++++++++++++++++++++| function: Swing Turn |++++++++++++++++++++++++++++++++++++
void swingTurn (int motorPower, int maxEncoderValue, INT leftOrRight)
{
    int stopMotor = 0;
 
    // Stop motors
    setDriveMotorPower(0, RIGHTSIDE);
    setDriveMotorPower(0, LEFTSIDE);
 
    //swing turn left: (L=0, R=+)
    if (leftOrRight == LEFTSIDE) {
 
        setDriveMotorPower(motorPower, RIGHTSIDE);
        while (nMotorEncoder[MOTOR_WITH_RIGHT_ENC] < maxEncoderValue) {
            // Keep turning while maxEncoderValue hasn't been reached
        }
        setDriveMotorPower(stopMotor, RIGHTSIDE);
 
    //swing turn right: (L=+, R=0)
    } else if (leftOrRight == RIGHTSIDE) {
 
        setDriveMotorPower(motorPower, LEFTSIDE);
        while (nMotorEncoder[MOTOR_WITH_LEFT_ENC] < maxEncoderValue) {
            // Keep turning while maxEncoderValue hasn't been reached
        }
        setDriveMotorPower(stopMotor, LEFTSIDE);
    }
 
}
 
//++++++++++++++++++++++++++| function: Swing Turn |++++++++++++++++++++++++++++++++++++
void pointTurn (int motorPower, int maxEncoderValue, int leftOrRight)
{
    int stopMotor = 0;
    int reverse = -1;
 
    // Stop motors
    setDriveMotorPower(stopMotor, RIGHTSIDE);
    setDriveMotorPower(stopMotor, LEFTSIDE);
 
    /***** swing turn left: (L=-, R=+) *****/
    if (leftOrRight == LEFTSIDE) {
 
        setDriveMotorPower(motorPower, RIGHTSIDE);
        setDriveMotorPower(reverse*motorPower, LEFTSIDE);
        while (nMotorEncoder[MOTOR_WITH_RIGHT_ENC] < maxEncoderValue) {
            // Keep turning while maxEncoderValue hasn't been reached
        }
 
    /***** swing turn right: (L=+, R=-) *****/
    } else if (leftOrRight == RIGHTSIDE) {
 
        setDriveMotorPower(motorPower, LEFTSIDE);
        setDriveMotorPower(reverse*motorPower, RIGHTSIDE);
        while (nMotorEncoder[MOTOR_WITH_LEFT_ENC] < maxEncoderValue) {
            // Keep turning while maxEncoderValue hasn't been reached
        }
    }
 
    // Stop motors
    setDriveMotorPower(stopMotor, RIGHTSIDE);
    setDriveMotorPower(stopMotor, LEFTSIDE);
 
}
