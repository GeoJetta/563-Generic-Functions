#pragma config(UART_Usage, UART2, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in2,    handPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in3,    gyroSensor,     sensorGyro)
#pragma config(Sensor, in4,    leftLine,       sensorLineFollower)
#pragma config(Sensor, in5,    rightLine,      sensorLineFollower)
#pragma config(Sensor, dgtl8,  sonarLeft,      sensorSONAR_mm)
#pragma config(Sensor, dgtl10, sonarRight,     sensorSONAR_mm)
#pragma config(Sensor, dgtl12, fingerControl,  sensorDigitalOut)
#pragma config(Sensor, I2C_1,  RightWheel,     sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  LeftWheel,      sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           leftFrontDrive, tmotorVex393HighSpeed_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           leftBackDrive, tmotorVex393HighSpeed_MC29, openLoop, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port3,           leftTopArm,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftBottomArm, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           leftHand,      tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port6,           rightHand,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           rightBottomArm, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightTopArm,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightBackDrive, tmotorVex393HighSpeed_MC29, openLoop, reversed, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port10,          rightFrontDrive, tmotorVex393HighSpeed_HBridge, openLoop, driveRight)
 
/*----------------------------------------------------------------------------------------------------*/
/*                                                                                                    */
/*                                MOTOR CONTROL & CURRENT MANAGEMENT                                  */
/*                                                                                                    */
/* Adapted from original code - Source:  http://www.vexforum.com/showpost.php?p=225727&postcount=25   */
/* Article: http://www.vexmen.com/2014/02/troubles-tripping-circuit-breakers-with-10-big-393-motors/  */
/*                                                                                                    */
/*----------------------------------------------------------------------------------------------------*/
 
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  definitions used by driver control                                         */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
 
#define     JOY_DRIVE_V     vexJSLeftV   // Ch 3
#define     JOY_DRIVE_H     vexJSLeftH   // Ch 4
#define     JOY_THRESHOLD   15
 
 
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  definitions and variables for the motor slew rate controller.              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
 
#define MOTOR_NUM               kNumbOfTotalMotors
#define MOTOR_MAX_VALUE         127
#define MOTOR_MIN_VALUE         (-127)
#define MOTOR_DEFAULT_SLEW_RATE 10      // Default will cause 375mS from full fwd to rev
#define MOTOR_FAST_SLEW_RATE    256     // essentially off
#define MOTOR_TASK_DELAY        15      // task 1/frequency in mS (about 66Hz)
#define MOTOR_DEADBAND          10
 
// Array to hold requested speed for the motors
int motorReq[ MOTOR_NUM ];
 
// Array to hold "slew rate" for the motors, the maximum change every time the task
// runs checking current mootor speed.
int motorSlew[ MOTOR_NUM ];
 
void moveLeftWheels(int motorSpeed){
    motor[leftFrontDrive] = motor[leftBackDrive] = motorSpeed;
}
 
void moveRightWheels(int motorSpeed){
    motor[rightBackDrive] = motor[rightFrontDrive] = motorSpeed;
}
 
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*  Task  - compares the requested speed of each motor to the current speed    */
/*          and increments or decrements to reduce the difference as nexessary */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
 
task MotorSlewRateTask()
{
    int motorIndex;
    int motorTmp;
 
    // Initialize stuff
    for(motorIndex=0;motorIndex<MOTOR_NUM;motorIndex++)
    {
        motorReq[motorIndex] = 0;
        motorSlew[motorIndex] = MOTOR_DEFAULT_SLEW_RATE;
    }
 
    // run task until stopped
    while( true )
    {
        // run loop for every motor
        for( motorIndex=0; motorIndex<MOTOR_NUM; motorIndex++)
        {
            // So we don't keep accessing the internal storage
            motorTmp = motor[ motorIndex ];
 
            // Do we need to change the motor value ?
            if( motorTmp != motorReq[motorIndex] )
            {
                // increasing motor value
                if( motorReq[motorIndex] > motorTmp )
                {
                    motorTmp += motorSlew[motorIndex];
                    // limit
                    if( motorTmp > motorReq[motorIndex] )
                        motorTmp = motorReq[motorIndex];
                    }
 
                // decreasing motor value
                if( motorReq[motorIndex] < motorTmp )
                {
                    motorTmp -= motorSlew[motorIndex];
                    // limit
                    if( motorTmp < motorReq[motorIndex] )
                        motorTmp = motorReq[motorIndex];
                }
 
                // finally set motor
                motor[motorIndex] = motorTmp;
            }
        }
 
        // Wait approx the speed of motor update over the spi bus
        wait1Msec( MOTOR_TASK_DELAY );
        }
}
 
 
task ArcadeDrive()
{
    int    ctl_v;
    int    ctl_h;
    int    drive_l;
    int    drive_r;
 
    // Basic arcade control
    while( true )
      {
            // Get joystick H and V control
            ctl_v = vexRT[ JOY_DRIVE_V ];
            ctl_h = vexRT[ JOY_DRIVE_H ];
 
            // Ignore joystick near center
            if( (abs(ctl_v) <= JOY_THRESHOLD) && (abs(ctl_h) <= JOY_THRESHOLD) )
            {
                drive_l = 0;
                drive_r = 0;
            }
            else
            {
                // Create drive for left and right motors
                drive_l = (ctl_v + ctl_h) / 2;
                drive_r = (ctl_v - ctl_h) / 2;
            }
 
            // Now send out to motors
            moveLeftWheels( drive_l );
            moveRightWheels( drive_r );
 
            // don't hog CPU
            wait1Msec( 25 );
        }
}
 
 
 
task main()
{
    // Start motor slew rate control
    startTask( MotorSlewRateTask );
 
    // Start driver control tasks
    startTask( ArcadeDrive );
 
    // Everything done in other tasks
    while( true )
    {
        wait1Msec( 100 );
    }
}
