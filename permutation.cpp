//два алгоритма генерации перестановок
//		- с помощью использования поиска с возвратом (лексикографический порядок)
//		- с помощью смежных транспозиций
#include <iostream>
#include <vector>
#include <list>
using namespace std;

//вычисление факториала n
long long factorial(int n)
{
    long long result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}
//генерация перестановок с помощью использования поиска с возвратом
vector< vector<int> > generate_using_backtracking(int n) //n - мощность множества
{
    int i, j, k, m, t;
    vector< vector<int> > v;
    int power_of_set = factorial(n);

    v.resize(power_of_set);

    //создаем базовую перестановку = 1 2 3 ... n
    v[0].resize(n);
    for (i = 0; i < n; i++) v[0][i] = i + 1;

    n--;//теперь n - индекс самого правого элемента

    for (k = 1; k < power_of_set; k++) //от 1 до числа всех перестановок
    {
        v[k].resize(n); //задаем размер выделенной памяти

        v[k] = v[k-1]; //текущая = предыдущей

		//ищем индекс элемента - "первый на спаде холма"
		//т.е в перестановке 3 1 6 5 8 7 2 это 5
        for (i = n - 1; v[k][i] > v[k][i+1]; i--);

		//ищем первый элемент в "холме", который > i-го
		//т.е в перестановке 3 1 6 5 8 7 2 это 7
        for (j = n; v[k][i] > v[k][j]; j--);

        //меняем i и j элементы
		//т.е из перестановки 3 1 6 5 8 7 2 получаем 3 1 6 7 8 5 2
        t = v[k][i];
        v[k][i] = v[k][j];
        v[k][j] = t;

        //реверсируем "холм"
		//т.е из перестановки 3 1 6 7 8 5 2 получаем 3 1 6 7 2 5 8
        m = (n-i)/2; //длина половины "холма"
        for (j = 0; j < m; j++)
        {
            t = v[k][j+i+1];
            v[k][j+i+1] = v[k][n-j];
            v[k][n-j] = t;
        }
    }
    return v;
}

//генерация перестановок с помощью смежных транспозиций
list< vector<int> > generate_using_transposition(int n)
{
    vector<int> temp;
    list< vector<int> > l1, l2;

	temp.resize(n);
	temp[0] = 1;
	l1.push_back(temp); //заносим подстановку {1} в первый список
    //
    for(int k = 1; k < n; k++) //перебираем все элементы множества, на котором задана перестановка
    {
    	list< vector<int> >::iterator i;
    	for (i = l1.begin(); i != l1.end(); i++) //перебираем первый список
    	{
    		temp = *i;
    		temp[k] = k + 1;//"добавляем" новый элемент в каждую перестановку
    		l2.push_back(temp);//заносим во второй список

    		for (int j = k; j > 0; j--) //применяем k-1 транспозицию к перестановке
    		{
    			int t = temp[j];
    			temp[j] = temp[j-1];
    			temp[j-1] = t;
    			l2.push_back(temp); //после транспозиции заносим во второй
    		}
    	}
    	l1 = l2; //первый становится вторым
    	l2.clear(); //второй становится пустым
    }

    return l1;
}

int main()
{
    int n = 1;
    vector< vector<int> > a;
    list< vector<int> > l;
    a = generate_using_backtracking(n);

    for (int i = 0; i < factorial(n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl;
    l = generate_using_transposition(n);

    list< vector<int> >::iterator i;
    for (i = l.begin(); i != l.end(); i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << (*i)[j] << ' ';
        }
        cout << endl;
    }
}
