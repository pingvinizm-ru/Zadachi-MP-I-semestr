//реализация списка с помощью связных структур
#include <iostream>

using namespace std;

template <typename element>
struct record
{
	element data;
    struct record<element> *pointer;
};

template <typename element>
class list
{
    private:
    	struct record<element> *head; //указатель на начальный элемент списка
        int count_of_element; //число элементов в списке на текущий момент
    public:
        list() //конструктор
        {
        	head = 0;//
            count_of_element = 0;
        }

        ~list() //деструктор
        {
        	del_list();
        }

        void del_list()
        {
            struct record<element> *prev = 0, *curr;
            //начиная с головы, пока не дойдем до указателя = 0
        	for (curr = head; curr != 0; curr = curr->pointer)
            {
                if (prev) delete prev; //если предыдущий элемент существует
                prev = curr; //предыдущий равен текущему
            }
			
			head = 0; //начального элемента не существует
        }

	//конструктор копирования
        list (const list<element> &x)
        {
            head = 0;//
            count_of_element = 0;
        	copy_list(x);
        }

        list operator= (const list<element> &x)
        {
        	if (this == &x) return *this; //защита от самокопирования
        	del_list();
            copy_list(x);
            return *this;
        }

        void copy_list(const list<element> &x)
        {
        	struct record<element> *p;
            element t;

            count_of_element = x.count_of_element;
           
            for (p = x.head; p != 0; p = p->pointer)
            {
            	t = p->data; //извлекаем данные из копируемого списка
            	add_record_to_tail(t); //добавляем в текущий список
				//или add_record_to_head в зависимости от требований к эффективности или упорядоченности
            }
        }

    	bool add_record_to_head(element x)
        {
        	try
        	{
        		struct record<element> *temp;
           	 temp = head; //сохраняем указатель на текущий начальный элемент списка
            	head = new struct record<element>; //создаем новый
            	head->data = x; //заносим данные в новый
            	head->pointer = temp; //указатель в новом на "старый" начальный
            	count_of_element++; //увеличиваем число элементов
            	return true;
            }
            catch(bad_alloc error)
            {
          		return false;
            }
        }
		
	//необязательно к реализации!
    	void add_record_to_tail(element x)
        {
        	struct record<element> *temp, *p;

            if (head) //если список не пуст
            {
            	for (p = head; p->pointer != 0; p = p->pointer); //пробегаем весь список до последнего элемента

            	p->pointer = new struct record<element>; //указатель в последнем элементе на новый элемент
            	p->pointer->data = x;
            	p->pointer->pointer = 0; //указатель в новом элементе равен 0 - конец списка
                count_of_element++;
            }
            else //иначем пользуемся готовой функцией
            	add_record_to_head(x);
        }

	//необязательно к реализации!
		//добавление с учетом значения 
		//(предполагается, что список уже упорядочен, т.е добавление элементов шло только через эту функцию)
        void add_record_with_sort(element x)
        {
        	struct record<element> *prev = 0, *curr;

            //если список пуст
            if (head == 0)
            {
            	add_record_to_head(x);
               	return;
            }

        	for (curr = head; curr != 0 ; curr = curr->pointer)
            {
            	//смотрим до тех пор, пока не найдем элемент больше(меньше) "x"
            	if (curr->data > x) //или < x
                {
                	if (prev) //если предыдущий существует
                    {
                    	prev->pointer = new struct record<element>;;
                        prev->pointer->data = x;
                    	prev->pointer->pointer = curr;
                        count_of_element++;
                    }
                    else //добавляем к началу
                    	add_record_to_head(x);

                    return;
                }
                prev = curr;
            }
            //если элемент до сих пор не добавлен - он наибольший -> добавляем в конец
            add_record_to_tail(x);//короче, но потребуется новый перебор списка
			//или
			//prev->pointer = new struct record<element>;;
            //prev->pointer->data = x;
            //prev->pointer->pointer = 0;
            //count_of_element++;
			
			return;
        }

        bool del_record(element x)
        {
            struct record<element> *prev = 0, *curr;

			//перебираем элементы списка
        	for (curr = head; curr != 0 ; curr = curr->pointer)
            {
            	if (curr->data == x) //нашли нужный
                {
                	if (prev) //если предыдущий существует
                    	prev->pointer = curr->pointer;
                    else 
                    	head = curr->pointer;

                    delete curr;//освобождаем память
                    count_of_element--;//уменьшаем значение числа элементов
                    return true;
                }
                prev = curr;
            }

            return false;
        }

        void print_list()
        {
        	struct record<element> *p;
            for (p = head; p != 0; p = p->pointer)
            {
                cout << p->data << " " ;            	
            }
            cout << endl;
        }

        bool search(element x)
        {
        	struct record<element> *temp, *p;
            for (p = head; p != 0; p = p->pointer)
                if (p->data == x) return true;

            return false;
        }

        int get_count_of_element()
        {
            return count_of_element;
        }
};