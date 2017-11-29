#include "stdafx.h"
#include <functional>
#include <vector>

/*
void func1() {
	printf("yoyo!");
}

void func2() {
	printf("DOEI.");
}

void test() {
	//Note: vector is kind of like a C# list in C++ (to use: #include <vector>).
	//function is a type that can easily point to a function.

	//Make a vector(list) of functions, these functions have a void return type and no parameters ()
	std::vector<std::function<void()>> functionList;

	//Add 3 functions to the list
	functionList.push_back(func1);
	functionList.push_back(func1);
	functionList.push_back(func2);

	//loop and execute all the functions in the list
	for (size_t i = 0; i < functionList.size(); i++) {
		functionList[i]();
	}
}
*/