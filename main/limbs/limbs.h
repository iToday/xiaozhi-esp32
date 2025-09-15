#pragma once

#include "motor/gpio_motor.h"

enum COLOR {
    BLACK,
    RED,
    GREEN,
    BLUE,
    WHITE
};

class Limbs
{

private:
    GpioMotor _left;
    GpioMotor _front_sub;
    GpioMotor _right;
    GpioMotor _rear_sub;

    gpio_num_t _r;
    gpio_num_t _g;
    gpio_num_t _b;
    gpio_num_t _color;

public:

    Limbs(gpio_num_t left_a, gpio_num_t left_b, gpio_num_t front_sub_a, gpio_num_t front_sub_b,
             gpio_num_t right_a, gpio_num_t right_b, gpio_num_t rear_sub_a, gpio_num_t rear_sub_b);

    virtual void InitEmoji(gpio_num_t r, gpio_num_t g, gpio_num_t b, gpio_num_t color);
    virtual void Forward();
    virtual void Backward();

    virtual void FrontLift();

    virtual void RearLift();

    virtual void StopWard();

    virtual void StopLift();

    virtual void TurnRight();

     virtual void TurnLeft();

    virtual void TurnAround();

    virtual void SetEmoticon(const char* em);

    virtual void SetColor(int color);

    virtual void SetAmbient(bool on);
};