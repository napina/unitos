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
#include "unitos/platform.h"
#if defined(UNITOS_MACOSX)
#include <mach/mach_time.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#elif defined(UNITOS_WINDOWS)
#include <windows.h>
#elif defined(UNITOS_LINUX)
#include <sys/ptrace.h>
#endif

namespace unitos {

bool isDebuggerConnected()
{
#if defined(UNITOS_MACOSX)
    // From Technical Q&A QA1361
    // Returns true if the current process is being debugged (either running
    // under the debugger or has a debugger attached post facto).
    int                 junk;
    int                 mib[4];
    struct kinfo_proc   info;
    size_t              size;
        
    // Initialize the flags so that, if sysctl fails for some bizarre reason, we get a predictable result.
    info.kp_proc.p_flag = 0;
        
    // Initialize mib, which tells sysctl the info we want, in this case we're looking for
    // information about a specific process ID.
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_PID;
    mib[3] = ::getpid();

    size = sizeof(info);
    junk = ::sysctl(mib, sizeof(mib) / sizeof(*mib), &info, &size, NULL, 0);

    return (info.kp_proc.p_flag & P_TRACED) != 0;
#elif defined(UNITOS_WINDOWS)
    return ::IsDebuggerPresent() == TRUE;
#elif defined(UNITOS_LINUX)
    return ::ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1;
#else
    #error isDebuggerConnected not implemented for current platform
#endif
}
//-----------------------------------------------------------------------------

int64_t getSystemTime()
{
#if defined(UNITOS_WINDOWS)
    static int64_t start = 0;
    static int64_t frequency = 0;
    static double timeToMilliseconds = 0.0;
    int64_t counter = 0;
    int64_t diff = 0;

    if(start == 0) {
        ::QueryPerformanceCounter((LARGE_INTEGER*)&start);
        ::QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
        timeToMilliseconds = 1000000.0 / (double)frequency;
        return 0;
    }

    ::QueryPerformanceCounter((LARGE_INTEGER*)&counter);
    diff = counter - start;
    return (int64_t)(diff * timeToMilliseconds);
#elif defined(UNITOS_MACOSX)
    static int64_t start = 0;
    static double timeToMilliseconds = 0.0;
    int64_t counter = 0;
    int64_t diff = 0;

    if(start == 0) {
        ::mach_timebase_info_data_t info;
        ::mach_timebase_info(&info);
        start = ::mach_absolute_time();
        timeToMilliseconds = 1e-6 * ((double)info.numer) / ((double)info.denom);
        return 0;
    }

    counter = ::mach_absolute_time();
    diff = counter - start;
    return (int64_t)(diff * timeToMilliseconds);
#else
#   error getSystemTime not implemented for current platform
#endif
}

}
