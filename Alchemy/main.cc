#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <windows.h>
#include <iostream>

void Help() {
	std::cout << "- Enter two numbers of your elements list to combine them." << std::endl <<
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
	std::unordered_set<std::string>found;
	int score = 0;
	std::string instruction;
	std::string subInstruction;
	std::string urlBegin = "https://en.wikipedia.org/wiki/";
	std::string url;
	int aux;

	std::cout << "------------------" << std::endl <<
		"FULLENTI ALCHEMIST" << std::endl <<
		"------------------" << std::endl;
	Help();

	while (true)
	{
		//IMPRIME LOS DATOS ACTUALES DEL JUEGO
		std::cout << "Your current score: " << score << std::endl <<
			"You have these elements:" << std::endl;

		for (int i = 0; i < inventory.size(); i++) {
			std::cout << i + 1 << ": " << inventory[i] << std::endl;
		}
		
		//RECIBE UNA INSTRUCCION DEL JUGADOR
		std::cin >> instruction;
		if (instruction == "sort") {

		}
		else if (instruction == "help") {

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
					aux = atoi(subInstruction.c_str() - 1);
					inventory.push_back(inventory[aux]);
				}
			}
			else {
				aux = atoi(subInstruction.c_str()) - 1;
			}
			if (instruction == "delete") {

				inventory.erase(inventory.begin() + aux);

			}
			else if (instruction == "info") {

				url = urlBegin + inventory[aux];
				ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);

			}
			else {

			}
		}

		std::cin.clear(); // clears all error state flags
		// extracts characters from the input buffer and discards them
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		

	}

	return 0;
}