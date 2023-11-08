#pragma once

#include "Data.h"
#include <unordered_map>

class Statistics {
	virtual float getMean() = 0;
	virtual float getMedian() = 0;
	virtual float getMode() = 0;
	virtual float getMeanDeviation() = 0;
	virtual float getStandardDeviation() = 0;
	virtual float getVariance() = 0;
};

class UnGroupedStatistics : Statistics {
	std::vector<float> data;
	bool isMeanCalculated;
	bool isMedianCalculated;
	bool isModeCalculated;
	bool isMeanDeviationCalculated;
	bool isStandardDeviationCalculated;
	bool isVarianceCalculated;
	bool isCoeffOfRangeCalculated;
	bool isCoeffOfStandardDeviationCalculated;
	bool isCoeffOfVariationCalculated;
	float mean;
	float median;
	float mode;
	float meanDeviation;
	float standardDeviation;
	float variance;
	float coeffOfRange;
	float coeffofStandardDeviation;
	float coeffOfVariation;
public:
	UnGroupedStatistics(std::vector<float> data);
	float getMean();
	float getMedian();
	float getMode();
	float getMeanDeviation();
	float getStandardDeviation();
	float getVariance();
	float getCoeffOfRange();
	float getCoeffOfStandardDeviation();
	float getCoeffOfVariation();
};

using groupedData = std::unordered_map<float, float>;

class GroupedStatisticsBuilder {
	groupedData data;
public:
	GroupedStatisticsBuilder();
	GroupedStatisticsBuilder* addItem(float group, float frequency);
	groupedData build();
};

class GroupedStatistics : Statistics {
	groupedData data;
	bool isMeanCalculated;
	bool isMedianCalculated;
	bool isModeCalculated;
	bool isMeanDeviationCalculated;
	bool isStandardDeviationCalculated;
	bool isVarianceCalculated;
	bool isCoeffOfRangeCalculated;
	bool isCoeffOfStandardDeviationCalculated;
	bool isCoeffOfVariationCalculated;
	float mean;
	float median;
	float mode;
	float meanDeviation;
	float standardDeviation;
	float variance;
	float coeffOfRange;
	float coeffofStandardDeviation;
	float coeffOfVariation;
public:
	GroupedStatistics(groupedData data);
	float getMean();
	float getMedian();
	float getMode();
	float getMeanDeviation();
	float getStandardDeviation();
	float getVariance();
	float getCoeffOfRange();
	float getCoeffOfStandardDeviation();
	float getCoeffOfVariation();
};

/*
using classifiedData = std::unordered_map<std::pair<float, float>, float>;
class ClassifiedStatistics : Statistics {
	classifiedData data;
	bool isMeanCalculated;
	bool isMedianCalculated;
	bool isModeCalculated;
	bool isMeanDeviationCalculated;
	bool isStandardDeviationCalculated;
	bool isVarianceCalculated;
	bool isCoeffOfRangeCalculated;
	bool isCoeffOfStandardDeviationCalculated;
	bool isCoeffOfVariationCalculated;
	float mean;
	float median;
	float mode;
	float meanDeviation;
	float standardDeviation;
	float variance;
	float coeffOfRange;
	float coeffofStandardDeviation;
	float coeffOfVariation;
public:
	ClassifiedStatistics(classifiedData data);
	float getMean();
	float getMedian();
	float getMode();
	float getMeanDeviation();
	float getStandardDeviation();
	float getVariance();
	float getCoeffOfRange();
	float getCoeffOfStandardDeviation();
	float getCoeffOfVariation();
};
*/
