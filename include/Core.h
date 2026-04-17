#pragma once

// In a central header like Core.h
#ifdef NDEBUG
#define ASSERT(x, msg)
#else
#define ASSERT(x, msg)                                                                             \
    if (!(x))                                                                                      \
    {                                                                                              \
        std::printf("ASSERT FAILED: %s\nFile: %s\nLine: %d\n", msg, __FILE__, __LINE__);           \
        __debugbreak();                                                                            \
    }
#endif