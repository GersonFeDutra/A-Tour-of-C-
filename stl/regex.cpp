#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using std::regex;
using std::smatch;
using std::sregex_iterator;
using std::string;


void search(const regex &pat)
{
	int line_n = 0;

	for (string line; std::getline(std::cin, line);) { // read into line buffer
		++line_n;
		smatch matches;                            // matched strings go here
		if (std::regex_search(line, matches, pat)) // search for pat in line
			std::cout << line_n << ": " << matches[0];
	}
}


void use(const char *path, const regex &pat)
{
	std::ifstream in(path);
	if (!in) {
		std::cerr << path << " invalid file\n";
		return;
	}

	int line_n = 0;
	for (string line; std::getline(in, line);) {
		++line_n;
		smatch matches; // matched strings go here
		if (std::regex_search(line, matches, pat)) {
			std::cout << line_n << ": " << matches[0] << '\n'; // the complete match
			if (1 < matches.size() &&                          // if there is a sub-pattern
				matches[1].matched)                            // and if it matched
				std::cout << "\t: " << matches[1] << '\n';     // sub-match
		}
	}
}


bool is_identifier(const string &s)
{
	regex pat{R"([_[:alpha:]]\w*)"}; // underscore or letter
	// followed by zero or more underscores, letters, or digits

	return std::regex_match(s, pat);
}


void test()
{
	string input = "aa as; asd ++e^asdf asdfg";
	//regex pat{R"(\s+(\w+))"}; // words after space
	regex pat{R"((\w+))"}; // all words

	for (sregex_iterator p(input.begin(), input.end(), pat); p != sregex_iterator{}; ++p)
		std::cout << (*p)[1] << '\n';
}


int main(int argc, const char *argv[])
{
	regex pat{R"(\w{2}\s*\d{5}(-\d{4})?)"}; // U. S postal code pattern: XXddddd-dddd and variants
	const char *path = nullptr;

	if (--argc)
		path = *++argv;

	if (path)
		use(path, pat);
	else
		search(pat);
}
