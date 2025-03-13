#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <stdexcept>
#include <utility>

template<typename Type>
class SinglyList {
private:
	struct Element {
		Type data;
		Element* next = nullptr;
	};

	Element* firstElement;
	Element* lastElement;
	size_t elementCount;

	Element* fetchElement(size_t index) const
	{
		if (index >= elementCount)
			throw std::out_of_range("Index out of range");
		Element* temp = firstElement;
		for (size_t i = 0; i < index; ++i)
			temp = temp->next;
		return temp;
	}

public:
	SinglyList() : elementCount(0), firstElement(nullptr), lastElement(nullptr) {};
	SinglyList(const SinglyList& source) : elementCount(0), firstElement(nullptr), lastElement(nullptr)
	{
		for (Element* node = source.firstElement; node; node = node->next)
			addToEnd(node->data);
	}
	SinglyList(SinglyList&& source) noexcept : firstElement(source.firstElement), lastElement(source.lastElement), elementCount(source.elementCount)
	{
		source.firstElement = source.lastElement = nullptr;
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

	void addToEnd(const Type& data)
	{
		Element* newNode = new Element{ data };
		if (lastElement)
			lastElement->next = newNode;
		else
			firstElement = newNode;
		lastElement = newNode;
		++elementCount;
	}
	void addToStart(const Type& data)
	{
		Element* newNode = new Element{ data, firstElement };
		firstElement = newNode;
		if (!lastElement)
			lastElement = newNode;
		++elementCount;
	}
	void eraseAt(size_t index)
	{
		if (index >= elementCount)
			throw std::out_of_range("Index out of range");
		Element* toRemove = nullptr;
		if (index == 0)
		{
			toRemove = firstElement;
			firstElement = firstElement->next;
			if (!firstElement) lastElement = nullptr;
		}
		else
		{
			Element* prev = fetchElement(index - 1);
			toRemove = prev->next;
			prev->next = toRemove->next;
			if (index == elementCount - 1)
				lastElement = prev;
		}
		delete toRemove;
		--elementCount;
	}
	void reset()
	{
		while (firstElement)
		{
			Element* temp = firstElement;
			firstElement = firstElement->next;
			delete temp;
		}
		lastElement = nullptr;
		elementCount = 0;
	}

	Type& getItem(size_t index)
	{
		return fetchElement(index)->data;
	}
	const Type& getItem(size_t index) const
	{
		return fetchElement(index)->data;
	}

	bool operator==(const SinglyList& source) const noexcept
	{
		if (elementCount != source.elementCount)
			return false;
		Element* current1 = firstElement;
		Element* current2 = source.firstElement;
		while (current1)
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
		if (this == &source)
			return *this;
		reset();
		for (Element* node = source.firstElement; node; node = node->next)
			addToEnd(node->data);
		return *this;
	}
	SinglyList& operator=(SinglyList&& source) noexcept
	{
		if (this == &source)
			return *this;
		reset();
		firstElement = source.firstElement;
		lastElement = source.lastElement;
		elementCount = source.elementCount;
		source.firstElement = source.lastElement = nullptr;
		source.elementCount = 0;
		return *this;
	}

	class Iter {
	private:
		Element* currentElem;
	public:
		explicit Iter(Element* element) : currentElem(element) {}
		Iter& operator++() { currentElem = currentElem->next; return *this; }
		bool operator==(const Iter& other) const { return currentElem == other.currentElem; }
		bool operator!=(const Iter& other) const { return currentElem != other.currentElem; }
		Type& operator*() { return currentElem->data; }
	};

	Iter begin() const { return Iter(firstElement); }
	Iter end() const { return Iter(nullptr); }
};


#endif

