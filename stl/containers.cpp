// utils
#include <iostream>
#include <memory>
#include <memory_resource>
#include <mutex>
#include <string>
// containers
#include <forward_list>
#include <hash_set>
#include <list>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::forward_list;
using std::list;
using std::map;
using std::unordered_map;
using std::unordered_set;
using std::vector;

struct Entry {
	std::string name;
	int number;
};

std::ostream &operator<<(std::ostream &os, const Entry &e)
{
	os << e.name << ": " << e.number << '\n';
}

std::istream &operator>>(std::istream &is, Entry &e)
{
	enum class State { Start, OpenBrace, Key, Colon, Number, CloseBrace, Done, Error };
	State state = State::Start;

	std::string key;
	std::string number_str;
	char c;

	while (is.get(c)) {
		switch (state) {
			case State::Start:
				if (std::isspace(c))
					continue; // Ignorar espaços iniciais
				if (c == '{')
					state = State::OpenBrace;
				else
					state = State::Error;
				break;

			case State::OpenBrace:
				if (std::isspace(c))
					continue; // Ignorar espaços
				if (c == '"')
					state = State::Key;
				else
					state = State::Error;
				break;

			case State::Key:
				if (c == '"')
					state = State::Colon; // Fim da chave
				else if (std::isprint(c))
					key += c; // Acumula a chave
				else
					state = State::Error;
				break;

			case State::Colon:
				if (std::isspace(c))
					continue; // Ignorar espaços
				if (c == ':')
					state = State::Number;
				else
					state = State::Error;
				break;

			case State::Number:
				if (std::isdigit(c))
					number_str += c; // Acumula o número
				else if (std::isspace(c) || c == '}') {
					if (c == '}')
						state = State::CloseBrace;
					else
						state = State::CloseBrace; // Permitir espaços antes da '}'
				}
				else
					state = State::Error;
				break;

			case State::CloseBrace:
				if (c == '}')
					state = State::Done;
				else
					state = State::Error;
				break;

			case State::Done:
				// Input completamente processado, sair do loop
				break;
			case State::Error:
				// Erro na entrada, marcar stream como inválido
				is.setstate(std::ios::failbit);
				return is;
		}
	}

	if (state == State::Done) {
		e.name = key;
		e.number = std::stoi(number_str);
	}
	else {
		is.setstate(std::ios::failbit);
	}

	return is;
}


void print_book(const vector<Entry> &book)
{
	/*
	for (int i = 0; i != book.size(); ++i)
	    std::cout << book[i] << '\n';
	*/
	/* ranged */
	for (const auto &x : book)
		std::cout << x << '\n';
}

namespace shapes
{
struct Point {
	double x, y;
};


class Shape
{
public:
	virtual Point center() const = 0; // pure virtual
	virtual void move(Point to) = 0;
	virtual void draw() const = 0; // draw on current "Canvas"
	virtual void rotate(int angle) = 0;
	virtual ~Shape()
	{
	} // destructor
	Shape(const Shape &) = delete; // disable copy
	Shape &operator=(const Shape &) = delete;
	// ...
};

} // namespace shapes


namespace vector_ex
{
using namespace shapes;

void ex1()
{
	vector<int> v1 = {1, 2, 3, 4}; // size is 4
	vector<std::string> v2;        // size is 2
	vector<Shape *> v3;            // size is 23; initial element value nullptr
	vector<double> v4(32, 8.9);    // size is 32; initial element value: 9.9
}

void input(vector<Entry> &phone_book)
{
	for (Entry e; std::cin >> e;)
		phone_book.emplace_back(e);
}

void silly(vector<Entry> &book)
{
	int i = book[book.size()].number; // book.size() is out of range
	                                  // ...
}

int main()
try // minimizing surprises
{
	vector<Entry> phone_book = {
		{"David Hume", 1234456},
		{"Karl Popper", 234567},
		{"Bertrand Arthur William Russel", 345678},
	};
	print_book(phone_book);

	auto book2 = phone_book; // copy

	vector<vector_ex::Shape> s;   // No don't! - there is no room for a Circle or a Smiley
	vector<vector_ex::Shape> *ss; // better, but try ti not leak!!!
	vector<std::unique_ptr<vector_ex::Shape>> shapes; // OK

	my_containers::Vec<Entry> safe{phone_book.begin(), phone_book.end()};
	my_containers::checked(safe);
	return 0;
}
catch (std::out_of_range &) {
	std::cerr << "range error\n";
	return 0;
}

} // namespace vector_ex


namespace list_ex
{
constexpr int NUM_NOT_FOUND = 0;
int get_number(const std::string &s, std::list<Entry> &phone_book)
{
	for (const auto &x : phone_book)
		if (x.name == s)
			return x.number;

	/*
	for (auto p = phone_book.begin(); p != phone_book.end(); ++p) // iterator
	    if (p->name == s)
	        return p->number;
	*/

	return NUM_NOT_FOUND; // symbolic flag
}


int main()
{
	list<Entry> phone_book = {
		{"David Hume", 123456},
		{"Karl Popper", 234567},
		{"Bertrand Arthur William Russel", 345678},
	};
	int n = get_number("Karl Popper", phone_book);

	return EXIT_SUCCESS;
}
} // namespace list_ex


