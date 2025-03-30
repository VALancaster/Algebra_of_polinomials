#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <stdexcept>
#include <utility>

using namespace std;

template<typename Type>
class SinglyList 
{
private:
	struct Element 
	{
		Type data;
		Element* next = nullptr;
	};

	Element* firstElement; // первый элемент (некоторые методы будут за O(1) вместо O(N))
	Element* lastElement; // последний элемент (некоторые методы будут за O(1) вместо O(N))
	size_t elementCount; // количество элементов

	Element* fetchElement(size_t index) const // получения указателя на элемент по индексу
	{
		if (index >= elementCount)
			throw out_of_range("Index out of range");
		Element* temp = firstElement;
		for (size_t i = 0; i < index; ++i)
			temp = temp->next;
		return temp;
	}

public:
	SinglyList() noexcept : elementCount(0), firstElement(nullptr), lastElement(nullptr) {};
	SinglyList(const SinglyList& source) : elementCount(0), firstElement(nullptr), lastElement(nullptr)
	{
		for (Element* node = source.firstElement; node; node = node->next) // пока node не nullptr
			addToEnd(node->data); // добавляет данные data из узла node
	}
	SinglyList(SinglyList&& source) noexcept : firstElement(source.firstElement), lastElement(source.lastElement), elementCount(source.elementCount)
	{
		source.firstElement = source.lastElement = nullptr; // при удалении исходного списка с новым ничего не произойдет
		source.elementCount = 0;
	}
	~SinglyList()
	{
		reset();
	}

	size_t length() const noexcept
	{
		return elementCount;
	}
	bool empty() const noexcept
	{
		return elementCount == 0;
	}

	void addToEnd(const Type& data) // вставка в конец
	{
		Element* newNode = new Element{ data }; // cоздается новый узел NewNode c данными data
		if (lastElement)
			lastElement->next = newNode;
		else
			firstElement = newNode; // если список пуст
		lastElement = newNode; // обновили последний элемент
		++elementCount;
	}
	void addToStart(const Type& data) // вставка в начало
	{
		Element* newNode = new Element{ data, firstElement }; // создается новый узел NewNode с данными data, который указывает на первый элемент
		firstElement = newNode; // обновили первый элемент
		if (!lastElement)
			lastElement = newNode; // если список пуст
		++elementCount;
	}
	void eraseAt(size_t index) // удаление элемента по индексу
	{	
		if (index >= elementCount)
			throw out_of_range("Index out of range");
		Element* toRemove = nullptr; // создается указатель на удаляемый элемент
		if (index == 0)
		{
			toRemove = firstElement;
			firstElement = firstElement->next; // обновили первый элемент для исключения нужного
			if (!firstElement) lastElement = nullptr;
		}
		else
		{
			Element* prev = fetchElement(index - 1); // предыдущий элемент до удаляемого	
			toRemove = prev->next; // берется указатель от предыдущего элемента на следующий (нужный)
			prev->next = toRemove->next; // исключаем из цепочки списка удаляемый элемент
			if (index == elementCount - 1)
				lastElement = prev; // обновили последний элемент
		}
		delete toRemove; // освобождается память
		--elementCount;
	}
	void reset() // удаление всех элементов из списка
	{
		while (firstElement) 
		{
			Element* temp = firstElement;
			firstElement = firstElement->next; // переставляем указатель вперед
			delete temp;
		}
		lastElement = nullptr;
		elementCount = 0;
	}

	Type& getItem(size_t index) // получение данных по индексу
	{
		return fetchElement(index)->data;
	}
	const Type& getItem(size_t index) const // получение данных по индексу
	{
		return fetchElement(index)->data;
	}

	bool operator==(const SinglyList& source) const noexcept
	{
		if (elementCount != source.elementCount)
			return false;
		Element* current1 = firstElement;
		Element* current2 = source.firstElement;
		while (current1) // эквивалентно while (current 2)
		{
			if (current1->data != current2->data)
				return false;
			current1 = current1->next;
			current2 = current2->next;
		}
		return true;
	}
	bool operator!=(const SinglyList& source) const noexcept
	{
		return !(*this == source);
	}

	SinglyList& operator=(const SinglyList& source)
	{
		if (this == &source) // cравнение указателей
			return *this; // вернули текущий список
		reset();
		for (Element* node = source.firstElement; node; node = node->next)
			addToEnd(node->data);
		return *this;
	}
	SinglyList& operator=(SinglyList&& source) noexcept
	{
		if (this == &source) // cравнение указателей
			return *this; // вернули текущий список
		reset();
		firstElement = source.firstElement;
		lastElement = source.lastElement;
		elementCount = source.elementCount;
		source.firstElement = source.lastElement = nullptr;
		source.elementCount = 0;
		return *this;
	}

	// класс Итератор будет применяться как абстракция для обхода элементов списка	
	class Iter 
	{
	private:
		Element* currentElem; // указатель на текущий элемент списка
	public:
		explicit Iter(Element* element) : currentElem(element) {} // конструктор
		Iter& operator++() // префиксный инкремент
		{ 
			currentElem = currentElem->next; // перемещаем итератор
			return *this; // возвращаем итератор
		}
		bool operator==(const Iter& other) const // сравнение 2 итераторов
		{ 
			return currentElem == other.currentElem; // сравнение указателей на элемент
		}
		bool operator!=(const Iter& other) const // сравнение 2 итераторов
		{ 
			return currentElem != other.currentElem; // сравнение указателей на элемент
		}
		Type& operator*() // разыменование итератора (получение данных текущего элемента)
		{ 
			return currentElem->data; 
		}
	};

	Iter begin() const // возвращает итератор: указывающий на первый элемент контейнера (списка)
	{ 
		return Iter(firstElement); 
	}
	Iter end() const // возвращает итератор: указывающий на последний элемент контейнера (списка)
	{ 
		return Iter(nullptr); 
	}
};


#endif

