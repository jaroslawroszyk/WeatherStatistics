#pragma once

#include <fstream>
#include <sstream>
#include <map>
#include <ctime>

#include "Statistics.hpp"

#define RESOURCE_PATH "../resources/" // path to files

class WeatherStatistics : public Statistics
{
public:
    WeatherStatistics();
	bool isValidDateTime(std::string date, std::string time) override;
	double computeCoeff(std::string startDate, std::string startTime,
	                    std::string endDate, std::string endTime) override;

private: 
	std::map<time_t, double> timeToPressure_;

	void loadData();
	time_t getFirstDateTime();
	time_t getLastDateTime();
	time_t convertDateTime(std::string date, std::string time);
};