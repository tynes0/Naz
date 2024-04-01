# Naz operator generator

Naz is a "header only" project that allows you to generate your own operators in C++.

## Usage

You can create the operator you want using the create_operator() macro.

Note: The value on the left side is called 'left', and the value on the right side is called 'right'.

```cpp
create_operator(operator_name, return_type, left_type, right_type)
```
Below you see a simple swap operator implementation.
```cpp
create_operator(swap_op, void, int&, int&)
{
	int temp = left;
	left = right;
	right = temp;
}
```

OK, I created the operator, so how do I use it? Here is the examples:

```cpp
// EXAMPLE - 1
/*
 *	We used || because the left_type is the reference, 
 *	and || because the right_type is the reference.
*/

#define _swap_ ||swap_op|| // don't use macros if you don't want to

void test1()
{
	int a = 0, b = 10;
	a _swap_ b;
	std::cout << a; // output: 10
}
```

```cpp
// EXAMPLE - 2
create_operator(in_op, bool, char, const std::string&)
{
	return right.find(left) != std::string::npos ? true : false;
}
/*
 *	We used | because the left_type is not the reference, 
 *	and | because the right_type is not the reference.
*/
#define is_in |in_op|

void test2()
{
	if('o' is_in "Hello, World!")
		std::cout << "YES!";
	else
		std::cout << "NO!";
	// output: YES!
}
```

```cpp
// EXAMPLE - 3
create_operator(add_to, void, int, int&)
{
	right += left;
}

/*
 *	We used | because the left_type is not the reference, 
 *	and || because the right_type is the reference.
*/

void test3()
{
	int a = 10;
	5 |add_to|| a;
	std::cout << a; // output: 15
}
```
Can I create an operator without using the create_operator() macro? Actually yes!

Let's redo example - 1 without using the create_operator() macro.

```cpp
// EXAMPLE - 4

void my_swap(int& lhs, int& rhs)
{
	int temp = lhs;
	lhs = rhs;
	rhs = temp;
}

// Here we use the naz::make_operator function
_NAZ_INLINE constexpr auto swap_op = naz::make_operator(my_swap);

#define _swap_ ||my_swap|| 

void test4()
{
	int a = 0, b = 10;
	a _swap_ b;
	std::cout << a; // output: 10
}
```
