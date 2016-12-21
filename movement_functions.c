/**********************************************************************
/* Author:  Titan Robotics Club
/*
/* FUNCTION LIBRARY:  Movement Functions  (TRC_FL_Movement_Functions.c)
/*
/* USAGE:
/*  These functions are meant for use with any robot with the following:
/*  - 4 motor drive  (2 left side, 2 right side, sides are from the perspective of the robot)
/*  - Integrated Encoders must be installed on "leftBackMotor" and "rightBackMotor"
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
 
// Change these to motor names
#define rightFrontMotor FR
#define rightBackMotor  BR
#define leftFrontMotor  FL
#define leftBackMotor       BL
 
// Set constant values for motor and turn functions
#define RIGHTSIDE   0
#define LEFTSIDE    1
#define ALL     2
 
 
//++++++++++++++++++++++| function: SET DRIVE MOTOR POWER |++++++++++++++++++++++++++++++++++++
void setDriveMotorPower (int motorPower, int motors)
{
    // Set power for RIGHTSIDE side drive motors
    if (motors == RIGHTSIDE) {
        motor[rightFrontMotor] = motorPower;
        motor[rightBackMotor] = motorPower;
 
    // Set power for LEFTSIDE side drive motors
    } else if (motors == LEFTSIDE) {
        motor[leftFrontMotor] = motorPower;
        motor[leftBackMotor] = motorPower;
 
    // Set power for ALL drive motors
    } else if (motors == ALL) {
        motor[rightFrontMotor] = motorPower;
        motor[rightBackMotor] = motorPower;
        motor[leftFrontMotor] = motorPower;
        motor[leftBackMotor] = motorPower;
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
    nMotorEncoder[leftBackMotor] = 0;
    nMotorEncoder[rightBackMotor] = 0;
 
    // Start the motors
    setDriveMotorPower(motorPower, RIGHTSIDE);
    setDriveMotorPower(motorPower, LEFTSIDE);
 
    // Keep driving straight until the absMaxEncoderValue is reached
    while (encoderValue < absMaxEncoderValue) {
 
    // If leftEncoderValue == rightEncoderValue, set motors to same power
        if (nMotorEncoder[leftBackMotor] == nMotorEncoder[rightBackMotor]) { //
                setDriveMotorPower(motorPower, RIGHTSIDE);
                setDriveMotorPower(motorPower, LEFTSIDE);
        }
        if (motorPower > 0) {  // Forward
            // If the left motor is moving faster, decrease power by 15%
            if (nMotorEncoder[leftBackMotor] > nMotorEncoder[rightBackMotor]) {
                setDriveMotorPower(motorPower, RIGHTSIDE);
                setDriveMotorPower(motorPower*.85, LEFTSIDE);
            }
            // If the right motor is moving faster, decrease power by 15%
            if (nMotorEncoder[leftBackMotor] < nMotorEncoder[rightBackMotor]) {
                setDriveMotorPower(motorPower*.85, RIGHTSIDE);
                setDriveMotorPower(motorPower, LEFTSIDE);
            }
        } else {  // Reverse
            // If the left motor is moving faster, decrease power by 15%
            if (nMotorEncoder[leftBackMotor] < nMotorEncoder[rightBackMotor]) {
                setDriveMotorPower(motorPower, RIGHTSIDE);
                setDriveMotorPower(motorPower*.85, LEFTSIDE);
            }
            // If the right motor is moving faster, decrease power by 15%
            if (nMotorEncoder[leftBackMotor] > nMotorEncoder[rightBackMotor]) {
                setDriveMotorPower(motorPower*.85, RIGHTSIDE);
                setDriveMotorPower(motorPower, LEFTSIDE);
            }
        }
 
        // Reset encoder value for loop test
        encoderValue = abs(nMotorEncoder[leftBackMotor]);
 
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
        while (nMotorEncoder[rightBackMotor] < maxEncoderValue) {
            // Keep turning while maxEncoderValue hasn't been reached
        }
        setDriveMotorPower(stopMotor, RIGHTSIDE);
 
    //swing turn right: (L=+, R=0)
    } else if (leftOrRight == RIGHTSIDE) {
 
        setDriveMotorPower(motorPower, LEFTSIDE);
        while (nMotorEncoder[leftBackMotor] < maxEncoderValue) {
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
        while (nMotorEncoder[rightBackMotor] < maxEncoderValue) {
            // Keep turning while maxEncoderValue hasn't been reached
        }
 
    /***** swing turn right: (L=+, R=-) *****/
    } else if (leftOrRight == RIGHTSIDE) {
 
        setDriveMotorPower(motorPower, LEFTSIDE);
        setDriveMotorPower(reverse*motorPower, RIGHTSIDE);
        while (nMotorEncoder[leftBackMotor] < maxEncoderValue) {
            // Keep turning while maxEncoderValue hasn't been reached
        }
    }
 
    // Stop motors
    setDriveMotorPower(stopMotor, RIGHTSIDE);
    setDriveMotorPower(stopMotor, LEFTSIDE);
 
}
