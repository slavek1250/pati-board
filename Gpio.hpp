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

}

#endif
