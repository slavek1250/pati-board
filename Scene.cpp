/// @file Scene.cpp
///
/// @copyright Pati-Board 2023

#include "Scene.hpp"

Scene::Scene(SceneIf* const* const pSubScenes, const uint8_t subScenesNum) :
    m_pSubScenes(pSubScenes),
    m_SubScenesNum(subScenesNum)
{
}

void Scene::Start()
{
    m_SceneIte = 0U;
    m_MsCnt = 0U;
    m_pSubScenes[0U]->Start();
}

void Scene::Tick()
{
    if (m_MsCnt >= m_pSubScenes[m_SceneIte]->GetDurationMs())
    {
        m_pSubScenes[m_SceneIte]->Stop();
        m_SceneIte = (m_SceneIte + 1U) % m_SubScenesNum;
        m_MsCnt = 0U;
        m_pSubScenes[m_SceneIte]->Start();
    }
    else
    {
        m_pSubScenes[m_SceneIte]->Tick();
    }

    ++m_MsCnt;
}

void Scene::Stop()
{
    m_pSubScenes[m_SceneIte]->Stop();
}

uint16_t Scene::GetDurationMs() const
{
    uint16_t durationMs = 0U;

    for (uint8_t i = 0U; i < m_SubScenesNum; ++i)
    {
        durationMs += m_pSubScenes[i]->GetDurationMs();
    }

    return durationMs;
}
