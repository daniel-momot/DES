#include <iostream>

#include "tables.h"
#include "keys_generator.h"
using namespace std;

// Array to hold the 16 keys
string round_keys[16];


int main(){  
	string key = "10101010101110110000100100011000001001110011"
	"01101100110011011101";
  	KeysGenerator::generate_keys(key);

	system("pause");
} 