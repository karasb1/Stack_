#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Node {
private:
	T* _data = nullptr;
	int* _amount_of_data = nullptr;

	void delete_data()
	{
		if (_amount_of_data == nullptr)
		{
			if (_data != nullptr)
				delete _data;
		}
		else
		{
			if (_data != nullptr)
				delete[] _data;
			delete _amount_of_data;
		}
	}

	friend ostream& operator<<(ostream& os, const Node<T>& node)
	{
		if (node._amount_of_data == nullptr)
		{
			os << *node._data;
		}
		else
		{
			for (int i = 0; i < *node._amount_of_data; i++)
			{
				os << node._data[i] << " ";
			}
		}
		return os;
	}
public:
	Node() = default;
	Node(T data)
	{
		_data = new T{ data };
	}
	Node(T* data, int size)
	{
		_amount_of_data = new int{ size };
		_data = new T[*_amount_of_data];
		for (size_t i = 0; i < *_amount_of_data; i++)
		{
			_data[i] = data[i];
		}
	}
	Node(const Node& other)
	{
		if (other._amount_of_data != nullptr)
		{
			_amount_of_data = new int{ *other._amount_of_data };
			_data = new T[*_amount_of_data];
			for (int i = 0; i < *_amount_of_data; i++)
			{
				_data[i] = other._data[i];
			}
		}
		else
		{
			_data = new T{ *other._data };
		}
	}

	void change_data(T new_value)
	{
		delete_data();
		_data = new T{ new_value };
	}

	void change_data(T* new_value, int size)
	{
		delete_data();

		_amount_of_data = new int{ size };
		_data = new T[size];

		for (int i = 0; i < size; i++)
		{
			_data[i] = new_value[i];
		}
	}

	T* get_data()
	{
		return _data;
	}

	int get_amount_of_data()
	{
		return *_amount_of_data;
	}



	~Node()
	{
		delete_data();
	}
};



template<typename T>
class Stack
{
private:
	Node<T>** _items = nullptr;
	const int _step = 10;
	int _size;
	int _fact_size = 0;

	void check_resize()
	{
		if (_fact_size == _size - 1)
		{
			resize();
		}
	}

	void resize()
	{
		Node<T>** new_items = new Node<T>*[_size + _step];
		for (int i = 0; i < _size; i++)
		{
			new_items[i] = _items[i];
		}
		delete[] _items;
		_items = new_items;
		_size += _step;
	}
public:
	Stack()
	{
		_size = _step;
		_items = new Node<T>*[_size];
	}

	void push(T value)
	{
		check_resize();
		Node<T>* new_node = new Node<T>(value);
		_items[_fact_size] = new_node;
		_fact_size++;
	}

	void push(T* value, int size)
	{
		check_resize();
		Node<T>* new_node = new Node<T>(value, size);
		_items[_fact_size] = new_node;
		_fact_size++;
	}

	Node<T> pop()
	{
		if (_fact_size == 0)
		{
			throw std::out_of_range("Stack is empty");
		}
		Node<T>* item = _items[_fact_size - 1];
		Node<T> result(*item);
		delete item;
		_fact_size--;
		return result;
	}

	T top()
	{
		if (_fact_size == 0)
		{
			throw std::out_of_range("Stack is empty");
		}
		Node<T>* item = _items[_fact_size - 1];
		T* data = item->get_data();
		T result = *data;
		return result;
	}


	~Stack()
	{
		delete[] _items;
	}
};

int main() {
	string my_string = "({x-y-z} * [x + 2y] - (z + 4x));";
	int number = 0;
	try
	{
		Stack<int> stack;
		while (my_string[number] != ';') {
			if (my_string[number] == 40 || my_string[number] == 91 || my_string[number] == 123) {
				stack.push(my_string[number]);
			}
			else if (my_string[number] == 41 || my_string[number] == 93 || my_string[number] == 125) {
				if (stack.top() == my_string[number] - 1 || stack.top() == my_string[number] - 2) {
					stack.pop();
				}
				else {
					break;
				}
			}
			number++;
		}
		if (my_string[number] == ';') {
			cout << "string is valid";
		}
		else {
			cout << "Problem is here: ";
			for (int j = 0; j < number + 1; j++) {
				cout << my_string[j];
			}
		}
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}

	return 0;
}