/*
    *  Flybrix Flight Controller -- Copyright 2018 Flying Selfie Inc. d/b/a Flybrix
    *
    *  http://www.flybrix.com
*/

#include "Arduino.h"
#include "led.h"
#include "state.h"
#include "command.h"
#include "controlVectors.h"

void runTestRoutine(State& state, LED& led, PilotCommand& pilot, size_t led_id, size_t motor_id) {
    pilot.resetMotors();
    pilot.setMotor(motor_id, 4095);
    pilot.applyControl(ControlVectors());
    led.setWhite(board::led::POSITION[led_id], board::led::POSITION[led_id], led_id % 2 == 0, led_id % 2 == 1);
    led.update();
}

void runTestMode(State& state, LED& led, PilotCommand& pilot) {
    pilot.override(true);
    size_t led_id{0};
    size_t motor_id{0};
    while (true) {
        runTestRoutine(state, led, pilot, led_id, motor_id);
        led_id = (led_id + 1) % 4;
        motor_id = (motor_id + 1) % 8;
        delay(500);
    }
}
