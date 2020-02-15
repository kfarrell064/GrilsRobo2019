#include "main.h"

Controller controller;
using namespace okapi;
const int DRIVE_MOTOR_LEFT_BACK = 2;
const int DRIVE_MOTOR_RIGHT_BACK = -6;
const int DRIVE_MOTOR_LEFT_FRONT = 3;
const int DRIVE_MOTOR_RIGHT_FRONT = -10;
const int LIFT_MOTOR_RIGHT = -9;
const int LIFT_MOTOR_LEFT = 4;
const int CLAW_MOTOR = 1;
const auto WHEEL_DIAMETER = 4.125_in;
const auto CHASSIS_WIDTH = 17.5_in;

auto drive = ChassisControllerBuilder()
                 .withMotors({DRIVE_MOTOR_LEFT_BACK, DRIVE_MOTOR_LEFT_FRONT},
                            {DRIVE_MOTOR_RIGHT_BACK, DRIVE_MOTOR_RIGHT_FRONT})
                 .withDimensions(AbstractMotor::gearset::green, {{WHEEL_DIAMETER, CHASSIS_WIDTH}, imev5GreenTPR})
                 .build();
auto lift = AsyncVelControllerBuilder()
                .withMotor({LIFT_MOTOR_RIGHT, LIFT_MOTOR_LEFT})
                .withGearset(AbstractMotor::gearset::green)
                .build();
MotorGroup liftMotors = MotorGroup({LIFT_MOTOR_RIGHT, LIFT_MOTOR_LEFT});
auto claw = AsyncVelControllerBuilder()
                .withMotor(CLAW_MOTOR)
                .withGearset(AbstractMotor::gearset::green)
                .build();

auto profileController = AsyncMotionProfileControllerBuilder()
                             .withOutput(drive)
                             .withLimits({1.06, 2.0, 10.0})
                             .buildMotionProfileController();

void initialize() {
  Logger::setDefaultLogger(std::make_shared<Logger>(
      std::make_unique<Timer>(), "/ser/sout", Logger::LogLevel::debug));

  drive->getModel()->setBrakeMode(AbstractMotor::brakeMode::hold);
  liftMotors.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  //moves forwards 1 meter
  drive->moveDistance(1_m);
  //chassis->turnAngle(90_deg);
  //moves backwards half a meter
  drive->moveDistance(-0.5_m);
}

void opcontrol() {
  while (true) {
    drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
                              controller.getAnalog(ControllerAnalog::leftX));

    lift->setTarget(controller.getAnalog(ControllerAnalog::rightY) * 100);

    if (controller.getDigital(ControllerDigital::R1))
      claw->setTarget(200);
    else if (controller.getDigital(ControllerDigital::R2))
      claw->setTarget(-200);
    else
      claw->setTarget(0);

    pros::delay(20);
  }
}
