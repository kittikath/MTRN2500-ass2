//written by Kath-Lin Han z5165314 with the help of 
//https://docs.microsoft.com/en-gb/windows/desktop/api/_xinput/

#include <iostream>
#include <Windows.h>
#include <Xinput.h>
#include "XInputWrapper.h"
#include "XboxController.h"
#include <math.h>

#define MAX_LENGTH 32767 

using namespace GamePad;
using namespace std;

XINPUT_VIBRATION Vibration; 

XBoxController::XBoxController(XInputWrapper* xinput, DWORD id){
	this->xinput = xinput;
	Uid = id;
}

DWORD XBoxController::GetControllerId() {
	return ControllerId;
}

bool XBoxController::IsConnected() {
	return xinput->XInputGetState(Uid, &cur_state);
}

bool XBoxController::PressedA() {   
	xinput->XInputGetState(Uid, &cur_state);									   	 // look inside GetState with pointer xinput to find current status of controller
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_A) == XINPUT_GAMEPAD_A);     // cur_state.Gamepad.wButtons acts as a bitmask 
																				     //"& AND" operation checks if their binary values are the same 											
																				     // will return 1 for true, 0 for false after commuting comparison
}
bool XBoxController::PressedB() {
	xinput->XInputGetState(Uid, &cur_state);       
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_B) == XINPUT_GAMEPAD_B);
}
bool XBoxController::PressedX() {   
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_X) == XINPUT_GAMEPAD_X);
}
bool XBoxController::PressedY() { 	
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) == XINPUT_GAMEPAD_Y);
}
	
bool XBoxController::PressedLeftShoulder() {
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) == XINPUT_GAMEPAD_LEFT_SHOULDER);
}
bool XBoxController::PressedRightShoulder(){
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) == XINPUT_GAMEPAD_RIGHT_SHOULDER);
}

bool XBoxController::PressedLeftDpad(){
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) == XINPUT_GAMEPAD_DPAD_LEFT);
}

bool XBoxController::PressedRightDpad()	{
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) == XINPUT_GAMEPAD_DPAD_RIGHT);
}
bool XBoxController::PressedUpDpad() {
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) == XINPUT_GAMEPAD_DPAD_UP);
}
bool XBoxController::PressedDownDpad() {
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) == XINPUT_GAMEPAD_DPAD_DOWN);
}
bool XBoxController::PressedStart() {
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_START) == XINPUT_GAMEPAD_START);
}

bool XBoxController::PressedBack() {
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) == XINPUT_GAMEPAD_BACK);
}

bool XBoxController::PressedLeftThumb(){
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) == XINPUT_GAMEPAD_LEFT_THUMB);
}
bool XBoxController::PressedRightThumb() {
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) == XINPUT_GAMEPAD_RIGHT_THUMB);
}

BYTE XBoxController::LeftTriggerLocation() {
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.bLeftTrigger));
}

BYTE XBoxController::RightTriggerLocation() {
	xinput->XInputGetState(Uid, &cur_state);
	return((cur_state.Gamepad.bRightTrigger));
}

GamePad::Coordinate GamePad::XBoxController::LeftThumbLocation()
{	
	Coordinate Coordinate(0, 0);						//from public class Coordinate, set values of Coordinate as (0,0) 
	xinput->XInputGetState(Uid, &cur_state);
	float range = MAX_LENGTH - deadzone;
	float LX = cur_state.Gamepad.sThumbLX;				//get current data of Left Thumb value 
	float LY = cur_state.Gamepad.sThumbLY;				

	float Lradius = sqrt(LX * LX + LY * LY);            //finding the pythagoras distance from centre
	if (Lradius > MAX_LENGTH) {
		Lradius = MAX_LENGTH;
	}
	if (Lradius < deadzone){						    //if radius is less than deadzone, radius is 0.
		Coordinate.SetX(0);
		Coordinate.SetY(0);
	}
	else {
		Lradius = Lradius - deadzone;					//determine the distance from centre excluding deadzone
		float Lratio = (Lradius / range)*MAX_LENGTH;    //find the % of the distance in comparison to max range without deadzone then calibrate to mag of joystick
		float deg = atan2(LY, LX);						//find the angle - argument from origin

		Coordinate.SetX((SHORT)(Lratio * cos(deg)));    //split angle into x and y components 
		Coordinate.SetY((SHORT)(Lratio * sin(deg)));	// x = Rcos(deg), y = Rsin(deg)
	}
	return Coordinate;

}


GamePad::Coordinate GamePad::XBoxController::RightThumbLocation()
{
	Coordinate Coordinate(0, 0);					    //follows same structure as LeftThumbLocation() 
	xinput->XInputGetState(Uid, &cur_state);
	float range = MAX_LENGTH - deadzone;
	float RX = cur_state.Gamepad.sThumbRX;
	float RY = cur_state.Gamepad.sThumbRY;

	float Rradius = sqrt(RX * RX + RY * RY); 
	if (Rradius > MAX_LENGTH) {				 
		Rradius = MAX_LENGTH;
	}
	if (Rradius < deadzone) {				 
		Coordinate.SetX(0);
		Coordinate.SetY(0);
	}
	else {
		Rradius = Rradius - deadzone;				    
		float Rratio = (Rradius / range)*MAX_LENGTH;    
		float deg = atan2(RY, RX);						

		Coordinate.SetX((SHORT)(Rratio * cos(deg)));    
		Coordinate.SetY((SHORT)(Rratio * sin(deg)));
	}
	return Coordinate;
}

void XBoxController::Vibrate(WORD left, WORD right){
	xinput->XInputSetState(Uid, &Vibration);			//Look inside function SetState with pointer xinput to look into magnitude of Vibration 
	Vibration.wLeftMotorSpeed = left;					//Set the Vibration value inside SetState as function input from Vibrate()
	Vibration.wRightMotorSpeed = right;				
}

void XBoxController::SetDeadzone(unsigned int radius) {
	deadzone = radius;									//unsigned int from private 'deadzone' = function input from SetDeadzone 
}