/// @file Gpio.cpp
///
/// @copyright Pati-Board 2023

#include "Gpio.hpp"
#include <avr/io.h>
#include <util/delay.h>

namespace Gpio
{

BinaryInput::BinaryInput(const uint8_t pin, const bool pullUp) :
    m_Pin(pin)
{
    // Clear bit, configure as input.
    DDRB &= ~(1U << m_Pin);

    if (pullUp)
    {
        // Enable pull-up.
        PORTB |= (1U << m_Pin);
    }
    else
    {
        // Disable pull-up.
        PORTB &= ~(1U << m_Pin);
    }
}

BinaryInput::~BinaryInput()
{
    // Disable pull-up.
    PORTB &= ~(1U << m_Pin);
}

bool BinaryInput::BinaryInput::Read() const
{
    return (PINB & (1U << m_Pin)) != 0U;
}

BinaryOutput::BinaryOutput(const uint8_t pin) :
    m_Pin(pin)
{
    // Configure as output.
    DDRB |= (1U << m_Pin);
    // Clear output.
    PORTB &= ~(1U << m_Pin);
}

BinaryOutput::~BinaryOutput()
{
    // Configure back as input.
    DDRB &= ~(1U << m_Pin);
    // Clear output.
    PORTB &= ~(1U << m_Pin);
}

bool BinaryOutput::Read() const
{
    return (PORTB & (1U << m_Pin)) != 0U;
}

void BinaryOutput::Write(const bool state) const
{
    if (state)
    {
        PORTB |= (1U << m_Pin);
    }
    else
    {
        PORTB &= ~(1U << m_Pin);
    }
}

PwmPb3::PwmPb3()
{
    // Configure as output.
    DDRB |= (1U << DDB3);
    // Enable PWM B, Toggle ~OC1B output line.
    GTCCR |= (1 << PWM1B) | (1U << COM1B0);
    // No clock prescaling, start timer.
    TCCR1 = (1U << CS10);
    OCR1B = 0U;
}

PwmPb3::~PwmPb3()
{
    // Disable timer.
    TCCR1 &= ~(1U << CS10);
    // Disable PWM B.
    TCCR0B &= ~((1 << PWM1B) | (1U << COM1B0));
    // Configure back as input.
    DDRB &= ~(1U << DDB3);
}

uint8_t PwmPb3::Read() const
{
    return OCR1B;
}

void PwmPb3::Write(const uint8_t value) const
{
    OCR1B = value;
}

}
