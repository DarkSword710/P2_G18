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

//Función que imprime la intro y los comandos disponibles al jugador
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

	//Coge una linea del archivo con las combinaciones
	while (getline(elementData, linea)) {
		//Find, substring
		igual = linea.find(" = ", 0); //Busca el igual
		if (igual == linea.npos) { //Si en la linea no encuentra un " = "
			system("pause");
		}
		element = linea.substr(0, igual); //Toma como elemento lo que hay antes
		key = linea.substr(igual + 3); //Toma como clave la suma de los dos elementos que lo componen, que esta depsués
		allElements.insert({ key, element }); //Los inserta en el unordered_map

	}

	elementData.close();

	//Vector con los elementos básicos
	std::vector<std::string>basics({ "Air", "Earth", "Fire", "Water" });

	//Vector inventario
	std::vector<std::string>inventory(basics);

	//Unordered_set de elementos encontrados por el jugador
	std::unordered_set<std::string>found (basics.begin(), basics.end());

	//Set auxiliar para el comando 'clean'
	std::set<std::string>cleaner;

	//Puntuación
	int score = 0;

	//Instrucciones enviadas por el jugador
	std::string instruction;
	std::string subInstruction;

	//String de la url básica de wikipedia
	std::string urlBegin = "https://en.wikipedia.org/wiki/";

	//String de la url
	std::string url;

	//String de la clave encontrada del elemento combinado
	std::string keyFound;

	//Valores introducidos por el jugador
	int aux;
	int aux2;

	//Comprobaciones de lo que ocurre en la acción
	bool helpNeeded = true;
	bool elementCombination;
	bool newElement = false;
	bool combinationFailure = false;

	do
	{
		//En la primera iteración o si el jugador usa 'help'
		if (helpNeeded) {
			Help();
			helpNeeded = false;
		}
		//Si se descubre un nuevo elemento
		if (newElement) {
			std::cout << "New element found: " << allElements[keyFound] << std::endl << std::endl;
			newElement = false;
		}
		//Si hay fallo al combinar
		if (combinationFailure) {
			std::cout << "Combination failure, try again!" << std::endl << std::endl;
			combinationFailure = false;
		}
		//Imprime puntuación e inventario
		std::cout << "Your current score: " << score << std::endl <<
			"You have these elements:" << std::endl;

		for (int i = 0; i < inventory.size(); i++) {
			std::cout << i + 1 << ": " << inventory[i] << std::endl;
		}
		
		//Recibe instruccion
		std::cin >> instruction;

		//Comprueba si es de las de una sola palabra
		if (instruction == "sort") {
			//Ordena el inventario
			std::sort(inventory.begin(), inventory.end());
		}
		else if (instruction == "help") {
			//Establece que el jugador lo ha usado para la siguiente impresión
			helpNeeded = true;
		}
		else if (instruction == "clean") {
			//Transfiere el inventario a el set auxiliar
			for (int i = 0; i < inventory.size(); i++) {
				cleaner.insert(inventory[i]);
			}
			//Limpia el inventario
			inventory.clear();

			//Inserta el set auxiliar en el inventario vacío
			for (auto it = cleaner.begin(); it != cleaner.end(); it++) {
				inventory.push_back(*it);
			}
			//Limpia el set auxiliar
			cleaner.clear();
		}
		//Si la instrucción tiene dos palabras
		else {
			//Recibe la segunda
			std::cin >> subInstruction;
			if (instruction == "add") {

				if (subInstruction == "basics") {

					//Añade el vector de basicos al inventario
					for (int i = 0; i < basics.size(); i++) {
						inventory.push_back(basics[i]);
					}

				}
				else {

					//Transforma la segunda instruccion en int
					aux = atoi(subInstruction.c_str()) - 1;

					//Añade al inventario el elemento que el usuario indica
					inventory.push_back(inventory[aux]);
				}
			}
			//Si no es add, en el resto la segunda palabra es un numero, por lo que la convertimos ya
			else {
				aux = atoi(subInstruction.c_str()) - 1;
				if (instruction == "delete") {

					//Borra el elemento que el usuario indica
					inventory.erase(inventory.begin() + aux);

				}
				else if (instruction == "info") {

					//Combina la url básica de Wikipedia con el string del elemento
					url = urlBegin + inventory[aux];

					//Abre la página en el navegador
					ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);

				}
				//Si no es ninguna de estas, el usuario intenta combinar dos elementos, por lo que la primera instruccioçón también es un int
				else {

					aux2 = atoi(instruction.c_str()) - 1;

					//Busca si existe en el mapa de los elementos uno que se forme combinando los dos que el usuario indica
					if (allElements.find(inventory[aux] + " + " + inventory[aux2]) != allElements.end()) {
						keyFound = inventory[aux] + " + " + inventory[aux2];
						elementCombination = true;
					}
					else if (allElements.find(inventory[aux2] + " + " + inventory[aux]) != allElements.end()) {
						keyFound = inventory[aux2] + " + " + inventory[aux];
						elementCombination = true;
					}
					//Si no es así, la combinación fracasa, si no, se guarda el string de los elementos combinados
					else {
						combinationFailure = true;
						elementCombination = false;
					}
					//Si la combinación es un éxito se busca si el elemento ha sido encontrado antes por el jugador
					if (elementCombination) {
						//Si es así se añade un punto y se inserta en el unordered_set, además de activar el mensaje en la siguiente impresión
						if (found.find(allElements[keyFound]) == found.end()) {
							score++;
							found.insert(allElements[keyFound]);
							newElement = true;
						}
						//Se añade al inventario el nuevo elemento
						inventory.push_back(allElements[keyFound]);

					}
					//Se realiza una comprobación del orden en el que los elementos deben ser borrados para que no borre fuera de los límites del vector y se borran
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
		//Se borra la pantalla para la siguiente iteración
		system("cls");
		std::cin.clear(); // clears all error state flags
		// extracts characters from the input buffer and discards them
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		
	} while (true);
	return 0;
}