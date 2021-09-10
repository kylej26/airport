#pragma once
#ifndef RUNWAY
#define RUNWAY

namespace runspace {

	class Runway {
	private:
		int workTime, landTime, takeOffTime;

	public:
		Runway(int lT, int tOT);
		bool isFree();
		void oneSecond();
		void takeOff();
		void land();
	};

	class Averager {
	private:
		int crashedCount, landedCount, tookOffCount, landingWaitSum, takeOffWaitSum;

	public:
		Averager();
		int landedPlanes();
		int tookOffPlanes();
		int crashedPlanes();
		int averageLandingWait();
		int averageTakeOffWait();
		void storeLanding(int wait);
		void storeTakeOff(int wait);
		void storeCrash();
	};

	class BoolSource {
	private:
		double probability;

	public:
		BoolSource(double thisInterval);

		bool isTrue();
	};
}
#endif // !RUNWAY;
