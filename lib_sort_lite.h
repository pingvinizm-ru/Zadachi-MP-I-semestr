#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stack>
#include "stack-array.h" //для реализации быстрой сортировки без рекурсии можно использовать или свой стек или из STL
using namespace std;
////ПРОТОТИПЫ ФУНКЦИЙ////
//служебные
template <typename type> void exch(type &, type &); //обмен элементов

//интерфейсы
template <typename type> void quick_flag(type array[], unsigned int);//быстрая на 3 участка - голландский флаг
template <typename type> void merge_top_down(type array[], unsigned int);//Слиянием нисходящая
template <typename type> void shell_sedj(type array[], unsigned int);//сортировка Шелла - последовательность Седжвика
template <typename type> void shell_knut(type array[], unsigned int);//сортировка Шелла - последовательность Кнута
/////реализации////
//Варианты быстрой
template <typename type> void quick_sort_flag(type array[], int, int);//быстрая на 3 участка - голландский флаг
template <typename type> void quick_sort_stack(type array[], unsigned int); //без рекурсии с использованием своего стека
template <typename type> void quick_sort_stack_stl(type array[], unsigned int); //без рекурсии с использованием STL стека
//Слиянием
template <typename type> void mergesort_top_down(type array[], int, int); //Слиянием нисходящая
template <typename type> void merge_bottom_up(type array[], unsigned int); //Слиянием восходящая
template <typename type> void merge(type array[], int, int, int); //вспомогательная
//Шелла
template <typename type> void shell(type array[], unsigned int, int); //сортировка Шелла - выбор последовательности зависит от последнего параметра
//Пирамидальная
template <typename type> void heap(type array[], unsigned int); //Пирамидальная
template <typename type> void down_list(type array[], unsigned int, unsigned int); //вспомогательная
//Поразрядные
//lsd сортировка строк идет как отдельная программа, из-за специфики задачи

//вспомогательная функция - обмен элементов
template <typename type>
void exch(type &a, type &b)
{
	type temp = a;
	a = b;
	b = temp;
}

////ИНТЕРФЕЙСЫ////
template <typename type>
void quick_flag(type array[], unsigned int num) //интерфейс
{
	quick_sort_flag(array, 0, num - 1);
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
////END ИНТЕРФЕЙСЫ////

////РЕАЛИЗАЦИИ////
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

	--l; ++r;
	for (int i = left; i < l_flag; ++i, --l) exch(array[i], array[l]);
	for (int i = right; i > r_flag; --i, ++r) exch(array[i], array[r]);

	if (left < l) quick_sort_flag(array, left,  l);
	if (r < right) quick_sort_flag(array, r, right);
}

//В текущей верси библиотеки сделаны 
//две быстрые сортировки без рекурсии (STL стек, и свой стек)
//для сдачи можно использовать любую из них!
template <typename type> //быстрая сортировка без рекурсии, используется STL стек
void quick_sort_stack_stl(type array[], unsigned int num)
{
	stack<int> stack;
	//заносим в стек самый левый и самый правый индекс массива
	stack.push(0); stack.push(num - 1);

	while (!stack.empty()) //пока стек не пуст
	{
		//извлекаем из стека крайние границы, обрабатываемой области
		int right = stack.top();//получаем значение верхнего элемента
		stack.pop();//удаляем верхний из стека!
		int left = stack.top();
		stack.pop();
		int l = left, r = right;
		
		//вычисляем медиану - случайный элемент из данного диапазона
		type middle = array[rand() % (right - left) + left] ;

		while (1)
		{
			while (array[l] < middle) l++;
			while (array[r] > middle) r--;
			if (l >= r) break;

			exch(array[l], array[r]);
			l++;
			r--;
		}

		//заносим в стек,
		//на следующей итерации цикла эта часть массива будет обработана
		/*отступление: STL стек "бесконечен", и вероятность выбора неудачной медианы -> 0, поэтому не будем выбирать меньшую часть*/
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
	
	//заносим в стек самый левый и самый правый индекс массива
	stack.push(0); stack.push(num - 1);

	while (!stack.empty())
	{
		//извлекаем из стека крайние границы, обрабатываемой области
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
		
		//заносим в стек,
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

		for (int i = num - 1; i >= 1; --i)
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

