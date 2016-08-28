/*=============================================================================

Copyright (c) 2010 Ville Ruusutie

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

=============================================================================*/
#pragma once
#ifndef unitos_platform_h
#define unitos_platform_h

#if defined(__linux__) && defined(__ELF__)
#   define UNITOS_LINUX (1)
#   define UNITOS_ARCH32 (1)
#elif defined(__APPLE__) && defined(__MACH__)
#   define UNITOS_MACOSX (1)
#   define UNITOS_ARCH32 (1)
#elif defined(_WIN64) || defined(_M_X64)
#   define UNITOS_WINDOWS (1)
#   define UNITOS_ARCH64 (1)
#elif defined(_WIN32) || defined(_M_IX86)
#   define UNITOS_WINDOWS (1)
#   define UNITOS_ARCH32 (1)
#else
#error Could not determine your operating system in platform.h
#endif

#if defined(UNITOS_WINDOWS)
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#endif

#if defined(UNITOS_WINDOWS)
#   define UNITOS_TRAP() if(unitos::isDebuggerConnected()) { __debugbreak(); }
#elif defined(UNITOS_LINUX)
#   define UNITOS_TRAP() if(unitos::isDebuggerConnected()) {  __asm { int 3 }; }
#elif defined(UNITOS_MACOSX)
#   if defined(__arm__)
#       define UNITOS_TRAP() if(unitos::isDebuggerConnected()) { __asm__ volatile("bkpt 0"); }
#   else
#       define UNITOS_TRAP() if(unitos::isDebuggerConnected()) { __asm__ __volatile__("int $3\nnop\n"); }
#   endif
#else
#error UNITOS_TRAP not implemented for this platform
#endif

#if defined(__GNUC__)
#	define __forceinline inline __attribute__((always_inline))
#elif !defined(UNITOS_WINDOWS) && !defined(__forceinline)
#	define __forceinline inline
#endif

#if defined(UNITOS_WINDOWS)
typedef signed __int64 int64_t;
typedef unsigned __int64 uint64_t;
#elif defined(UNITOS_MACOSX)
#   include <stddef.h>
#   include <inttypes.h>
#else
typedef signed long long int64_t;
typedef unsigned long long uint64_t;
#endif

typedef decltype(nullptr) nullptr_t;

namespace unitos {

bool isDebuggerConnected();
int64_t getSystemTime();

}

#endif
