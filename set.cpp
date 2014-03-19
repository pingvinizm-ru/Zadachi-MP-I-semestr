//реализация функций класса множество
#include <iostream>
#include <string>
#include <sstream>
#include "set.h"

#define ARRAY_SIZE 32
#define BYTE_SIZE 8

using namespace std;

//конструктор
set::set()
{
	for(int i = 0; i < ARRAY_SIZE; ++i) arr[i] = 0;
}

//добавление элемента в множество
void set::add_symbol(char x)
{
	int t = x + 128;
    arr[t / BYTE_SIZE] |= (1 << (t % BYTE_SIZE));
}

//удаление элемента из множества
void set::del_symbol(char x)
{
	int t = x + 128;
    arr[t / BYTE_SIZE] &= ~(1 << (t % BYTE_SIZE));
}

//объединение
set set::operator+ (set x)
{
	set result;
	for(int i = 0; i < ARRAY_SIZE; ++i)
		result.arr[i] = arr[i] | x.arr[i];
	return result;
}

//пересечение
set set::operator* (set x)
{
	set result;
	for(int i = 0; i < ARRAY_SIZE; ++i)
    	result.arr[i] = arr[i] & x.arr[i];

	return result;
}

void set::print_symbols()
{
	unsigned char t;
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
    	t = arr[i];
    	for (int j = 0; j < BYTE_SIZE; ++j)
    	{
        	if (t % 2)
            	cout << (char)(i * BYTE_SIZE + j - 128)<< " ";

    		t >>= 1;
    	}
    }
    cout << "\n";
}

void set::print_int_arr()
{
	for (int i = 0; i < ARRAY_SIZE; ++i)
		cout << (int) arr[i] << " " ;
	cout << "\n";
}

//подсчет мощности множества
int set::get_cardinal_number()
{
	int result = 0, t;
    for (int i = 0; i < ARRAY_SIZE; ++i)
    	for (t = arr[i]; t; t >>= 1)
         	if (t % 2) ++result;

    return result;
}

//необязательно к реализации!
//вывод
ostream &operator<< (ostream &stream, set x)
{
	unsigned char t;
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
    	t = x.arr[i];
    	for (int j = 0; j < BYTE_SIZE; ++j)
    	{
        	if (t % 2)
            	stream << (char)(i * BYTE_SIZE + j - 128) << " ";

    		t >>= 1;
    	}
    }
    stream << "\n";
    return stream;
}

//необязательно к реализации!
//ввод
istream &operator>> (istream &stream, set &x)
{
	char c;
    int t;
    stream >> c;
    t = c + 128;
    x.arr[t / BYTE_SIZE] |= (1 << (t % BYTE_SIZE));
    return stream;
}
