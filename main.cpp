/// @file main.cpp
///
/// @copyright Pati-Board 2023

#include <avr/wdt.h>
#include <util/delay.h>

#include "Scene.hpp"
#include "SceneParts.hpp"
#include "Gpio.hpp"
#include "Button.hpp"

class ButtonObserver :
    public ObserverIf
{
public:
    void Notify() override
    {
        m_bChangeScene = true;
    }

    bool IfChangeScene()
    {
        const bool bChangeScene = m_bChangeScene;
        m_bChangeScene = false;
        return bChangeScene;
    }

private:
    bool m_bChangeScene = false;
};

#define countof(x) (sizeof(x) / sizeof(x[0U]))

int main(void)
{
    wdt_enable(WDTO_1S);
    Gpio::PwmPb3 ledPwmOutputRaw;
    Gpio::PwmReverse ledPwmOutput(ledPwmOutputRaw);
    Gpio::BinaryInput btnDriver(4U, true);
    ButtonObserver btnObserver;
    Button btn(btnObserver, btnDriver, true);

    ScenePartOn sceneOn(ledPwmOutput, 250U);
    ScenePartOff sceneOff(ledPwmOutput, 250U);
    ScenePartOnRamp sceneLongOnRamp(ledPwmOutput, 4096U);
    ScenePartOffRamp sceneLongOffRamp(ledPwmOutput, 4096U);

    SceneIf* const pSceneSlowBreathingParts[] = {
        &sceneLongOnRamp,
        &sceneLongOffRamp
    };
    Scene sceneSlowBreathing(pSceneSlowBreathingParts, countof(pSceneSlowBreathingParts));

    SceneIf* const pSceneQuickBlinkingParts[] = {
        &sceneOn,
        &sceneOff
    };
    Scene sceneQuickBlinking(pSceneQuickBlinkingParts, countof(pSceneQuickBlinkingParts));

    // All scenes
    SceneIf* const pScenes[] = {
        &sceneOff,
        &sceneOn,
        &sceneSlowBreathing,
        &sceneQuickBlinking,
    };

    uint8_t sceneIte = 0U;

    sceneOff.Start();

    while (true)
    {
        if (btnObserver.IfChangeScene())
        {
            pScenes[sceneIte]->Stop();
            sceneIte = (sceneIte + 1U) % countof(pScenes);
            pScenes[sceneIte]->Start();
        }
        else
        {
            pScenes[sceneIte]->Tick();
        }

        wdt_reset();
        btn.Scan();
        _delay_ms(1U);
    }
}
