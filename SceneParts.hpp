/// @file SceneParts.hpp
///
/// @copyright Pati-Board 2023

#ifndef SCENEPARTS_HPP
#define SCENEPARTS_HPP

#include "SceneIf.hpp"
#include "Gpio.hpp"

template<uint16_t DurationMs>
class ScenePartOff :
   public SceneIf
{
public:
    ScenePartOff(const Gpio::PwmIf& rPwm) :
        m_rPwm(rPwm)
    {
    }

    void Start() override
    {
        m_rPwm.Write(0U);
    }

    uint16_t GetDurationMs() const override
    {
        return DurationMs;
    }

private:
    const Gpio::PwmIf& m_rPwm;
};

template<uint16_t DurationMs>
class ScenePartOn :
   public SceneIf
{
public:
    ScenePartOn(const Gpio::PwmIf& rPwm) :
        m_rPwm(rPwm)
    {
    }

    void Start() override
    {
        m_rPwm.Write(255U);
    }

    uint16_t GetDurationMs() const override
    {
        return DurationMs;
    }

private:
    const Gpio::PwmIf& m_rPwm;
};

template<uint16_t DurationMs>
class ScenePartOnRamp :
   public SceneIf
{
public:
    ScenePartOnRamp(const Gpio::PwmIf& rPwm) :
        m_rPwm(rPwm),
        m_IncCnt(0U)
    {
    }

    void Start() override
    {
        m_IncCnt = 0U;
        m_rPwm.Write(0U);
    }

    void Tick() override
    {
        if (++m_IncCnt == INC_INTERVAL)
        {
            m_rPwm.Write(m_rPwm.Read() + 1U);
            m_IncCnt = 0U;
        }
    }

    uint16_t GetDurationMs() const override
    {
        return DurationMs;
    }

private:
    static constexpr const uint16_t PWM_DUTY_CYCLE = 256U;
    static_assert((DurationMs % PWM_DUTY_CYCLE == 0U), "Duration must be mult. of 256");
    static constexpr const uint8_t INC_INTERVAL = static_cast<uint8_t>(DurationMs / PWM_DUTY_CYCLE);
    const Gpio::PwmIf& m_rPwm;
    uint8_t m_IncCnt = 0U;

};

template<uint16_t DurationMs>
class ScenePartOffRamp :
   public SceneIf
{
public:
    ScenePartOffRamp(const Gpio::PwmIf& rPwm) :
        m_rPwm(rPwm),
        m_IncCnt(0U)
    {
    }

    void Start() override
    {
        m_IncCnt = 0U;
        m_rPwm.Write(255U);
    }

    void Tick() override
    {
        if (++m_IncCnt == INC_INTERVAL)
        {
            m_rPwm.Write(m_rPwm.Read() - 1U);
            m_IncCnt = 0U;
        }
    }

    uint16_t GetDurationMs() const override
    {
        return DurationMs;
    }

private:
    static constexpr const uint16_t PWM_DUTY_CYCLE = 256U;
    static_assert((DurationMs % PWM_DUTY_CYCLE == 0U), "Duration must be mult. of 256");
    static constexpr const uint8_t INC_INTERVAL = static_cast<uint8_t>(DurationMs / PWM_DUTY_CYCLE);
    const Gpio::PwmIf& m_rPwm;
    uint8_t m_IncCnt = 0U;

};

#endif
