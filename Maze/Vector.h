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
		// _capacity �� �״��, _size �� 0 ����.
		
		//TODO : �Ҹ�
		if (_buffer)
		{
			delete[] _buffer;
			_buffer = new T[_capacity];
		}

		_size = 0;
	}

	void push_back(const T& data)
	{
		// �ٽ����� �κ�
		if (_size == _capacity)
		{
			// ���� �۾�
			int newCapacity = static_cast<int>(_capacity * 1.5);
			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity);
		}

		// ������ ����
		_buffer[_size] = data;
		
		// ������ ���� ����
		_size++;
	}

	void pop_back()
	{
		// TODO: �Ҹ�
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

	// ���ο� capacity�� ��û�ϸ� ũ�⿡ ���� �����۾��� Ŀ���� �������θ� ���ش�.
	void reserve(int capacity)
	{
		if (_capacity >= capacity)
			return;

		_capacity = capacity;

		T* newData = new T[_capacity]; // ���ο� ����� ����ֱ�

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
		`assert`�� C ���� ���̴� ����� ������ ��ũ�� �Լ��Դϴ�. 
		�� �ڵ忡�� `assert` �Լ��� �Է¹��� `index`�� 0 �̻��̰� `_size`���� �������� �˻��Ͽ� �׷��� ���� ��� ���α׷��� �����ϰ� �˴ϴ�. �̷��� ���α׷��� ����ġ ���� ������ �� ��� ���� �޽����� �Բ� ���α׷��� ���� ��������ִ� ������ �մϴ�. 
		`assert` �Լ��� ����� �������θ� ���Ǹ�, 
		�Ϲ� ����ڿ��Դ� ���� �޽����� ǥ������ �ʽ��ϴ�.
		*/
	}

	int size() { return _size; }
	int capacity() { return _capacity; }

private:
	T*   _buffer = nullptr;
	int  _size = 0;
	int  _capacity = 0;
};

