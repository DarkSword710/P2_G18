#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <windows.h>
#include <iostream>

void Help() {

	std::cout << "------------------" << std::endl <<
		"FULLENTI ALCHEMIST" << std::endl <<
		"------------------" << std::endl <<
		"- Enter two numbers of your elements list to combine them." << std::endl <<
		"- Enter the word 'add' and the number of an element to add a new instance of that element." << std::endl <<
		"- Enter 'add basics' to add new instances of the 4 basic elements." << std::endl <<
		"- Enter the word 'delete and the number of an element to erase it from your list." << std::endl <<
		"- Enter the word 'info' and the number of an element to get information about it in the explorer." << std::endl <<
		"- Enter the word 'sort' to sort by alphabetical order the elements in the list." << std::endl <<
		"- Enter the word 'clean' to delete all the instances of repeated elements." << std::endl <<
		"- Enter the word 'help' to show this tutorial." << std::endl << std::endl;
}

int main() {

	//Abrir el archivo con las combinaciones
	std::ifstream elementData("elements.dat");

	//Leerlo y guardarlo en un mapa
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
		//Falta implementar comprobación con system("pause) si algo va mal
		allElements.insert({ key, element });

	}

	elementData.close();

	std::vector<std::string>basics({ "Air", "Earth", "Fire", "Water" });
	std::vector<std::string>inventory(basics);
	std::unordered_set<std::string>found (basics.begin(), basics.end());
	std::set<std::string>cleaner;
	int score = 0;
	std::string instruction;
	std::string subInstruction;
	std::string urlBegin = "https://en.wikipedia.org/wiki/";
	std::string url;
	std::string keyFound;
	int aux;
	int aux2;
	bool helpNeeded = true;
	bool elementCombination;
	bool newElement = false;
	bool combinationFailure = false;

	while (true)
	{
		//EN LA PRIMERA ITERACIÓN O SI EL JUGADOR NECESITA AYUDA IMPRIME LOS COMANDOS BÁSICOS JUNTO CON LA PANTALLA DE TÍTULO
		if (helpNeeded) {
			Help();
			helpNeeded = false;
		}
		if (newElement) {
			std::cout << "New element found: " << allElements[keyFound] << std::endl << std::endl;
			newElement = false;
		}
		if (combinationFailure) {
			std::cout << "Combination failure, try again!" << std::endl << std::endl;
			combinationFailure = false;
		}
		//IMPRIME LOS DATOS ACTUALES DEL JUEGO
		std::cout << "Your current score: " << score << std::endl <<
			"You have these elements:" << std::endl;

		for (int i = 0; i < inventory.size(); i++) {
			std::cout << i + 1 << ": " << inventory[i] << std::endl;
		}
		
		//RECIBE UNA INSTRUCCION DEL JUGADOR
		std::cin >> instruction;
		if (instruction == "sort") {
			std::sort(inventory.begin(), inventory.end());
		}
		else if (instruction == "help") {
			//EL JUGADOR NECESITA AYUDA
			helpNeeded = true;
		}
		else if (instruction == "clean") {
			for (int i = 0; i < inventory.size(); i++) {
				cleaner.insert(inventory[i]);
			}
			inventory.clear();
			for (auto it = cleaner.begin(); it != cleaner.end(); it++) {
				inventory.push_back(*it);
			}
			cleaner.clear();
		}
		else {
			std::cin >> subInstruction;
			if (instruction == "add") {
				if (subInstruction == "basics") {
					for (int i = 0; i < basics.size(); i++) {
						inventory.push_back(basics[i]);
					}
				}
				else {
					aux = atoi(subInstruction.c_str()) - 1;
					inventory.push_back(inventory[aux]);
				}
			}
			else {
				aux = atoi(subInstruction.c_str()) - 1;
				if (instruction == "delete") {

					inventory.erase(inventory.begin() + aux);

				}
				else if (instruction == "info") {

					url = urlBegin + inventory[aux];
					ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);

				}
				else {

					aux2 = atoi(instruction.c_str()) - 1;
					if (allElements.find(inventory[aux] + " + " + inventory[aux2]) != allElements.end()) {
						keyFound = inventory[aux] + " + " + inventory[aux2];
						elementCombination = true;
					}
					else if (allElements.find(inventory[aux2] + " + " + inventory[aux]) != allElements.end()) {
						keyFound = inventory[aux2] + " + " + inventory[aux];
						elementCombination = true;
					}
					else {
						combinationFailure = true;
						elementCombination = false;
					}
					if (elementCombination) {
						if (found.find(allElements[keyFound]) == found.end()) {
							score++;
							found.insert(allElements[keyFound]);
							newElement = true;
						}
						else {
							newElement = false;
						}

						inventory.push_back(allElements[keyFound]);

					}
					if (aux2 < aux) {
						inventory.erase(inventory.begin() + aux);
						inventory.erase(inventory.begin() + aux2);
					}
					else {
						inventory.erase(inventory.begin() + aux2);
						inventory.erase(inventory.begin() + aux);
					}
				}
			}
		}

		system("cls");
		std::cin.clear(); // clears all error state flags
		// extracts characters from the input buffer and discards them
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		
	}

	return 0;
}