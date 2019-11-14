#include "main.h"

// auto lift = AsyncControllerFactory::posIntegrated({9,10});
// auto spin = ChassisControllerFactory::create({2, 3}, {4, 5}, AbstractMotor::gearset::green);
Controller controller;
ChassisControllerIntegrated drive = ChassisControllerFactory::create({8, 10}, {-3, -2}, AbstractMotor::gearset::green);
ChassisControllerIntegrated lift = ChassisControllerFactory::create({9, -10}, {8, 6}, AbstractMotor::gearset::red);
// AsyncVelIntegratedController claw =
//   AsyncControllerFactory::velIntegrated(7);
//
// AsyncVelIntegratedController spacer =
//   AsyncControllerFactory::velIntegrated(20);
AsyncMotionProfileController profileController =
		AsyncControllerFactory::motionProfile(1.06, 2.0, 10.0, drive);

void initialize() {
	drive.setBrakeMode(AbstractMotor::brakeMode::hold);
  // lift.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
// auto chassis = ChassisControllerFactory::create({15, 14}, {-12, -13}/*, AbstractMotor::gearset::green, {4.25_in, 14.5_in}*/);
// auto lift = ChassisControllerFactory::create(9, -10);
// auto claw = ChassisControllerFactory::create(7, 2);
// RED PUSH CAP AND PARK
// lift.moveDistance(90);
// lift.moveDistance(-90);
// chassis.moveDistance(620);
// chassis.turnAngle(160);
// chassis.moveDistance(-490);

// BLUE PUSH CAP AND PARK
// lift.moveDistance(60);
// lift.moveDistance(-60);
// chassis.moveDistance(590);
// chassis.turnAngle(-160);
// chassis.moveDistance(-460);

// RED FLAG AND PARK
// chassis.moveDistance(-650);
// chassis.turnAngle(-20);
// chassis.moveDistance(1070);
// chassis.turnAngle(170);
// chassis.moveDistance(-570);
}

void opcontrol() {
	while (true) {
		drive.arcade(controller.getAnalog(ControllerAnalog::leftY),
			controller.getAnalog(ControllerAnalog::leftX));


			// lift.setTarget(controller.getAnalog(ControllerAnalog::leftY));
			// lift.arcade(controller.getAnalog(ControllerAnalog::rightY),
			// 	controller.getAnalog(ControllerAnalog::rightX));


			// if (controller.getDigital(ControllerDigital::R1))
	    // 	claw.setTarget(1000);
	  	// else if (controller.getDigital(ControllerDigital::R2))
	    // 	claw.setTarget(-1000);
	  	// else
	    // 	claw.setTarget(0);
	    //
	    // if (controller.getDigital(ControllerDigital::L1))
	    //   	spacer.setTarget(-45);
	    // else if (controller.getDigital(ControllerDigital::L2))
	    //     spacer.setTarget(45);
	    // else
	    //   	spacer.setTarget(0);
			// spin.arcade(controller.getDigital(ControllerDigital::B),
			// 	controller.getDigital(ControllerDigital::X));
		pros::delay(20);
	}
}
