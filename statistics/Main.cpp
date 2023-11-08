#include <iostream>
#include <vector>
#include <unordered_map>

// #include "Data/h"
#include "Statstics.h"

int main() {

	/*std::unordered_map<std::string, std::string> colors = {
		{"RED",   "#FF0000"},
		{"GREEN", "#00FF00"},
		{"BlUE",  "#0000FF"}
	};

	for (const auto& [name, hex] : colors) {
		std::cout << "name: " << name << ", hex: " << hex << "\n";
	}

	return 0;*/
	GroupedStatisticsBuilder builder{};

	builder.addItem(1, 20);
	builder.addItem(3, 37);
	builder.addItem(4, 12);
	builder.addItem(2, 22);

	auto build = builder.build();

	std::cout << build.size() << "\n";

	for (auto& x : build) {
		std::cout << x.first << ": " << x.second << "\n";
	}
}