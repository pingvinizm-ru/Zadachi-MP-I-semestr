//Кирюхин В. ККС-1-11
//"облегченная" реализация двоичного дерева
//отсутствуют процедуры поворота листа, вывод только в одном режиме
//при желании, можно вырезать процедуру удаления листа - bool del_leaf(...)
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

        //добавление листа в дерево
        void add_leaf(element x, struct leaf<element> *parent)
        {
        	if (root == 0) //если корня не существует, т.е. дерево пустое
            {
            	root = create_new_leaf(x);
            }
            else
            {
                if (x < parent->data) //если х меньше значения родителя
                {
                	if (parent->left == 0) //левая ветвь не существует
                    	parent->left = create_new_leaf(x);
                    else
                       	add_leaf(x, parent->left);
                }
                else //если х больше или равно
                {
                	if (parent->right == 0) //если правая ветвь не существует
                    	parent->right = create_new_leaf(x);
                    else
                       	add_leaf(x, parent->right);
                }
            }
        }

        //выделение памяти под новый лист
        struct leaf<element>* create_new_leaf(element x)
        {
        	struct leaf<element> *place;
        	try
        	{
				place = new struct leaf<element>;
				place->data = x;
				place->left = 0;
				place->right = 0;
            }
            catch(bad_alloc err)
            {
            	cerr << "bab_alloc" << endl;
            	return 0;
            }
            return place; //возвращаем выделенный под лист адрес
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

        void copy_tree(struct leaf<element> *parent, struct leaf<element> *source)
        {
        	//parent - исходное дерево
            //source - источник копирования
            if (source) //копируемое дерево не пустое
            {
            	if (root == 0)//��������� � ����� �� ��
            	{
                	root = parent = create_new_leaf(source->data); //������� ����� ����
            	}
            	if (source->left)
            	{
            		parent->left = create_new_leaf(source->left->data);
                	copy_tree(parent->left, source->left);
            	}
            	if (source->right)
            	{
            		parent->right = create_new_leaf(source->right->data);
                	copy_tree(parent->right, source->right);
            	}
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
        bool del_leaf(struct leaf<element> *grandparent, struct leaf<element> *parent, element x)
        {
            /*
                Идея алгоритма:
                1)Найдем адрес x, удаляемого листа;
                2)Обозначим за z самое правый лист левой ветви удаляемого элемента(или самый левый лист правой ветви);
                3)Правой(левой) ветви родителя z присвоим левую(правую) ветвь z;
                4)В поле data удаляемого элемента занесем z.data;
                5)Освободим память, которую занимает z;
            */
            struct leaf<element> *parent_z, *addr_z, *addr_x;
        	if (parent == 0) return false; //родителя не существует
            if (x < parent->data) return del_leaf(parent, parent->left, x); //смотрим левую ветвь
            if (x > parent->data) return del_leaf(parent, parent->right, x); //смотрим правую ветвь

            if (x == parent->data) //нашли удаляемое значение
            {
                if (!parent->left && !parent->right) //у листа нет потомков
                {
                    if (grandparent->left == parent) grandparent->left = 0; else grandparent->right = 0;
                    if (root == parent) root = 0; //дерево пустое
                    delete parent;
                }
                else //есть хоть одна ветвь
                {
                    if (parent->left) //левая ветвь существует
                    {
                        //осуществляем пробег по ветке, сохраняя предыдущий(родитель), как в связном списке
                        for (addr_z = parent->left, parent_z = parent; addr_z->right != 0; addr_z = addr_z->right) parent_z = addr_z;
                        //получили в addr_z адрес максимального листа поддерева, в parent_z адрес его родителя

                        if (parent_z->left == addr_z) parent_z->left = addr_z->left; else parent_z->right = addr_z->left;//Шаг 3 алгоритма. Т.о. исключили лист из дерева
                    }
                    else //существует только правая ветвь - действия аналогичны
                    {
                        for (addr_z = parent->right, parent_z = parent; addr_z->left != 0; addr_z = addr_z->left) parent_z = addr_z;
                        if (parent_z->left == addr_z) parent_z->left = addr_z->right; else parent_z->right = addr_z->right;
                    }

                    parent->data = addr_z->data; //Шаг 4 - копируем данные
                    delete addr_z; //Шаг 5 - освобождаем память
                }
                return true;
            }
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
			return del_leaf(root, root, x);
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
