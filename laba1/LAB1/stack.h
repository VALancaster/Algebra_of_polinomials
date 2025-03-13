#ifndef __STACK_H__
#define __STACK_H__

using namespace std;

template <class T>
class TStack
{
	int top;
	size_t size;
	T* pMem;

public:
	TStack() : top(-1), size(1), pMem(new T[size]) {}

	~TStack() {
		delete[] pMem;
	}

	TStack(const TStack&) = delete;
	TStack& operator=(const TStack&) = delete;


	TStack(TStack&& other) noexcept {
		other.pMem = nullptr;
		other.top = -1;
		other.size = 0;
	}


	TStack& operator=(TStack&& other) noexcept {

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
  
	size_t GetSize() const {
		return top + 1;
	}

	bool IsEmpty() const {
		return top == -1;
	}

	T Pop() {
		if (IsEmpty())
			throw std::underflow_error("Stack is empty");
		return pMem[top--];
	}

	void Push(const T& val) {
		if (top == size - 1)
		{
			size *= 2;
			T* tmp = new T[size];
			std::copy(pMem, pMem + top + 1, tmp);
			delete[] pMem;
			pMem = tmp;
		}
		pMem[++top] = val;
	}
};

#endif
