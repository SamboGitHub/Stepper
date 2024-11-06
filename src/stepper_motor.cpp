#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/dma.h"
#include "hardware/pio.h"
#include "hardware/interp.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/clocks.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"

#include "include/global.h"
#include "include/stepper_motor.h"
#include "include/stepper.h"


StepperMotor::StepperMotor(Stepper &input)
    : tuning_motor(input)
{
}

void StepperMotor::run(void)
{
    switch (m_state)
    {
    case TurnMe:
        // turn the motor here
        tuning_motor.step(step_count);
        timer=msSinceBoot();     
        
        m_state = Turn_Complete;
        printf("StepperMotor.Turned \n");
        break;

    case Turning:
        if(msSinceBoot() >= timer + motor_delay)
        {
            m_state = Turn_Complete;
            printf("StepperMotor.Turning_Complete \n");
        }
        else
        {
            printf("StepperMotor.Turning \n");
        }
        break;
    case Turn_Complete:
        Ready = true;
        printf("StepperMotor.Turn_Complete \n");
        step_count=0;
        m_state = Idle;
        break;

    case Idle:
        break;
    };
}

void StepperMotor::Turn(int num_steps)
{
    step_count = num_steps;
    m_state = Turning;
}

void StepperMotor::SetSpeed(int speed)
{
     tuning_motor.setSpeed(speed);
}

// void StepperMotor::Turn(int step_size, int direction)
// {
//   int speed = 500;
//   // Set motor speed
//   tuning_motor->setSpeed(speed);

//   switch (direction)
//   {
//   case 0:
//    {
//     tuning_motor->step(step_size, BACKWARD, DOUBLE);
//     break;
//    }
//   case 1:
//    {
//     tuning_motor->step(step_size, FORWARD, DOUBLE);
//     break;
//    }
//   }
//   tuning_motor->release();
// };

// https://learn.adafruit.com/adafruit-tb6612-h-bridge-dc-stepper-motor-driver-breakout/using-stepper-motors

// // // change this to the number of steps on your motor
// // #define STEPS 200

// // // create an instance of the stepper class, specifying
// // // the number of steps of the motor and the pins it's
// // // attached to
// // Stepper stepper(STEPS, 4, 5, 6, 7);

// // void setup()
// // {
// //   Serial.begin(9600);
// //   Serial.println("Stepper test!");
// //   // set the speed of the motor to 30 RPMs
// //   stepper.setSpeed(60);
// // }

// // void loop()
// // {
// //   Serial.println("Forward");
// //   stepper.step(STEPS);
// //   Serial.println("Backward");
// //   stepper.step(-STEPS);
// // }