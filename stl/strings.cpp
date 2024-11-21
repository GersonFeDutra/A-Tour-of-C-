#include <iostream>
#include <string>

using std::string;
using std::string_view;

string compose(const string &name, const string &domain)
{
	return name + '@' + domain;
}


void m2(string &s1, string &s2)
{
	s1 = s1 + '\n'; // append newline
	s2 += '\n';     // append newline
}


void m3()
{
	string name = "Niels Stroustrup";
	string s = name.substr(6, 10);  // s = "Stroustrup"
	name.replace(0, 5, "nicholas"); // name becomes "nicholas Stroustrup"
	name[0] = toupper(name[0]);
}


string cat(string_view sv1, string_view sv2)
{
	string res{sv1};   // initialize from sv1
	return res += sv2; // append from sv2 and return
}


void print_lower(string_view sv1)
{
	for (char ch : sv1)
		std::cout << tolower(ch);
}

int main(void)
{
	using std::string_literals::operator""s;
	using std::string_view_literals::operator""sv;

	auto addr = compose("dmr", "bell-labs.com");

	string s = "hello", t = "world";
	m2(s, t);

	string king = "Harold";
	auto s1 = cat(king, "William");              // HaroldWilliam: string and const char*
	auto s2 = cat(king, king);                   // HaroldHarold: string and string
	auto s3 = cat("Edward", "Stephen"sv);        // EdwardStephen: const char * and string_view
	auto s4 = cat("Canute"sv, king);             // CanuteHarold
	auto s5 = cat({&king[0], 2}, "Henry"sv);     // HaHenry
	auto s5 = cat({&king[0], 2}, {&king[2], 4}); // Harold

	print_lower("Test"sv);
}
