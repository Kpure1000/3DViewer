#include"system/Time.h"

namespace rtx
{
	namespace system
	{

		float Time::currentTime()
		{
			return static_cast<float>(clock() - programStart_time) / 1000.0f;
		}

		float Time::deltaTime()
		{
			return static_cast<float>(delta_time) / 1000.0f;
		}

		void Time::TimeStart()
		{
			programStart_time = clock();
		}

		void Time::FrameDisplay()
		{
			delta_time = clock() - frameStart_time;
			frameStart_time = clock();
		}

		clock_t Time::programStart_time = 0;
		clock_t Time::frameStart_time = 0;
		clock_t Time::delta_time = 0;

	}
}

