// utils
#include <cassert>
#include <chrono>
// data structures
#include <array>
#include <string>
#include <vector>
// io
#include <format>
#include <fstream>
#include <ios>
#include <iostream>
#include <spanstream>
#include <syncstream>
// file systems
#include <filesystem>

using std::array;
using std::vector;

using std::string, std::stringstream, std::istringstream, std::ostringstream;

using std::cin, std::cout, std::cerr;
using std::format, std::vformat, std::make_format_args, std::format_to;
using std::fstream, std::ifstream, std::ofstream;
using std::istream, std::ostream;
using std::osyncstream;
using std::spanstream, std::ispanstream, std::ospanstream;

using std::filesystem::directory_iterator, std::filesystem::directory_entry;
using std::filesystem::is_directory, std::filesystem::is_regular_file;
using std::filesystem::path, std::filesystem::filesystem_error;

void h(int i)
{
	cout << "the value of i is ";
	cout << i;
	cout << '\n';
}


void h2(int i)
{
	cout << "the value of i is " << i << '\n';
}


void hello()
{
	cout << "Please enter your name\n";
	string str;
	cin >> str;
	cout << "Hello, " << str << "!\n";
}

void hello()
{
	cout << "Please enter your fullname\n";
	string str;
	std::getline(cin, str);
	cout << "Hello, " << str << "!\n";
}


vector<int> read_ints(istream &is = cin)
{
	vector<int> res;
	for (int i; is >> i;)
		res.push_back(i);
	return res;
}


vector<int> read_ints(istream &is, const string &terminator)
{
	vector<int> res;

	vector<int> res;
	for (int i; is >> i;)
		res.push_back(i);

	if (is.eof()) // fine: end of file
		return res;

	if (is.fail()) { // we failed to read an int; was it the terminator?
		is.clear();  // reset the state to good()
		string s;
		if (is >> s && s == terminator)
			return res;
		is.setstate(std::ios_base::failbit); // add fail() to is's state
	}
	return res;
}


struct Entry {
	string name;
	int number;
};


ostream &operator<<(ostream &os, const Entry &e)
{
	return os << R"({")" << e.name << R"(", )" << e.number << "}";
}


istream &operator>>(istream &is, Entry &e)
// read { "name", number } pair.
{
	char c, c2;
	if (is >> c && c == '{' && is >> c2 && c2 == '"') { // start with a { followed by a "
		string name; // the default value of a string is the empty string: ""

		while (is.get(c) && c != '"')
			name += c;

		if (is >> c && c == ',') { // read the number and a }
			int number = 0;
			if (is >> number >> c && c == '}') {
				e = {name, number}; // assign to the entry
				return is;
			}
		}
	}

	is.setstate(std::ios_base::failbit); // register the failure in the stream
	return is;
}


void test()
{
	ostringstream oss;

	oss << "{temperature," << std::scientific << 123.456789 << "}";
	cout << oss.view() << '\n';
}

template <typename Target = string, typename Source = string>
Target to(Source arg) // convert Source to Target
{
	stringstream buf;
	Target result;

	if (!(buf << arg)               // write arg into stream
		|| !(buf >> result)         // read result from stream
		|| !(buf >> std::ws).eof()) // is anything left in stream?
		throw runtime_error{"to<>() failed"};

	return result;
}


template <typename... T> void error(T... args)
{
	cerr "\33[31m" << ... << args << "\33[m" << '\n';
}


void user(int arg)
{
	array<char, 128> buf;
	ospanstream ss(buf);
	ss << "write " << arg << " to memory\n";
	// attempts overflow the target buffer sets the string state to failure.
	// ...
}


/* concurrency */
void unsafe(int x, string &s)
{
	cout << x;
	cout << s;
}
void safer(int x, string &s)
{
	osyncstream oss(cout);
	oss << x;
	oss << s;
}


int f_main(int argc, char *argv[])
{
	if (argc < 2) {
		cerr << "arguments expected\n";
		return 1;
	}

	path p{argv[1]}; // create a path from the command line

	cout << p << " " << exists(p) << '\n'; // note: a path can be printed like a string

	// ...
	return 0;
}


void use_file(path p)
{
	ofstream f{p};

	if (!f)
		error("bad file name: ", p);
	f << "Hello, file!";
}


