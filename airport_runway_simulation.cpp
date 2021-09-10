#include <iostream>
#include <ctime>
#include <queue>
#include "Header1.h"
using namespace std;
using namespace runspace;


void airportSimulation(int landInterval, int takeOffInterval, int simTime) {
	int landPeriod, takeOffPeriod, fuelTime;
	cout << "How long does it take a plane to land: ";
	cin >> landPeriod;
	cout << "How long does a take-off last: ";
	cin >> takeOffPeriod;
	cout << "How long can a plane hover without refuelling: ";
	cin >> fuelTime;

	cout << "\nGenerating results...\n\n";

	Runway thisRunway(landPeriod, takeOffPeriod);
	Averager thisAverage;
	BoolSource newLandPlane(landInterval);
	BoolSource newTakeOffPlane(takeOffInterval);
	queue<int> landingPlanes;
	queue<int> departingPlanes;

	for (int time = 1; time <= simTime; time++) {
		if (newLandPlane.isTrue()) { landingPlanes.push(time); }
		if (newTakeOffPlane.isTrue()) { departingPlanes.push(time); }

		if (thisRunway.isFree()) {
			if (!landingPlanes.empty()) {
				int aircraft = landingPlanes.front();
				landingPlanes.pop();
				int wait = time - aircraft;
				if (wait > fuelTime) { thisAverage.storeCrash(); }
				else {
					thisRunway.land();
					thisAverage.storeLanding(wait);
				}
			}
			else if (!departingPlanes.empty()) {
				int aircraft = departingPlanes.front();
				departingPlanes.pop();
				thisRunway.takeOff();
				thisAverage.storeTakeOff(time - aircraft);
			}
		}

		thisRunway.oneSecond();
	}

	cout << thisAverage.tookOffPlanes() << " aircrafts took off during this simulation...\n";
	cout << thisAverage.landedPlanes() << " aircrafts landed...\nwhile ";
	cout << thisAverage.crashedPlanes() << " aircrafts crashed, during this simulation.\n\n";
	cout << "Landing aircrafts waited for an average of " << thisAverage.averageLandingWait() << " simulation minutes...\nwhile ";
	cout << "departing aircrafts waited for an average of " << thisAverage.averageTakeOffWait() << " simulation minutes.\n\n";
}

int main()
{
	cout << "WELCOME TO MY AIRPORT SIMULATION PROJECT.\n";
	cout << "!!PLEASE ENSURE THAT ALL ENTIRES ARE INTEGERS!!\n";
	cout << "ALL TIME ENTRIES ARE IN SECONDS\n\n";
	int landInterval, departInterval, simDuration;

	cout << "What is the average interval between arrivals of departing aircrafts: ";
	cin >> departInterval;
	cout << "What is the average interval between arrivals of landing aircrafts: ";
	cin >> landInterval;
	cout << "For how long do you want to run this simulation: ";
	cin >> simDuration;

	cout << "\nRunning simulation algorithm...\n\n";

	airportSimulation(landInterval, departInterval, simDuration);

	return (0);
}