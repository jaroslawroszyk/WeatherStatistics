#include "WeatherStatistics.hpp"

#include <iostream>

WeatherStatistics::WeatherStatistics()
{
    loadData();
}

bool WeatherStatistics::isValidDateTime(std::string date, std::string time)
{
    time_t dateTime = convertDateTime(date, time);

    if (dateTime < 0)
    {
        return false; // failure to parse date/time
    }

    if ((dateTime < getFirstDateTime()) || (dateTime > getLastDateTime()))
    {
        std::cerr << "ERROR: " << date << " " << time << " is outside available data range" << std::endl;
        return false;
    }

    return true;
}

double WeatherStatistics::computeCoeff(std::string startDate, std::string startTime,
                                       std::string endDate, std::string endTime)
{
    time_t startDateTime = convertDateTime(startDate, startTime);
    time_t endDateTime = convertDateTime(endDate, endTime);

    if (endDateTime < startDateTime)
    {
        std::cerr << "ERROR: The start date/time must occur before the end date/time" << std::endl;
        exit(1);
    }

    std::map<time_t, double>::iterator startTimePressure;
    std::map<time_t, double>::iterator endTimePressure;
    startTimePressure = timeToPressure_.lower_bound(startDateTime);
    endTimePressure = timeToPressure_.lower_bound(endDateTime);

    double timeDiff = static_cast<double>(endTimePressure->first - startTimePressure->first);
    double pressureDiff = endTimePressure->second - startTimePressure->second;

    return (pressureDiff) / (timeDiff);
}

void WeatherStatistics::loadData()
{
    for (int year = 2012; year <= 2015; year++)
    {
        std::ostringstream fileNameStream;
        fileNameStream << RESOURCE_PATH << "Environmental_Data_Deep_Moor_" << year << ".txt";
        std::string fileName = fileNameStream.str();
        std::cout << "Loading " << fileName << std::endl;

        std::fstream dataFileStream;
        dataFileStream.open(fileName);

        std::string line;
        getline(dataFileStream, line);
        while (getline(dataFileStream, line))
        {
            std::string date, time;
            double Air_Temp, Barometric_Press, Dew_Point, Relative_Humidity, Wind_Dir, Wind_Gust, Wind_Speed;
            std::istringstream buffer(line);

            buffer >> date >> time >> Air_Temp >> Barometric_Press >> Dew_Point >> Relative_Humidity >> Wind_Dir >> Wind_Gust >> Wind_Speed;
            time_t dateTime = convertDateTime(date, time);
            timeToPressure_[dateTime] = Barometric_Press;
        }

        dataFileStream.close();
    }
}

time_t WeatherStatistics::getFirstDateTime()
{
    return timeToPressure_.begin()->first;
}

time_t WeatherStatistics::getLastDateTime()
{
    return timeToPressure_.rbegin()->first;
}

time_t WeatherStatistics::convertDateTime(std::string date, std::string time)
{
    int yyyy, mon, dd = 0;
    if (sscanf(date.c_str(), "%d_%d_%d", &yyyy, &mon, &dd) != 3)
    {
        std::cerr << "ERROR: Failed to parse date std::string " << date << std::endl;
        return -1;
    }

    int hh, mm, ss = 0;
    if (sscanf(time.c_str(), "%d:%d:%d", &hh, &mm, &ss) != 3)
    {
        std::cerr << "ERROR: Failed to parse time std::string " << date << std::endl;
        return -2;
    }

    struct tm dateTime = {};
    dateTime.tm_year = yyyy - 1900; // years since 1900
    dateTime.tm_mon = mon - 1;      // months since January
    dateTime.tm_mday = dd;          // day of the month
    dateTime.tm_hour = hh;          // hours since midnight
    dateTime.tm_min = mm;           // minutes after the hour
    dateTime.tm_sec = ss;           // seconds after the minute

    return mktime(&dateTime);
}