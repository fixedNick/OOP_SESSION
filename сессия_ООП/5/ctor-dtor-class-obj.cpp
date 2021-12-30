#include <iostream>

class Example
{
protected: // Для текущего класса и классов наследников
	int v;

private: // Только для текущего класса
	int b;
	int c;
	int* any_size; // память выделяется только в конструкторе Example(int a, int b);

public:
	int a;

	Example() { a = 0; b = 0; c = 0; v = 0; } // Конструктор по умолчанию
	Example(int a, int b, int _c) // Другой конструктор
	{
		this->a = a;
		this->b = b;
		c = _c;
		v = 0;
	}
	Example(int a, int b) // Перегрузка конструктора
	{
		this->a = a;
		this->b = b;
		c = 0;
		v = 0;

		any_size = (int*) malloc(5 * sizeof(int));
	}
	void print() // Метод класса, вызывается у объекта
	{
		std::cout << "Example object print [a: " << a <<" b: " << b <<" v: " << v << "]" << std::endl;
	}
	void print(const char* text) // Перегруженный метод print, вызывается у объекта
	{
		std::cout << "Example object print, text: " << text << std::endl;
	}
	// static void print() {} - Невозможно определить статический и нестатический метод у класса с одним и тем же именем.
	static void staticPrint() // Статический метод класса, вызывается у класса, не может быть вызван у объекта
	{
		std::cout << "static print()" << std::endl;
		// a = 5; - Создан для всех объектов класса, поэтому не может оперировать данными конкретного объекта
	}
	// Некий public сеттер для protected члена
	void setProtectedMember(int _v)
	{
		if(_v > 0)
			v = _v;
	}

	~Example()
	{
		std::cout << "destructor called" << std::endl;
		free(any_size);
	}
};



int main()
{
	Example* ex_ptr = new Example(1, 2, 3);
	ex_ptr->a = 5;
	ex_ptr->print();
	delete ex_ptr;

	Example ex{0,5};
	Example ex2{ 15,14 };
	
	const char* text = "hello world";

	ex.print();
	ex.print(text); // Данный метод лучше сделать static, т.к. он не оперирует данными объекта класса

	ex2.print();
	ex2.print(text); // Данный метод лучше сделать static, т.к. он не оперирует данными объекта класса

	Example::staticPrint();

	ex.setProtectedMember(7); // У объекта ex v = 7
	ex2.setProtectedMember(17); // У объекта ex2 v = 17
	ex2.setProtectedMember(-17); // У объекта ex2 v = 17 - Значение не изменилось, потому что в логике сеттера стоит проверка, на неотрицательные значения
	ex.print();
	ex.print();
	return 0;
}