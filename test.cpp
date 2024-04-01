#include <iostream>

#include "operator.h"

create_operator(swap_op, void, int&, int&)
{
	int a = left;
	left = right;
	right = a;
}

create_operator(in_op, bool, char, const std::string&)
{
	return (right.find(left) != std::string::npos) ? true : false;
}

#define _swap_ <=swap_op>=
#define is_in <in_op>

int add_test(int l, int r)
{
	return l + r;
}

inline constexpr auto add_op = naz::make_operator(add_test);

int main()
{
	int a = 0, b = 10;
	a _swap_ b; // a == 10, b == 0;
	std::cout << std::boolalpha << ('t' is_in "some string"); // prints -> true

	std::cout << (5 < add_op > 10); // prints -> 15

}
