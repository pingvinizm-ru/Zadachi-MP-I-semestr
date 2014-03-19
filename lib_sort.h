#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#include "stack-array.h"
using namespace std;
////ПРОТОТИПЫ ФУНКЦИЙ////
//служебные
template <typename type> void exch(type &, type &);
template <typename type> void comp_exch(type &, type &);

//интерфейсы
template <typename type> void msd(type array[], unsigned int); //поразрядная MSD сортировка
template <typename type> void lsd(type array[], unsigned int);
template <typename type> void quick(type array[], unsigned int); //быстрая на 2 участка
template <typename type> void quick_flag(type array[], unsigned int);//быстрая на 3 участка - голландский флаг
template <typename type> void quick_flag_ins(type array[], unsigned int);// на 3 участка с сортировкой вставками малых участков
template <typename type> void merge_top_down(type array[], unsigned int);//Слиянием нисходящая
template <typename type> void shell_sedj(type array[], unsigned int);//сортировка Шелла - последовательность Седжвика
template <typename type> void shell_knut(type array[], unsigned int);//сортировка Шелла - последовательность Кнута
template <typename type> void insert(type array[], unsigned int);//Вставками
//STL интерфейсы
//template <typename type> void stl_qsort(type array[], unsigned int);//
//template <typename type> void stl_heap(type array[], unsigned int);//

/////реализации////
///Логарифмические - O(n*log n)
//поразрядные
template <typename type> void msd_sort(type array[], int, int, int); //поразрядная MSD сортировка
template <typename type> void lsd_sort(type array[], int, int, int); //поразрядная LSD сортировка
//Варианты быстрой
template <typename type> void quick_sort(type array[], int, int); //быстрая на 2 участка
template <typename type> void quick_sort_flag(type array[], int, int);//быстрая на 3 участка - голландский флаг
template <typename type> void quick_sort_flag_ins(type array[], int, int);// на 3 участка с сортировкой вставками малых участков
template <typename type> void quick_sort_stack(type array[], unsigned int); //без рекурсии с использованием стэка
//Слиянием
template <typename type> void mergesort_top_down(type array[], int, int); //Слиянием нисходящая
template <typename type> void merge_bottom_up(type array[], unsigned int); //Слиянием восходящая
template <typename type> void merge(type array[], int, int, int); //вспомогательная
//Шелла
template <typename type> void shell(type array[], unsigned int, int); //сортировка Шелла - выбор последовательности зависит от последнего параметра
//Пирамидальная
template <typename type> void heap(type array[], unsigned int); //Пирамидальная
template <typename type> void down_list(type array[], unsigned int, unsigned int); //вспомогательная
//Расчесткой
template <typename type> void comb_sort(type array[], unsigned int); //Пирамидальная
///Квадратичные - O(n^2)
template <typename type> void bubble(type array[], unsigned int);//Пузырьковая
template <typename type> void selection(type array[], unsigned int);//Выбором
template <typename type> void insert_sort(type array[], int, int);//Вставками
template <typename type> void insert_with_bar(type array[], unsigned int);//Вставками с барьером

//вспомогательная функция - безусловный обмен
template <typename type>
void exch(type &a, type &b)
{
	type temp = a;
	a = b;
	b = temp;
}

//вспомогательная функция - условный обмен
template <typename type>
void comp_exch(type &a, type &b)
{
	if (a > b) exch(a, b);
}

////ИНТЕРФЕЙСЫ////
template <typename type> //Поразрядная MSD сортировка
void msd(type array[], unsigned int num) //интерфейс
{
	msd_sort(array, 0, num-1, 0);
}

template <typename type> //Поразрядная LSD сортировка
void lsd(type array[], unsigned int num) //интерфейс
{
	lsd_sort(array, 0, num-1, 3);
}

template <typename type> //быстрая сортировка
void quick(type array[], unsigned int num) //интерфейс
{
	quick_sort(array, 0, num - 1);
}

template <typename type>
void quick_flag(type array[], unsigned int num) //интерфейс
{
	quick_sort_flag(array, 0, num - 1);
}

template <typename type>
void quick_flag_ins(type array[], unsigned int num) //интерфейс
{
	quick_sort_flag_ins(array, 0, num - 1);
}

