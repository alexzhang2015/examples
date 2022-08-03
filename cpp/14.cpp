/**
 @file
 @brief C++14
 @defgroup CPP14 C++14 examples

 https://en.wikipedia.org/wiki/C++14

 https://isocpp.org/wiki/faq/cpp14-language

 https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP14.md

 @{
 */

static_assert(__cplusplus == 201402, "");

#include <bits/stdc++.h>

using namespace std;

/**
 @defgroup ded14 Deduction
 @{
 */

#define static_assert(a) static_assert(a, "")
static_assert(__cpp_return_type_deduction);

auto implicit_int_return_type()
{
	return 1;
}

// template <typename T> T before_deduced_return_type(int a) { return a; }
auto deduced_return_type(int a)
{
	return a;
}

// template <typename T> T& before_deduced_return_type_template(T& a) { return a; }
template <typename T> auto& deduced_return_type_template(T& t)
{
	return t;
}

// Returns a reference to a deduced type.
auto deduced_return_type_lambda = [](auto& x) -> auto& {
	return deduced_return_type_template(x);
};

void return_type_deduction_demo()
{
	implicit_int_return_type();
	auto x = deduced_return_type(1);
	int& y = deduced_return_type_lambda(x); // reference to `x`
	assert(&y == &x);
	assert(y == 1);
}

///  @}
/**
 @defgroup other14 Other
 @{
 TODO:

 https://en.cppreference.com/w/cpp/container/map/find

 https://en.cppreference.com/w/cpp/language/constexpr

 https://en.cppreference.com/w/cpp/language/integer_literal

 https://en.cppreference.com/w/cpp/language/function // decltype(auto)

 https://en.cppreference.com/w/cpp/language/aggregate_initialization

 https://en.cppreference.com/w/cpp/thread/shared_timed_mutex

 https://en.cppreference.com/w/cpp/thread/shared_lock

 https://en.cppreference.com/w/cpp/utility/integer_sequence

 https://en.cppreference.com/w/cpp/utility/exchange

 https://en.cppreference.com/w/cpp/utility/forward

 https://en.cppreference.com/w/cpp/io/manip/quoted

 // [[deprecated]]
 */

/// Binary literals, digit separators

/// Template variables
/// https://en.cppreference.com/w/cpp/language/variable_template

static_assert(__cpp_variable_templates);

/// Numeric pi
template<typename T>
T pi = T(3.141592653589793238462643383);

// String pi
// Usual specialization rules apply:
template<>
const char* pi<const char*> = "pi";

static void demo()
{
	assert(pi<int> == 3);
	assert(string(pi<const char*>) == "pi");

	auto binary_literal = 0b0100'1100'0110;

	auto integer_literal = 1'000'000;

	auto floating_point_literal = 0.000'015'3;

	/// Standard user-defined literals

	auto str = "hello world"s; // auto deduces string
	auto dur = 60s;            // auto deduces chrono::seconds

}

void types_14()
{
	static_assert(is_null_pointer<decltype(nullptr)>::value);
	static_assert(is_null_pointer<nullptr_t>::value);
	static_assert(__cpp_decltype);
	static_assert(is_integral<int>());

	// Tuple addressing via type
	tuple<string, string, int> tuple_by_type("foo", "bar", 7);

	int i = get<int>(tuple_by_type);
	assert(i == 7);

	int j = get<2>(tuple_by_type);
	assert(j == 7);

	// https://en.cppreference.com/w/cpp/language/auto
	int a = 0;
	static_assert(__cpp_decltype_auto);
	decltype(auto) a_copy = a;
	assert(&a_copy != &a);
	decltype(auto) a_ref = (a);
	assert(&a_ref == &a);

	// https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
	//auto u = unique_ptr<int>(new int(1));
	auto u = make_unique<int>(1);
	assert(u);
	assert(*u == 1);
	auto ua = make_unique<int[]>(3);
}

/// @}
/**
 @defgroup lambda14 Lambda
 https://en.cppreference.com/w/cpp/language/lambda
 @{
 */
static void lambda_14()
{
	// Generic lambdas
	// auto before_generic_lambda = [](int x) { return x; };
	static_assert(__cpp_generic_lambdas);
	auto generic_lambda = [](auto x) { return x; };

	auto universal_size = [](const auto& m) { return m.size(); };

	static_assert(__cpp_init_captures);
	auto capture_initializers = [value = 1] { return value; };

	assert(capture_initializers() == 1);

	auto mutable_lambda = [value = 1] () mutable { return ++value; };

	assert(mutable_lambda() == 2);
	assert(mutable_lambda() == 3);

	// capture initialization can change context
	int c = 0;
	auto change_c = [value = ++c] { };
	assert(c == 1);

	unique_ptr<int> ptr(new int(10));
	auto capture_by_move = [value = move(ptr)] { return *value; };
}

/// Compare with @ref lambda::sort_11

void sort_14()
{
	array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
	sort(s.begin(), s.end(),
		  // sort using a generic lambda expression
		  [](auto a, auto b) // C++14 allows auto
		  { return a > b; }
		 );

	// https://stackoverflow.com/questions/18045208/override-mapcompare-with-lambda-function-directly
	auto reverse = map<string, int, function<bool(const string&, const string&)>>{
		[](const auto& a, const auto& b) { return a > b; }
		} = {{"a", 2}, {"b", 1}, {"c", 0}, };
	assert(reverse.begin()->first == "c");
	assert(reverse.begin()->second == 0);
}

/// @}

int main(void)
{
	return_type_deduction_demo();
	demo();
	sort_14();
	types_14();
	lambda_14();
}
/// @}
