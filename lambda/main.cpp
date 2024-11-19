#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using std::literals::string_literals::operator"" s;
void f(const std::vector<int> &vec, const std::list<std::string> &lst, int x, const std::string &s)
{
	std::cout << "number of values less than " << x << ": "
			  << std::count_if(vec.begin(), vec.end(), [&](int a) { return a < x; }) << '\n';
	std::cout << "number of values less than " << s << ": "
			  << std::count_if(lst.begin(), lst.end(), [&](const std::string &a) { return a < s; }) << '\n';
}


int main()
{
    f(std::vector{1, 2, 3}, std::list{"abc"s, "def"s, "tuv"s}, 2, "test"s);
}
