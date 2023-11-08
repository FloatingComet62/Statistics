#include "Statstics.h"

#include <iostream>
#include <algorithm>

static float mod(float x) {
	if (x >= 0) {
		return x;
	}
	return -x;
}

#pragma region UnGrouped Statistics

UnGroupedStatistics::UnGroupedStatistics(std::vector<float> data) {
	this->data = data;
}

float UnGroupedStatistics::getMean() {
	if (this->isMeanCalculated) {
		return this->mean;
	}

	float total = 0;
	for (const float& item : this->data) {
		total += item;
	}
	this->mean = total / data.size();

	this->isMeanCalculated = true;
	return this->mean;
}

float UnGroupedStatistics::getMedian() {
	if (this->isMedianCalculated) {
		return this->median;
	}

	std::sort(this->data.begin(), this->data.end());
	float median;
	if (this->data.size() % 2) {
		median = this->data.at(this->data.size() / 2);
	}
	else {
		int medianIndex = this->data.size() / 2;
		float median_1 = this->data.at(medianIndex);
		float median_2 = this->data.at(static_cast<std::vector<float, std::allocator<float>>::size_type>(medianIndex) - 1);

		median = (median_1 + median_2) / 2;
	}
	this->median = median;

	this->isMedianCalculated = true;
	return this->median;
}

float UnGroupedStatistics::getMode() {
	if (this->isModeCalculated) {
		return this->mode;
	}

	int prev = this->data.back();
	int mode = this->data.at(0);
	int maxcount = 0;
	int currcount = 0;
	for (const float& n : this->data) {
		if (n == prev) {
			++currcount;
			if (currcount > maxcount) {
				maxcount = currcount;
				mode = n;
			}
		}
		else {
			currcount = 1;
		}
		prev = n;
	}
	this->mode = mode;

	this->isModeCalculated = true;
	return this->mode;
}

float UnGroupedStatistics::getMeanDeviation() {
	if (this->isMeanDeviationCalculated) {
		return this->meanDeviation;
	}

	auto mean = this->getMean();
	auto meanDeviation = 0;
	for (const float& item : this->data) {
		meanDeviation += mod(item - mean);
	}
	this->meanDeviation = meanDeviation / this->data.size();

	this->isMeanDeviationCalculated = true;
	return this->meanDeviation;
}

float UnGroupedStatistics::getStandardDeviation() {
	if (this->isStandardDeviationCalculated) {
		return this->standardDeviation;
	}

	auto variance = this->getVariance();
	this->standardDeviation = std::sqrtf(variance);

	this->isStandardDeviationCalculated = true;
	return this->standardDeviation;
}

float UnGroupedStatistics::getVariance() {
	if (this->isVarianceCalculated) {
		return this->variance;
	}

	auto mean = this->getMean();
	auto variance = 0;
	for (const float& item : this->data) {
		auto binding = item - mean;
		variance += binding * binding;
	}
	this->variance = variance / this->data.size();

	this->isVarianceCalculated = true;
	return this->variance;
}

float UnGroupedStatistics::getCoeffOfRange() {
	if (this->isCoeffOfRangeCalculated) {
		return this->coeffOfRange;
	}

	auto min = data.at(0);
	auto max = data.at(0);
	for (const float& item : this->data) {
		if (item > max) {
			max = item;
		}
		if (item < min) {
			min = item;
		}
	}
	auto numerator = max - min;
	auto denominator = max + min;
	this->coeffOfRange = numerator / denominator;

	this->isCoeffOfRangeCalculated = true;
	return this->coeffOfRange;
}

float UnGroupedStatistics::getCoeffOfStandardDeviation() {
	if (this->isCoeffOfStandardDeviationCalculated) {
		return this->coeffofStandardDeviation;
	}

	auto standardDeviation = this->getStandardDeviation();
	auto mean = this->getMean();
	this->coeffofStandardDeviation = standardDeviation / mean;

	this->isCoeffOfStandardDeviationCalculated = true;
	return this->coeffofStandardDeviation;
}

float UnGroupedStatistics::getCoeffOfVariation() {
	if (this->isCoeffOfVariationCalculated) {
		return this->coeffOfVariation;
	}

	auto coeffOfStandardDeviation = this->getCoeffOfStandardDeviation();
	this->coeffOfVariation = coeffOfStandardDeviation * 100;

	this->isCoeffOfVariationCalculated = true;
	return this->coeffOfVariation;
}

