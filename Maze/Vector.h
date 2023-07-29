#pragma once
#include <assert.h>

template <typename T>
class Vector
{
public:
	Vector(){ }

	~Vector()
	{
		if(_buffer)
			delete[] _buffer;
	}

	void clear()
	{
		// _capacity 는 그대로, _size 만 0 으로.
		
		//TODO : 소멸
		if (_buffer)
		{
			delete[] _buffer;
			_buffer = new T[_capacity];
		}

		_size = 0;
	}

	void push_back(const T& data)
	{
		// 핵심적인 부분
		if (_size == _capacity)
		{
			// 증설 작업
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity);
		}

		// 데이터 저장
		_buffer[_size] = data;
		
		// 데이터 개수 증가
		_size++;
	}

	void pop_back()
	{
		// TODO: 소멸
		_size--;
	}

	T& back()
	{
		return _buffer[_size - 1];
	}

	void resize(int size)
	{
		reserve(size);
		_size = size;
	}

	// 새로운 capacity를 요청하면 크기에 따라 증설작업을 커지는 방향으로만 해준다.
	void reserve(int capacity)
	{
		if (_capacity >= capacity)
			return;

		_capacity = capacity;

		T* newData = new T[_capacity]; // 새로운 방들을 잡아주기

		for (int i = 0; i < _size; i++)
			newData[i] = _buffer[i];

		if (_buffer)
			delete[] _buffer;

		_buffer = newData;
	}

	T& operator[](int index)
	{
		assert(index >= 0 && index < _size);
		return _buffer[index];

		/*
		`assert`는 C 언어에서 쓰이는 디버깅 목적의 매크로 함수입니다. 
		위 코드에서 `assert` 함수는 입력받은 `index`가 0 이상이고 `_size`보다 작은지를 검사하여 그렇지 않은 경우 프로그램을 종료하게 됩니다. 이렇게 프로그램이 예상치 못한 동작을 할 경우 에러 메시지와 함께 프로그램을 강제 종료시켜주는 역할을 합니다. 
		`assert` 함수는 디버깅 목적으로만 사용되며, 
		일반 사용자에게는 에러 메시지를 표시하지 않습니다.
		*/
	}

	int size() { return _size; }
	int capacity() { return _capacity; }

private:
	T*   _buffer = nullptr;
	int  _size = 0;
	int  _capacity = 0;
};

