//Кирюхин В. ККС-1-11
//полная версия бинарного дерева
//Реализованы процедуры поворота элемента, удаления элемента, различные режимы вывода
#include <iostream>
#define LEFT_ROOT_RIGHT 1
#define ROOT_LEFT_RIGHT 2
#define LEFT_RIGHT_ROOT 3
#define GRAPH_TREE 4
using namespace std;

template <typename element>
struct leaf
{
	element data;
    struct leaf<element> *left;
    struct leaf<element> *right;
};

template <typename element>
class binary_tree
{
    private:
    	struct leaf<element> *root; //������ ������

        //���������� ����� � ������
        void add_leaf(element x, struct leaf<element> *parent)
        {
        	if (root == 0) //���� ������ �� ���������
            {
            	root = create_new_leaf(x);
            }
            else
            {
                if (x < parent->data) //���������� ������-�������
                {
                	if (parent->left == 0) //����������: ��������� ���� ��� ���� ������
                    	parent->left = create_new_leaf(x);
                    else
                       	add_leaf(x, parent->left);
                }
                else
                {
                	if (parent->right == 0)
                    	parent->right = create_new_leaf(x);
                    else
                       	add_leaf(x, parent->right);
                }
            }
        }

        //�������� ������ �����
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
            return place;
        }

        void print_tree(struct leaf<element> *parent, int type = LEFT_ROOT_RIGHT, int deep = 0)
        {
        	if (parent == 0) //���� �������� �� ���������
            {
            	cout << "empty" << endl;
            }
            else
            {
            	if (type <= LEFT_ROOT_RIGHT) //ЛКП
                {
            		//�����: �����-������-������
                	if (parent->left) //���� ����� ���������� - �������
                		print_tree(parent->left, type);

                	cout << parent->data << " ";// << parent << endl; //������

            		if (parent->right)
                		print_tree(parent->right, type);
                }

             	if (type == ROOT_LEFT_RIGHT)//КЛП
                {
                    cout << parent->data << " ";

                	if (parent->left)
                		print_tree(parent->left, type);

            		if (parent->right)
                		print_tree(parent->right, type);
                }

            	if (type == LEFT_RIGHT_ROOT) //ЛПК
                {
                	if (parent->left)
                		print_tree(parent->left, type);

            		if (parent->right)
                		print_tree(parent->right, type);

                    cout << parent->data << " ";
                }

            	if (type >= GRAPH_TREE) //структурная
                {
                	if (parent->left)
                		print_tree(parent->left, type, deep + 1);

					for (int i = 0; i < deep; ++i) cout << "   ";
                    cout << parent->data << endl;

            		if (parent->right)
                		print_tree(parent->right, type, deep + 1);

                }

            }
        }

        void clear_tree(struct leaf<element> *parent)
        {
        	//cout << "priv clear"<< endl;
        	if (parent == 0) return;//если дерево уже пустое -> выходим
            if (parent->left) //если левая ветвь существует
            	clear_tree(parent->left); //запускаем ее очистку
            if (parent->right) //если правая ветвь существует
            	clear_tree(parent->right);

            //cout << parent->data << " ";
            //parent->data = 100;
            //cout << "parent = " << parent << endl;
            //к этому моменту левая и правая ветви пусты
            delete parent;
            //если мы удалили все дерево, и находимся в корне
            //устанавливаем root = 0, показывая, что дерево пусто
        	if (parent == root) root = 0;
        }

        void copy_tree(struct leaf<element> *parent, struct leaf<element> *source)
        {
        	//cout << "priv copy"<< endl;
            //cout << "root = " << root << " source = " << source << endl;
        	//parent - ��������� �� �������� ������
            //source - �� �����������
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

        struct leaf<element>* get_addr_of_element(struct leaf<element> *parent, element x)
        {
            if (parent == 0) return 0;//
            if (parent->data == x) return parent; //нашли адрес нужного элемента

            if (x < parent->data)
            {
            	if (parent->left)
                	get_addr_of_element(parent->left, x);
                else
                {   //элемент меньше текущего, но таких нет
                	return 0;
                }
            }
            else //x > data
            {
            	if (parent->right)
                	get_addr_of_element(parent->right, x);
                else
                {   //элемент меньше текущего, но таких нет
                	return 0;
                }
            }
        };

        //удаление листа - новый вариант
        bool del_leaf(struct leaf<element> *grandparent, struct leaf<element> *parent, element x)
        {
            /*
                Идея алгоритма:
                1)Найдем адрес x, удаляемого листа;
                2)Обозначим за z самое правый лист левой ветви удаляемого элемента(или самый правый лист левой ветви);
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

		bool del_leaf_old_version(struct leaf<element> *parent, element x)
        {
            struct leaf<element> *addr_x, *temp;
        	if (root == 0 ) return false;
        	if (x == parent->data) //случай корня
            {
            		addr_x = root;
            		//cout << "x == root->data" << endl;

                    //к самому правому элементу левой ветви присоединяем правую ветвь справа
                    //1.ищем адрес
                    if (addr_x->left) //если левая ветка существует
                    {
                    	for (temp = addr_x->left; temp->right != 0; temp = temp->right);
                        //2.присоединяем
                        root = addr_x->left;
                        temp->right = addr_x->right;
                    }
                    else
                    {
                        root = addr_x->right;
                    }
                    delete addr_x;
                    return true;
            }
            if (x < parent->data)
            {
            	if (parent->left)//нужная ветвь существует
                {
                	if (parent->left->data == x) //потомок - искомый элемент
                    {
                    	addr_x = parent->left;
                        //к самому правому элементу левой ветви присоединяем правую ветвь справа
                        //1.ищем адрес
                        if (addr_x->left) //если левая ветка существует
                        {
                        	for (temp = addr_x->left; temp->right != 0; temp = temp->right);
                        	//2.присоединяем
                            parent->left = addr_x->left;
                        	temp->right = addr_x->right;
                        }
                        else
                        {
                        	parent->left = addr_x->right;
                        }
                        delete addr_x;
                        return true;
                        //righted_of_element->right = addr_x->right;
                    }
                    else
                    	return del_leaf(parent->left, x);
                }
                else
                	return false; //запрашиваемого элемента не существует
            }
            else //x > parent->data
            {
             	if (parent->right)
                {
                	if (parent->right->data == x) //потомок - искомый элемент
                    {
                    	addr_x = parent->right;
                        //к самому правому элементу левой ветви присоединяем правую ветвь справа
                        //1.ищем адрес
                        if (addr_x->left) //если левая ветка существует
                        {
                        	for (temp = addr_x->left; temp->right != 0; temp = temp->right);
                        	//2.присоединяем
                            parent->right = addr_x->left;
                        	temp->right = addr_x->right;
                        }
                        else
                        {
                        	parent->right = addr_x->right;
                        }

                        delete addr_x; //освобождаем память
                        return true;
                    }
                    else
                    	return del_leaf(parent->right, x);
                }
                else return false; //запрашиваемого элемента не существует
            }
        };

       	bool rotate_leaf(struct leaf<element> *grandparent, struct leaf<element> *parent, element x)
        {
            struct leaf<element> *addr_x, *temp;
            if (parent == 0 ) return false;
        	if (x == parent->data) //случай корня
            {
                    return false; //корень не вращаем
            }
            if (x < parent->data)
            {
            	if (parent->left)//нужная ветвь существует
                {
                	if (parent->left->data == x) //потомок - искомый лист
                    {
                    	addr_x = parent->left; //указатель на найденный лист
                        temp = addr_x->right;  //указатель на правую ветвь найденного элемента

                        if (grandparent == 0) //если родитель - корень дерева
                        {                   //т.е. искомый лист станет новым корнем
                        	root = addr_x;
                        }
                        else
                        {
                            //определим: родитель правая или левая ветвь прародителя?
                            if (grandparent->left == parent)
                                grandparent->left = addr_x;
                            else
                                grandparent->right = addr_x;
                        }
                        addr_x->right = parent;
                        parent->left = temp;

                        return true;

                    }
                    else
                    	return rotate_leaf(parent, parent->left, x);
                }
                else
                	return false; //запрашиваемого элемента не существует
            }
            else //x > parent->data
            {
             	if (parent->right)
                {
                	if (parent->right->data == x) //потомок - искомый элемент
                    {
                    	addr_x = parent->right; //указатель на найденный лист
                        temp = addr_x->left;  //указатель на правую ветвь найденного элемента

                        if (grandparent == 0) //если прародитель не определен - корень дерева
                        {                     //т.е. искомый лист станет новым корнем
                        	root = addr_x;
                        }
                        else
                        {
                            //определим: родитель правая или левая ветвь прародителя?
                            if (grandparent->left == parent)
                                grandparent->left = addr_x;
                            else
                                grandparent->right = addr_x;
                        }
                        addr_x->left = parent;
                        parent->right = temp;
                        return true;
                    }
                    else
                    	return rotate_leaf(parent, parent->right, x);
                }
                else
                	return false; //запрашиваемого элемента не существует
            }            ///
        }



    public:

    	binary_tree()
        {
        //	cout << "constr" << endl;
            root = 0;
        }

        ~binary_tree()
        {
        //	cout << "destr" << endl;
        	clear_tree();
        }

        binary_tree (const binary_tree<element> &x)
        {
        //	cout << "copies root = " << root << " x.root = "<< x.root << endl;
            //clear_tree();
            root = 0;
        	copy_tree(root, x.root);
        }

        binary_tree operator= (const binary_tree<element> &x)
        {
        //	cout << "op=" << endl;
            if (this == &x) return *this;
        //    cout << "op2=" << endl;
            clear_tree();
            if (x.root) copy_tree(root, x.root);

            return *this;
        }


        //�������� ������ - ���������
        void clear_tree()
        {
        	clear_tree(root);
            //root = 0;//�������� �������� ����� - ������ �������
        }

        //���������� ����� � ������ - ���������
        void add_leaf(element x)
        {
        	add_leaf(x, root);
        }

		bool del_leaf(element x)
		{
			return del_leaf(root, root, x);
		}
        //����� ���� ������ ������ - ���������
        void print_tree(int type_of_print = 1)
        {
            print_tree(root, type_of_print);
            cout << endl;
        }

        void print_root()
        {
            cout << "root = " << root << endl;
        }

        //существует ли такой элемент в дереве
        bool is_exist(element x)
        {
            return get_addr_of_element(root, x);
        }

        bool rotate_leaf(element x)
        {
            return rotate_leaf(0, root, x);
        }

};
