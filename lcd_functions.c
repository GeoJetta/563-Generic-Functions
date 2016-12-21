/**********************************************************************
/* Author:  Titan Robotics Club
/*
/* FUNCTION LIBRARY:  LCD Functions  (TRC_FL_LCD_Autonomous_Choice.c)
/*
/* USAGE: This file is meant to be included for use with any robot
/*              with a 3-button LCD display in stalled on UART Port 2 (UART2)
/*
/* FUNCTION DEFINITIONS:
/*  void waitForPress()
/*  void waitForRelease()
/*  int chooseAutonomous (string choice_0, string choice_1, string choice_2, string choice_3)
/*
/* ROBOT CONFIGURATION
/*  MOTORS & SENSORS:
/*  [I/O Port]                  [Name]                          [Type]                              [Description]
/*  UART Port 2                 none                                VEX LCD                             VEX LCD Screen
/*
/* VERSION HISTORY:
/*  11.22.2014 - Created (jrushing)
/*
/**********************************************************************/
 
//////////////////////
// GLOBAL VARIABLES //
//////////////////////
int gAutonomousChoice_LCD = 0;
 
//Wait for Press--------------------------------------------------
void waitForPress()
{
    while(nLCDButtons == 0){}
    wait1Msec(5);
}
//----------------------------------------------------------------
 
//Wait for Release------------------------------------------------
void waitForRelease()
{
    while(nLCDButtons != 0){}
    wait1Msec(5);
}
//----------------------------------------------------------------
 
//Choose Autonomous------------------------------------------------
int chooseAutonomous (string choice_0, string choice_1, string choice_2, string choice_3, string choice_4)
{
    //Define the LCD buttons
    const short leftButton = 1;
    const short centerButton = 2;
    const short rightButton = 4;
 
    //Set the variable for the return value of the function
    int autonomousChoice;
 
    //Declare count variable to keep track of our choice
    int count = 0;
 
    //------------- Beginning of User Interface Code ---------------
    //Clear LCD
    clearLCDLine(0);
    clearLCDLine(1);
    //Loop while center button is not pressed
    while(nLCDButtons != centerButton)
    {
        //Switch case that allows the user to choose from 4 different options
        switch(count){
        case 0:
            //Display first choice
            displayLCDCenteredString(0, choice_0);
            displayLCDCenteredString(1, "<        Enter      >");
            waitForPress();
            //Increment or decrement "count" based on button press
            if(nLCDButtons == leftButton)
            {
                waitForRelease();
                count = 3;
            }
            else if(nLCDButtons == rightButton)
            {
                waitForRelease();
                count++;
            }
            break;
        case 1:
            //Display second choice
            displayLCDCenteredString(0, choice_1);
            displayLCDCenteredString(1, "<        Enter      >");
            waitForPress();
            //Increment or decrement "count" based on button press
            if(nLCDButtons == leftButton)
            {
                waitForRelease();
                count--;
            }
            else if(nLCDButtons == rightButton)
            {
                waitForRelease();
                count++;
            }
            break;
        case 2:
            //Display 3rd choice
            displayLCDCenteredString(0, choice_2);
            displayLCDCenteredString(1, "<        Enter      >");
            waitForPress();
            //Increment or decrement "count" based on button press
            if(nLCDButtons == leftButton)
            {
                waitForRelease();
                count--;
            }
            else if(nLCDButtons == rightButton)
            {
                waitForRelease();
                count++;
            }
            break;
        case 3:
            //Display 4th choice
            displayLCDCenteredString(0, choice_3);
            displayLCDCenteredString(1, "<        Enter      >");
            waitForPress();
            //Increment or decrement "count" based on button press
            if(nLCDButtons == leftButton)
            {
                waitForRelease();
                count--;
            }
            else if(nLCDButtons == rightButton)
            {
                waitForRelease();
                count++;
            }
            break;
        case 4:
            //Display 5th choice
            displayLCDCenteredString(0, choice_4);
            displayLCDCenteredString(1, "<        Enter      >");
            waitForPress();
            //Increment or decrement "count" based on button press
            if(nLCDButtons == leftButton)
            {
                waitForRelease();
                count--;
            }
            else if(nLCDButtons == rightButton)
            {
                waitForRelease();
                count = 0;
            }
            break;
        default:
            count = -1;
            break;
        }
 
    }
    //------------- End of User Interface Code ---------------------
 
    // Set autonomousChoice to the current count
    autonomousChoice = count;
 
    // Return autonomousChoice
    return autonomousChoice;
}
 
//Run Autonomous------------------------------------------------
void runAutonomous (int autonomousChoice, string choice_0, string choice_1, string choice_2, string choice_3, string choice_4)
{
    //------------- Beginning of Robot Movement Code ---------------
    //Clear LCD
    clearLCDLine(0);
    clearLCDLine(1);
    //Switch Case that actually runs the user choice
    switch(autonomousChoice){
    case 0:
        //If count = 0, run the code correspoinding with choice 1
        displayLCDCenteredString(0, choice_0);
        displayLCDCenteredString(1, "is running!");
 
        // RUN - Autonomous (1st Option)
        runAutonomous_choice_0();
 
        break;
    case 1:
        //If count = 1, run the code correspoinding with choice 2
        displayLCDCenteredString(0, choice_1);
        displayLCDCenteredString(1, "is running!");
 
        // RUN - Autonomous (2nd Option)
        runAutonomous_choice_1();
 
        break;
    case 2:
        //If count = 2, run the code correspoinding with choice 3
        displayLCDCenteredString(0, choice_2);
        displayLCDCenteredString(1, "is running!");
 
        // RUN - Autonomous (3rd Option)
        runAutonomous_choice_2();
 
        break;
    case 3:
        //If count = 3, run the code correspoinding with choice 3
        displayLCDCenteredString(0, choice_3);
        displayLCDCenteredString(1, "is running!");
 
        // RUN - Autonomous (4th Option)
        runAutonomous_choice_3();
 
        break;
    case 4:
        //If count = 4, run the code correspoinding with choice 4
        displayLCDCenteredString(0, choice_4);
        displayLCDCenteredString(1, "is running!");
 
        // RUN - Autonomous (5th Option)
        runAutonomous_choice_4();
 
        break;
    default:
        displayLCDCenteredString(0, "No valid choice");
        displayLCDCenteredString(1, "was made!");
        break;
    }
    //------------- End of Robot Movement Code -----------------------
 
}
