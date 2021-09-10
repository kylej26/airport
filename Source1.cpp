#include "Header1.h"
#include <ctime>
#include <cstdlib>

namespace runspace {

	Runway::Runway(int lT, int tOT) {
		landTime = lT;
		takeOffTime = tOT;
		workTime = 0;
	}
	bool Runway::isFree() { return (workTime == 0); }
	void Runway::oneSecond() {
		if (workTime > 0) { workTime -= 1; }
	}
	void Runway::takeOff() { workTime = takeOffTime; }
	void Runway::land() { workTime = landTime; }

	Averager::Averager() {
		crashedCount = 0;
		landedCount = 0;
		tookOffCount = 0;
		landingWaitSum = 0;
		takeOffWaitSum = 0;
	}
	int Averager::landedPlanes() { return landedCount; }
	int Averager::tookOffPlanes() { return tookOffCount; }
	int Averager::crashedPlanes() { return crashedCount; }
	int Averager::averageLandingWait() {
		if (landedCount == 0) { return 0; }
		return landingWaitSum / landedCount;
	}
	int Averager::averageTakeOffWait() {
		if (tookOffCount == 0) { return 0; }
		return takeOffWaitSum / tookOffCount;
	}
	void Averager::storeLanding(int wait) {
		landedCount++;
		landingWaitSum += wait;
	}
	void Averager::storeTakeOff(int wait) {
		tookOffCount++;
		takeOffWaitSum += wait;
	}
	void Averager::storeCrash() { crashedCount++; }

	BoolSource::BoolSource(double thisInterval) {
		probability = 1 / thisInterval;
	}

	bool BoolSource::isTrue() {
		srand((unsigned)time(0));
		int key = rand();
		double maxx = 32767.0;

		if (key <= (probability * maxx)) {
			return true;
		}
		return false;
	}
}