template <typename type> //сортировка слиянием
void merge_top_down(type array[], unsigned int num) //интерфейс
{
	mergesort_top_down(array, 0, num - 1);
}

template <typename type> //сортировка Шелла - последовательность Седжвика
void shell_sedj(type array[], unsigned int num)
{
		shell(array, num, 0);
}

template <typename type> //сортировка Шелла - последовательность Кнута
void shell_knut(type array[], unsigned int num)
{
		shell(array, num, 1);
}

template <typename type> //сортировка вставками
void insert(type array[], unsigned int num)
{
	insert_sort(array, 0, num - 1);
}

//STL интерфейсы
/**/
////END ИНТЕРФЕЙСЫ////

////РЕАЛИЗАЦИИ////
#define BASE 256
#define MAX_SIZE 1000000
const int size_of_char = sizeof(char);
const int size_of_long = sizeof(int);
//вспомогательная функция: возвращает значение определенного байта
inline int byte(int x, int pos) {return (x >> (size_of_long - pos - 1)*8) & 255;}

template <typename type>
void msd_sort(type array[], int left, int right, int depth)
{
	int i, j, count[BASE + 1];
	static type temp[MAX_SIZE];
	int bytes_in_type = sizeof(type);//число байт в сортируемом типе данных

	if (depth > bytes_in_type) return;
	if (left >= right) return;
	if (right - left < 128) //оптимизация малых участков сортировкой вставками
	{
		//insert_sort(array, left, right);
		//return;
	}
	for (i = 0; i < BASE; i++) count[i] = 0;

	//определяем число элементов в каждом контейнере
	for (i = left; i <= right; i++) count[byte(array[i], depth) + 1]++; //+1 т.к. "первый контейнер" начинается с 0

	//устанавливаем границы
	for (i = 1; i < BASE; i++) count[i] += count[i - 1];

	//заносим элементы, распределенные по контейнерам во временный массив
	for (i = left; i <= right; i++)
		//при занесении элемента, увеличиваем границу соотв. контейнера
		temp[left + count[byte(array[i], depth)]++] = array[i];

	for (i = left; i <= right; i++) array[i] = temp[i];

	//запускаем рекурсию...
	//"первый" контейнер
	msd_sort(array, left, left + count[0] - 1, depth + 1);
	//остальные контейнеры
	for (i = 0; i < BASE - 1; i++)
		msd_sort(array, left + count[i], left + count[i+1] - 1, depth + 1);

}

template <typename type> //LSD  сортировка
void lsd_sort(type array[], int left, int right, int depth = 3)
{
	int i, j, count[BASE + 1];
	static type temp[MAX_SIZE];
	//int bytes_in_type = sizeof(type);//число байт в сортируемом типе данных

	if (depth < 0) return;
	if (left >= right) return;
	if (right - left < 16) //оптимизация малых участков сортировкой вставками
	{
		insert_sort(array, left, right);
		return;
	}
	for (i = 0; i < BASE; i++) count[i] = 0;

	//определяем число элементов в каждом контейнере
	for (i = left; i <= right; i++) count[byte(array[i], depth) + 1]++; //+1 т.к. "первый контейнер" начинается с 0

	//устанавливаем границы
	for (i = 1; i < BASE; i++) count[i] += count[i - 1];

	//заносим элементы, распределенные по контейнерам во временный массив
	for (i = left; i <= right; i++)
		//при занесении элемента, увеличиваем границу соотв. контейнера
		temp[left + count[ byte(array[i], depth)]++] = array[i];

	for (i = left; i <= right; i++) array[i] = temp[i];

	//запускаем рекурсию...
	lsd_sort(array, left, right, depth - 1);
}

template <typename type>
void quick_sort(type array[], int left, int right)
{
	int l = left, r = right;
	type middle = array[rand() % (right - left) + left] ; //среднее значение

	while (1)
	{
		while (array[l] < middle) l++;
		while (array[r] > middle) r--;
		if (l >= r) break;

		exch(array[l], array[r]);
		l++;
		r--;
	}

	if (left < l - 1) quick_sort(array, left,  l - 1);
	if (r + 1 < right) quick_sort(array, r + 1, right);
}

