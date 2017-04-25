#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

int main() {

	std::ifstream elementData("elements.dat");

	std::unordered_map<std::string, std::string> allElements;

	std::string linea;
	std::string key;
	std::string element;
	int igual;

	while (getline(elementData, linea)) {
		//Find, substring
		igual = linea.find(" = ", 0);
		element = linea.substr(0, igual);
		key = linea.substr(igual + 3);

		allElements.insert({ key, element });

	}

	elementData.close();

	//Imprimimos usando iteradores
	std::cout << "elements.dat contains:" << std::endl;
	for (auto it = allElements.begin(); it != allElements.end(); ++it)
		std::cout << " " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;

	std::vector<std::string>basics({ "Air", "Earth", "Fire", "Water" });
	std::vector<std::string>inventory(basics);

	return 0;
}