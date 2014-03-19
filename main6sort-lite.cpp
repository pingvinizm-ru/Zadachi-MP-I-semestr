//g++ main6sort.cpp -o sort
#include <iostream>
#include <string>
#include <cstdlib>
#include "lib_sort_lite.h"
#define N 15
using namespace std;

void create_random_array(int array[], int num, int mod = 100)
{
	for (int i = 0; i < num; ++i)
	{
		array[i] = rand() % mod;
	}
}

void print_array(int array[], int num, int type_of_print = 0)
{
	for (int i = 0; i < num; ++i)
	{
		cout << array[i];
		if (type_of_print == 0) cout << " "; else cout << endl;
	}
	cout << endl;
}


int main()
{
	int array[N];

	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "merge_bottom_up:" << endl;
	merge_bottom_up(array, N);
	print_array(array, N);
	cout << endl;

	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "merge_top_down:" << endl;
	merge_top_down(array, N);
	print_array(array, N);
	cout << endl;

	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "qsort with stack:" << endl;
	quick_sort_stack(array, N);
	print_array(array, N);
	cout << endl;

	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "qsort with STL stack:" << endl;
	quick_sort_stack_stl(array, N);
	print_array(array, N);
	cout << endl;
	
	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "quick_flag:" << endl;
	quick_flag(array, N);
	print_array(array, N);
	cout << endl;

	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "heap sort:" << endl;
	heap(array, N);
	print_array(array, N);
	cout << endl;

	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "shell_knut:" << endl;
	shell_knut(array, N);
	print_array(array, N);
	cout << endl;

	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "shell_sedj:" << endl;
	shell_sedj(array, N);
	print_array(array, N);
	cout << endl;
	return 0;
}