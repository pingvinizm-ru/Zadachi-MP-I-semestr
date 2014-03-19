//реализация очереди в виде массива
#include <iostream>
#define FREE_SPACE -1
#define END_OF_QUEUE -2
using namespace std;

template <typename element>
struct record
{
	element data;
    int next; //"указатель" на следующий элемент
};

template <typename element>
class queue_array
{
    private:
    	struct record<element> *array; //ìàññèâ ñ äàííûìè
		unsigned int begin; //"óêàçàòåëü" íà íà÷àëî î÷åðåäè
		unsigned int end; //"óêàçàòåëü" íà êîíåö î÷åðåäè
    	unsigned int max_size_of_queue; //ìàêñèìàëüíîå ÷èñëî ýëåìåíòîâ ñïèñêà
        unsigned int size_of_queue;//òåêóùåå ÷èñëî ýëåìåíòîâ ñïèñêà
    public:
    	//êîíñòðóêòîð
       	queue_array(unsigned int max = 10500)
        {
        	begin = end = 0;//óêàçûâàåò íà íóëåâóþ çàïèñü â ìàññèâå
			size_of_queue = 0;
            max_size_of_queue = max;
            array = new struct record<element>[max_size_of_queue];//âûäåëÿåì ïàìÿòü ïîä ìàññèâ çàïèñåé
            for (int i = 0; i < max_size_of_queue; i++)
            	array[i].next = FREE_SPACE;
        }

        //äåñòðóêòîð
        ~queue_array()
        {
        	delete[]array;
        }

        //êîíñòðóêòîð êîïèðîâàíèÿ
        queue_array (const queue_array &x)
        {
        	copy_queue(x);
        }

        //îïåðàòîð ïðèñâàèâàíèÿ
        queue_array operator= (const queue_array &x)
        {
        	if (this == &x) return *this;
        	delete[]array; //î÷èùàåì äàííûå òåêóùåãî ñïèñêà
            copy_queue(x);
            return *this;
        }

        //êîïèðîâàíèå äàííûõ èç àðãóìåíòà â òåêóùèé ñïèñîê
        void copy_queue(const queue_array &x)
        {
			begin = x.begin;
			end = x.end;
            max_size_of_queue = x.max_size_of_queue;
            size_of_queue = x.size_of_queue;
            array = new struct record<element>[max_size_of_queue];//âûäåëÿåì ïàìÿòü ïîä ìàññèâ çàïèñåé
        	for (int i = 0; i < max_size_of_queue; i++)
            	array[i] = x.array[i];
        }

        bool push(element x)
        {
            if (size_of_queue < max_size_of_queue)
            {
            	if (size_of_queue == 0) //î÷åðåäü ïóñòà
                {
                	array[begin].data = x;
					array[begin].next = END_OF_QUEUE;
                }
                else
                {   //èùåì ñâîáîäíîå ìåñòî
                	for (int i = 0; i < max_size_of_queue; i++)
                    {
                        if (array[i].next == FREE_SPACE)
                    	{
							array[i].data = x;
							array[i].next = END_OF_QUEUE;
							array[end].next = i;
							end = i;
                            break;
                    	}
                    }
                }
                size_of_queue++;
                return true;
            }
            else
            	return false;
        }

	element pop()
    {
        if (size_of_queue > 0)
		{
		element result = array[begin].data;
            int temp = begin;
        	if ((size_of_queue - 1) == 0)//ñïèñîê ïóñòîé
            {
            	begin = end = 0;
            }
            else
            {
            	begin = array[begin].next;
            }
            array[temp].next = FREE_SPACE;
            size_of_queue--;
            return result;
		}
		else
			throw exception();
	}
        //âûâîä ñïèñêà
        void print_queue()
        {
        	if (size_of_queue > 0)
            {
				for (int p = begin; p != END_OF_QUEUE; p = array[p].next)
            	{
                	cout << array[p].data << " ";
            	}
            	cout << endl;
            }
            else
            	cout << "queue is empty" << endl;

        }

        //âûâîä ñïèñêà ñ "óêàçàòåëÿìè"
        void print_array()
        {
            for (int i = 0; i < max_size_of_queue; ++i)
            {
                cout << array[i].data << " " << array[i].next << endl;
            }
        }

        bool is_empty()
        {
			return size_of_queue;
        }

};
