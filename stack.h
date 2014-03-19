//реализация стэка с помощью связного списка
#include <iostream>

using namespace std;

template <typename element>
struct record
{
	element data;
    struct record<element> *pointer;
};

template <typename element>
class stack
{
    private:
    	struct record<element> *top;
        int count_of_element;

    public:
        stack()
        {
        	top = 0;//
            count_of_element = 0;
        }

        ~stack()
        {
        	clear_stack();
        }

        void clear_stack()
        {
            struct record<element> *prev = 0, *curr;
            
        	for (curr = top; curr != 0; curr = curr->pointer)
            {
                if (prev) delete prev;
                prev = curr;
            }
			
			top = 0;
        }

        stack (const stack<element> &x)
        {
		    top = 0;//
            count_of_element = 0;
        	copy_stack(x);
        }

        stack operator= (const stack<element> &x)
        {
        	if (this == &x) return *this;
        	clear_stack();
            copy_stack(x);
            return *this;
        }

        void copy_stack(const stack<element> &x)
        {
        	struct record<element> *p;
            element t;

            count_of_element = x.count_of_element;

            for (p = x.top; p != 0; p = p->pointer)
            {
            	t = p->data;
            	push(t);
            }
        }

        void print_stack()
        {
        	struct record<element> *p;
            for (p = top; p != 0; p = p->pointer)
            {
                cout << p->data << " " ;
            	//cout << p->data << " " << p->pointer << endl;
            }
            cout << endl;
        }

        int get_count_of_element()
        {
            return count_of_element;
        }

        bool push(element x)
        {
        	try
        	{
            	struct record<element> *temp;
            	temp = top;
            	top = new struct record<element>;
            	top->data = x;
            	top->pointer = temp;
            	count_of_element++;
            	return true;
            }
            catch (bad_alloc error)
            {
            	return false;
            }
        }

        element pop()
        {
            if (count_of_element > 0)
            {
                struct record<element> *temp;
                element x;
                x = top->data;
            	temp = top->pointer;
                delete top;
                top = temp;
            	count_of_element--;
            	return x;
            }
            else
            {
            	throw exception();
            }
        }
};
 