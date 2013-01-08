// Copyright (C) Ville Ruusutie, 2010

#pragma once
#ifndef unitos_platform_h
#define unitos_platform_h

#if defined(__linux__) && defined(__ELF__)
#   define __UNITOS_LINUX__ (1)
#elif defined(WIN32) || defined(_WIN32)
#   define __UNITOS_WIN32__ (1)
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#elif defined(__APPLE__) && defined(__MACH__)
#   define __UNITOS_MACOSX__ (1)
#else
#error Could not determine your operating system in platform.h
#endif

#if defined(__UNITOS_WIN32__) || defined(__UNITOS_LINUX__)
#   define UNITOS_TRAP() if(unitos::IsDebuggerConnected()) { __asm { int 3 }; }
#elif defined(__UNITOS_MACOSX__)
#   if defined(__arm__)
#       define UNITOS_TRAP() if(unitos::IsDebuggerConnected()) { __asm__ volatile("bkpt 0"); }
#   else
#       define UNITOS_TRAP() if(unitos::IsDebuggerConnected()) { __asm__ __volatile__("int $3\nnop\n"); }
#   endif
#else
#error UNITOS_TRAP not implemented for this platform
#endif

#if !defined(_MSC_VER) && !defined(__forceinline)
#   if defined(__GNUC__)
#       define __forceinline inline __attribute__((always_inline))
#   else
#       define __forceinline inline
#   endif
#endif

#if !defined(_MSC_VER)
typedef signed long long __int64;
#endif

namespace unitos {

void MemCopy(void* dest, void const* src, int length);
int StrCmp(char const* str, char const* otherStr);
int StrLen(char const* text);
bool IsDebuggerConnected();
__int64 GetSystemTime();

}

#endif
