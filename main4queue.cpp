#include <iostream>
#include "queue.h"

using namespace std;

int main()
{
    int t;
	queue<int> a ,b;

	cout << "add to queue" << endl;
    for (int i = 0; i < 5; i++)
    {
    	cin >> t;
        a.push(t);
		cout << "a:";
        a.print_queue();
    }
    cout << endl;
	cout << "b = a" << endl;
    b = a;
	cout << "a:";
    a.print_queue();
	cout << "b:";
    b.print_queue();
	
	cout << "auto del from queue" << endl;
    for (int i = 0; i < 10; i++)
    {
    	try
    	{
        	t = a.pop();
			cout << "a:";
        	a.print_queue();
        }
        catch(...)
        {
        	cout << "exception" << endl;
        }
    }
	
	cout << "add to queue" << endl;
    for (int i = 0; i < 5; i++)
    {
    	cin >> t;
        a.push(t);
		cout << "a:";
        a.print_queue();
    }
	
	cout << "press any key" << endl;

	return 0;
}