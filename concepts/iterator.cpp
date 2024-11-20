#include <list>
#include <string>
#include <vector>
#include <ranges>


template <std::forward_iterator Iter> void advance(Iter p, int n) // move p n elements forward
{
	while (n--)
		++p; // a forward iterator has ++, but not + or +=
}

template <std::random_access_iterator Iter> void advance(Iter p, int n) // move p n elements forward
{
	p += n; // arandom-access iterator has +=
}


void user(std::vector<int>::iterator vip, std::list<std::string>::iterator lsp)
{
	advance(vip, 10); // use the fast advance()
	advance(lsp, 10); // use the slow advance()
}

/* ugly requires expression
template <Forward_iterator Iter, int n>
	requires requires(Iter p, int i) {
		p[i];
		p + i;
	}                       // Iter has subscripting and addition
void advance(Iter p, int n) // move p n elements forward
{
	p += n; // a random-access iterator has +=
}
*/
