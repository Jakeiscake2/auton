#include "main.h"

using namespace std;
using namespace pros;

Controller controls(E_CONTROLLER_MASTER);

Motor flywheel(19, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

Motor intake_roller_indexer(10, E_MOTOR_GEARSET_18, false,
                            E_MOTOR_ENCODER_DEGREES);

Motor FrontLeft(1, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor BackLeft(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);

Motor FrontRight(3, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor BackRight(4, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

pros::MotorGroup leftMotors({FrontLeft, BackLeft});
pros::MotorGroup rightMotors({FrontRight, BackRight});

vector<double> lefti = leftMotors.get_positions(),
               righti = rightMotors.get_positions();
vector<double> leftt = leftMotors.get_target_positions(),
               rightt = rightMotors.get_target_positions();

void go(int left, int right) {
  leftMotors.move_relative(left, 127);
  rightMotors.move_relative(right, 127);
  while (lefti <= leftt && righti <= rightt) {
    lefti = leftMotors.get_positions();
    righti = rightMotors.get_positions();
  }
}

int turn90 = 0;
int turn1 = turn90 / 90;
// Yulian get this done
int tile = 0;
int three_disc_unload = 0;

void initialize() {
  lcd::initialize();
  pros::lcd::set_text(1, "Program running");
}

void soloHard() {
  go(-1 * tile, -1 * tile);
  go(turn90, -turn90);
  intake_roller_indexer = 127;
  go(0.8 * tile, 0.8 * tile);
  intake_roller_indexer = 0;
  go(-turn90 / 2, turn90 / 2);
  // roller

  intake_roller_indexer = 127;
  go(1.25 * tile, 1.25 * tile);
  intake_roller_indexer = 0;
  // nom nom 1 disc

  go(85 * turn1, -85 * turn1);
  flywheel = 127;
  intake_roller_indexer = -127;
  delay(three_disc_unload * 1000);
  go(-85 * turn1, 85 * turn1);
  // shoot 3 discs

  intake_roller_indexer = 127;
  go(2 * tile, 2 * tile);
  intake_roller_indexer = 0;
  // nom nom 2 discs

  go(34 * turn1, -34 * turn1);
  flywheel = 127;
  intake_roller_indexer = -127;
  delay(three_disc_unload * 1000);
  go(-34 * turn1, 34 * turn1);
  // shoot 2 discs

  intake_roller_indexer = 127;
  go(1.414213562 * tile, 1.414213562 * tile);
  intake_roller_indexer = 0;
  // nom nom 3 stack

  go(14 * turn1, -14 * turn1);
  flywheel = 127;
  intake_roller_indexer = -127;
  delay(three_disc_unload * 1000);
  go(-14 * turn1, 14 * turn1);
  // shoot 3 stack

  go(turn90 / 2, -turn90 / 2);
  intake_roller_indexer = 127;
  go(0.5 * tile, 0.5 * tile);
  intake_roller_indexer = 0;
  go(0.2 * tile, 0.2 * tile);
  // roller
}
void Hard() {
  go(-1 * tile, -1 * tile);
  go(turn90, -turn90);
  intake_roller_indexer = 127;
  go(0.8 * tile, 0.8 * tile);
  intake_roller_indexer = 0;
  go(-turn90 / 2, turn90 / 2);
  // roller

  intake_roller_indexer = 127;
  go(1.25 * tile, 1.25 * tile);
  intake_roller_indexer = 0;
  // nom nom 1 disc

  go(85 * turn1, -85 * turn1);
  flywheel = 127;
  intake_roller_indexer = -127;
  delay(three_disc_unload * 1000);
  go(-85 * turn1, 85 * turn1);
  // shoot 3 discs

  intake_roller_indexer = 127;
  go(2 * tile, 2 * tile);
  intake_roller_indexer = 0;
  // nom nom 2 discs

  go(34 * turn1, -34 * turn1);
  flywheel = 127;
  intake_roller_indexer = -127;
  delay(three_disc_unload * 1000);
  go(-34 * turn1, 34 * turn1);
  // shoot 2 discs
  // optional for if you want the next 2 discs
}
void Easy() {
  intake_roller_indexer = 127;
  go(-0.2 * tile, -0.2 * tile);
  intake_roller_indexer = 0;
  go(turn90 / 2, -turn90 / 2);
  // roller

  intake_roller_indexer = 127;
  go(1.414213562 * tile, 1.414213562 * tile);
  intake_roller_indexer = 0;
  // nom nom 3 stack

  go(-76 * turn1, 76 * turn1);
  flywheel = 127;
  intake_roller_indexer = -127;
  delay(three_disc_unload * 1000);
  go(76 * turn1, -76 * turn1);
  // shoot 3 stack

  intake_roller_indexer = 127;
  go(2 * tile, 2 * tile);
  intake_roller_indexer = 0;
  // nom nom 2 discs

  go(66 * turn1, -66 * turn1);
  flywheel = 127;
  intake_roller_indexer = -127;
  delay(three_disc_unload * 1000);
  go(-66 * turn1, 66 * turn1);
  // shoot 2 discs
  // optional for if you want the next 2 discs

  // nom nom 2 discs
}
screen_touch_status_s_t status;
string color = "no colour";
string auton = "no auton";
bool status_checker(int x1, int x2, int y1, int y2) {
  if (status.x >= x1 && status.x <= x2 && status.y >= y1 && status.y <= y2) {
    return true;
  }
  return false;
}
void auton_selector() {
  screen::erase();
  screen::set_eraser(COLOR_BLACK);

  while (true) {
    if (status.x != c::screen_touch_status().x &&
        status.y != c::screen_touch_status().y) {
      screen::erase();
      status = c::screen_touch_status();

      screen::set_pen(COLOR_RED);
      screen::draw_rect(0, 0, 100, 50);
      pros::c::screen_print_at(TEXT_LARGE, 10, 10, "RED");
      screen::set_pen(COLOR_BLUE);
      pros::c::screen_print_at(TEXT_LARGE, 400, 10, "BLYEU");
      screen::draw_rect(380, 0, 480, 50);

      screen::set_pen(COLOR_SLATE_GRAY);
      pros::c::screen_print_at(TEXT_MEDIUM, 1, 150, "Roller");
      pros::c::screen_print_at(TEXT_MEDIUM, 1, 200, "easy");
      screen::draw_rect(1, 150, 120, 250);

      pros::c::screen_print_at(TEXT_MEDIUM, 180, 150, "solo");
      pros::c::screen_print_at(TEXT_MEDIUM, 180, 200, "hard");
      screen::draw_rect(120, 150, 360, 250);

      pros::c::screen_print_at(TEXT_MEDIUM, 360, 150, "Roller");
      pros::c::screen_print_at(TEXT_MEDIUM, 360, 200, "hard");
      screen::draw_rect(360, 150, 480, 250);

      c::screen_print_at(TEXT_LARGE, 300, 69, "Im sure");
      screen::draw_rect(300, 69, 480, 169);

      if (status_checker(300, 480, 69, 169)) {
        break;
      }

      if (status_checker(0, 100, 0, 50)) {
        color = "red";
      } else if (status_checker(380, 480, 0, 50)) {
        color = "blue";
      } else if (status_checker(360, 480, 150, 200)) {
        auton = "roller hard";
      } else if (status_checker(120, 360, 150, 200)) {
        auton = "hard solo";
      } else if (status_checker(0, 120, 150, 200)) {
        auton = "roller easy";
      }

      screen::set_pen(COLOR_WHITE);
      if (color == "red") {
        c::screen_print_at(TEXT_LARGE, 100, 10, "selected red");
      } else if (color == "blue") {
        c::screen_print_at(TEXT_LARGE, 100, 10, "selected blue");
      } else {
        c::screen_print_at(TEXT_LARGE, 100, 10, "select a color");
      }

      if (auton == "roller easy") {
        c::screen_print_at(TEXT_LARGE, 0, 69, "selected easy roller");
      } else if (auton == "roller hard") {
        c::screen_print_at(TEXT_LARGE, 0, 69, "selected hard roller");
      } else if (auton == "hard solo") {
        c::screen_print_at(TEXT_LARGE, 0, 69, "selected hard solo");
      } else {
        c::screen_print_at(TEXT_LARGE, 0, 69, "select an auton");
      }
      controls.set_text(0, 0, color);
      controls.set_text(0, 6, auton);
    }
  }
  screen::erase();
}


void disabled() {}
void competition_initialize() {
  auton_selector();
  delay(250);
  c::screen_print_at(TEXT_LARGE, 300, 69, "jk mb");
  screen::draw_rect(300, 69, 480, 169);
  if (status_checker(300, 480, 69, 169)) {
    auton_selector();
  }
}
void autonomous() {
  if (auton == "roller easy") {
    Easy();
  } else if (auton == "roller hard") {
    Hard();
  } else if (auton == "hard solo") {
    soloHard();
  } else {
    leftMotors = 127;
    rightMotors = -127;
    delay(3593);
  }
}
void opcontrol() {

  while (true) {
    controls.set_text(0, 0, "How did we get here?");
  }
}