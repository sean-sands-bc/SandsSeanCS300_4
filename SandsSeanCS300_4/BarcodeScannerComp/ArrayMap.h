#pragma once

template <class K, class V>
class ArrayMap
{
private:
	K *keyArr = nullptr;
	V *valArr = nullptr;

	size_t sz = 0;
	size_t cap = 0;

public:
	ArrayMap(size_t c) :
		keyArr(new K[c]), valArr(new V[c]), cap(c) {}
	~ArrayMap() { clear(); }

	void insert(const K &k, const V &v);
	//void erase(const K &k);	//	
	const V &find(const K &k) const;

	bool empty() const { return sz == 0; }
	size_t size() const { return sz; }
	void clear() { if (keyArr) { delete[] keyArr; delete[] valArr; sz = 0; cap = 0; } }
};

template<class K, class V>
inline void ArrayMap<K, V>::insert(const K & k, const V & v)
{
	if (sz < cap)
	{
		keyArr[sz] = k;
		valArr[sz] = v;
		++sz;
		return;
	}
	throw 1;	//	full array
}

template<class K, class V>
inline const V &ArrayMap<K, V>::find(const K & k) const
{
	for (size_t i = 0; i < sz; ++i)
	{
		if (k == keyArr[i]) { return valArr[i]; }
	}

	throw 2;	//	not found
}
