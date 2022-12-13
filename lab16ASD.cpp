#include <iostream>
#include <string>
#include <vector>
#include <stack>

const std::string Numerals = { "1234567890" };//символы в строке 
 //читаем введенное выражение 
struct Node //заполняем бинарное дерево
{
	int value;
	Node* left = nullptr, * right = nullptr;//пустые поддеревья

	//создаем бинарное дерево
	Node(std::string& s)
	{
		value = getValue(s);
		s.erase(0, cut(value));
		if (s[0] == '(')
			s = unbracket(s);
		else return;
		if (isDigit(s[0]))//условие добавления в левый потомок
			left = new Node(s);
		if (s[0] == ',' && isDigit(s[1]))//в правый
		{
			s.erase(0, 1);
			right = new Node(s);
		}
	}

private:
	bool isDigit(char c) //считывание строки
	{
		return Numerals.find(c) != std::string::npos;
	}
	int cut(int n)//разделяем поразрядно
	{
		int i = 0;
		if (n == 0) return 1;
		while (n > 0)
		{
			n /= 10;
			i++;
		}
		return i;
	}

	int getValue(std::string& s)//переводим string в int
	{
		int i = 0, tmp = 0;
		for (int i = 0; i < s.size(); i++)
			if (isDigit(s[i]))
			{
				tmp = tmp * 10 + int(s[i] - 48);
				if (!isDigit(s[i + 1]))
					return tmp;
			}
	}

	std::string unbracket(std::string s)//скобки
	{
		int brackets = 0;//счетчик
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == '(') brackets++;//если "(" то увеличиваем
			if (s[i] == ')') brackets--;//если ")" то уменьшаем
			if (!brackets)
			{
				s.erase(0, 1);
				s.erase(i - 1, 1);
				return s;
			}
		}
		return s;
	}
};

/************************************************************************/
class BinaryTree
{
	Node* root = nullptr;//создаем пустой корень

public:
	BinaryTree(std::string s)
	{
		root = new Node(s);//выделяем память под корень
	}

	void Print()//выводим обход с помощью стека 
	{
		std::stack <Node*> stack;//создаем стек
		Node* tmp;
		stack.push(root);//корень это вершина стека
		while (!stack.empty())//пока стек не пуст
		{
			tmp = stack.top();//верхний элемент
			stack.pop();//удаляем и возвращаем верхний элемент
			std::cout << tmp->value << ' ';
			
			if (tmp->right != nullptr) stack.push(tmp->right);//вставляет обьект правого поддерева как верхний эл-т стека
			if (tmp->left != nullptr)  stack.push(tmp->left);//вставляет обьект левого поддерева как верхний эл-т стека
		}
	}

};

/************************************************************************/
int main() {
	std::string s = "8(3(1,6(4,7)),10(,14(13,)))";
	BinaryTree tree(s);
	tree.Print();

	return 0;
}