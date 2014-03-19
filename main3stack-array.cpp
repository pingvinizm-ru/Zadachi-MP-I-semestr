#include <iostream>
#include "stack-array.h"

using namespace std;

int main()
{
	stack_array<int> a(40), b(200), c(100);
    int t;
	cout << "[5..20] -> a" << endl;
    for (int i = 5; i < 20; i++)
    {    	
        a.push(i);        
    }	
    cout << "c = b = a = a" << endl;
    c = b = a = a;
    cout << "a:";
    a.print_stack();
    cout << "b:";
    b.print_stack();
	cout << "c:";
    c.print_stack();

    for (int i = 0; i < 10; i++)
    {
    	//cin >> t;
        cout << "pop x: " << a.pop() << endl;
        //a.print_array();
    }
    
    cout << "a:";
    a.print_stack();
    cout << "b:";
    b.print_stack();
	cout << "c:";
    c.print_stack();
	
	cout << "press any key" << endl;
    cin >> t;
	return 0;

}