#include "Types.h"

#include <fstream>
#include <iostream>

int* LoadFile(const char *name, int &n) {
	std::ifstream file(name);
	if (!file.good())
		return nullptr;

	file >> n;

	int *values = new int[n];
	for (int i = 0; i < n; i++)
		file >> values[i];

	return values;
}
bool WriteFile(const char *name, int *values, int n) {
	std::ofstream file(name);
	if (!file.good())
		return false;

	file << n << '\n';
	for (int i = 0; i < n; i++)
		file << values[i] << ' ';

	return true;
}

int main(int argc, char **argv) {
	std::cout << "Hello computer.";
	return 0;
}