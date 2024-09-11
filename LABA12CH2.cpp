#include <iostream>
#include <stack>

struct Binary_Tree_Search
{
	int value;
	Binary_Tree_Search* l;
	Binary_Tree_Search* r;

	Binary_Tree_Search(int key)
	{
		value = key;
		l = nullptr;
		r = nullptr;
	}

	~Binary_Tree_Search()
	{
		if (l) delete l;
		if (r) delete r;
	}


};



bool find(Binary_Tree_Search* root, int key) //поиск элемента
{
	while (root != nullptr)
	{
		if (root->value == key)
		{
			return true;
		}
		else if (key < root->value)
		{
			root = root->l;
		}
		else
		{
			root = root->r;
		}
	}
	return false;
}


Binary_Tree_Search* insert(Binary_Tree_Search* root, int key) //добавление элемента
{
	if (root == nullptr)
	{
		return new Binary_Tree_Search(key);
	}
	Binary_Tree_Search* curr = root;
	Binary_Tree_Search* parent = nullptr;
	while (curr != nullptr)
	{
		parent = curr;
		if (key < curr->value)
		{
			curr = curr->l;
		}
		else if (key > curr->value)
		{
			curr = curr->r; 
		}
		else
		{
			return root;
		}
	}
	Binary_Tree_Search* new_Tree = new Binary_Tree_Search(key);
	if (key < parent->value)
	{
		parent->l = new_Tree;
	}
	else
	{
		parent->r = new_Tree;
	}
	return root;
}


int depth(Binary_Tree_Search* root) //подсчет количества листьев 
{
	if (root == nullptr)
	{
		return 0;
	}
	else
	{
		return depth(root->r) + depth(root->l) + 1;
	}
}


Binary_Tree_Search* remove(Binary_Tree_Search* root, int key) //удаление элемента 
{
	Binary_Tree_Search* curr = root;
	Binary_Tree_Search* parent = nullptr;
	while (curr != nullptr && curr->value != key)
	{
		parent = curr;
		if (key < curr->value)
		{
			curr = curr->l;
		}
		else
		{
			curr = curr->r;
		}
	}
	if (curr == nullptr)
	{
		return root;
	}
	if (curr->l == nullptr && curr->r == nullptr)
	{
		if (curr == root) 
		{
			delete curr;
			return nullptr;
		}
		else if (parent->l == curr)
		{
			parent->l = nullptr;
		}
		else
		{
			parent->r = nullptr; 
		}
	}

	//Узел имеет только одного ребенка
	else if (curr->l == nullptr || curr->r == nullptr)
	{
		Binary_Tree_Search* child = (curr->l != nullptr) ? curr->l : curr->r;

		if (curr == root)
		{
			delete curr;
			return child;
		}
		else if (parent->l == curr)
		{
			parent->l = child;
		}
		else
		{
			parent->r = child; 
		}
	}

	//Узел имеет двух детей
	else
	{
		// Находим минимальный узел в правом поддереве
		Binary_Tree_Search* minParent = curr;
		Binary_Tree_Search* minNode = curr->r;

		while (minNode->l != nullptr)
		{
			minParent = minNode;
			minNode = minNode->l;
		}
		curr->value = minNode->value;
		if (minParent->l == minNode)
		{
			minParent->l = minNode->r;
		}
		else
		{
			minParent->r = minNode->r; 
		}

		delete minNode;
	}
	return root;
}


void print(Binary_Tree_Search* root) //просмотр дерева
{
	std::stack<Binary_Tree_Search*> stack;
	Binary_Tree_Search* current = root;

	while (current != nullptr || !stack.empty())
	{
		while (current != nullptr)
		{
			stack.push(current);
			current = current->l;
		}
		current = stack.top();
		stack.pop();
		std::cout << current->value << " ";

		current = current->r;
	}
}


void clear(Binary_Tree_Search* root) //очистка дерева
{
	if (root == nullptr)
	{
		return;
	}
	clear(root->l);
	clear(root->r);
	delete root;
}


int main()
{
	setlocale(LC_ALL, "ru");

	Binary_Tree_Search* root = nullptr;

	insert(root, 3);
	insert(root, 6);
	insert(root, 7);
	insert(root, 9);
	insert(root, 8);
	insert(root, 11);
	insert(root, 12);

	print(root);
	std::cout << std::endl;

	std::cout << "В дереве есть элемент 5?   -" ;
	if (find(root, 5))
	{
		std::cout << "Есть";
	}
	else
	{
		std::cout << "Нет";
	}
	std::cout << std::endl;
	std::cout << "В дереве есть элемент 0?   -";
	if (find(root, 0))
	{
		std::cout << "Есть";
	}
	else
	{
		std::cout << "Нет";
	}
	std::cout << std::endl;
	std::cout << "Количество листьев дерева: " << depth(root) << std::endl;



	std::cout << "Удаляем элемент 1: " << std::endl;
	remove(root, 1);

	print(root);
	std::cout << std::endl;



	std::cout << "Добавляем элемент 10: " << std::endl;
	remove(root, 10);

	print(root);
	std::cout << std::endl;


	std::cout << "В дереве есть элемент 1?    -";
	if (find(root, 5))
	{
		std::cout << "Есть";
	}
	else
	{
		std::cout << "Нет";
	}

	clear(root);
	return 0;
}