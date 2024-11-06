#ifndef STEPPER_MOTOR_H_MARK
#define STEPPER_MOTOR_H_MARK 1

class Stepper;

class StepperMotor
{
    public:
        StepperMotor(Stepper &input);
        void run(void);
        void Turn (int num_steps);
        bool Ready;
        void PulseWidth(int width);
        void SetSpeed(int speed);

    private:
        Stepper &tuning_motor;
         int step_count;
         unsigned long motor_delay = 10;
         unsigned long timer;
        enum motor_state{
            Idle,
            TurnMe,
            Turning,
            Turn_Complete
        };
        motor_state m_state;

        enum direction_state{
            Backward,
            Forward
        };
        direction_state direction;


};





#endif