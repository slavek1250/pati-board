/// @file SceneParts.hpp
///
/// @copyright Pati-Board 2023

#ifndef SCENEPARTS_HPP
#define SCENEPARTS_HPP

#include "SceneIf.hpp"
#include "Gpio.hpp"

/// @brief Scene turned off.
class ScenePartOff :
   public SceneIf
{
public:
    /// @brief Constructor.
    /// @param rPwm PWM driver.
    /// @param durationMs Scene duration in milliseconds.
    ScenePartOff(const Gpio::PwmIf& rPwm, const uint16_t durationMs);

    /// @copydoc SceneIf::Start()
    void Start() override;

    /// @copydoc SceneIf::GetDurationMs()
    uint16_t GetDurationMs() const override;

private:
    const Gpio::PwmIf& m_rPwm;
    const uint16_t m_DurationMs;
};

/// @brief Scene turned on.
class ScenePartOn :
   public SceneIf
{
public:
    /// @brief Constructor.
    /// @param rPwm PWM driver.
    /// @param durationMs Scene duration in milliseconds.
    ScenePartOn(const Gpio::PwmIf& rPwm, const uint16_t durationMs);

    /// @copydoc SceneIf::Start()
    void Start() override;

    /// @copydoc SceneIf::GetDurationMs()
    uint16_t GetDurationMs() const override;

private:
    const Gpio::PwmIf& m_rPwm;
    const uint16_t m_DurationMs;
};

/// @brief Scene ramping on.
class ScenePartOnRamp :
   public SceneIf
{
public:
    /// @brief Constructor.
    /// @param rPwm PWM driver.
    /// @param durationMs Scene duration in milliseconds.
    ScenePartOnRamp(const Gpio::PwmIf& rPwm, const uint16_t durationMs);

    /// @copydoc SceneIf::Start()
    void Start() override;

    /// @copydoc SceneIf::Tick()
    void Tick() override;

    /// @copydoc SceneIf::GetDurationMs()
    uint16_t GetDurationMs() const override;

private:
    static constexpr const uint16_t PWM_DUTY_CYCLE = 256U;
    const Gpio::PwmIf& m_rPwm;
    const uint8_t m_IncInterval;
    uint8_t m_IncCnt = 0U;
    const uint16_t m_DurationMs;
};

/// @brief Scene ramping off.
class ScenePartOffRamp :
   public SceneIf
{
public:
    /// @brief Constructor.
    /// @param rPwm PWM driver.
    /// @param durationMs Scene duration in milliseconds.
    ScenePartOffRamp(const Gpio::PwmIf& rPwm, const uint16_t durationMs);

    /// @copydoc SceneIf::Start()
    void Start() override;

    /// @copydoc SceneIf::Tick()
    void Tick() override;

    /// @copydoc SceneIf::GetDurationMs()
    uint16_t GetDurationMs() const override;

private:
    static constexpr const uint16_t PWM_DUTY_CYCLE = 256U;
    const Gpio::PwmIf& m_rPwm;
    const uint8_t m_IncInterval;
    uint8_t m_IncCnt = 0U;
    const uint16_t m_DurationMs;
};

#endif
