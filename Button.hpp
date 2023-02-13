/// @file Button.hpp
///
/// @copyright Pati-Board 2023

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Gpio.hpp"
#include "ObserverIf.hpp"

/// @brief Button class that scans input with debouncing and notifies observer when button is pressed.
class Button
{
public:
    /// @brief Constructor.
    /// @param rObserver Observer of button press event.
    /// @param rInput Input to scan.
    /// @param activeLow Set to true when input is active low.
    Button(ObserverIf& rObserver, const Gpio::BinaryInput& rInput, const bool activeLow);

    /// @brief Scan input. It should be called every 1ms.
    void Scan();

private:
    static constexpr const uint8_t ACTIVE_VAL = 0x0FU;

    bool Read();
    bool Debounce(const bool state);

    ObserverIf& m_rObserver;
    const Gpio::BinaryInput& m_rInput;
    const bool m_ActiveLow;
    uint8_t m_Fifo;
};

#endif
