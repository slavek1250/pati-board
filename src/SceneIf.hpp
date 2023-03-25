/// @file SceneIf.hpp
///
/// @copyright Pati-Board 2023

#ifndef SCENEIF_HPP
#define SCENEIF_HPP

#include <stdint.h>

/// @brief Scene interface.
class SceneIf
{
public:
    /// @brief Start scene.
    virtual void Start()
    {
    }

    /// @brief Scene tick.
    virtual void Tick()
    {
    }

    /// @brief Stop scene.
    virtual void Stop()
    {
    }

    /// @brief Get scene duration.
    /// @return Scene duration in milliseconds.
    virtual uint16_t GetDurationMs() const
    {
        return 0U;
    }
};

#endif