void print_directory(path p) // print the names of all files in p
try {
	if (is_directory(p)) {
		cout << p << ":\n";
		for (const directory_entry &x : std::filesystem::directory_iterator{p})
			cout << " " << x.path() << '\n';
	}
}
catch (const filesystem_error &ex) {
	cerr << ex.what() << '\n';
}


void use()
{
	print_directory(".");  // current directory
	print_directory(".."); // parent directory
	print_directory("/");  // Unix root directory
	print_directory("c:"); // Windows volume C

	for (string s; cin >> s;)
		print_directory(s);
}


void test(path p)
{
	if (is_directory(p)) {
		cout << p << ":\n";

		for (const directory_entry &x : directory_iterator(p)) {
			const path &f = x; // refer to the path part of a directory entry

			if (f.extension() == ".exe")
				cout << f.stem() << " is a Window Executable\n";
			else {
				string n = f.extension().string();

				if (n == ".cpp" || n == ".c" || n == ".cxx")
					cout << f.stem() << " is a C++ source file\n";
			}
		}
	}
}


int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false); // avoid significant overhead.

	using std::string_literals::operator""s;

	auto v = read_ints(cin, "s");

	Entry e{};
	cout << Entry{"Bjarne"s, 42} << '\n';

	cin >> e;
	cout << e;

	// manipulators
	constexpr double d = 123.456;
	cout << d << "; "                       // use the default format for d
		 << std::scientific << d << "; "    // use 1.123e2 style format for d
		 << std::hexfloat << d << "; "      // use hexadecimal notation for d
		 << std::fixed << d << "; "         // use 123.456 style format for d
		 << std::defaultfloat << d << '\n'; // use the default format for d
	cout.precision(8);
	cout << "precision(8): " << 1234.56789 << ' ' << 123456 << '\n';
	cout.precision(4);
	cout << "precision(4): " << 1234.56789 << ' ' << 123456 << '\n';

	{
		using namespace std::chrono;
		cout << "birthday" << November / 28 / 2021 << '\n';
		cout << "zt: " << zoned_time{current_zone(), system_clock::now()} << '\n';
	}

	auto val = "World!";
	string s = format("Hello, {}\n", val);

	// cout << format("{} {:x} {:o} {:d} {:b}\n", 1234, 1234, 1234, 1234, 1234);
	cout << format("{3:} {1:x} {2:o} {0:b}\n", 000, 111, 222, 333);
	cout << format("{0:} {0:x} {0:o} {0:d} {0:b}\n", 1234);     // default, hex, oct, dec, bin
	cout << format("{0:} {0:e} {0:a} {0:f} {0:g}\n", 1234.456); // def, sci, hex-float, fix, def

	cout << format("precision(8): {0:.8} {0:.4} {0:} {1:}\n", 1234.5678, 1234);

	{
		using namespace std::chrono;
		cout << format("birthday: {}\n", November / 28 / 2021);
		cout << format("\t: {}", zoned_time{current_zone(), system_clock::now()});

		auto ymd = 2021y / March / 30;
		cout << format(
			"ymd: {3:%A}, {1:} {2:%B}, {0:}\n", ymd.year(), ymd.month(), ymd.day(), weekday(ymd));
		// <- Tuesday, March 30, 2021  // datetime format start with %
	}

	string fmt = "{}";
	int arg;
	cout << vformat(fmt, std::make_format_args(arg)); // OK

	// fmt = "{:%F}";
	//  cout << vformat(fmt, make_format_args(arg)); // error: format and argument mismatch; caught
	//  at run time

	string buf;
	int year = 2022;
	format_to(std::back_inserter(buf), "iterator: {} {}\n", "Hi!", year);
	cout << buf;

	ofstream ofs{"target"}; // "o" for output
	if (!ofs)
		error("couldn't open target for writing\n");

	ifstream ifs{"source"}; // "i" for input
	if (!ifs)
		error("couldn't open 'source' for reading\n");

	auto x1 = to<string, double>(1.2); // very explicit (and verbose)
	auto x2 = to<string>(1.2);         // source is deduced to double
	auto x3 = to<>(1.2);               // Target is defaulted to string; Source is deduced to double
	                                   // the <> is redundant
	auto x4 = to(1.2);                 // Target is defaulted to string; Source is deduced to double

	path f = "dir/hypothetical.cpp"; // naming a file

	assert(exists(f)); // f must exist

	if (is_regular_file(f)) // is f an ordinary file?
		cout << f << " is a file; its size is " << file_size(f) << '\n';

	f_main(argc, argv);

	use_file(f);

	print_directory("dir");
}
