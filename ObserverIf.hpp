/// @file ObserverIf.hpp
///
/// @copyright Pati-Board 2023

#ifndef OBSERVERIF_HPP
#define OBSERVERIF_HPP

/// @brief Observer interface.
class ObserverIf
{
public:
    /// @brief Method called when event is fired.
    virtual void Notify() = 0;
};

#endif
