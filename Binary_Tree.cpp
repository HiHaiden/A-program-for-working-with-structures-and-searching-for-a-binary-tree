#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;
struct Tree
{
	int Key;
	Tree* Right;
	Tree* Left;
};

Tree* Root = NULL, * Delete = NULL;
bool delete1 = 0, way = 0;

void AllTreeDeleter(Tree* root)
{
	if (root == NULL)
	{
		return;
	}
	AllTreeDeleter(root->Left);
	AllTreeDeleter(root->Right);
	delete root;
}

void TreeDeleter(Tree* root)
{
	if (root == NULL)
	{
		return;
	}
	TreeDeleter(root->Left);
	root->Left = NULL;
	TreeDeleter(root->Right);
	root->Right = NULL;
	delete root;
}

Tree* PosFinder()
{
	Tree* root_loc = Root, * root_nextL, * root_nextR;
	short Find;
	cout << "Введите число которое нужно найти: " << endl;
	cin >> Find;
	cout << "Путь к объекту: " << endl;
	while (root_loc != NULL)
	{
		root_nextL = root_loc->Left;
		root_nextR = root_loc->Right;
		if (Find == root_loc->Key)
		{
			cout << "Корень" << endl;
			cout << root_loc->Key << endl;
			return root_loc;
		}
		if (Find < root_loc->Key)
		{
			if (root_nextL->Key == Find)
			{
				way = 0;
				Delete = root_loc;
			}
			cout << "Левый ";
			root_loc = root_loc->Left;
		}
		if (Find > root_loc->Key)
		{
			if (root_nextR->Key == Find)
			{
				Delete = root_loc;
				way = 1;
			}
			cout << "Правый ";
			root_loc = root_loc->Right;
		}
	}
}

void PlaceFinder(Tree* newobj)
{
	Tree* temp = Root;
	while (temp != NULL)
	{
		if (newobj->Key > temp->Key)
		{
			if (temp->Right == NULL)
			{
				temp->Right = newobj;
				return;
			}
			else
			temp = temp->Right;
		}
		else
		{
			if (newobj->Key <= temp->Key)
			{
				if (temp->Left == NULL)
				{
					temp->Left = newobj;
					return;
				}
				else
				temp = temp->Left;
			}
		}
	}
}

void AllToViewForward(Tree* root)
{
	if (root == NULL)
	{
		return;
	}
	cout << root->Key << " " << endl;
	AllToViewForward(root->Right);
	AllToViewForward(root->Left);
}

void AllToViewSymmetry(Tree* root)
{
	if (root == NULL)
	{
		return;
	}

	AllToViewSymmetry(root->Left);
	cout << root->Key << " " << endl;
	AllToViewSymmetry(root->Right);
}

void AllToViewBack(Tree* root)
{
	if (root == NULL)
	{
		return;
	}

	AllToViewBack(root->Left);
	AllToViewBack(root->Right);
	cout << root->Key << " " << endl;
}

void push()
{
	short l_Key1;
	Tree* temp = new Tree;
	cout << "Введите число." << endl;
	cin >> l_Key1;
	if (Root != NULL)
	{
		temp->Key = l_Key1;
		temp->Left = NULL;
		temp->Right = NULL;
		PlaceFinder(temp);
	}
	else
	{
		Root = temp;
		Root->Key = l_Key1;
		Root->Left = NULL;
		Root->Right = NULL;
	}
}

int main()
{
	SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
	int l_Key;
	Tree* lr;
	do
	{
		Tree* temp = Root;
		Delete = NULL;
		cout << "1 - Добавить элемент к дереву." << endl;
		cout << "2 - Вывести дерево прямым порядком." << endl;
		cout << "3 - Вывести дерево симметричным порядком." << endl;
		cout << "4 - Вывести дерево обратным порядком." << endl;
		cout << "5 - Найти узел по заданному значению." << endl;
		cout << "6 - Найти и удалить поддерево." << endl;
		cout << "7 - Удалить всё дерево." << endl;
		cout << "\nВыбранная команда:" << endl;
		cin >> l_Key;
		cout << "------" << endl;
		switch (l_Key)
		{
		case 1:
			push();
			break;
		case 2:
			AllToViewForward(temp);
			break;
		case 3:
			AllToViewSymmetry(temp);
			break;
		case 4:
			AllToViewBack(temp);
			break;
		case 5:
			PosFinder();
			break;
		case 6:
			lr = PosFinder();
			TreeDeleter(lr);
			if (way)
			Delete->Right = NULL;
			else Delete->Left = NULL;
			break;
		case 7:
			lr = Root;
			AllTreeDeleter(lr);
			Root = NULL;
			cout << "Дерево удалено." << endl;
			break;
		}
	} while (l_Key != 0);
	lr = Root;
	AllTreeDeleter(lr);
	_getch();
	return 0;
}