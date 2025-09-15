#include "limbs.h"
#include <font_awesome.h>
#include <esp_log.h>

#define TAG "Limbs"

Limbs::Limbs(gpio_num_t left_a, gpio_num_t left_b, gpio_num_t front_sub_a, gpio_num_t front_sub_b,
             gpio_num_t right_a, gpio_num_t right_b, gpio_num_t rear_sub_a, gpio_num_t rear_sub_b)
    : _left(left_a, left_b), _front_sub(front_sub_a, front_sub_b), _right(right_a, right_b), _rear_sub(rear_sub_a, rear_sub_b)
{
    _r = GPIO_NUM_MAX;
    _b = GPIO_NUM_MAX;
    _g = GPIO_NUM_MAX;
}
void Limbs::Forward()
{
    StopWard();
    _left.SetDirection(MotorDriection::POSITIVE);
    _right.SetDirection(MotorDriection::POSITIVE);

    _right.Start();
    _left.Start();
}
void Limbs::Backward()
{
    StopWard();
    _left.SetDirection(MotorDriection::NEGATIVE);
    _right.SetDirection(MotorDriection::NEGATIVE);

    _left.Start();
    _right.Start();
}

void Limbs::FrontLift()
{
    StopLift();
    _front_sub.SetDirection(MotorDriection::POSITIVE);
    _front_sub.Start();
}

void Limbs::RearLift()
{
    StopLift();
    _rear_sub.SetDirection(MotorDriection::POSITIVE);
    _rear_sub.Start();
}

void Limbs::StopWard()
{
    _left.Coasting();
    _right.Coasting();
}

void Limbs::StopLift()
{
    _rear_sub.Coasting();
    _front_sub.Coasting();
}


void Limbs::TurnAround()
{
    _left.Coasting();
    _right.Coasting();

    _left.SetDirection(MotorDriection::POSITIVE);
    _right.SetDirection(MotorDriection::NEGATIVE);

    _left.Start();
    _right.Start();
}

void Limbs::TurnLeft()
{
    _left.Coasting();
    _right.Coasting();

    _left.SetDirection(MotorDriection::POSITIVE);

    _left.Start();
}

void Limbs::TurnRight()
{
    _left.Coasting();
    _right.Coasting();

    _right.SetDirection(MotorDriection::POSITIVE);

    _right.Start();    
}

void Limbs::InitEmoji(gpio_num_t r, gpio_num_t g, gpio_num_t b, gpio_num_t color)
{
    gpio_config_t io_conf;
    io_conf.pin_bit_mask = (1ULL << r) | (1ULL << g) | (1ULL << b) | (1ULL << color);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);

    _r = r;
    _b = b;
    _g = g;
    _color = color;
}

void Limbs::SetColor(int color)
{
    switch (color)
    {
    case BLACK:
        gpio_set_level(_b, 0);
        gpio_set_level(_r, 0);
        gpio_set_level(_g, 0);
        break;
    case GREEN:
        gpio_set_level(_b, 0);
        gpio_set_level(_r, 0);
        gpio_set_level(_g, 1);
        break;
    case RED:
        gpio_set_level(_b, 0);
        gpio_set_level(_r, 1);
        gpio_set_level(_g, 0);
        break;
    case BLUE:
        gpio_set_level(_b, 1);
        gpio_set_level(_r, 0);
        gpio_set_level(_g, 0);
        break;
    case WHITE:
        gpio_set_level(_b, 1);
        gpio_set_level(_r, 1);
        gpio_set_level(_g, 1);
        break;
    
    default:
        break;
    }
}

void Limbs::SetAmbient(bool on)
{
    gpio_set_level(_color, on ? 1: 0);
}
void Limbs::SetEmoticon(const char* emotion)
{
    if (_r == GPIO_NUM_MAX || _g == GPIO_NUM_MAX || _b == GPIO_NUM_MAX){
        ESP_LOGE(TAG, "not init Emoticon PIN");        
        return;
    }

    return;

    const char* utf8 = font_awesome_get_utf8(emotion);
    if (utf8 != nullptr) {

        gpio_set_level(_b, 0);
        gpio_set_level(_r, 0);
        gpio_set_level(_g, 0);

        if (strcmp(utf8, FONT_AWESOME_SAD) == 0
        || strcmp(utf8, FONT_AWESOME_CRYING) == 0
        || strcmp(utf8, FONT_AWESOME_ANGRY) == 0){
            gpio_set_level(_r, 1);
            ESP_LOGI(TAG, "Start pin r %d : 1, g %d : 0, b %d : 0,", _r, _g, _b);
        } else if (strcmp(utf8, FONT_AWESOME_HAPPY) == 0
        || strcmp(utf8, FONT_AWESOME_LAUGHING) == 0
        || strcmp(utf8, FONT_AWESOME_FUNNY) == 0){
            gpio_set_level(_g, 1);
            ESP_LOGI(TAG, "Start pin r %d : 0, g %d : 1, b %d : 0,", _r, _g, _b);
        } else {
            gpio_set_level(_b, 1);
            ESP_LOGI(TAG, "Start pin r %d : 0, g %d : 0, b %d : 1,", _r, _g, _b);
        } 
     } else {
        ESP_LOGI(TAG, "Start pin r %d : 1, g %d : 1, b %d : 1,", _r, _g, _b);
        gpio_set_level(_b, 1);
        gpio_set_level(_r, 1);
        gpio_set_level(_g, 1);
     }

}