#pragma endregion

#pragma region Grouped Statistics Builder

GroupedStatisticsBuilder::GroupedStatisticsBuilder() {}

GroupedStatisticsBuilder* GroupedStatisticsBuilder::addItem(float group, float frequency) {
	this->data.insert(std::make_pair(group, frequency));
	return this;
}

groupedData GroupedStatisticsBuilder::build() {
	return this->data;
}

#pragma endregion

#pragma region Grouped Statistics

GroupedStatistics::GroupedStatistics(groupedData data) {
	this->data = data;
}
float GroupedStatistics::getMean() {
	if (this->isMeanCalculated) {
		return this->mean;
	}

	float total = 0;
	float n = 0;
	for (const auto& x : this->data) {
		total += x.first * x.second;
		n += x.second;
	}
	this->mean = total / n;

	this->isMeanCalculated = true;
	return this->mean;
}
float GroupedStatistics::getMedian() {
	if (this->isMedianCalculated) {
		return this->median;
	}



	this->isMedianCalculated = true;
	return this->median;
}
float GroupedStatistics::getMode() {
	if (this->isModeCalculated) {
		return this->mode;
	}

	float max = this->data.begin()->second;
	std::vector<std::pair<float, float>> classes;
	classes.reserve(this->data.size());
	for (const auto& x: this->data) {
		classes.push_back(x);
		float val = x.second;
		if (val > max) {
			max = val;
		}
	}
	float modelClass = this->data.begin()->first;
	Node<std::pair<float, float>>* nodeList = createNodeList(classes);
	do {
		if (nodeList == NULL) {
			break;
		}

		if (max == nodeList->data.second) {
			float freqOfModalClass = nodeList->data.second;
			float freqOfPrecdClass = nodeList->previous->data.second;
			float freqOfSucceClass = nodeList->next->data.second;

			float numerator = freqOfModalClass - freqOfPrecdClass;
			float denominator = 2 * freqOfModalClass - freqOfPrecdClass - freqOfSucceClass;
			this->mode = nodeList->data.first + numerator / denominator;
			break;
		}
	} while (nodeList = nodeList->next);

	this->isModeCalculated = true;
	return this->mode;
}
float GroupedStatistics::getMeanDeviation() {
	if (this->isMeanDeviationCalculated) {
		return this->meanDeviation;
	}

	float total = 0;
	float n = 0;
	for (const auto& x : this->data) {
		total += x.second * mod(x.first - this->getMean());
		n += x.second;
	}
	this->meanDeviation = total / n;

	this->isMeanDeviationCalculated = true;
	return this->meanDeviation;
}
float GroupedStatistics::getStandardDeviation() {
	if (this->isStandardDeviationCalculated) {
		return this->standardDeviation;
	}

	auto variance = this->getVariance();
	this->standardDeviation = std::sqrtf(variance);

	this->isStandardDeviationCalculated = true;
	return this->standardDeviation;
}
float GroupedStatistics::getVariance() {
	if (this->isVarianceCalculated) {
		return this->variance;
	}

	float total = 0;
	float n = 0;
	for (const auto& x : this->data) {
		auto binding = x.first - this->getMean();
		total += x.second * binding * binding;
		n += x.second;
	}
	this->variance = total / n;

	this->isVarianceCalculated = true;
	return this->variance;
}
float GroupedStatistics::getCoeffOfRange() {
	if (this->isCoeffOfRangeCalculated) {
		return this->coeffOfRange;
	}



	this->isCoeffOfRangeCalculated = true;
	return this->coeffOfRange;
}
float GroupedStatistics::getCoeffOfStandardDeviation() {
	if (this->isCoeffOfStandardDeviationCalculated) {
		return this->coeffofStandardDeviation;
	}



	this->isCoeffOfStandardDeviationCalculated = true;
	return this->coeffofStandardDeviation;
}
float GroupedStatistics::getCoeffOfVariation() {
	if (this->isCoeffOfVariationCalculated) {
		return this->coeffOfVariation;
	}



	this->isCoeffOfVariationCalculated = true;
	return this->coeffOfVariation;
}

#pragma endregion

#pragma region Classified Statistics

#pragma endregion

