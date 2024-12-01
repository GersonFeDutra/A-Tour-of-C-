#include <chrono>
#include <condition_variable>
#include <coroutine>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <thread>

// external library
#include <cppcoro/task.hpp>

// utils
#include <functional>
#include <generator>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>


using std::atomic;
using std::condition_variable;
using std::future;
using std::jthread;
using std::lock_guard;
using std::mutex;
using std::packaged_task;
using std::promise;
using std::scoped_lock;
using std::shared_lock;
using std::shared_mutex;
using std::stop_source;
using std::stop_token;
using std::thread;
using std::unique_lock;

namespace this_thread = std::this_thread;

using std::async;

#define forever for (;;)

void f(); // function

struct F {             // function object
	void operator()(); // F's call operator
};

void user()
{
	thread t1{f};   // f() executes in separate thread
	thread t2{F{}}; // F{}() executes in separate thread

	t1.join(); // wait for t1
	t2.join(); // wait for t2
}

void user2()
{
	jthread t1{f};   // f() executes in separate thread
	jthread t2{F{}}; // F{}() executes in separate thread
}


// notice that f and F introduce data races
namespace ex1
{
void f()
{
	std::cout << "Hello ";
}

void F::operator()()
{
	std::cout << "Parallel world\n";
}
} // namespace ex1


namespace ex2
{
void f()
{
	std::cout << "Hello ";
}
} // namespace ex2


namespace ex3
{
void f(std::vector<double> &v); // function: do something with v

struct F { // function object: do something with v
	std::vector<double> &v;
	F(std::vector<double> &vv) : v{vv}
	{
	}
	void operator()(); // application operator
};

int main()
{
	std::vector<double> some_vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<double> vec2{10, 11, 12, 13, 14};

	jthread t1{f, std::ref(some_vec)}; // f(some_vec) executes in a separate thread
	jthread t2{F{vec2}};               // F(vec2)() executes in a separate thread
}

} // namespace ex3


namespace ex4
{

void f(const std::vector<double> &v, double *res); // take input from v; place result in *res

class F
{
public:
	F(const std::vector<double> &vv, double *p) : v{vv}, res{p}
	{
	}
	void operator()(); // place result in *res
private:
	const std::vector<double> &v; // source of input
	double *res;
};

double g(const std::vector<double> &); // use return value

void user(std::vector<double> &v1, std::vector<double> v2, std::vector<double> v3)
{
	using std::cref;
	double res[3];

	thread t1{f, cref(v1), &res[0]};      // f(v1, &res[0]) executes in a separate thread
	thread t2{F{v2, &res[1]}};            // F{v2, &res[1]}() executes in a separate thread
	thread t3{[&]() { res[2] = g(v3); }}; // capture local variables by reference

	// join before using results
	t1.join();
	t2.join();
	t3.join();

	std::cout << res[0] << ' ' << res[1] << ' ' << res[2] << '\n';
}

} // namespace ex4


namespace ex5
{
mutex m; // controlling mutex
int sh;  // shared data

void f()
{
	scoped_lock lck{m}; // acquire mutex
	sh += 7;            // manipulate shared data
	                    // release mutex implicitly
}

} // namespace ex5


namespace ex6
{
class Record
{
public:
	mutex rm;
	// ...
};

mutex mutex1, mutex2, mutex3;

void f()
{
	scoped_lock lck{mutex1, mutex2, mutex3}; // acquire all three locks
	                                         // .. manipulate shared data ...
} // implicitly release all mutexes

} // namespace ex6


namespace ex7
{
shared_mutex mx; // a mutex that can be shared

void reader()
{
	shared_lock lck{mx}; // willing to share access with other readers

	// ... read ...
}

void writer()
{
	unique_lock lck{mx}; // needs exclusive (unique) access

	// ... write ...
}

} // namespace ex7


