/// @file Button.cpp
///
/// @copyright Pati-Board 2023

#include "Button.hpp"

Button::Button(ObserverIf& rObserver, const Gpio::BinaryInput& rInput, const bool activeLow) :
    m_rObserver(rObserver),
    m_rInput(rInput),
    m_ActiveLow(activeLow)
{
}

void Button::Scan()
{
    if (Debounce(Read()))
    {
        m_rObserver.Notify();
    }
}

bool Button::Read()
{
    return m_ActiveLow ? !m_rInput.Read() : m_rInput.Read();
}

bool Button::Debounce(const bool state)
{
    m_Fifo <<= 1U;
    m_Fifo |= static_cast<uint8_t>(state);
    return (m_Fifo == ACTIVE_VAL);
}
