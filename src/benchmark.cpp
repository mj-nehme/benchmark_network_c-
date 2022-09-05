#include <sys/time.h>
#include <iostream>
#include <string>

#ifndef __CONFIG_H__
#define __CONFIG_H__
#include "config.h"
#endif

double Kilo = 1000;
double Mega = 1000 * Kilo;
double Giga = 1000 * Mega;
double Tera = 1000 * Giga;
double Peta = 1000 * Tera;

std::string getMetric(double size)
{

    if (size >= Peta)

        return std::to_string(size / Peta) + "P";

    else if (size >= Tera)

        return std::to_string(size / Tera) + "T";

    else if (size >= Giga)

        return std::to_string(size / Giga) + "G";

    else if (size >= Mega)

        return std::to_string(size / Mega) + "M";

    else if (size >= Kilo)

        return std::to_string(size / Kilo) + "K";

    else

        return std::to_string(size);
}

std::string getThroughputString(double Throughput)
{

    return getMetric(Throughput) + "b/s";
}

std::string getDataAmount(double dataAmount)
{

    return getMetric(dataAmount) + "B";
}

void calculateThroughput(struct timeval startTime, struct timeval endTime)
{

    double data = MessageSize * NbMessages;
    if (verbose)
        std::cout << "Transmitted Data: " << getDataAmount(data) << std::endl;
    double elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1'000'000 + (endTime.tv_usec - startTime.tv_usec);
    if (verbose)
        std::cout << "Elapsed time: " << elapsedTime << " usecs" << std::endl;

    double throughput = (data *8 / elapsedTime) *1'000'000 ;
    std::cout << "Throughput: " << getThroughputString(throughput) << std::endl;
}
