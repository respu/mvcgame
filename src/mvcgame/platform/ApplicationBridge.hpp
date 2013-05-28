#ifndef mvcgame_ApplicationBridge_hpp
#define mvcgame_ApplicationBridge_hpp

#ifdef MVCGAME_PLATFORM_LINUX
#include <mvcgame/platform/linux/ApplicationBridge.hpp>
#elif defined(MVCGAME_PLATFORM_WIN)
#include <mvcgame/platform/win/ApplicationBridge.hpp>
#endif

#endif