#include <iostream>
#include <cstdlib>

#include "binary_tree.h"

using namespace std;

int main()
{
	binary_tree<int> a, b, c;
    int t;
    
	cout << "auto add to a" << endl;
    for (int i = 0; i < 25; i++)
    {
    	//cin >> t;
        a.add_leaf(rand() % 100);
        //a.add_leaf(t);
    }
    //a.clear_tree();
    //a = a;
    cout << "LeftRootRight a:"; a.print_tree(LEFT_ROOT_RIGHT);
    cout << "RootLeftRight a:"; a.print_tree(ROOT_LEFT_RIGHT);
	cout << "Graph tree a:" <<endl; a.print_tree(GRAPH_TREE);
    cout << "rotate element in a" << endl;
    for (int i = 0; i < 5; i++)
    {
    	cin >> t;
    	a.rotate_leaf(t);
		cout << "Graph tree a:\n"; a.print_tree(GRAPH_TREE);
		
    }


	cout << "del from a" << endl;
    for (int i = 0; i < 5; i++)
    {
    	cin >> t;
    	a.del_leaf(t);
		cout << "a:"; a.print_tree();
    }
    //a.print_root();

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