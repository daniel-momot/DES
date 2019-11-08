#pragma once

#include <string>
#include <vector>

class KeysGenerator {
private:

	// Function to do a circular left shift by 1
	static std::string _shift_left_once(std::string key_chunk);

	// Function to do a circular left shift by 2
	static std::string _shift_left_twice(std::string key_chunk);

public:
	static const size_t keys_count = 16;
	static const size_t key_length = 56; 

	static std::vector<std::string> generate_keys(std::string key);

};

