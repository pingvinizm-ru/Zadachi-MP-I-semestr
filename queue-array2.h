//реализация очереди в виде массива с "кольцевой организацией"
#include <iostream>
using namespace std;

template <typename element>
class queue_array
{
    private:
    	element *array; //массив элементов
		unsigned int begin; //"указатель" на начальный элемент
		unsigned int end; //"указатель" на пустой элемент, следующий за последним
    	unsigned int max_size_of_queue; //макимальное число элементов в очереди
        unsigned int size_of_queue;//текущий размер очереди
    public:
    	//конструктор
        queue_array(unsigned int max = 100500)
        {
        	begin = end = 0;
			size_of_queue = 0;
            max_size_of_queue = max;
            array = new element[max_size_of_queue];
        }

        //деструктор
        ~queue_array()
        {
        	delete[]array;
        }

        //конструктор копировния
        queue_array (const queue_array &x)
        {
        	copy_queue(x);
        }

        //оператор присваивания
        queue_array operator= (const queue_array &x)
        {
        	if (this == &x) return *this; //защита от самокопировния
        	delete[]array; //освобождение выделенной памяти
            copy_queue(x);
            return *this;
        }

        //копирование очереди-аргумента в текущую очередь
        void copy_queue(const queue_array &x)
        {
			begin = x.begin;
			end = x.end;
            max_size_of_queue = x.max_size_of_queue;
            size_of_queue = x.size_of_queue;
            array = new element[max_size_of_queue];//выделение пмяти под новый размер очереди
        	for (int i = 0; i < max_size_of_queue; i++)
            	array[i] = x.array[i];
        }

		//добавление в хвост очереди
        bool push(element x)
        {
            if (size_of_queue <= max_size_of_queue)
            {
                array[end] = x; //заносим элемент    	
                end++; //переходим на следующую ячейку
                end %= max_size_of_queue;//берем модуль по размеру массива, образуется кольцо
                size_of_queue++;
                return true;
            }
            else
            	return false;
        }
		
		//извлечение элемента
		element pop()
    	{
        	if (size_of_queue > 0)
			{
				element result = array[begin];
				begin++;
				begin %= max_size_of_queue;         
            	size_of_queue--;
        		return result;
			}
			else
				throw exception();
		}
        //печать очереди
        void print_queue()
        {
        	if (size_of_queue > 0)
            {
            	//р - проходит по кольцу, k - считает число элементов
            	int p = begin;
            	for (int k = 0; k < size_of_queue; k++)
            	{
            		cout << array[p] << " ";
            		p = (p+1) % max_size_of_queue;
                }
            	cout << endl;
            }
            else
            	cout << "queue is empty" << endl;
        }
		
		//проверка на пустоту
        bool empty()
        {
			return !size_of_queue;
        }

};