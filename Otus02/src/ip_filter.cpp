#include <iostream>
#include <string>
#include <sstream>
#include <cstddef> // std::size_t
#include <cstdint> // providing fixed width integer types
#include <vector>
#include <algorithm>
#include <functional>

class ipv4 {
public:
	std::uint32_t address = 0; // contains ipv4 address
    explicit ipv4(const std::string ip_address)
	{
		make_ip(ip_address);
	}
	bool check_valid() { return valid; }

	friend    std::ostream& operator<<(std::ostream& os, const ipv4& ip)
    	{
        	// shift left bits and left only first significant byte
        	std::uint32_t part1 = (ip.address >> 24) & 0xFF;
        	std::uint32_t part2 = (ip.address >> 16) & 0xFF;
        	std::uint32_t part3 = (ip.address >> 8) & 0xFF;
        	std::uint32_t part4 = ip.address & 0xFF;
        	os << part1 << '.' << part2 << '.' << part3 << '.' << part4;
		return os;
	}
	friend bool operator<(const ipv4& a, const ipv4& b)
	{
		return	a.address < b.address;
	}
    friend bool operator>(const ipv4& a, const ipv4& b)
    {
        return !(a < b);
    }
private:
	bool valid = false; // valid ip adress: consists of 4 parts

	void make_ip(std::string source)
	{
		std::istringstream ss(source);
		std::string digit;
		std::uint32_t counter = 0;
		address = 0;
		while (std::getline(ss, digit, '.'))
		{
			std::uint32_t current_part;
			std::stringstream css(digit);
			if((css >> current_part) && (current_part >= 0 && current_part <= 255)) // if operation not fails and [0;255]
			{
				address = (address << 8) | current_part;
				++counter;
			}
		}
		if (counter == 4)
			valid = true;
	}
};

int main()
{
	std::vector<ipv4> ipv4_vector; // a vector contains our ipv4 addresses

	// preprocessing input
	for (std::string line; std::getline(std::cin, line);)
	{
		//remove useless information
		std::size_t found = line.find_first_of("\t");

		if (found == std::string::npos) // if \t not found terminate program
			return 0;

		line.erase(found);

		// construct ipv4 from this string
		ipv4 curr_ipv4{ line };

		// pushing ipv4 to the vector
		if (curr_ipv4.check_valid())
		{
			ipv4_vector.push_back(curr_ipv4);
		}
	}

	std::sort(ipv4_vector.begin(), ipv4_vector.end(), [](ipv4 a, ipv4 b){ return a > b; }); // sorting in decreasing order

	// print all sorted elements
	for (auto cur_ip : ipv4_vector)
	{
		std::cout << cur_ip << std::endl;
	}

	// elements are already sorted so just check other conditions

	// print elements where first byte is equal 1
	for (auto cur_ip : ipv4_vector)
	{
		if ((cur_ip.address >> 24) == 1)
			std::cout << cur_ip << std::endl;
	}

	// print elements where first byte is equal 46 & second byte is equal 70
	for (auto cur_ip : ipv4_vector)
	{
		if ((cur_ip.address >> 24) == 46 && ((cur_ip.address >> 16) & 0xFF) == 70)
			std::cout << cur_ip << std::endl;
	}
	// print elements where any of bytes are equal 46
	for (auto cur_ip : ipv4_vector)
	{
		if ((cur_ip.address & 0xFF) == 46 ||
            ((cur_ip.address >> 8) & 0xFF) == 46 ||
            ((cur_ip.address >> 16) & 0xFF) == 46 ||
            ((cur_ip.address >> 24) & 0xFF) == 46
           )
		    std::cout << cur_ip << std::endl;
	}
}
