//реализация списка с помощью массива
#include <iostream>
#define FREE_SPACE -1
#define END_OF_LIST -2
using namespace std;

template <typename element>
struct record
{
	element data;
    int next; //"указатель" на следующий элемент
};

template <typename element>
class list_array
{
    private:
    	struct record<element> *array; //массив элементов
        unsigned int head; //"указатель" на головной элемент
    	unsigned int max_size_of_list; //максимальный размер списка
        unsigned int size_of_list;//текущий размер списка
    public:
    	//конструктор
       	list_array(unsigned int max = 10500)
        {
        	head = 0;//указывает на нулевую ячейку массива
            size_of_list = 0;
            max_size_of_list = max;
            array = new struct record<element>[max_size_of_list];//выделение памяти
            for (int i = 0; i < max_size_of_list; i++)
            	array[i].next = FREE_SPACE;
        }

        //деструктор
        ~list_array()
        {
        	delete[]array;
        }

        //конструктор копирования
        list_array (const list_array &x)
        {
        	copy_list(x);
        }

        //оператор присваивания
        list_array operator= (const list_array &x)
        {
        	if (this == &x) return *this; //защита от самокопирования
        	delete[]array; //освобождение памяти
            copy_list(x);
            return *this;
        }

        //копирование списка-аргумента в текущий список
        void copy_list(const list_array &x)
        {
        	head = x.head;
            max_size_of_list = x.max_size_of_list;
            size_of_list = x.size_of_list;
            array = new struct record<element>[max_size_of_list];//выделение памяти 
        	for (int i = 0; i < max_size_of_list; i++) //копирование элементов
            	array[i] = x.array[i];
        }

	//добавление в список
        bool add_record(element x)
        {
            if (size_of_list < max_size_of_list)
            {
            	if (size_of_list == 0) //список пуст
                {
                	array[head].data = x;
                    array[head].next = END_OF_LIST;
                }
                else //список не пуст
                {   
                	for (int i = 0; i < max_size_of_list; i++) //поиск свободной ячейки
                    {
                        if (array[i].next == FREE_SPACE)
                    	{
                        	array[i].next = head;
                            array[i].data = x;
                            head = i;
                            break;
                    	}
                    }
                }
                size_of_list++;
            	return true;    
            }
            else
            	return false;
        }

	//удаление из списка
        bool del_record(element x)
        {
        	int prev = FREE_SPACE;
            for (int p = head; p != END_OF_LIST; p = array[p].next)
            {
            	if (array[p].data == x)//найден нужный элемент
                {
                	if (prev == FREE_SPACE)//предыдущий не существует
                    {
                    	if (size_of_list == 1)//список будет пуст после удаления
                        	head = 0;
                        else
                        	head = array[p].next;
                    	array[p].next = FREE_SPACE;

                    }
                    else
                    {
                    	array[prev].next = array[p].next;
                        array[p].next = FREE_SPACE;
                    }
                    size_of_list--;
                    return true;
                }
                prev = p;//предыдущий равен текущему - увеличиваем текущий
            }
            return false;
        }
        //распечатка списка
        void print_list()
        {
        	if (size_of_list > 0)
            {
            	for (int p = head; p != END_OF_LIST; p = array[p].next)
            	{
                	cout << array[p].data << " ";
            	}
            	cout << endl;
            }
            else
            	cout << "list is empty" << endl;
            //cout << head << " " << size_of_list << endl;
            
        }

        //отладочная функция
        void print_array()
        {
            for (int i = 0; i < max_size_of_list; ++i)
            {
                cout << array[i].data << " " << array[i].next << endl;
            }
        }

};