namespace ex8
{

template <typename X> int main()
{
	mutex mut;
	atomic<bool> init_x; // initially false

	X x; // variable that requires nontrivial initialization

	if (!init_x) {
		lock_guard lck{mut};
		if (!init_x) {
			// ... do nontrivial initialization of x ...
			init_x = true;
		}
	}

	return 0;
}

} // namespace ex8


namespace ex9
{
using namespace std::chrono;

void f()
{
	auto t0 = high_resolution_clock::now();

	auto t0 = high_resolution_clock::now();
	this_thread::sleep_for(milliseconds{20});
	auto t1 = high_resolution_clock::now();

	std::cout << duration_cast<nanoseconds>(t1 - t0).count() << "nanoseconds passed\n";
}

} // namespace ex9


namespace ex10
{
using std::queue;

class Message
{ // object to be communicated
  // ...
};

queue<Message> m_queue;    // the queue of messages
condition_variable m_cond; // the variable communicating events
mutex m_mutex;             // for synchronizing access to m_cond

namespace ex_a
{
void consumer()
{
	forever
	{
		unique_lock lck{m_mutex}; // acquire mutex
		m_cond.wait(lck, [] { return !m_queue.empty(); });
		// release mutex and wait;
		// re-acquire m_mutex upon wakeup
		// don't wake up unless m_queue is non-empty

		auto m = m_queue.front(); // get the message
		m_queue.pop();
		lck.unlock(); // release m_mutex
	}
}
} // namespace ex_a

void producer()
{
	forever
	{
		Message m;
		// ... fill the message ...
		scoped_lock lck{m_mutex}; // protect operations
		m_queue.push(m);
		m_cond.notify_one(); // notify
	} // release m_mutex (at end of scope)
}

} // namespace ex10


namespace ex11
{

template <typename X> void f(promise<X> &px) // a task: place the result in px
{
	// ..
	try {
		X res;
		// ... compute a value for res ...
		px.set_value(res);
	}
	catch (...) {                                   // oops: couldn't compute res ...
		px.set_exception(std::current_exception()); // pass the exception to the future's thread
	}
}

template <typename X> void g(future<X> &fx) // a task: get the result from fx
{
	// ...
	try {
		X v = fx.get(); // if necessary, wait for the value to get computed
		                // ... use v ...
	}
	catch (...) { // oops: someone couldn't compute v
		          // ... handle error ...
	}
	// reduce to the minimal code (remove the try catch) if error-treatment must be postponed
}

} // namespace ex11


namespace ex12
{

double accum(std::vector<double>::iterator beg, std::vector<double>::iterator end, double init)
// compute the sum of [beg, end) starting with the initial value init
{
	return std::accumulate(&*beg, &*end, init);
}

double comp2(STD::VECTOR<DOUBLE> &V)
{
	packaged_task pt0{accum}; // package the task (i.e., accum)
	packaged_task pt1{accum};

	future<double> f0{pt0.get_future()}; // get hold of pt0's future
	future<double> f1{pt1.get_future()}; // get hold of pt1's future

	double *first = &v[0];
	thread t1{std::move(pt0), first, first + v.size() / 2, 0.0}; // start a thread for pt0
	thread t1{std::move(pt1), first + v.size() / 2, first + v.size(), 0.0};
	// start a thread for pt0
	// ...

	return f0.get() + f1.get(); // get the results
}

} // namespace ex12


