//Лексикографическая сортировка строк с помощью поразрядной LSD сортировки
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

#define COUNT_OF_SYMBOLS 256

void lsd(string array[], int num)
{
	vector< list<string> > v;
	int depth = 0;

	v.resize(COUNT_OF_SYMBOLS); //устанавливаем размер вектора
	// предварительная подготовка
	for (int i = 0; i < num; i++)
	{
		v[0].push_back(array[i]); //заносим весь массив в нулевой список
		if (array[i].length() > depth) depth = array[i].length();//ищем макс. длину слова
	}

	//перебираем, начиная с последних букв
	for (depth = depth - 1; depth >= 0; depth--)
	{
		//разбиваем базовый список по соотв. букве
		list<string>::iterator i = v[0].begin();

		for (int k = 0; k < num; ++k)
		{
			if ((*i).size() > depth)
			{
				v[(*i)[depth] + 128].push_back(*i);//добавляем к соотв. списку
				i = v[0].erase(i);//удаляем из базового				
			}
			else
				i++;
		}

	    //добавляем к базовому списку все остальные
	    for (int i = 1; i < COUNT_OF_SYMBOLS; ++i)
	    	v[0].splice(v[0].end(), v[i]);
	}

	//записываем базовый список в массив
	list<string>::iterator i = v[0].begin();
	for (int k = 0; k < num; ++i, ++k)
	{
	    array[k] = *i;
		//cout << (*i) << ' ';
	}
}

int main()
{
    string s;
	string arr[10] = {"bac","abc","dbac","abc","aa","a","aaaa","adb","bd","dddd"};

	for (int i = 0; i < 10; i++) cout << arr[i] << " ";
	cout << endl;

	lsd(arr, 10);

	for (int i = 0; i < 10; i++) cout << arr[i] << " ";
	cout << endl;

	cout << "add strings to empty array" << endl;
	for (int i = 0; i < 10; i++)
	{
	    cin >> s;
	    arr[i] = s;
	}

	lsd(arr, 10);

	for (int i = 0; i < 10; i++) cout << arr[i] << " ";
	cout << endl;
	return 0;
}
