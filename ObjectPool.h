#pragma once

template<class T, size_t initNum = 100>
class ObjectPool
{
public:
	ObjectPool()
	{
		_start = _end = malloc(initNum*sizeof(T));
	}

	//T* Alloc()
	T* NEW()
	{
		if (_start == _end)
		{
			_start = _end = malloc(initNum*sizeof(T));
		}
		
		T* obj = _start;
		_start += sizeof(T);

		//new的定位表达式，对一段已有空间调构造函数初始化,可以显式地调用构造函数
		new(obj)T;

		return obj;//不能直接return，要对空间先初始化

		void Delete(T* ptr)
		{
			ptr->~T();

			*(int*)ptr = _freeList;
			_freeList = ptr;
		}
	}
private:
	char* _start;
	char* _end;//管理内存池指针

	T* _freeList;
};
