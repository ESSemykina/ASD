#include <iostream>
#include <string>

const std::string Numerals = { "1234567890" }; //символы в строке 
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
		if (isDigit(s[0]))//условеи добавления в левый потомок
			left = new Node(s);
		if (s[0] == ',' && isDigit(s[1]))//в правый
		{
			s.erase(0, 1);
			right = new Node(s);
		}
	}

private:
	bool isDigit(char c)//считывание строки 
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
	Node* root = nullptr; //пустой корень

public:
	BinaryTree(std::string s)
	{
		root = new Node(s);//выделяем память для корня
	}

	void direct() { Ddirect(root);  std::cout << "\n"; }//функция прямого обхода и вывод результата
	void central() { Ccentral(root); std::cout << "\n"; }//функция центрального обхода и вывод результата
	void inverse() { Iinverse(root); std::cout << "\n"; }//функция концевого обхода и вывод результата

	void Ddirect(Node* n)//прямой обход - сначала посещаем корневой узел, потом все узлы в левом поддереве, затем все узлы в правом
	{
		if (!n) return;
		std::cout << n->value << " ";
		Ddirect(n->left);
		Ddirect(n->right);
	}

	void Ccentral(Node* n)//центральный обход - сначала идем в левое поддерево, потом в корень, затем в правое
	{
		if (!n) return;
		Ccentral(n->left);
		std::cout << n->value << " ";
		Ccentral(n->right);
	}

	void Iinverse(Node* n)//концевой - сначала в левое, потом в правое, потом в корень
	{
		if (!n) return;
		Iinverse(n->left);
		Iinverse(n->right);
		std::cout << n->value << " ";
	}
};

/************************************************************************/
int main() {
	std::string s = "8(3(1,6(4,7)),10(,14(13,)))";
	BinaryTree tree(s);//заполнение дерева
	tree.direct();//прямой
	tree.central();//центральный 
	tree.inverse();//концевой

	return 0;
}