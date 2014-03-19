//"облегченная" реализация двоичного дерева
//отсутствуют процедуры поворота листа, вывод только в одном режиме
//при желании, можно вырезать процедуру удаления листа - bool del_leaf(...)
//UPD: объём кода уменьшен за счет применения ссылок
#include <iostream>
using namespace std;

template <typename element>
struct leaf
{
	element data; //содержимое
    struct leaf<element> *left; //указатель на левый лист
    struct leaf<element> *right; //на правый лист
};

template <typename element>
class binary_tree
{
    private:
    	struct leaf<element> *root; //корень дерева

		void add_leaf(element x, struct leaf<element> (*&parent))
		{
			if (parent == 0) //листа нет - создаем новый
				create_new_leaf(x, parent);
			else
				if (x < parent->data)					
					add_leaf(x, parent->left); //если х меньше значения родителя
				else
					add_leaf(x, parent->right); //если х больше или равно
		}

		void create_new_leaf(element x, struct leaf<element> (*&parent))
		{
				parent = new struct leaf<element>; //выделили память
				parent->data = x; //занесли данные
				parent->left = 0; //потомков нет
				parent->right = 0;
		}

		//вывод дерева на печать - ЛКП режим
        void print_tree(struct leaf<element> *parent, int deep = 0)
        {
			if (root == 0) cout << "empty" << endl; //дерево пустое
        	if (parent == 0) return; //родитель не существует -> выходим

			//выводим левую ветвь
			print_tree(parent->left, deep + 1);

			//выводим пробелы, соответствующие "глубине" листа
			for (int i = 0; i < deep; ++i) cout << "   ";
            //выводим значение корня
			cout << parent->data << endl;

			//выводим правую ветвь
			print_tree(parent->right, deep + 1);
        }

        void clear_tree(struct leaf<element> *parent)
        {
        	if (parent == 0) return;//если родителя нет -> выходим

			clear_tree(parent->left); //запускаем очистку левой ветви
			clear_tree(parent->right);//запускаем очистку правой ветви

            //к этому моменту левая и правая ветви пусты
            delete parent;
            //если мы удалили все дерево, и находимся в корне
            //устанавливаем root = 0, показывая, что дерево пусто
        	if (parent == root) root = 0;
        }

        void copy_tree(struct leaf<element> (*&parent), struct leaf<element> *source)
        {
        	//parent - исходное дерево
            //source - источник копирования
            if (source) //копируемое дерево не пустое
            {
            	create_new_leaf(source->data, parent); //создаем новый лист

                copy_tree(parent->left, source->left); //запускаем копирование левой ветви
                copy_tree(parent->right, source->right); //запускаем копирование правой ветви           	
            }
        }

		//нахождение адреса листа по его значению
        struct leaf<element>* get_addr_of_element(struct leaf<element> *parent, element x)
        {
            if (parent == 0) return 0;//
            if (parent->data == x) return parent; //нашли адрес нужного элемента

            if (x < parent->data)
				get_addr_of_element(parent->left, x);  //смотрим левую ветвь
            else
				get_addr_of_element(parent->right, x); //смотрим правую ветвь

        };

        //удаление листа
        bool del_leaf(element x, struct leaf<element> (*&parent))
        {
            /*
                Идея алгоритма:
                1)Найдем адрес x, удаляемого листа;
                2)Обозначим за z самый правый лист левой ветви удаляемого элемента(или самый правый лист левой ветви);
                3)В поле data удаляемого элемента занесем z.data;
				4)Правой(левой) ветви родителя z присвоим левую(правую) ветвь z;                
                5)Освободим память, которую занимает z;
            */
			struct leaf<element> *temp;

        	if (parent == 0) return false; //родителя не существует

            if (x < parent->data) return del_leaf(x, parent->left); //смотрим левую ветвь
            if (x > parent->data) return del_leaf(x, parent->right); //смотрим правую ветвь
			
            if (x == parent->data) //нашли удаляемое значение
            {
                if (!parent->left && !parent->right) //у листа нет потомков
                {                    
                    delete parent; //освобождаем память 
					parent = 0;
                }
                else //есть хоть одна ветвь
                {					
                    if (parent->left) //левая ветвь существует
                    {
						struct leaf<element> *&addr_z = search_righted(parent->left); //нашли самый правый в левой ветви                  
						parent->data = addr_z->data; //переместили значение в корень						
                        temp = addr_z->left; //запомнили адрес левой ветви
						delete addr_z; //освободили память 
						addr_z = temp; //правой ветви родителя z присвоили адрес левой ветви z
                    }
                    else //существует только правая ветвь - действия аналогичны
                    {
                        struct leaf<element> *&addr_z = search_lefted(parent->right);
						parent->data = addr_z->data;						
                        temp = addr_z->right;
						delete addr_z;
						addr_z = temp;                   
					}			
                }
                return true; //возвращаем истину - мы удалили искомое значение
            }
        }
		
		//поиск самого правого элемента дерева
		struct leaf<element> *&search_righted(struct leaf<element> (*&parent))
		{
			if (parent->right) return search_righted(parent->right); else return parent;
		}
		//поиск самого левого элемента дерева
		struct leaf<element> *&search_lefted(struct leaf<element> (*&parent))
		{
			if (parent->left) return search_lefted(parent->left); else return parent;
		}

    public:

    	binary_tree() //конструктор
        {
            root = 0;
        }

        ~binary_tree() //деструктор
        {
        	clear_tree();
        }

        binary_tree (const binary_tree<element> &x) //конструктор копирования
        {
            root = 0; //изначально дерево пустое
        	copy_tree(root, x.root); //запуск копирования
        }

        binary_tree operator= (const binary_tree<element> &x) //оператор присваивания
        {
            if (this == &x) return *this; //защита от самокопирования
            clear_tree(); //освобождение памяти занятой, текущим деревом
            copy_tree(root, x.root); //запуск копирования переданного в текущее
            return *this;//возвращение значения текущего
        }

        //функции - интерфейсы
        void clear_tree()
        {
        	clear_tree(root);
        }

        void add_leaf(element x)
        {
        	add_leaf(x, root);
        }

		bool del_leaf(element x)
		{
			return del_leaf(x, root);
		}

        void print_tree()
        {
            print_tree(root);
            cout << endl; //перевод на следующую строку
        }

        //существует ли такой элемент в дереве
        bool is_exist(element x)
        {
            return get_addr_of_element(root, x); //если адрес != 0, элемент существует, возвращаем true
        }
};
