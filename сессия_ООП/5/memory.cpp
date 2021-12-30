// Глобальная переменная, память выделяется при старте программы - СТАТИЧЕСКАЯ ПАМЯТЬ
int A = 125; 

void SomeMethod()
{ // начало области видимости метода SomeMethod

    // Локальная переменная, память выделяется в начале области видимости метода SomeMethod, при его вызове..
    // Автоматическая память, потому что удалится автоматически в конце области видимости метода SomeMethod
    int a = 5; 

    while(a-- > 0) // 5 итераций
    { // начало области видимости цикла while
        // Переменная b - тоже относится к автоматическому типу памяти.
        // Каждую итерацию цикла будет выделяться память для b, 
        // а при каждом завершении итерации - память будет автоматически очищаться, 
        // то есть память будет выделена и очищена 5 раз
        int b = 5;
        b *= 2;
    } // конец области видимости цикла while
} // конец области видимости метода SomeMethod

void ExampleDynamicMemoryUsage()
{
    int a = 5;
	int arrSize = 0;
	while (a-- > 0) // 5 итераций
		arrSize += 2; // в итоге arrSize = 10.
	char* chars = new char[arrSize]; // выделение памяти для массива char'ов из 10 ячеек

	delete[] chars; // очистка памяти массива char'ов
}

void ExampleMallocFreeForVariable()
{
    // Пример с обычной перменной
    int* mallocVariable = (int*) malloc(sizeof(int));

    // Проверим, успешно ли получилось выделить память
    if (!mallocVariable)
    {
        std::cout << "Malloc failed!" << std::endl;
        return 0;
    }

    *mallocVariable = 125;
    std::cout << *mallocVariable << std::endl;
    free(mallocVariable);
}

void ExampleMallocFreeForArray()
{
     // Пример с выделением динмаческой памяти с помощью malloc для массива int из 5 элементов, заполнение их и вывод
    int intArraySize = 5;
    int* mallocIntArray = (int*)malloc(intArraySize * sizeof(int));
    for (int i = 0; i < intArraySize; i++)
    {
        // (0+1) * 25 = 25
        // (0+2) * 25 = 50
        // (0+3) * 25 = 75
        // (0+4) * 25 = 100
        // (0+5) * 25 = 125
        
        mallocIntArray[i] = (i + 1) * 25;
        // *(mallocIntArray + i) = (i+1) * 25; // Возможна такая запись, продемострируем ее при выводе
    }

    for (int i = 0; i < intArraySize; i++)
        std::cout << *(mallocIntArray + i) << std::endl; // Аналог mallocIntArray[i]

    // Почистим память, когда нам больше не нужен массив
    free(mallocIntArray);
}

int main()
{
    // Пример автоматической памяти
    SomeMethod();
    // Пример динамического выделения памяти:
    ExampleDynamicMemoryUsage();
    // Пример выделения/очистки памяти с помощью malloc/free для переменной
    ExampleMallocFreeForVariable();
    // Пример выделения/очистки памяти с помощью malloc/free для массива
    ExampleMallocFreeForArray();

    return 0;
}

// Пример из статьи принципа RAII, в конструкторе мы выделяем динамическую память, а в деструкторе очищаем память
class String
{
public:
    explicit String(const char* const c_string)
    {
        size = strlen(c_string) + 1;
        this->c_string = new char[size]; // выделяем память
        strcpy_s(this->c_string, size, c_string);
    }

    ~String() noexcept
    {
        delete[] c_string; // очищаем память
    }

private:
    char* c_string;
    size_t size;
};