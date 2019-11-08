#include "keys_generator.h"
#include "tables.h"
#include <iostream>

using namespace std;

// Function to do a circular left shift by 1
std::string KeysGenerator::_shift_left_once(std::string key_chunk){ 
	std::string shifted="";  
	for(int i = 1; i < 28; i++){ 
		shifted += key_chunk[i]; 
	} 
	shifted += key_chunk[0];   
	return shifted; 
}

// Function to do a circular left shift by 2
std::string KeysGenerator::_shift_left_twice(std::string key_chunk){ 
	std::string shifted=""; 
	for(int i = 0; i < 2; i++){ 
		for(int j = 1; j < 28; j++){ 
			shifted += key_chunk[j]; 
		} 
		shifted += key_chunk[0]; 
		key_chunk= shifted; 
		shifted =""; 
	} 
	return key_chunk; 
}

std::vector<std::string> KeysGenerator::generate_keys(string key){
	std::vector<std::string> round_keys(keys_count);

	// 1. Compressing the key using the PC1 table
	string perm_key =""; 
	for(int i = 0; i < key_length; i++){ 
		perm_key+= key[pc1[i]-1]; 
	} 
	// 2. Dividing the result into two equal halves
	string left= perm_key.substr(0, key_length/2); 
	string right= perm_key.substr(key_length/2, 28); 

	size_t keys_to_shift_1[4] = { 0, 1, 8, 15};

	for(int i=0; i<keys_count; i++){ 
		if( find(begin(keys_to_shift_1), end(keys_to_shift_1), i) != end(keys_to_shift_1) ){
			left= _shift_left_once(left); 
			right= _shift_left_once(right);
		} 
		else{
			left= _shift_left_twice(left); 
			right= _shift_left_twice(right);
		}

		string combined_key = left + right;
		string round_key = ""; 
		// 5. Finally, the PC2 table is used to transpose
		// the key bits
		for(int j = 0; j < 48; j++){ 
			round_key += combined_key[pc2[j]-1]; 
		}   
		round_keys[i] = round_key;
	cout<<"Key "<<i+1<<": "<<round_keys[i]<<endl; 
	} 

	return round_keys;
}
