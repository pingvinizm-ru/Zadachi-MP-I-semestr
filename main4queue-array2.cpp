#include <iostream>
#include "queue-array2.h"

using namespace std;

int main()
{
	queue_array<int> a(10), b(200), c(100);
    int t;
    for (int i = 0; i < 10; i++)
    {
    	//cin >> t;
		a.push(i);
	}
	cout << "a:";
	a.print_queue();
	cout << "c = b = a = a" << endl;
	c = b = a = a;
	
	cout << "a:";	a.print_queue();
	cout << "b:";   b.print_queue();
	cout << "c:";   c.print_queue();

	cout << "auto del from a" << endl;
	for (int i = 0; i < 5; i++)
	{		
		cout << "pop = " << a.pop() << endl;		
	}

	cout << "add to queue" << endl;
	for (int i = 0; i < 5; i++)
	{
		cin >> t;
        a.push(t);
		//cout << "pop = " << a.pop() << endl;
		cout << "a:"; a.print_queue();
	}

	cout << "auto del from a" << endl;
	for (int i = 0; i < 10; i++)
	{		
		cout << "pop = " << a.pop() << endl;		
	}
	
	cout << "a:";	a.print_queue();
	cout << "b:";   b.print_queue();
	cout << "c:";   c.print_queue();
	
	cout << "add to queue" << endl;
	for (int i = 0; i < 5; i++)
	{
		cin >> t;
        a.push(t);
		//cout << "pop = " << a.pop() << endl;
		cout << "a:"; a.print_queue();
	}
	
	cout << "press any key" << endl;
    cin >> t;
	return 0;

}