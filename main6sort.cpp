//g++ main6sort.cpp -o sort -lrt
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "lib_sort.h"

#define N 5000
#define MOD 20
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

unsigned long long get_time(timespec start_time, timespec end_time, long precision = 1000000)
{
	return (unsigned long long) ((end_time.tv_sec - start_time.tv_sec) * 1000000000 + (end_time.tv_nsec - start_time.tv_nsec))/precision;
}

unsigned long long get_time_of_work(void (*sort)(int[], unsigned int), int *test, int n, int mod, int d, int precision = 1000000)
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
			result += get_time(start_time, end_time, precision);
		}

		//print_array(test, n);
		delete []test;
		return (result / d);
}

//функция возвращает значение = адресу функции сортировки
//с прототипом void sort(type array[], unsigned int num)
void (*get_addres_of_sort(int tag))(int[], unsigned int)
{
	//if (tag == 0) return NULL;
	if (tag == 1) return msd;
	if (tag == 2) return lsd;
	//if (tag == 3) return NULL;
	//if (tag == 4) return NULL;
	if (tag == 5) return quick;
	if (tag == 6) return quick_flag;
	if (tag == 7) return quick_flag_ins;
	if (tag == 8) return quick_sort_stack;
	if (tag == 9) return quick_sort_stack_stl;
	if (tag == 10) return merge_top_down;
	if (tag == 11) return merge_bottom_up;
	//if (tag == 12) return NULL;
	//if (tag == 13) return NULL;
	if (tag == 14) return shell_sedj;
	if (tag == 15) return shell_knut;
	//if (tag == 16) return NULL;
	if (tag == 17) return heap;
	//if (tag == 18) return NULL;
	if (tag == 19) return comb_sort;
	if (tag == 20) return bubble;
	if (tag == 21) return selection;
	if (tag == 22) return insert;
	if (tag == 23) return insert_with_bar;

	return NULL; //не нашлось функции соответствующей данному номеру
}

int get_tag_of_sort(string name)
{
	//if (tag == 0) return NULL;
	if (name == "msd" || name == "MSD") return 1;
	if (name == "lsd") return 2;
	//if (tag == 3) return NULL;
	//if (tag == 4) return NULL;
	if (name == "qsort" || name == "quick") return 5;
	if (name == "flag" || name == "qflag" || name == "q_flag") return 6;
	if (name == "flagins" || name == "qflagins" || name == "q_flag_ins") return 7;
	if (name == "q_stack" || name == "qstack") return 8;
	if (name == "qstackstl") return 9;
	if (name == "merge" || name == "merge_td" || name == "mergetd") return 10;
	if (name == "merge_bu" || name == "mergebu") return 11;
	//if (tag == 12) return NULL;
	//if (tag == 13) return NULL;
	if (name == "shell" || name == "sedj" || name == "sh_sedj" || name == "shell_sedj") return 14;
	if (name == "knut" || name == "sh_knut" || name == "shell_knut") return 15;
	//if (tag == 16) return NULL;
	if (name == "heap") return 17;
	//if (tag == 18) return NULL;
	if (name == "comb" || name == "comb_sort" || name == "combsort") return 19;
	if (name == "bubble") return 20;
	if (name == "selection" || name == "select") return 21;
	if (name == "insert") return 22;
	if (name == "ins_bar" || name == "insbar" || name == "insertbar") return 23;

	return 0; //не нашлось функции соответствующей данному номеру
}
//возврашает название функции
string get_name_of_sort(int tag)
{
	//if (tag == 0) return NULL;
	if (tag == 1) return "MSD";
	if (tag == 2) return "LSD";
	//if (tag == 3) return NULL;
	//if (tag == 4) return NULL;
	if (tag == 5) return "qsort";
	if (tag == 6) return "q_flag";
	if (tag == 7) return "q_flag_ins";
	if (tag == 8) return "q_stack";
	if (tag == 9) return "q_stack_stl";
	if (tag == 10) return "merge_td";
	if (tag == 11) return "merge_bu";
	//if (tag == 12) return NULL;
	//if (tag == 13) return NULL;
	if (tag == 14) return "sh_sedj";
	if (tag == 15) return "sh_knut";
	//if (tag == 16) return NULL;
	if (tag == 17) return "heap";
	//if (tag == 18) return NULL;
	if (tag == 19) return "comb_sort";
	if (tag == 20) return "bubble";
	if (tag == 21) return "selection";
	if (tag == 22) return "insert";
	if (tag == 23) return "ins_bar";

	return "нет соотв. сортировки"; //не нашлось функции соответствующей данному номеру
}

