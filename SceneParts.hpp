/// @file SceneParts.hpp
///
/// @copyright Pati-Board 2023

#ifndef SCENEPARTS_HPP
#define SCENEPARTS_HPP

#include "SceneIf.hpp"
#include "Gpio.hpp"

class ScenePartOff :
   public SceneIf
{
public:
    ScenePartOff(const Gpio::PwmIf& rPwm, const uint16_t durationMs) :
        m_rPwm(rPwm),
        m_DurationMs(durationMs)
    {
    }

    void Start() override
    {
        m_rPwm.Write(0U);
    }

    uint16_t GetDurationMs() const override
    {
        return m_DurationMs;
    }

private:
    const Gpio::PwmIf& m_rPwm;
    const uint16_t m_DurationMs;
};

class ScenePartOn :
   public SceneIf
{
public:
    ScenePartOn(const Gpio::PwmIf& rPwm, const uint16_t durationMs) :
        m_rPwm(rPwm),
        m_DurationMs(durationMs)
    {
    }

    void Start() override
    {
        m_rPwm.Write(255U);
    }

    uint16_t GetDurationMs() const override
    {
        return m_DurationMs;
    }

private:
    const Gpio::PwmIf& m_rPwm;
    const uint16_t m_DurationMs;
};

class ScenePartOnRamp :
   public SceneIf
{
public:
    ScenePartOnRamp(const Gpio::PwmIf& rPwm, const uint16_t durationMs) :
        m_rPwm(rPwm),
        m_IncInterval(durationMs / PWM_DUTY_CYCLE),
        m_IncCnt(0U),
        m_DurationMs(durationMs)
    {
    }

    void Start() override
    {
        m_IncCnt = 0U;
        m_rPwm.Write(0U);
    }

    void Tick() override
    {
        if (++m_IncCnt == m_IncInterval)
        {
            m_rPwm.Write(m_rPwm.Read() + 1U);
            m_IncCnt = 0U;
        }
    }

    uint16_t GetDurationMs() const override
    {
        return m_DurationMs;
    }

private:
    static constexpr const uint16_t PWM_DUTY_CYCLE = 256U;
    const Gpio::PwmIf& m_rPwm;
    const uint8_t m_IncInterval;
    uint8_t m_IncCnt = 0U;
    const uint16_t m_DurationMs;
};

class ScenePartOffRamp :
   public SceneIf
{
public:
    ScenePartOffRamp(const Gpio::PwmIf& rPwm, const uint16_t durationMs) :
        m_rPwm(rPwm),
        m_IncInterval(durationMs / PWM_DUTY_CYCLE),
        m_IncCnt(0U),
        m_DurationMs(durationMs)
    {
    }

    void Start() override
    {
        m_IncCnt = 0U;
        m_rPwm.Write(255U);
    }

    void Tick() override
    {
        if (++m_IncCnt == m_IncInterval)
        {
            m_rPwm.Write(m_rPwm.Read() - 1U);
            m_IncCnt = 0U;
        }
    }

    uint16_t GetDurationMs() const override
    {
        return m_DurationMs;
    }

private:
    static constexpr const uint16_t PWM_DUTY_CYCLE = 256U;
    const Gpio::PwmIf& m_rPwm;
    const uint8_t m_IncInterval;
    uint8_t m_IncCnt = 0U;
    const uint16_t m_DurationMs;
};

#endif
