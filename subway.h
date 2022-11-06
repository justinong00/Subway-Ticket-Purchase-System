#ifndef SUBWAY_H_
#define SUBWAY_H_

# include <string>

using namespace std;

class Subway{

	public:
		int subwayId{};
		string currentStationName;
		string previousStationName;
		string nextStationName;
		double travelDistanceBetweenPreviousStation{};
		double travelFareBetweenPreviousStation{};
		double travelTimeBetweenPreviousStation{};
		double travelDistanceBetweenNextStation{};
		double travelFareBetweenNextStation{};
		double travelTimeBetweenNextStation{};
		string nearbySightseeingSpots;

		Subway() = default;

		Subway(int subwayId, string currentStationName, string previousStationName, string nextStationName,
				double travelDistanceBetweenPreviousStation, double travelFareBetweenPreviousStation, double travelTimeBetweenPreviousStation,
				double travelDistanceBetweenNextStation, double travelFareBetweenNextStation, double travelTimeBetweenNextStation,
				string nearbySightseeingSpots)
		{
			this->subwayId = subwayId;
			this->currentStationName = currentStationName;
			this->previousStationName = previousStationName;
			this->nextStationName = nextStationName;
			this->travelDistanceBetweenPreviousStation = travelDistanceBetweenPreviousStation;
			this->travelFareBetweenPreviousStation = travelFareBetweenPreviousStation;
			this->travelTimeBetweenPreviousStation = travelTimeBetweenPreviousStation;
			this->travelDistanceBetweenNextStation = travelDistanceBetweenNextStation;
			this->travelFareBetweenNextStation = travelFareBetweenNextStation;
			this->travelTimeBetweenNextStation = travelTimeBetweenNextStation;
			this->nearbySightseeingSpots = nearbySightseeingSpots;
		}
};
#endif
