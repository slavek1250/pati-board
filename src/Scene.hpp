/// @file Scene.hpp
///
/// @copyright Pati-Board 2023

#ifndef SCENE_HPP
#define SCENE_HPP

#include "SceneIf.hpp"

class Scene :
   public SceneIf
{
public:
    Scene(SceneIf* const* const pSubScenes, const uint8_t subScenesNum);

    void Start() override;

    void Tick() override;

    void Stop() override;

    uint16_t GetDurationMs() const override;

private:
    SceneIf* const* const m_pSubScenes = nullptr;
    const uint8_t m_SubScenesNum = 0U;
    uint16_t m_MsCnt;
    uint8_t m_SceneIte;
};

#endif