namespace ex13
{

double comp4(std::vector<double> &v)
// spawn many tasks if v is large enough
{
	using t = std::vector<double>::iterator;

	if (v.size() < 10'000) // is it worth using concurrency?
		return ex12::accum(v.begin(), v.end(), 0.0);

	auto v0 = &v[0];
	auto sz = v.size();

	auto f0 = async(ex12::accum, (t)v0, (t)(v0 + sz / 4), 0.0);                // fist quarter
	auto f0 = async(ex12::accum, (t)(v0 + sz / 4), (t)(v0 + sz / 2), 0.0);     // second quarter
	auto f0 = async(ex12::accum, (t)(v0 + sz / 2), (t)(v0 + sz * 3 / 4), 0.0); // third quarter
	auto f0 = async(ex12::accum, (t)(v0 + sz * 3 / 4), (t)(v0 + sz), 0.0);     // fourth quarter

	return f0.get() + f1.get() + f2.get() + f3.get(); // collect and combine the results
}

} // namespace ex13


namespace ex14
{
atomic<int> result = -1; // put a resulting index here

template <class T> struct Range {
	T *first;
	T *last;
}; // a way of passing a range of Ts


bool match(const std::string &s, const std::string &target)
{
	// test
	return s == target;
}


void find(
	stop_token tok, const std::string *base, const Range<std::string> r, const std::string target)
{
	for (std::string *p = r.first; p != r.last && !tok.stop_requested(); ++p) {
		if (match(*p, target)) { // match() applies some matching criteria to the two strings
			result = p - base;   // the index of the found element
		}
		return;
	}
}

void find_all(std::vector<std::string> &vs, const std::string &key)
{
	using namespace std::chrono_literals;

	int mid = vs.size() / 2;
	std::string *pvs = &vs[0];

	stop_source ss1{};

	jthread t1(find, ss1.get_token(), pvs, Range{pvs, pvs + mid}, key); // first half of vs

	stop_source ss2{};
	jthread t2(
		find, ss2.get_token(), pvs, Range{pvs + mid, pvs + vs.size()}, key); // second half of vs

	while (result == -1)
		this_thread::sleep_for(10ms);

	ss1.request_stop(); // we have a result: stop all threads
	ss2.request_stop();

	// ... use result ...
}

} // namespace ex14


namespace ex15
{

std::generator<long long> fib() // generate Fibonacci numbers
{
	long long a = 0, b = 1;
	while (a < b) {
		auto next = a + b;
		co_yield next; // save state, return value and wait
		a = b;
		b = next;
	}
	co_return 0LL; // a fib too far
}

void user(int max)
{
	for (int i = 0; i++ < max;)
		std::cout << fib() << ' ';
}

} // namespace ex15


namespace ex16
{

struct Event_base {
	virtual void operator()() = 0;

	virtual ~Event_base()
	{
		coro.resume();
	}

	struct promise_type { // mapping to the language features
		suspend_always initial_suspend()
		{
			return {};
		}
		suspend_always final_suspend() noexcept
		{
			return {};
		} // co_return
		suspend_always yield_value(int)
		{
			return {};
		} // co_yield
		auto get_return_object()
		{
			return task{handle_type::fro_promise(*this)};
		}
		void return_void()
		{
		}
		void unhandled_exception()
		{
			exit(1);
		}
	};

	using handle_type = coroutine_handle<promise_type>;
	task(handle_type h) : coro{h}
	{
	}                 // called by get_return_object()
	handle_type coro; // here is the coroutine handle
};

template <class Act> struct Event : Event_base {
	Event(const std::string n, Act a) : name{n}, act{std::move(a)}
	{
	}
	std::string name;
	void operator()() override
	{
		act();
	}
};

struct task {
	void operator()()
	{
	}

	// ... implementation details ...
};

task sequencer(int start, int strp = 1)
{
	auto value = start;

	while (true) {
		std::cout << "value: " << value << '\n'; // communicate a result
		co_yield 0;                              // sleep until someone resumes this coroutine
		value += strp;                           // update state
	}
}

task char_seq(char start)
{
	auto value = start;
	forever
	{
		std::cout << "value: " << value << '\n'; // communicate a result
		co_yield 0;
		++value;
	}
}

void test()
{
	std::vector<Event_base *> events = {
		// create a couple of Events holding coroutines
		new Event{"integers ", sequencer(10)},
		new Event{"chars ", char_seq('a')},
	};

	std::vector order{0, 1, 1, 0, 1, 0, 1, 0, 0}; // choose some order

	for (int x : order) // invoke coroutines in order
		(*events[x])();

	for (auto p : events) // clean up
		delete p;
}


} // namespace ex16
