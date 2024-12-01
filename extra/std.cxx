module;

#include <algorithm>
#include <any>
#include <array>
#include <atomic>
#include <bit>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <charconv>
#include <chrono>
#include <cinttypes>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <codecvt>
#include <compare>
#include <condition_variable>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <ctgmath>
#include <cuchar>
#include <cwchar>
#include <cwctype>
#include <exception>
#include <filesystem>
#include <forward_list>
#include <functional>
#include <future>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <optional>
#include <random>
#include <ranges>
#include <regex>
#include <set>
#include <shared_mutex>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <valarray>
#include <variant>
#include <vector>
// ...


/* implementation defined modules
export module std;

export import std.regex; // <regex>
export import std.filesystem; // <filesystem>
export import std.memory; // <memory>
export import std.threading; // <atomic>, <condition_variable>, <future>,
                             // <mutex>, <shared_mutex>, <thread>
export import std.core; // all the rest
*/

export module std;


/* manual import */
export namespace std
{
};

export namespace std::literals
{
};
export namespace std::literals::chrono_literals
{
};
export namespace std::literals::string_literals
{
};
export namespace std::literals::regex_literals
{
};
export namespace std::literals::filesystem_literals
{
};
export namespace std::ranges
{
};
// etc...
