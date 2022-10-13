#include <iostream>
#include <string>

#include "WeatherStatistics.hpp"


int main() {
	
    WeatherStatistics stats;

    std::string startDate, startTime;
	std::cout << std::endl << "Enter START DATE as yyyy_mm_dd: ";
	std::cin >> startDate;
	std::cout << "Enter START TIME as hh:mm:ss (24-hour): ";
	std::cin >> startTime;

    if (!stats.isValidDateTime(startDate, startTime))
    {
        return 1;
    }

    std::string endDate, endTime;
	std::cout << "Enter END DATE as yyyy_mm_dd: ";
	std::cin >> endDate;
	std::cout << "Enter END TIME as hh:mm:ss (24-hour): ";
	std::cin >> endTime;

    if (!stats.isValidDateTime(endDate, endTime))
    {
        return 1;
    }

	double coeff = stats.computeCoeff(startDate, startTime, 
                                      endDate, endTime);

    std::cout << std::endl << "Coefficient: " << coeff * 24 * 60 * 60 << " inHg/day" << std::endl;

    if (coeff < 0)
    {
        std::cout << "Stormy conditions... Looks like you might need an umbrella!" << std::endl;
    }
    else
    {
        std::cout << "Sunny conditions... Don't forget your sunscreen!" << std::endl;
    }

    return 0;
}