#pragma once

enum MotorDriection{
    POSITIVE, //正向
    NEGATIVE, //反向
} ;

class Motor {
protected:
    MotorDriection _direction;
public:
    virtual ~Motor() = default;
    // Set the led state based on the device state
    virtual void SetSpeed(int speed) = 0;

    virtual void Coasting() = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void SetDirection(MotorDriection direction){_direction = direction;};
};


class NoMotor : public Motor {
public:
    virtual void Start() override {}
    virtual void Stop() override {}

    virtual void SetSpeed(int speed) override {}

    virtual void Coasting() override {}

};


