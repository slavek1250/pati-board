/// @file SceneParts.cpp
///
/// @copyright Pati-Board 2023

#include "SceneParts.hpp"

ScenePartOff::ScenePartOff(const Gpio::PwmIf& rPwm, const uint16_t durationMs) :
    m_rPwm(rPwm),
    m_DurationMs(durationMs)
{
}

void ScenePartOff::Start()
{
    m_rPwm.Write(0U);
}

uint16_t ScenePartOff::GetDurationMs() const
{
    return m_DurationMs;
}

ScenePartOn::ScenePartOn(const Gpio::PwmIf& rPwm, const uint16_t durationMs) :
    m_rPwm(rPwm),
    m_DurationMs(durationMs)
{
}

void ScenePartOn::Start()
{
    m_rPwm.Write(255U);
}

uint16_t ScenePartOn::GetDurationMs() const
{
    return m_DurationMs;
}

ScenePartOnRamp::ScenePartOnRamp(const Gpio::PwmIf& rPwm, const uint16_t durationMs) :
    m_rPwm(rPwm),
    m_IncInterval(durationMs / PWM_DUTY_CYCLE),
    m_IncCnt(0U),
    m_DurationMs(durationMs)
{
}

void ScenePartOnRamp::Start()
{
    m_IncCnt = 0U;
    m_rPwm.Write(0U);
}

void ScenePartOnRamp::Tick()
{
    if (++m_IncCnt == m_IncInterval)
    {
        m_rPwm.Write(m_rPwm.Read() + 1U);
        m_IncCnt = 0U;
    }
}

uint16_t ScenePartOnRamp::GetDurationMs() const
{
    return m_DurationMs;
}

ScenePartOffRamp::ScenePartOffRamp(const Gpio::PwmIf& rPwm, const uint16_t durationMs) :
    m_rPwm(rPwm),
    m_IncInterval(durationMs / PWM_DUTY_CYCLE),
    m_IncCnt(0U),
    m_DurationMs(durationMs)
{
}

void ScenePartOffRamp::Start()
{
    m_IncCnt = 0U;
    m_rPwm.Write(255U);
}

void ScenePartOffRamp::Tick()
{
    if (++m_IncCnt == m_IncInterval)
    {
        m_rPwm.Write(m_rPwm.Read() - 1U);
        m_IncCnt = 0U;
    }
}

uint16_t ScenePartOffRamp::GetDurationMs() const
{
    return m_DurationMs;
}
