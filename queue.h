//реализация очереди с помощью связного списка
#include <iostream>

using namespace std;

template <typename element>
struct record
{
	element data;
    struct record<element> *pointer;
};

template <typename element>
class queue
{
    private:
    	struct record<element> *begin;
        struct record<element> *end;
        int count_of_element;

    public:
        queue()
        {
        	begin = 0;//
            end = 0;
            count_of_element = 0;
        }

        ~queue()
        {
        	clear_queue();
        }

        void clear_queue()
        {
            struct record<element> *prev = 0, *curr;
            
        	for (curr = begin; curr != 0; curr = curr->pointer)
            {
                if (prev) delete prev;
                prev = curr;
            }
			
			begin = end = 0;
        }

        queue (const queue &x)
        {
			begin = 0;//
            end = 0;
            count_of_element = 0;
        	copy_queue(x);
        }

        queue operator= (const queue &x)
        {
        	if (this == &x) return *this;//защита от самокопирования
            clear_queue();	
            copy_queue(x);
            return *this;
        }

        void copy_queue(const queue &x)
        {
        	struct record<element> *p;
            element t;

            count_of_element = x.count_of_element;
         
            for (p = x.begin; p != 0; p = p->pointer)
            {
            	t = p->data;
            	push(t); //добавляем в конец очереди
            }
        }

        void print_queue()
        {
        	struct record<element> *p;
            for (p = begin; p != 0; p = p->pointer)
            {
                cout << p->data << " " ;
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
                if (end == 0)
                {
                	end = new struct record<element>;
                    end->data = x;
                    end->pointer = 0;
                    begin = end;
                }
                else
                {
                	end->pointer = new struct record<element>;
                    end->pointer->data = x;
                    end->pointer->pointer = 0;
                    end = end->pointer;
                }
                count_of_element++;
                return true;
            }
            catch(bad_alloc error) //отлов ошибки выделения памяти
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

                x = begin->data;
                if (begin->pointer == 0)//извлекается единственный элемент
                {
                	delete begin;
                    begin = end = 0;
                }
                else
                {
                	temp = begin->pointer;
                    delete begin;
                    begin = temp;
                }

            	count_of_element--;

            	return x;
            }
            else
            	throw exception();
        }

        bool is_empty()
        {
            return count_of_element;
        }
};