namespace map_ex
{
int get_number(const std::string &s, map<std::string, int> &phone_book)
{
	return phone_book[s];
}

int main()
{
	map<std::string, int> phone_book{
		{"David Hume", 123456},
		{"Karl Popper", 234567},
		{"Bertrand Arthur William Russel", 3455678},
	};

	int n = get_number("Karl Popper", phone_book);
}
} // namespace map_ex


namespace un_map_ex
{
template <typename K, typename V> V get_number(const K &s, unordered_map<K, V> phone_book)
{
	return phone_book[s];
}

int main()
{
	using std::string_literals::operator""s;

	unordered_map<std::string, int> phone_book{
		{"David Hume", 123456},
		{"Karl Popper", 234567},
		{"Bertrand Arthur William Russel", 3455678},
	};

	auto n = get_number("Karl Popper"s, phone_book);
}
} // namespace un_map_ex


namespace alloc_ex
{
constexpr std::size_t _AL_LEN = 512;
struct Event {
	vector<int> data = vector<int>(_AL_LEN);
};


struct condition_variable {
	void notify_one();
};

struct Event2 {
	//vector<int> data = vector<int>(512, &pool); // let Events use the pool
};


constexpr int LOTS = 6;
std::mutex m;
std::conditional_t cv;

void producer(list<std::shared_ptr<Event>> &q)
{
	for (int n = 0; n != LOTS; ++n) {
		std::lock_guard lk{m}; // m is a mutex;
		q.push_back(std::make_shared<Event>());
		cv.notify_one(); // cv is a condition_variable
	}
}


void producer2(list<std::shared_ptr<Event2>> &q)
{
	for (int n = 0; n != LOTS; ) {
		std::scoped_lock lk{m}; // m is a mutex
		//q.push_back(std::allocate_shared<Event, std::pmr::polymorphic_allocator<Event2>>(&pool));
		cv.notify_one();
	}
}

// std::pmrsyncr
std::pmr::synchronized_pool_resource pool; // make a pool

int main()
{
	list<std::shared_ptr<Event>> q;
	//list<std::shared_ptr<Event2>> q2{&pool}; // let q use the pool
	producer(q);
}

} // namespace alloc_ex

namespace my_containers
{

template <typename T> class Vector
{
	allocator<T> alloc; // standard-library allocator of space for Ts
	T *elem;            // pointer to first element
	T *space;           // pointer to first unused (and uninitialized) slot
	T *last;            // pointer to last slot
public:
	// ...
	int size() const
	{
		return space - elem;
	} // number of elements
	int capacity() const
	{
		return last - elem;
	} // number of slots available for elements
	// ...
	void reserve(int newsz); // increase capacity() to news
	// ...
	void push_back(const T &t); // copy t into Vector
	void push_back(T &&t);      // move t into Vector
};

template <typename T> void Vector<T>::push_back(const T &t)
{
	if (capacity() <= size())                  // make sure we have space for t
		reserve(size() == 0 ? 7 : 2 * size()); // double the capacity
	construct_at(space(t); // initialize *space to t ("place t at space")
    ++space;
}

/* range - checked vector */
template <typename T> struct Vec : std::vector<T> {
	using vector<T>::vector; // use the constructors from vector (under the name Vec)

	T &operator[](int)
	{
		return vector<T>::at(i);
	} // range check
	const T &operator[](int i) const
	{
		return vector<T>::at(i);
	} // rage check const objects

	auto begin()
	{
		return Checked_iter<vector<T>>{*this};
	}
	auto end()
	{
		return Checked_iter<vector<T>>{*this, vector<T>::end()};
	}
};


void checked(Vec<Entry> &book)
try {
	book[book.size()] = {"Joe", 9999999}; // will throw an exception
	                                      // ...
}
catch (std::out_of_range &) {
	std::cerr << "range error\n";
}


struct Record {
	std::string name;
	int product_code;
	// ...
};

struct Rhash { // a hash function for Record
	size_t operator()(const Record &r) const
	{
		return std::hash<std::string>()(r.name) ^ std::hash<int>()(r.product_code);
	}
};

void unset()
{
	unordered_set<Record, Rhash> my_set; // set of Records using Rhash for lookup
}

} // namespace my_containers


namespace std
{ // make a hash function for Record
using namespace my_containers;

template <> struct hash<Record> {
	using argument_type = Record;
	using result_type = size_t;

	result_type operator()(const Record &r) const
	{
		return hash<string>()(r.name) ^ hash<int>()(r.product_code);
	}
};

} // namespace std


int main()
{
	int r = vector_ex::main();
	r |= list_ex::main();
	r |= map_ex::main();
	r |= un_map_ex::main();
	r |= alloc_ex::main();

	return r;
}
