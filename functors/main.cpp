#include <string>

template <typename T> class Less_than
{
	const T val;
	// value to compare against
public:
	Less_than(const T &v) : val{v}
	{
	}
	bool operator()(const T &x) const
	{
		return x < val;
	} // call operator
};

void fct(int n, const std::string &s)
{
	using std::literals::string_literals::operator"" s;

	Less_than lti{42};        // lti(i) will compare i to 42 using < (i<42)
	Less_than lts{"Backus"s}; // lts(s) will compare s to "Backus" using < (s<"Backus")
	Less_than<std::string> lts2{
		"Naur"}; // "Naur" is a C-style string, so we need <string> to get the right <

	bool b1 = lti(n);
	bool b2 = lts(s);
	// ...
}


int main(void)
{
    fct(2, "test");
}
