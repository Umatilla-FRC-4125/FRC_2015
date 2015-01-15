#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	//Joysticks
	Joystick *stick= new Joystick (0); // only joystick stick (0)
	//Solenoids
	DoubleSolenoid *shift= new DoubleSolenoid (0,1);
	//Drive stuff
	RobotDrive *myDrive;
	Talon *top_left = new Talon(0);
	Talon *top_right = new Talon(1);
	Talon *bottom_left = new Talon(2);
	Talon *bottom_right = new Talon(3);
	//Sensors
	Encoder *right_encoder = new Encoder(0, 1, false);
	Encoder *left_encoder = new Encoder(2, 3, true);
	void RobotInit()
	{
		//lw = LiveWindow::GetInstance();
		myDrive = new RobotDrive(top_left, bottom_left, top_right, bottom_right);
		right_encoder->SetMaxPeriod(.1);
		right_encoder->SetMinRate(10);
		left_encoder->SetMaxPeriod(.1);
		left_encoder->SetMinRate(10);
		right_encoder->SetDistancePerPulse(1.0 / 360.0 * 2.0 * 3.1415 * 3);
		right_encoder->SetReverseDirection(true);
		right_encoder->SetSamplesToAverage(7);
				//C = 28.26
		left_encoder->SetDistancePerPulse(1.0 / 360.0 * 2.0 * 3.1415 * 3);
		left_encoder->SetReverseDirection(true);
		left_encoder->SetSamplesToAverage(7);

	}

	void AutonomousInit()
	{

	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

	}

	void TeleopPeriodic()
	{
		if(stick->GetRawAxis(2)){
			myDrive->Drive(stick->GetRawAxis(2),stick->GetRawAxis(0));
		}else{myDrive->Drive(stick->GetRawAxis(3),stick->GetRawAxis(0));}
		if(stick->GetRawButton(1)){
			shift->Set(DoubleSolenoid::kForward);
		}
		else if(stick->GetRawButton(2)){
			shift->Set(DoubleSolenoid::kReverse);
		}

	}

	void TestPeriodic()
	{
	//	lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
