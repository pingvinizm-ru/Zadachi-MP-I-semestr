#include <iostream>

#include "list.h"

using namespace std;

int main()
{
	int t;

    list<int> a, b, c;

	cout << "add to a" << endl;
    for (int i = 0; i < 4; i++)
    {
    	cin >> t;
        a.add_record_to_head(t);
    }
    cout << "a : ";
    a.print_list();
	
    cout << "auto: add to head" << endl;
    for (int i = 0; i < 10; i += 2)
    	a.add_record_to_head(i);
	
	cout << "a : ";
	a.print_list();
	
    cout << "auto: add to tail" << endl;	
    for (int i = 20; i < 30; i += 2)
    	a.add_record_to_tail(i);

	cout << "a : ";
	a.print_list();

    cout << "|a| = " << a.get_count_of_element() << endl;
	cout << "a = a" << endl;
	a = a;
	cout << "a : ";
    a.print_list();
	cout << "auto add to b" << endl;
    b.add_record_to_head(120);
    b.add_record_to_head(123);
    b.add_record_to_head(193);
	cout << "b:";
	b.print_list();
	cout << "c = b = a" << endl;
    c = b = a;    
	cout << "b:";
	b.print_list();
	cout << "del from a" << endl;
    for (int i = 0; i < 3; i++)
    {
    	cin >> t;
        a.del_record(t);

        cout << "a : ";
        a.print_list();

        cout << "b : ";
    	b.print_list();

        cout << "c : ";
    	c.print_list();
    }

	cout << "del from b" << endl;
    for (int i = 0; i < 3; i++)
    {
    	cin >> t;
        b.del_record(t);

        cout << "a : ";
        a.print_list();

        cout << "b : ";
    	b.print_list();

        cout << "c : ";
    	c.print_list();
    }
    
    //cout << "b = ";
    //b.print_list();
	cout << "press any key" << endl;
    cin >> t;
	return 0;
}