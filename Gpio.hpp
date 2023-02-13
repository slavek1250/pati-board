/// @file Gpio.hpp
///
/// @copyright Pati-Board 2023

#ifndef GPIO_HPP
#define GPIO_HPP

#include <stdint.h>

namespace Gpio
{

/// @brief Binary input driver.
class BinaryInput
{
public:
    /// @brief Constructor.
    /// @param pin    Pin to read.
    /// @param pullUp Use pull up or not.
    BinaryInput(const uint8_t pin, const bool pullUp = false);

    ~BinaryInput();

    /// @brief Read input.
    /// @return Input state.
    bool Read() const;

private:
    const uint8_t m_Pin;
};

/// @brief Binary output driver.
class BinaryOutput
{
public:
    /// @brief Constructor.
    /// @param pin Pin to drive.
    BinaryOutput(const uint8_t pin);

    ~BinaryOutput();

    /// @brief Read-back output value.
    /// @return Output state.
    bool Read() const;

    /// @brief Write state to output.
    /// @param state State to write.
    void Write(const bool state) const;

private:
    const uint8_t m_Pin;
};

/// @brief PWM interface.
class PwmIf
{
public:
    /// @brief Read back PWM duty-cycle
    /// @return PWM duty cycle.
    virtual uint8_t Read() const = 0;

    /// @brief Set PWM duty-cycle
    /// @param value PWM duty cycle to set.
    virtual void Write(const uint8_t value) const = 0;
};

/// @brief Implementation of PWM for PB3 pin.
class PwmPb3 :
    public PwmIf
{
public:
    PwmPb3();

    ~PwmPb3();

    /// @copydoc Gpio::PwmIf::Read()
    uint8_t Read() const override;

    /// @copydoc Gpio::PwmIf::Write()
    void Write(const uint8_t value) const override;
};

}

#endif
