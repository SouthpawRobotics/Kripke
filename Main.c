#pragma config(UART_Usage, UART2, uartNotUsed, baudRate4800, IOPins, None, None)
#pragma config(Sensor, dgtl1,  rightArmUp,     sensorTouch)
#pragma config(Sensor, dgtl2,  rightArmDown,   sensorTouch)
#pragma config(Sensor, dgtl3,  leftArmUp,      sensorTouch)
#pragma config(Sensor, dgtl4,  leftArmDown,    sensorTouch)
#pragma config(Motor,  port1,           backLeft,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightArm,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftArm,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightClaw,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           leftClaw,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          backRight,     tmotorVex269_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		motor[frontLeft]  = vexRT[Ch3] + vexRT[Ch4];
    motor[frontRight] = vexRT[Ch3] - vexRT[Ch4];
    motor[backLeft]  = vexRT[Ch3] + vexRT[Ch4];
    motor[backRight] = vexRT[Ch3] - vexRT[Ch4];
		byte rightArmActive = vexRT[Btn7R];
		if(vexRT[Btn5U] && !SensorBoolean[rightArmActive ? rightArmUp : leftArmUp]){ // Find if the upper left trigger is pressed and make sure the limit switch is not activated
			motor[rightArmActive ? rightArm : leftArm] = 127; // Set the left arm to up at full speed
		} else if(vexRT[Btn5D] && !SensorBoolean[rightArmActive ? rightArmDown : leftArmDown]) { // Otherwise if the lower left trigger is pressed and make sure the limit switch is not activated
			motor[rightArmActive ? rightArm : leftArm] = -127; // Set the left arm to down at full speed
		} else { // If no motion is to occur
			motor[rightArmActive ? rightArm : leftArm] = 0; // Turn off the left arm
		}
		if(vexRT[Btn7U]){ // If the top button on the left D-Pad is pressed
			motor[rightArmActive ? rightClaw : leftClaw] = 127; // Open the left claw at full speed
		} else if(vexRT[Btn7D]) { // If the bottom button on the left D-Pad is pressed
			motor[rightArmActive ? rightClaw : leftClaw] = -127; // Close the left claw at full speed
		} else { // If neither button is pushed
			motor[rightArmActive ? rightClaw : leftClaw] = 0; // Turn off the left claw
		}
		if(rightArmActive){
			motor[leftArm] = 0;
			motor[leftClaw] = 0;
		} else {
			if(vexRT[Btn6U] && !SensorBoolean[rightArmUp]){ // Find if the upper right trigger is pressed and the limit switch is not activated
				motor[rightArm] = 127; // Set the right arm to up at full speed
			} else if(vexRT[Btn6D] && !SensorBoolean[rightArmDown]) { // Otherwise if the lower right trigger is pressed and the limit switch is not activated
				motor[rightArm] = -127; // Set the right arm to down at full speed
			} else { // If no motion is to occur
				motor[rightArm] = 0; // Turn off the right arm
			}
			if(vexRT[Btn8U]){ // If the top button on the right D-Pad is pressed
				motor[rightClaw] = 127; // Turn on the right claw at full speed
			} else if(vexRT[Btn8D]) { // If the bottom button on the right D-Pad is pressed
				motor[rightClaw] = -127; // Close the right claw at full speed
			} else { // If neither button is pushed
				motor[rightClaw] = 0; // Turn off the right claw
			}
		}
	}
}
