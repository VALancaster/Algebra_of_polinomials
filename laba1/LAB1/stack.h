#ifndef __STACK_H__
#define __STACK_H__

using namespace std;

template <class T>
class TStack
{
private:
	T* pMem;
	size_t size;
	int top;
public:
	TStack(int sz = 1) 
	{
		size = sz;
		top = -1;
		if (sz < 1)
			throw out_of_range("Stack size should be greater or equal than 1");
		pMem = new T[size];
	}
	TStack(const TStack&) = delete;
	TStack(TStack&& other) noexcept 
	{
		other.pMem = nullptr;
		other.top = -1;
		other.size = 0;
	}

	~TStack() 
	{
		delete[] pMem;
	}

	
	TStack& operator=(const TStack&) = delete;
	TStack& operator=(TStack&& other) noexcept 
	{
		if (this != &other)
		{
			delete[] pMem;
			top = other.top;
			size = other.size;
			pMem = other.pMem;
			other.pMem = nullptr;
			other.top = -1;
			other.size = 0;
		}
		return *this;
	}
  
	size_t GetSize() const 
	{
		return size;
	}	
	bool IsEmpty() const 
	{
		return top == -1;
	}
	bool IsFull() const
	{
		return top == size - 1;
	}

	T Pop() 
	{
		if (IsEmpty())
			throw out_of_range("Stack is empty");
		return pMem[top--];
	}
	void Push(const T& val) 
	{
		if (IsFull())
		{
			size *= 2;
			T* tmp = new T[size];
			copy(pMem, pMem + top + 1, tmp);
			delete[] pMem;
			pMem = tmp;
		}
		pMem[++top] = val;
	}
	T GetTop()
	{
		if (IsEmpty())
			throw out_of_range("Stack is empty");
		return pMem[top];
	}
};

#endif