template <typename type>
void quick_sort_flag(type array[], int left, int right)
{
	int l = left, r = right, l_flag = left, r_flag = right;
	type middle = array[rand() % (right - left) + left] ; //среднее значение
	//cout << "middle = " << middle << endl;

	while (1)
	{
		while (array[l] < middle) l++;
		while (array[r] > middle) r--;
		if (l >= r) break;

		exch(array[l], array[r]);

		if (array[l] == middle)
		{
			exch(array[l_flag], array[l]);
			l_flag++;
		}

		if (array[r] == middle)
		{
			exch(array[r_flag], array[r]);
			r_flag--;
		}

		l++;
		r--;
	}
	/*
	for (int i = 0; i < right+1; ++i) cout << array[i] << " ";

	cout << endl;
	cout << "l = " << l << " r = " << r << endl;
	cout << "l_flag = " << l_flag << " r_flag = " << r_flag << endl;
	cout << "left = " << left << " right = " << right << endl;
	*/
	--l; ++r;
	for (int i = left; i < l_flag; ++i, --l) exch(array[i], array[l]);
	for (int i = right; i > r_flag; --i, ++r) exch(array[i], array[r]);
	/*
	cout << "l = " << l << " r = " << r << endl;
	cout << "l_flag = " << l_flag << " r_flag = " << r_flag << endl;
	cout << "left = " << left << " right = " << right << endl;
	*/
	if (left < l) quick_sort_flag(array, left,  l);
	if (r < right) quick_sort_flag(array, r, right);
}

template <typename type>
void quick_sort_flag_ins(type array[], int left, int right)
{
	const int small = 16;
	int l = left, r = right, l_flag = left, r_flag = right;
	type middle = array[rand() % (right - left) + left] ; //среднее значение

	if (right - left <= small)
	{
		insert_sort(array, left, right);
		return;
	}

	while (1)
	{
		while (array[l] < middle) l++;
		while (array[r] > middle) r--;
		if (l >= r) break;

		exch(array[l], array[r]);

		if (array[l] == middle)
		{
			exch(array[l_flag], array[l]);
			l_flag++;
		}

		if (array[r] == middle)
		{
			exch(array[r_flag], array[r]);
			r_flag--;
		}

		l++;
		r--;
	}

	--l; ++r;
	for (int i = left; i < l_flag; ++i, --l) exch(array[i], array[l]);
	for (int i = right; i > r_flag; --i, ++r) exch(array[i], array[r]);

	if (left < l) quick_sort_flag_ins(array, left,  l);
	if (r < right) quick_sort_flag_ins(array, r, right);
}

template <typename type> //быстрая сортировка без рекурсии, используется STL стек
void quick_sort_stack_stl(type array[], unsigned int num)
{
	stack<int> stack;
	//заносим в стэк самый левый и самый правый индекс массива
	stack.push(0); stack.push(num - 1);

	while (!stack.empty())
	{
		//извлекаем из стэка крайние границы, обрабатываемой области
		int right = stack.top();//получаем значение верхнего элемента
		stack.pop();//удаляем верхний из стека!
		int left = stack.top();
		stack.pop();
		int l = left, r = right;
		type middle = array[rand() % (right - left) + left] ; //среднее значение

		while (1)
		{
			while (array[l] < middle) l++;
			while (array[r] > middle) r--;
			if (l >= r) break;

			exch(array[l], array[r]);
			l++;
			r--;
		}

		//заносим в стэк,
		//на следующей итерации цикла эта часть массива будет обработана
		/*отступление: STL стек "бесконечен", и вероятность выбора неудачной медианы -> к 0, не будем выбирать меньшую часть*/
		if (left < l - 1)
		{
			stack.push(left);
			stack.push(l - 1);
		}
		if (r + 1 < right)
		{
			stack.push(r + 1);
			stack.push(right);
		}
	}
}

