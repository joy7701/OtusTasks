#include <iostream>
#include <string>
#include <sstream>
#include <cstddef> // std::size_t
#include <vector>
#include <algorithm>
#include <functional>

class ipv4 {
public:
	ipv4() : valid{false} {} // default constructor
	ipv4(const std::string ip_address) : valid{false}
	{
		split_string(ip_address);
	}
	bool check_valid() { return valid; }
	std::vector<int> data;

private:
	bool valid; // valid ip adress: consists of 4 parts

	void split_string(std::string source)
	{
		std::istringstream ss(source);
		std::string digit;
		int counter = 0;
		while (std::getline(ss, digit, '.'))
		{
			int value;
			std::stringstream css(digit);

			if((css >> value) && (value >= 0 && value <= 255)) // if operation not fails and [0;255]
			{
				counter++;
				data.push_back(value); // load current part of ipv4
			}
		}
		if (counter == 4)
			valid = true;
	}
};

std::ostream& operator<<(std::ostream& os, const ipv4& ip)
{
	os << ip.data[0] << '.' << ip.data[1] << '.' << ip.data[2] << '.' << ip.data[3];
	return os;
}

auto ipv4_less_lambda = [](ipv4 a, ipv4 b) 
{
	if (a.data[0] < b.data[0]) // 1st part "<"
		return true;
	else
	{
		if (a.data[0] > b.data[0])// ">"
			return false;
		else // 2nd part; if current are equal
		{
			if (a.data[1] < b.data[1]) // 2nd part "<"
				return true;
			else
			{
				if (a.data[1] > b.data[1]) // ">"
					return false;
				else // 3nd part; if current are equal
				{
					if (a.data[2] < b.data[2]) // "<"
						return true;
					else
					{
						if (a.data[2] > b.data[2]) // ">"
							return false;
						else
						{
							if (a.data[3] < b.data[3]) // "<"
								return true;
							else
							{
								if (a.data[3] > b.data[3])
									return false;
								else
								{
									return true;
								}
							}
						}
					}
				}
			}
		}
	}
	
	if(a.data[2] < b.data[2]) // 3rd pard
		return true;
	else if (a.data[3] < b.data[3]) // 4th part
		return true;
	else
		return false;
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
	std::sort(ipv4_vector.begin(), ipv4_vector.end(), std::not_fn(ipv4_less_lambda)); // sorting in decreasing order

	// print all sorted elements
	for (auto cur_ip : ipv4_vector)
	{
		std::cout << cur_ip << std::endl;
	}

	// elements are already sorted so just check other conditions
	
	// print elements where first byte is equal 1
	for (auto cur_ip : ipv4_vector)
	{
		if (cur_ip.data[0] == 1)
			std::cout << cur_ip << std::endl;
	}

	// print elements where first byte is equal 46 & second byte is equal 70
	for (auto cur_ip : ipv4_vector)
	{
		if (cur_ip.data[0] == 46 && cur_ip.data[1] == 70)
			std::cout << cur_ip << std::endl;
	}
	// print elements where any of bytes are equal 46
	for (auto cur_ip : ipv4_vector)
	{
		if (cur_ip.data[0] == 46 || cur_ip.data[1] == 46 || cur_ip.data[2] == 46 || cur_ip.data[3] == 46)
			std::cout << cur_ip << std::endl;
	}
}