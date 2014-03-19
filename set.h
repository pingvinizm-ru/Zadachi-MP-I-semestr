#pragma once
#include <string>
using namespace std;

class set
{
	private:
		char arr[32];
	public:
		set();
		void add_symbol(char);
		void del_symbol(char);
		set operator + (set);
		set operator * (set);
		void print_symbols();
        void print_int_arr();
        int get_cardinal_number();
        //������������� ������� -> �� �������� ������� ������!!
        friend ostream &operator<< (ostream&, set);
        friend istream &operator>> (istream&, set&);
};

//костыль gcc android
