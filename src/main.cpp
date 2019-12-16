#include "main.h"

Controller controller;
auto drive = ChassisControllerBuilder()
                 .withMotors({2, 3}, {-6, -10})
                 .withGearset(AbstractMotor::gearset::green)
                 .withDimensions({{4.125_in, 14.75_in}, imev5GreenTPR})
                 .build();
auto lift = AsyncVelControllerBuilder()
                .withMotor({-9, 4})
                .withGearset(AbstractMotor::gearset::red)
                .build();
MotorGroup liftMotors = MotorGroup({-9, 4});
auto claw = AsyncVelControllerBuilder()
                .withMotor(1)
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

void autonomous() {}

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