template <typename type> //быстрая сортировка без рекурсии, используется собственный стек
void quick_sort_stack(type array[], unsigned int num)
{
	//при использовании собственного стека проигрыш ~20-30%
	//при использовании stl стека проигрыш ~50-70%
	stack_array<int> stack((int) 3 * (log(num)/log(2))); // = 3*log2(num) //хватит 2 двоичных логарифмов, 3 с запасом

	//заносим в стэк самый левый и самый правый индекс массива
	stack.push(0); stack.push(num - 1);

	while (!stack.empty())
	{
		//извлекаем из стэка крайние границы, обрабатываемой области
		int right = stack.pop();
		int left = stack.pop();
		int l = left, r = right;
		type middle = array[rand() % (right - left) + left] ; //среднее значение

		while (1)
		{
			while (array[l] < middle) l++;
			while (array[r] > middle) r--;
			if (l >= r) break;

			exch(array[l], array[r]);
			l++;
			r--;
		}

		//заносим в стэк,
		//на следующей итерации цикла эта часть массива будет обработана
		if ((l-1-left) > (right-r-1)) //сначала выбираем для обработки меньшую часть
		{
			//левая больше чем правая
			//заносим в стек левую, а потом правую
			//при следующем проходе будет выбрана
			//меньшая - правая часть
			if (left < l - 1)
			{
				stack.push(left);
				stack.push(l - 1);
			}
			if (r + 1 < right)
			{
				stack.push(r + 1);
				stack.push(right);
			}
		}
		else
		{
			//правая больше левой
			if (r + 1 < right)
			{
				stack.push(r + 1);
				stack.push(right);
			}
			if (left < l - 1)
			{
				stack.push(left);
				stack.push(l - 1);
			}
		}
	}
}


//нисходящая
template <typename type>
void mergesort_top_down(type array[], int left, int right)
{
	if (right <= left) return;
	int median = (left+right)/2;
	mergesort_top_down(array, left, median);
	mergesort_top_down(array, median + 1, right);
	merge(array, left, median, right); // => min размер сортируемого подмассива = 2
}

//восходящая
template <typename type>
void merge_bottom_up(type array[], unsigned int num)
{
	num--;//становится индексом самой правой ячейки
	for (int step = 1; step <= num; step *= 2) //идем двоичными шагами
	{
		for (int i = 0; i <= num - step; i += 2 * step) //перебираем шагами удвоенного размера
		{
			merge(array, i, i + step - 1, (i+2*step - 1 < num)?(i+2*step - 1):(num));
			//правый край выбираем исходя из того, поместится ли еще один блок, или нужно сортировать до края массива
		}
	}
}

//вспомогательная - объединение двух подфайлов
#define MAX_SIZE_OF_ARRAY 1000000
template <typename type>
void merge(type array[], int left, int median, int right)
{
	int i, j, k;
	static type temp_array[MAX_SIZE_OF_ARRAY]; //макс. размер временного = макс. размеру сортируемого массива

	for (i = median;     i >= left;  --i) temp_array[i] = array[i];
	for (j = median + 1; j <= right; ++j) temp_array[right + median + 1 - j] = array[j];
	//array = 1,3,5,2,4,8
	//temp  = 1,3,5,8,4,2
	//i = -1; j = 6;
	i = left; j = right;

	for (k = left; k <= right; k++)
		if (temp_array[j] < temp_array[i])
			array[k] = temp_array[j--];
		else
			array[k] = temp_array[i++];
	//array = 1,2,3,4,5,8


}

template <typename type>
void shell(type array[], unsigned int num, int type_of_seq = 0)
{

	int seq[40] = {0};
	int p1 = 1, p2 = 1, p3 = 1, s = 0, d;

	if (type_of_seq == 0) //создаем последовательность Седжвика
	{
		do
		{
			if (s % 2) //нечетные
			{
				seq[s] = 8*p1 - 6*p2 + 1;
				p3 *= 2;
			}
			else //четные
			{
				seq[s] = 9*p1 - 9*p3 + 1;
				p2 *= 2;
			}
			p1 *= 2;
		}
		while (seq[s++] * 3 < num);
	}

	if (type_of_seq == 1) //создаем последовательность Кнута
	{
		seq[0] = 1;
		for (s = 1; seq[s - 1] * 3 < num; s++) seq[s] = seq[s - 1] * 3 + 1;
	}

	//отладочный вывод последовательностей
	//for (int i = 0; i < s; ++i) cout << seq[i] << " ";
	//cout << endl;

	while (s >=0)
	{
		d = seq[s--];
		int i, j;
		for (i = d; i < num; i++)
		{
			type temp = array[i];
			for (j = i - d; j >= 0 && array[j] > temp; j -= d)
				array[j + d] = array[j];

			array[j + d] = temp;
		}
	}
}

