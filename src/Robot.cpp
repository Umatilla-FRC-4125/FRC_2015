#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	RobotDrive *myDrive;
	Joystick *stick= new Joystick (0); // only joystick stick (0)
	void RobotInit()
	{
		//lw = LiveWindow::GetInstance();
		myDrive = new RobotDrive(0,1);
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
		myDrive->Drive(stick->GetRawAxis(2),stick->GetRawAxis(0));

	}

	void TestPeriodic()
	{
	//	lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
