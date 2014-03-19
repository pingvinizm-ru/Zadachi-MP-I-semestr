#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    int t;
	stack<int> a;

	cout << "push element to a" << endl;
    for (int i = 0; i < 5; i++)
    {
    	std::cin >> t;
        a.push(t);
        a.print_stack();
    }
	
	cout << "a.pop() a.pop()" << endl;
    for (int i = 0; i < 12; i++)
    {
    	try
    	{
        cout << a.pop() << endl;
        }
        catch (exception)
        {
        	cerr << "error: stack is empty" << endl;
        }
             
    }
	cout << "a:";
	a.print_stack();
	
	cout << "push element to a" << endl;
    for (int i = 0; i < 5; i++)
    {
    	std::cin >> t;
        a.push(t);
        a.print_stack();
    }
	
	cout << "press any key" << endl;

return 0;
}