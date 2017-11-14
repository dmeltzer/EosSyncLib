// Copyright (c) 2015 Electronic Theatre Controls, Inc., http://www.etcconnect.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "EosTimer.h"

#ifdef WIN32
	#include <Winsock2.h>
	#include <Windows.h>
#elif defined __APPLE__
	#include <mach/mach.h>
	#include <mach/mach_time.h>
#else // LINUX
    #include <sys/time.h>
#endif
    #include <unistd.h>
    double EosTimer::sm_toMS = 0;
////////////////////////////////////////////////////////////////////////////////

EosTimer::EosTimer()
{
	Start();
}

////////////////////////////////////////////////////////////////////////////////

void EosTimer::Start()
{
	m_Timestamp = GetTimestamp();
}

////////////////////////////////////////////////////////////////////////////////

unsigned int EosTimer::Restart()
{
	unsigned int elapsed = GetElapsed();
	Start();
	return elapsed;
}

////////////////////////////////////////////////////////////////////////////////

unsigned int EosTimer::GetElapsed() const
{
	return (GetTimestamp() - m_Timestamp);
}

////////////////////////////////////////////////////////////////////////////////

bool EosTimer::GetExpired(unsigned int ms) const
{
	return (GetElapsed() >= ms);
}

////////////////////////////////////////////////////////////////////////////////

void EosTimer::Init()
{
#ifdef __APPLE__
	if(sm_toMS == 0)
	{
		mach_timebase_info_data_t timeBase;
		mach_timebase_info( &timeBase );
		sm_toMS = timeBase.numer/static_cast<double>(timeBase.denom);
		sm_toMS /= 1000000;
	}
#endif
}

////////////////////////////////////////////////////////////////////////////////

unsigned int EosTimer::GetTimestamp()
{
#if defined WIN32
    return timeGetTime();
#elif defined __APPLE__
    return static_cast<unsigned int>(mach_absolute_time() * sm_toMS);
#else // Linux
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_usec/1000;
#endif
}

////////////////////////////////////////////////////////////////////////////////

void EosTimer::SleepMS(unsigned int ms)
{
#ifdef WIN32
	Sleep(ms);
#else
	usleep(ms*1000);
#endif
}

////////////////////////////////////////////////////////////////////////////////
