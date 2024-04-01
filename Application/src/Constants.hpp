#pragma once

#include <cstdint>

inline constexpr std::int32_t winWidth = 1280;
inline constexpr std::int32_t winHeight = 720;

inline constexpr std::int32_t gameWidth = 720;
inline constexpr std::int32_t videoWidth = winWidth-gameWidth;

inline constexpr float leftLanePos = -10.0f;
inline constexpr float centerLanePos = 0.0f;
inline constexpr float rightLanePos = 10.0f;