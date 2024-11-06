#pragma once

template<typename T>
class ObjectPool
{
protected:
	using iter = typename std::list<T*>::iterator;
	using iter_const = typename std::list<T*>::const_iterator;

public:
	std::list<T*> unused;
	std::list<T*> used;

public:
	ObjectPool(int initSize = 10)
	{
		for (int i = 0; i < initSize; ++i)
		{
			auto obj = new T();
			obj->Init();
			unused.push_back(obj);
		}
	}

	~ObjectPool()
	{
		for (auto obj : unused)
		{
			delete obj;
		}
		for (auto obj : used)
		{
			delete obj;
		}
	}

	template<typename ...Args>
	T* Take(Args&& ...args)
	{
		if (unused.empty())
		{
			auto obj = new T(std::forward(args)...);
			obj->Init();
			obj->Reset();
			used.push_back(obj);
			return obj;
		}

		auto obj = unused.front();
		unused.pop_front();
		used.push_back(obj);
		obj->SetActive(true);
		obj->Reset();
		return obj;
	}

	void Return(T* obj)
	{
		auto find = std::find(used.begin(), used.end(), obj);
		if (find == used.end())
		{
			std::cout << "Invaild Obj" << std::endl;
			return;
		}
		used.erase(find);
		obj->SetActive(false);
		unused.push_back(obj);
	}

	inline iter begin()					{ return used.begin(); }
	inline iter end()					{ return used.end(); }
	inline iter_const begin() const		{ return used.begin(); }
	inline iter_const end() const		{ return used.end(); }
};