#include "main.h"

Controller controller;
auto drive = ChassisControllerBuilder()
                 .withMotors({-14, -2}, {20, 15})
                 .withGearset(AbstractMotor::gearset::green)
                 .withDimensions({{4.125_in, 14.75_in}, imev5GreenTPR})
                 .build();
auto lift = AsyncVelControllerBuilder()
                .withMotor({10, 9})
                .withGearset(AbstractMotor::gearset::red)
                .build();
MotorGroup liftMotors = MotorGroup({10, -9});
auto claw = AsyncVelControllerBuilder()
                .withMotor(1)
                .withGearset(AbstractMotor::gearset::green)
                .build();

auto profileController = AsyncMotionProfileControllerBuilder()
                             .withOutput(drive)
                             .withLimits({1.06, 2.0, 10.0})
                             .buildMotionProfileController();

void initialize() {
  drive->getModel()->setBrakeMode(AbstractMotor::brakeMode::hold);
  liftMotors.setBrakeMode(AbstractMotor::brakeMode::hold);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
  while (true) {
    drive->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY),
                              controller.getAnalog(ControllerAnalog::leftX));

    lift->setTarget(controller.getAnalog(ControllerAnalog::rightY)*100);

    if (controller.getDigital(ControllerDigital::R1))
      claw->setTarget(200);
    else if (controller.getDigital(ControllerDigital::R2))
      claw->setTarget(-200);
    else
      claw->setTarget(0);

    pros::delay(20);
  }
}
