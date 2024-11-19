#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <vector>

using std::literals::string_literals::operator"" s;
void f(const std::vector<int> &vec, const std::list<std::string> &lst, int x, const std::string &s)
{
	std::cout << "number of values less than " << x << ": "
			  << std::count_if(vec.begin(), vec.end(), [&](int a) { return a < x; }) << '\n';
	std::cout << "number of values less than " << s << ": "
			  << std::count_if(lst.begin(), lst.end(), [&](const std::string &a) { return a < s; })
			  << '\n';
}

template <typename C, typename Oper>
void for_all(C &c, Oper op) // assume that C is a container of pointers
                            // requires Sequence<C> && Callable<Oper,Value_type<C>> (see §7.2.1)
{
	for (auto &x : c)
		op(x); // pass op() a reference to each element pointed to
}

class Shape
{
public:
	void draw();
	void rotate(double t);
};

std::unique_ptr<Shape> read_shape(const std::istream &)
{
}

void user2()
{
	std::vector<std::unique_ptr<Shape>> v;
	while (std::cin)
		v.push_back(read_shape(std::cin));

	for_all(v, [](std::unique_ptr<Shape> &ps) { ps->draw(); });     // draw_all()
	for_all(v, [](std::unique_ptr<Shape> &ps) { ps->rotate(45); }); // rotate_all(45)
}

template <class S> void rotate_and_draw(std::vector<S> &v, int r)
{
	for_all(v, [](auto &s) {
		s->rotate(r);
		s->draw();
	});
}

void user4()
{
	std::vector<std::unique_ptr<Shape>> v1;
	std::vector<Shape *> v2;
	// ...
	rotate_and_draw(v1, 45);
	rotate_and_draw(v2, 90);
}

int main()
{
	f(std::vector{1, 2, 3}, std::list{"abc"s, "def"s, "tuv"s}, 2, "test"s);
	user2();
}
