#include "gpio_motor.h"
#include <esp_log.h>
#define TAG "GpioMotor"

GpioMotor ::GpioMotor (gpio_num_t a, gpio_num_t b)
{
    assert(a != GPIO_NUM_NC && b != GPIO_NUM_NC);

    _a = a;
    _b = b;

    gpio_config_t io_conf;
    io_conf.pin_bit_mask = (1ULL << _a) | (1ULL << _b);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);

    Coasting();
}

GpioMotor ::~GpioMotor ()
{
    Stop();
}

void GpioMotor::Start()
{
    if (_direction == MotorDriection::POSITIVE)
    {
        gpio_set_level(_a, 0);
        gpio_set_level(_b, 1);
        ESP_LOGI(TAG, "Start pina %d : 0, pinb %d : 1, direction:%d", _a, _b, _direction);
    } 
    else if (_direction == MotorDriection::NEGATIVE)
    {
        gpio_set_level(_a, 1);
        gpio_set_level(_b, 0);
        ESP_LOGI(TAG, "Start pina %d : 1, pinb %d : 0, direction:%d", _a, _b, _direction);
    }
    else
    {
        Coasting();
    }
}

void GpioMotor::Stop()
{
    ESP_LOGI(TAG, "Stop pina %d :1, pinb %d :1, direction:%d", _a, _b, _direction);
    gpio_set_level(_a, 1);
    gpio_set_level(_b, 1);
}


void GpioMotor::SetSpeed(int speed) 
{

}

void GpioMotor::Coasting() 
{
    ESP_LOGI(TAG, "Coasting pina %d :0, pinb %d :0, direction:%d", _a, _b, _direction);
    gpio_set_level(_a, 0);
    gpio_set_level(_b, 0);
}