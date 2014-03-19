//g++ main6sort.cpp -o sort -lrt
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "lib_sort.h"
#define N 10000
#define MOD 300000
using namespace std;

void create_random_array(int array[], int num, int mod = 10)
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
/*
unsigned long long get_time_in_sec(timespec start_time, timespec end_time)
{
	return (unsigned long long) (end_time.tv_sec - start_time.tv_sec);
}

unsigned long long get_time_in_nanosec(timespec start_time, timespec end_time)
{
	return (unsigned long long) ((end_time.tv_sec - start_time.tv_sec) * 1000000000 + (end_time.tv_nsec - start_time.tv_nsec));
}

unsigned long long get_time_in_microsec(timespec start_time, timespec end_time)
{
	return (unsigned long long) ((end_time.tv_sec - start_time.tv_sec) * 1000000000 + (end_time.tv_nsec - start_time.tv_nsec))/1000;
}

unsigned long long get_time_in_millisec(timespec start_time, timespec end_time)
{
	return (unsigned long long) ((end_time.tv_sec - start_time.tv_sec) * 1000) + (end_time.tv_nsec - start_time.tv_nsec) / 1000000;
}

unsigned long long get_time_of_work(void (*sort)(int[], unsigned int), int *test, int n, int mod, int d)
{
		unsigned long long result = 0;
		timespec start_time, end_time;
		test = new int[n];

		for (int i = 0; i < d; ++i)
		{
			create_random_array(test, n, mod);
			clock_gettime(CLOCK_MONOTONIC, &start_time);
			sort(test, n);
			clock_gettime(CLOCK_MONOTONIC, &end_time);
			//result += get_time_in_millisec(start_time, end_time);
			//result += get_time_in_nanosec(start_time, end_time);
			result += get_time_in_microsec(start_time, end_time);
		}

		//print_array(test, n);
		delete []test;
		return (result / d);
}
*/
int main()
{
	int array[N], *test, n;
	char arr[N];

{
    cout << "create array..." << endl;
	create_random_array(array, N,2);
	print_array(array, N);
	cout << "quick_flag:" << endl;
	quick_flag(array, N);
	print_array(array, N);
	cout << endl;
}

	/*
	cout << "create array..." << endl;
	create_random_array(array, N, 1000);
	print_array(array, N,1);
	cout << "insert:" << endl;
	insert(array, N);
	print_array(array, N,1);
	cout << endl;

	cout << "create array..." << endl;
	create_random_array(array, N, 1000);
	print_array(array, N);
	cout << "msd:" << endl;
	msd(array, N);
	print_array(array, N);
	cout << endl;


	//return 0;
	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "merge_bottom_up:" << endl;
	merge_bottom_up(array, N);
	print_array(array, N);
	cout << endl;
	//return 0;

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
	cout << "bubble:" << endl;
	bubble(array, N);
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
	cout << "insert sort with barrier:" << endl;
	insert_with_bar(array, N);
	print_array(array, N);
	cout << endl;

	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "selection sort:" << endl;
	selection(array, N);
	print_array(array, N);
	cout << endl;

	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "quick sort:" << endl;
	quick(array, N);
	print_array(array, N);
	cout << endl;

	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "shell sort:" << endl;
	shell(array, N);
	print_array(array, N);
	cout << endl;

	cout << "create array..." << endl;
	create_random_array(array, N);
	print_array(array, N);
	cout << "heap sort:" << endl;
	heap(array, N);
	print_array(array, N);
	cout << endl;
*/


	/*
	cout << setw(11) << " "
		 << setw(10) << "insert"
		 << setw(10) << "ins with bar"
		 << setw(10) << "selection"
		 << setw(10) << "bubble"
		 << endl;
	for (n = 100; n <= 40000; n += 1000)
	{
			cout << setw(5) << "n = " << setw(5) << n << " ";
			cout << setw(10) << get_time_of_work(insert, test, n, MOD,15);
			cout << setw(10) << get_time_of_work(insert_with_bar, test, n, MOD, 15);
			cout << setw(10) << get_time_of_work(selection, test, n, MOD, 15);
			cout << setw(10) << get_time_of_work(bubble, test, n, MOD, 15);
			cout << endl;
	}
	*/
	/*
	cout << endl << setw(16) << "mod=100 000 "
				 << setw(15) << "qsort"
				 << setw(15) << "flag"
				 << endl;

	for (n = 30000; n <= 80000; n+= 10000)
	{
			cout << setw(5) << "n = " << setw(10) << n << " ";
			cout << setw(15) << get_time_of_work(quick, test, n, 100000, 15);
			cout << setw(15) << get_time_of_work(quick_flag, test, n, 100000, 15);
			cout << endl;
	}

	cout << endl << setw(16) << "mod=100 "
				 << setw(15) << "qsort"
				 << setw(15) << "flag"
				 << endl;

	for (n = 30000; n <= 80000; n+= 10000)
	{
			cout << setw(5) << "n = " << setw(10) << n << " ";
			cout << setw(15) << get_time_of_work(quick, test, n, 100, 15);
			cout << setw(15) << get_time_of_work(quick_flag, test, n, 100, 15);
			cout << endl;
	}

	cout << endl << setw(16) << "mod=10 "
				 << setw(15) << "qsort"
				 << setw(15) << "flag"
				 << endl;

	for (n = 30000; n <= 80000; n+= 10000)
	{
			cout << setw(5) << "n = " << setw(10) << n << " ";
			cout << setw(15) << get_time_of_work(quick, test, n, 10, 15);
			cout << setw(15) << get_time_of_work(quick_flag, test, n, 10, 15);
			cout << endl;
	}

	cout << endl << setw(16) << "mod=3 "
				 << setw(15) << "qsort"
				 << setw(15) << "flag"
				 << endl;

	for (n = 30000; n <= 80000; n+= 10000)
	{
			cout << setw(5) << "n = " << setw(10) << n << " ";
			cout << setw(15) << get_time_of_work(quick, test, n, 3, 15);
			cout << setw(15) << get_time_of_work(quick_flag, test, n, 3, 15);
			cout << endl;
	}

	return 0;

	cout << endl << setw(16) << "mod=100 000 "
				 << setw(15) << "q_flag"
				 << setw(15) << "insert"
				 << endl;
	double t1,t2;
	for (n = 2; n <= 50; n+= 1)
	{
			t1 = get_time_of_work(quick_flag, test, n, 100000, 80000);
			t2 = get_time_of_work(insert, test, n, 100000, 80000);
			cout << setw(5) << "n = " << setw(10) << n << " ";
			cout << setw(15) << t1;
			cout << setw(15) << t2;
			cout << setw(15) << t1/t2;
			cout << endl;
	}
	return 0;

	cout << endl << setw(16) << "mod=100 000 "
				 << setw(15) << "shell_sedj"
				 << setw(15) << "shell_knut"
				 << endl;

	for (n = 30000; n <= 80000; n+= 10000)
	{
			cout << setw(5) << "n = " << setw(10) << n << " ";
			cout << setw(15) << get_time_of_work(shell_sedj, test, n, 100000, 15);
			cout << setw(15) << get_time_of_work(shell_knut, test, n, 100000, 15);
			cout << endl;
	}

	cout << endl << setw(16) << "mod=1000 "
				 << setw(15) << "shell_sedj"
				 << setw(15) << "shell_knut"
				 << endl;

	for (n = 30000; n <= 80000; n+= 10000)
	{
			cout << setw(5) << "n = " << setw(10) << n << " ";
			cout << setw(15) << get_time_of_work(shell_sedj, test, n, 1000, 15);
			cout << setw(15) << get_time_of_work(shell_knut, test, n, 1000, 15);
			cout << endl;
	}

	cout << endl << setw(16) << "mod=10 "
				 << setw(15) << "shell_sedj"
				 << setw(15) << "shell_knut"
				 << endl;

	for (n = 30000; n <= 80000; n+= 10000)
	{
			cout << setw(5) << "n = " << setw(10) << n << " ";
			cout << setw(15) << get_time_of_work(shell_sedj, test, n, 10, 15);
			cout << setw(15) << get_time_of_work(shell_knut, test, n, 10, 15);
			cout << endl;
	}

	cout << endl << setw(16) << "mod=5"
				 << setw(15) << "shell_sedj"
				 << setw(15) << "shell_knut"
				 << endl;

	for (n = 30000; n <= 80000; n+= 10000)
	{
			cout << setw(5) << "n = " << setw(10) << n << " ";
			cout << setw(15) << get_time_of_work(shell_sedj, test, n, 5, 15);
			cout << setw(15) << get_time_of_work(shell_knut, test, n, 5, 15);
			cout << endl;
	}


		cout << endl << setw(16) << "mod=3"
				 << setw(15) << "shell_sedj"
				 << setw(15) << "shell_knut"
				 << setw(15) << "qsort flag"
				 << endl;

	for (n = 30000; n <= 80000; n+= 10000)
	{
			cout << setw(5) << "n = " << setw(10) << n << " ";
			cout << setw(15) << get_time_of_work(shell_sedj, test, n, 3, 15);
			cout << setw(15) << get_time_of_work(shell_knut, test, n, 3, 15);
			cout << setw(15) << get_time_of_work(quick_flag, test, n, 3, 15);
			cout << endl;
	}

	return 0;*/
/*
	cout << endl << setw(8) << "|Zn| = " << setw(8) << MOD
				 << setw(12) << "quick"
				 << setw(12) << "q_flag"
				 << setw(12) << "q_flag_ins"
				 << setw(12) << "sedj"
				 //<< setw(12) << "knut"
				 //<< setw(12) << "heap"
				 //<< setw(12) << "merge TD"
				 << setw(12) << "MSD"
				 << endl;

	for (n = 20000; n <= 100000; n+= 10000)
	{
			cout << setw(5) << "n = " << setw(10) << n << " ";
			cout << setw(12) << get_time_of_work(quick, test, n, MOD, 15);
			cout << setw(12) << get_time_of_work(quick_flag, test, n, MOD, 15);
			cout << setw(12) << get_time_of_work(quick_flag_ins, test, n, MOD, 15);
			cout << setw(12) << get_time_of_work(shell_sedj, test, n, MOD, 15);
			//cout << setw(12) << get_time_of_work(shell_knut, test, n, MOD, 15);
			//cout << setw(12) << get_time_of_work(heap, test, n, MOD, 15);
			//cout << setw(12) << get_time_of_work(merge_top_down, test, n, MOD, 15);
			cout << setw(12) << get_time_of_work(msd, test, n, MOD, 15);
			cout << endl;
	}
*/


	return 0;
}
