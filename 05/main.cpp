#include <iostream>
#include <string>

using std::string;

struct Entry {
	string name;
	int value;
};

Entry read_entry(std::istream &is) // naive read function (for a better version, see §10.5)
{
	string s;
	int i;
	is >> s >> i;
	return {s, i};
}

int main()
{
	// auto e = read_entry(std::cin);
	// std::cout << "{ " << e.name << " , " << e.value << " }\n";
	auto [name, value] = read_entry(std::cin); // using structured binding
	std::cout << "{ " << name << " , " << value << " }\n";
}