void manager_of_command(int array_size = 1000, //начальный размер массива
						int count_of_tests = 10, //число тестов
						int module_of_ring = 100000, //модуль кольца
						int step = 1000, //шаг изменения размера массива
						int count_of_step = 10,//число шагов
						int precision = 1000000, //точность 1-нано 1000-микро 1000000-милли
						bool help = true)
{
	int *test_array; //массив для тестирования
	int type_of_sort[10];
	int count_of_sort = 0;
	string command;
	int par_command;

	if (help)
	{
		cout
		<< "Выход   " << "'ex'" << endl
		<< "Добавить сортировку   " <<"'номер'" << endl
		<< "Установить начальный размер массива   " <<"'size'" << endl
		<< "Установить число тестов   " <<"'test'" << endl
		<< "Установить модуль кольца Zn   " <<"'mod'" << endl
		<< "Запустить тестирование   " <<"'run'" << endl
		<< "Очистить список сортировок на тестирование  " <<"'clear'" << endl
		<< "Установить размер шага тестирования  " <<"'step'" << endl
		<< "Установить число шагов  " <<"'сstep'" << endl;
	}

	while (true)
	{

		cin >> command;
		if (command == "ex"){return;}
		if (command == "run")
		{
			if (count_of_sort == 0)
			{
				cout << "Нет сортировок для тестирования" << endl;
				continue;
			}

			//Шапка
			cout << "Число тестов: " << count_of_tests << endl;
			cout << "Модуль кольца: " << module_of_ring << endl;
			cout << endl << setw(15) << "SIZE       ";
			for (int i = 0; i < count_of_sort; i++)
				cout << setw(12) << get_name_of_sort(type_of_sort[i]);
			cout << endl;

			//Тестирование
			for (int j = 0, n = array_size; j < count_of_step; j++, n += step)
			{
				cout << setw(10) << n << setw(5) << " ";
				for (int i = 0; i < count_of_sort; i++)
				{
					cout << setw(12)
						 << get_time_of_work(
											get_addres_of_sort(type_of_sort[i]),
											test_array,
											n,
											module_of_ring,
											count_of_tests,
											precision);
				}

				cout << endl;
			}

			cout << "Тестирование завершено" << endl;
			cout << "Введите команду" << endl;
			continue;
			//cout << setw(5) << "n = " << setw(10) << n << " ";
		}

		if (command == "clear")
		{
			count_of_sort = 0;
			cout << "Список сортировок пуст" << endl;
			continue;
		}

		try
		{
			if (command == "size")
			{
				cout << "Введите размер массива" << endl;
				cin >> command;
				par_command = atoi(command.c_str());
				if (par_command > 0)
				{
					array_size = par_command;
					cout << "Размер массива установлен" << endl;
				}
				else
					cout << "Некорректная команда" << endl;
				continue;
			}

			if (command == "test")
			{
				cout << "Введите число тестов" << endl;
				cin >> command;
				par_command = atoi(command.c_str());
				if (par_command > 0)
				{
					count_of_tests = par_command;
					cout << "Число тестов установлено" << endl;
				}
				else
					cout << "Некорректная команда" << endl;
				continue;
			}

			if (command == "mod")
			{
				cout << "Введите модуль кольца Zn" << endl;
				cin >> command;
				par_command = atoi(command.c_str());
				if (par_command > 0)
				{
					module_of_ring = par_command;
					cout << "Модуль кольца установлен" << endl;
				}
				else
					cout << "Некорректная команда" << endl;
				continue;
			}

			if (command == "step")
			{
				cout << "Введите размер шага тестирования" << endl;
				cin >> command;
				par_command = atoi(command.c_str());
				if (par_command > 0)
				{
					step = par_command;
					cout << "Размер шага установлен" << endl;
				}
				else
					cout << "Некорректная команда" << endl;
				continue;
			}

			if (command == "cstep")
			{
				cout << "Введите число шагов" << endl;
				cin >> command;
				par_command = atoi(command.c_str());
				if (par_command > 0)
				{
					count_of_step = par_command;
					cout << "Число шагов установлено" << endl;
				}
				else
					cout << "Некорректная команда" << endl;
				continue;
			}

			if (command == "prec")
			{
				cout << "Введите точность" << endl;
				cin >> command;
				par_command = atoi(command.c_str());
				if (par_command > 0)
				{
					precision = par_command;
					cout << "Точность установлена" << endl;
				}
				else
					cout << "Некорректная команда" << endl;
				continue;
			}

			//если получено имя сортировки, получаем её номер
			//иначе пытаемся преобразовать строку в номер
			if (!(par_command = get_tag_of_sort(command)))
				par_command = atoi(command.c_str());

			if (get_addres_of_sort(par_command) != NULL)
			{
				if (count_of_sort < 10)
				{
					type_of_sort[count_of_sort] = par_command;
					count_of_sort++;
					cout << "'" << get_name_of_sort(par_command) << "'" << "добавлена" << endl;
				}
				else
					cout << "Нельзя тестировать больше 10 сортировок" << endl;
			}
			else
				cout << "Нет сортировки с таким номером" << endl;
		}
		catch(...)
		{
			cout << "Некорректная команда" << endl;
		}
		//cout << command << endl;
	}
}

int main()
{
	int array[N], *test, n;
	//manager_of_command(100000,25,100000,25000,10,10000,false);//ПК
	//manager_of_command(10000,25,100000,5000,10,100000,false);//android
	//return 0;
    cout << byte(0b10000000111001110000000000001111, 0) << endl;

    cout << byte(0b10000000111001110000000000001111, 1) << endl;

    cout << byte(0b10000000111001110000000000001111, 2) << endl;

    cout << byte(0b10000000111001110000000000001111, 3) << endl;
    //return 0;
	cout << "create array..." << endl;
	create_random_array(array, N, 1000);
	print_array(array, N);
	cout << "lsd:" << endl;
	lsd(array, N);
	print_array(array, N);
	cout << endl;
	return 0;
/*
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



	return 0;
}