//пирамидальная сортировка
template <typename type>
void heap(type array[], unsigned int num)
{
		for (int i = (num / 2) - 1; i >= 0; --i)
			down_list(array, i, num);

		for (int i = num - 1; i > 1; --i)
		{
			type temp = array[0];
			array[0] = array[i];
			array[i] = temp;

			down_list(array, 0, i);
		}
}

template <typename type> //вспомогательная функция пирамидальной сортировки - просеивание вниз
void down_list(type array[], unsigned int index, unsigned int num)
{
	int num_max = index;

	while (true)
	{
		int children_index = 2 * index + 1;

		if (children_index < num) //левая ветвь
			if (array[children_index] > array[num_max])
				num_max = children_index;

		children_index++;

		if (children_index < num) //правая ветвь
			if (array[children_index] > array[num_max])
				num_max = children_index;

		if (num_max == index) return; //корень больше листьев

		type temp = array[index];
		array[index] = array[num_max];
		array[num_max] = temp;

		index = num_max;
	}
}

//сортировка расчесткой
template <typename type>
void comb_sort(type array[], unsigned int num)
{
    const float delta = 1.24733;
    int step = num;
    bool swapped = true;

    while (step > 1 || swapped) //пока производились перестановки или не была проезведена окончательная сортировка пузырьком
    {
        swapped = false; //перестановок не производилось
        if (step > 1) step /= delta;
        for (int i = 0; i+step < num; i++)
            if (array[i] > array[i+step])
            {
                comp_exch(array[i], array[i+step]);
                swapped = true; //произведена перестановка элементов
            }

    }
}

//пузырьковая сортировка
template <typename type>
void bubble(type array[], unsigned int num)
{
	//Простейшая реализация
	/*
	for (int i = 0; i < num; ++i)
		for (int j = 0; j < num - 1; ++j)
			comp_exch(array[j], array[j + 1]);
	*/

	//Оптимизированная версия 1
	for (int i = 0; i < num; ++i)
	{
		bool c = false;
		for (int j = 0; j < num - 1 - i; ++j)
			if (array[j] > array[j + 1])
			{
				exch(array[j], array[j + 1]);
				c = true;
			}
		if (c == false) break;
	}
	//Оптимизированная версия 2
	/*
	 *
	 */
}
//сортировка выбором
template <typename type>
void selection(type array[], unsigned int num)
{
	for (int i = 0; i < num - 1; ++i)
	{
		int min = i;

		for (int j = i + 1; j < num; ++j)
			if (array[j] < array[min]) min = j; //запоминаем индекс мин. элемента

		exch(array[i], array[min]); //ставим на текущее место минимальный
	}
}

//сортировка вставками
template <typename type>
void insert_sort(type array[], int left, int right)
{
	int i, j;
	for (i = left + 1; i <= right; ++i)
	{
		type temp = array[i];
		for (j = i - 1; j >= left && array[j] > temp; --j)
			array[j + 1] = array[j];

		array[j + 1] = temp;
	}
}

//сортировка вставками с барьером
template <typename type>
void insert_with_bar(type array[], unsigned int num)
{
	int i, j;
	type zero_element = array[0]; //сохранили нулевую ячейку массива

	//отсортируем весь массив, кроме нулевой ячейки
	//нулевую используем как временную переменную
	for (i = 1; i < num; ++i)
	{
		array[0] = array[i];
		for (j = i - 1; array[j] > array[0]; --j)
			array[j + 1] = array[j];

		array[j + 1] = array[0];
	}

	//ищем подходящее место для нулевого элемента
	//и сдвигаем налево элементы массива перед ним
	for (i = 1; array[i] < zero_element && i < num; ++i)
		array[i - 1] = array[i];

	// в нужное место нулевой элемент
	array[i - 1] = zero_element;
}
