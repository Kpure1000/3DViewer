#ifndef TIME_H
#define TIME_H
#include<ctime>

namespace rtx
{
	namespace system
	{
		/// <summary>
		/// Time counter
		/// </summary>
		class Time
		{
		public:
			
			static float currentTime();

			static float deltaTime();
			
			static void TimeStart();

			static void FrameDisplay();

		private:
			
			static clock_t programStart_time;

			static clock_t frameStart_time;

			static clock_t delta_time;
		};

	}
}

#endif // !TIME_H

