#pragma once

#include <string>

class Statistics
{
public:
    virtual bool isValidDateTime(std::string date, std::string time) = 0;
	virtual double computeCoeff(std::string startDate, std::string startTime,
	                    std::string endDate, std::string endTime) = 0;
};