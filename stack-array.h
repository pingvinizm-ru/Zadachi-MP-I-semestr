//реализация стэка с помощью массива
#include <iostream>

using namespace std;

template <typename element>
class stack_array
{
    private:
    	element *array; //указатель на массив под стэк
        unsigned int top; //"указатель" на вершину стэка
    	unsigned int max_size_of_stack; //максимальный размер стэка
    public:
    	//конструктор
        stack_array(unsigned int max = 100500)
        {
        	top = 0;//
            max_size_of_stack = max;
            array = new element[max_size_of_stack];//выделение памяти под запрашиваемый размер
        }

        //деструктор
        ~stack_array()
        {
        	delete[]array;
        }

        //конструктор копирования
        stack_array (const stack_array &x)
        {
        	copy_stack(x);
        }

        //оператор присваивания
        stack_array operator= (const stack_array &x)
        {
        	if (this == &x) return *this;
        	delete[]array; //высвобождение памяти
            copy_stack(x);
            return *this;
        }

        //функция копирования стэка-аргумента в текущий стэк
        void copy_stack(const stack_array &x)
        {
        	top = x.top;
            max_size_of_stack = x.max_size_of_stack;
            array = new element[max_size_of_stack];
        	for (int i = 0; i < top; i++)
            	array[i] = x.array[i];
        }

	//добавление элемента
        bool push(element x)
        {
            if (top < max_size_of_stack)
            {
          	  array[top] = x; 
                top++;
                return true;
            }
            else
            	return false;
        }

	//извлечение элемента
        element pop()
        {
			if (top > 0)
			{
				top--;
				return array[top];
			}
			else //исключительная ситуация
            		{
            			throw exception();
            		}
        }
        
        //
        void print_stack()
        {
        	if (top > 0)
            {
            	for (int i = 0; i < top; ++i)
            	{
                	cout << array[i] << " ";
            	}
            	cout << endl;
            }
            else
            	cout << "stack is empty" << endl;      
        }
        
        int max_size()
        {
        	return max_size_of_stack;
        }

        bool empty()
        {
            return !top;
        }
};