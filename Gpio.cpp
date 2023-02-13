/// @file Gpio.cpp
///
/// @copyright Pati-Board 2023

#include "Gpio.hpp"
#include <avr/io.h>

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

}
