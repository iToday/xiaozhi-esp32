#pragma once

#include "motor.h"
#include <driver/gpio.h>

class GpioMotor : public Motor
{
private:
    /* data */
    gpio_num_t _a;
    gpio_num_t _b;

public:
    GpioMotor (gpio_num_t a, gpio_num_t b);
    ~GpioMotor ();

    virtual void Start() override;
    virtual void Stop() override;

    virtual void SetSpeed(int speed) override;

    virtual void Coasting() override;
};
