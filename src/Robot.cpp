#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	//Joysticks
	Joystick *stick= new Joystick (0); // only joystick stick (0)
	//Solenoids
	DoubleSolenoid *shift= new DoubleSolenoid (0,1);
	DoubleSolenoid *strafe = new DoubleSolenoid(2,3);
	//Drive stuff
	RobotDrive *myDrive;
	CANTalon *top_left = new CANTalon(0);
	CANTalon *top_right = new CANTalon(1);
	CANTalon *bottom_left = new CANTalon(2);
	CANTalon *bottom_right = new CANTalon(3);
	CANTalon *Strafe_bottom=new CANTalon(4);
	CANTalon *Strafe_top=new CANTalon(5);
	CANTalon *lift = new CANTalon(6);
	CANTalon *spin1 = new CANTalon(7);
	CANTalon *spin2 = new CANTalon(8);
	//Gyros
	Gyro *gyro1 = new Gyro(0);
	//Sensors
	//Encoder *right_encoder = new Encoder(0, 1, false);
	//Encoder *left_encoder = new Encoder(2, 3, true);
	void RobotInit()
	{
		//lw = LiveWindow::GetInstance();
		//Gyros
	//float angle = gyro1->GetAngle();
	//myRobot.Drive(-1.0, -angle * Kp);
	//Wait(0.004);
		//Motors
		top_left->SetFeedbackDevice(CANTalon::QuadEncoder);
		top_right->SetFeedbackDevice(CANTalon::QuadEncoder);
		bottom_left->SetControlMode(CANSpeedController::kFollower);
		bottom_right->SetControlMode(CANSpeedController::kFollower);
		bottom_left->Set(0);
		bottom_right->Set(1);
		top_left->SetControlMode(CANSpeedController::kPercentVbus);
		top_right->SetControlMode(CANSpeedController::kPercentVbus);
		//Drive
		myDrive = new RobotDrive(top_left, top_right);
		//Encoders
//		right_encoder->SetMaxPeriod(.1);
//		right_encoder->SetMinRate(10);
//		left_encoder->SetMaxPeriod(.1);
//		left_encoder->SetMinRate(10);
//		right_encoder->SetDistancePerPulse(1.0 / 360.0 * 2.0 * 3.1415 * 3);
//		right_encoder->SetReverseDirection(true);
//		right_encoder->SetSamplesToAverage(7);
//				//C = 28.26
//		left_encoder->SetDistancePerPulse(1.0 / 360.0 * 2.0 * 3.1415 * 3);
//		left_encoder->SetReverseDirection(true);
//		left_encoder->SetSamplesToAverage(7);

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
			myDrive->Drive(stick->GetRawAxis(2)/2,stick->GetRawAxis(0));
		}
		else if(stick->GetRawAxis(3)){
			myDrive->Drive(-stick->GetRawAxis(3)/2,stick->GetRawAxis(0));

		}
		else{
			top_left->Set(-stick->GetRawAxis(0));
			bottom_left->Set(-stick->GetRawAxis(0));
			top_right->Set(-stick->GetRawAxis(0));
			bottom_right->Set(-stick->GetRawAxis(0));
		}
		if(stick->GetRawButton(1)){
			shift->Set(DoubleSolenoid::kForward);
		}
		else if(stick->GetRawButton(2)){
			shift->Set(DoubleSolenoid::kReverse);
		}
		Strafe_top->Set(stick->GetRawAxis(4)/4);
		Strafe_bottom->Set(-stick->GetRawAxis(4)/4);
		if(stick->GetRawButton(6)){strafe->Set(DoubleSolenoid::kForward);}
		else if(stick->GetRawButton(7)){strafe->Set(DoubleSolenoid::kReverse);}

		if(stick->GetRawAxis(5)>0.1 || stick->GetRawAxis(5)<-0.1){
			lift->Set(stick->GetRawAxis(5));
		}
		if(stick->GetRawButton(3)){
			spin1->Set(stick->GetRawButton(3))
		}
		if(stick->GetRawButton(4)){
			spin2->Set(stick->GetRawButton(4))
		}
	}

	void TestPeriodic()
	{
	//	lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
