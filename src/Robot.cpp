#include "WPILib.h"

class Robot: public IterativeRobot
{
private:
	//Joysticks
	Joystick *stick= new Joystick (0); // only joystick stick (0)
	Joystick *stick2 = new Joystick (1);
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
	Talon *lift = new Talon(0);
	Talon *linearSlide = new Talon(1);
	DigitalInput *squeezeLeft = new DigitalInput(10);
	DigitalInput *squeezright = new DigitalInput(11);
	//Gyros
	Gyro *gyro1 = new Gyro(0);
	//Sensors
	Encoder *right_encoder = new Encoder(2, 3, false);
	Encoder *left_encoder = new Encoder(0, 1, true);
	Encoder *strafe_front_enc = new Encoder(6,7,false);
	Encoder *strafe_back_enc = new Encoder(8,9,true);
	Encoder *elev_enc = new Encoder(4,5,false);
	void RobotInit()
	{
		//lw = LiveWindow::GetInstance();
		//Gyros
	//float angle = gyro1->GetAngle();
	//myRobot.Drive(-1.0, -angle * Kp);
	//Wait(0.004);
		//Motors
		//top_left->SetFeedbackDevice(CANTalon::QuadEncoder);
		//top_right->SetFeedbackDevice(CANTalon::QuadEncoder);



		//Drive
		myDrive = new RobotDrive(top_left,bottom_left, top_right,bottom_right);
		myDrive->SetExpiration(1000);
		//Encoders
		//C = 28.26
		right_encoder->SetMaxPeriod(.1);
		right_encoder->SetMinRate(10);
		left_encoder->SetMaxPeriod(.1);
		left_encoder->SetMinRate(10);
		right_encoder->SetDistancePerPulse(.016);
		right_encoder->SetReverseDirection(true);
		right_encoder->SetSamplesToAverage(7);
		//1/4 of the rest of them
		left_encoder->SetDistancePerPulse(.016);
		left_encoder->SetReverseDirection(false);
		left_encoder->SetSamplesToAverage(7);
		strafe_back_enc->SetMaxPeriod(.1);
		strafe_back_enc->SetMinRate(10);
		strafe_front_enc->SetMaxPeriod(.1);
		strafe_front_enc->SetMinRate(10);
		strafe_front_enc->SetDistancePerPulse(.016);
		strafe_front_enc->SetReverseDirection(true);
		strafe_front_enc->SetSamplesToAverage(7);
		strafe_back_enc->SetDistancePerPulse(.016);
		strafe_back_enc->SetReverseDirection(true);
		strafe_back_enc->SetSamplesToAverage(7);
		elev_enc->SetMaxPeriod(.1);
		elev_enc->SetMinRate(10);
		elev_enc->SetDistancePerPulse(.016);
		elev_enc->SetReverseDirection(true);
		elev_enc->SetSamplesToAverage(7);
	}

	void AutonomousInit()
	{
		elev_enc->Reset();
		strafe_back_enc->Reset();
		strafe_front_enc->Reset();
		right_encoder->Reset();
		left_encoder->Reset();

	}

	void AutonomousPeriodic()
	{
		strafe->Set(DoubleSolenoid::kForward);
		if(right_encoder->GetDistance()< 3.8){
			myDrive->SetLeftRightMotorOutputs(-.4,.4);

		}
		else
		{
			myDrive->SetLeftRightMotorOutputs(0, 0);
		}
		SmartDashboard::PutBoolean("Squeeze Left", squeezeLeft->Get());
		SmartDashboard::PutBoolean("Squeeze Right", squeezright->Get());
		SmartDashboard::PutNumber("Left Encoder", left_encoder->GetDistance());
		SmartDashboard::PutNumber("Right Encoder", right_encoder->GetDistance());
		SmartDashboard::PutNumber("Top Strafe Enc", strafe_front_enc->GetDistance());
		SmartDashboard::PutNumber("Bottom Strafe Enc", strafe_back_enc->GetDistance());
		SmartDashboard::PutNumber("Elevator Enc", elev_enc->GetDistance());
	}

	void TeleopInit()
	{
		elev_enc->Reset();
		strafe_back_enc->Reset();
		strafe_front_enc->Reset();
		right_encoder->Reset();
		left_encoder->Reset();
	}

	void TeleopPeriodic()
	{
		if(stick->GetRawAxis(2)>.1 ){
			myDrive->Drive(stick->GetRawAxis(3)-stick->GetRawAxis(2),stick->GetRawAxis(0));

		}
		else if(stick->GetRawAxis(3)>.10){
			myDrive->Drive(stick->GetRawAxis(3)-stick->GetRawAxis(2),stick->GetRawAxis(0));
//
		}
		else{
			myDrive->SetLeftRightMotorOutputs(stick->GetRawAxis(0),-stick->GetRawAxis(0));
		}
		if(stick->GetRawButton(1)){
			shift->Set(DoubleSolenoid::kForward);
		}
		else if(stick->GetRawButton(2)){
			shift->Set(DoubleSolenoid::kReverse);
		}
		Strafe_top->Set(stick->GetRawAxis(4)*.75);
		Strafe_bottom->Set(-stick->GetRawAxis(4)*.75);
		if(stick->GetRawButton(6)){strafe->Set(DoubleSolenoid::kForward);}
		else if(stick->GetRawButton(5)){strafe->Set(DoubleSolenoid::kReverse);}

		if(stick2->GetRawButton(1)){
			lift->Set(.5);
		}
		else if(stick2->GetRawButton(2)){
			lift->Set(-.5);
		}
		else {lift->Set(0);}
		if(stick2->GetRawButton(4)){
			if(squeezeLeft->Get()){
				linearSlide->Set(.5);}
			else {linearSlide->Set(0);}
		}
		else if(stick2->GetRawButton(5)){
			if(squeezright->Get()){
				linearSlide->Set(-.5);}
			else{linearSlide->Set(0);}
		}
		else{linearSlide->Set(0);}
		SmartDashboard::PutBoolean("Squeeze Left", squeezeLeft->Get());
		SmartDashboard::PutBoolean("Squeeze Right", squeezright->Get());
		SmartDashboard::PutNumber("Left Encoder", left_encoder->GetDistance());
		SmartDashboard::PutNumber("Right Encoder", right_encoder->GetDistance());
		SmartDashboard::PutNumber("Top Strafe Enc", strafe_front_enc->GetDistance());
		SmartDashboard::PutNumber("Bottom Strafe Enc", strafe_back_enc->GetDistance());
		SmartDashboard::PutNumber("Elevator Enc", elev_enc->GetDistance());

	}

	void TestPeriodic(){

	//	lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
