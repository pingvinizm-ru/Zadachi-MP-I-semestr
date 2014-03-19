// tree_lite.cpp: определяет точку входа для консольного приложения.

#include "stdafx.h"
#include <iostream>
#include <cstdlib>

#include "binary_tree_lite.h"

using namespace std;

int main()
{
	binary_tree<int> a, b, c;
    int t;

	cout << "auto add to a" << endl;
    for (int i = 0; i < 15; i++)
    {
        a.add_leaf(rand() % 100);
    }
    a.print_tree();
	cout << "del from a" << endl;
    for (int i = 0; i < 10; i++)
    {
    	cin >> t;
    	a.del_leaf(t);
        cout << "a:" << endl;
		a.print_tree();
    }


	cout << "add to a" << endl;
    for (int i = 0; i < 5; i++)
    {
    	cin >> t;
    	a.add_leaf(t);
        cout << "a:" << endl;
		a.print_tree();
    }

    cout << "a:" << endl;
    a.print_tree();

    c = b = a = a;
    cout << "c = b = a = a" << endl;
    cout << "a:";
    a.print_tree();
    cout << "b:";
    b.print_tree();
    cout << "c:";
    c.print_tree();

	cout << "add to 'b'" << endl;
	for (int i = 0; i < 5; i++)
	{
		cin >> t;
		b.add_leaf(t);
	}

	cout << "add to 'c'" << endl;
	for (int i = 0; i < 5; i++)
	{
		cin >> t;
		c.add_leaf(t);
	}

    cout << "a:";
    a.print_tree();
    cout << "b:";
    b.print_tree();
    cout << "c:";
    c.print_tree();

	cout << "press any key" << endl;
    cin >> t;
	return 0;
}
