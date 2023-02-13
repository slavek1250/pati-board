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

int main(void)
{
    wdt_enable(WDTO_1S);
    Gpio::PwmPb3 ledPwmOutput;
    Gpio::BinaryInput btnDriver(4U, true);
    ButtonObserver btnObserver;
    Button btn(btnObserver, btnDriver, true);

    ScenePartOn<500U> sceneOn(ledPwmOutput);
    ScenePartOff<500U> sceneOff(ledPwmOutput);
    ScenePartOnRamp<1024U> sceneOnRamp(ledPwmOutput);
    ScenePartOffRamp<1024U> sceneOffRamp(ledPwmOutput);

    // Scene one.
    SceneIf* const pSceneOneParts[] = {
        &sceneOn,
        &sceneOff,
    };
    Scene sceneOne(pSceneOneParts, 2U);

    // Scene two.
    SceneIf* const pSceneTwoParts[] = {
        &sceneOnRamp,
        &sceneOn,
        &sceneOn,
        &sceneOffRamp,
        &sceneOff
    };
    Scene sceneTwo(pSceneTwoParts, 5U);

    // All scenes
    SceneIf* const pScenes[] = {
        &sceneOne,
        &sceneTwo
    };

    uint8_t sceneIte = 0U;

    while(true)
    {
        if (btnObserver.IfChangeScene())
        {
            pScenes[sceneIte]->Stop();
            sceneIte = (sceneIte + 1U) % 2U;
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
