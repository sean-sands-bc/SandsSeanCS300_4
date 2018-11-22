#pragma once

template <class K, class V>
struct Node
{
public:
	K key;
	V val;

	Node<K, V> *left;
	Node<K, V> *right;

	Node(const K &k, const V &v, Node<K, V> *l = nullptr, Node<K, V> *r = nullptr) :
		key(k), val(v), left(l), right(r) {}
};

template <class K, class V>
class BSTMap
{
private:
	Node<K, V> *root = nullptr;

	size_t sz = 0;

	void clear(Node<K, V> *r);
public:
	BSTMap() {}
	~BSTMap() { clear(); }

	void insert(const K &k, const V &v);
	//void erase(const K &k);	//	
	const V &find(const K &k) const;

	bool empty() const { return sz == 0; }
	size_t size() const { return sz; }
	void clear() { clear(root); root = nullptr; sz = 0; }
};

template<class K, class V>
inline void BSTMap<K, V>::clear(Node<K, V>* r)
{
	if (r)
	{
		clear(r->left);
		clear(r->right);
		delete r;
	}
}

template<class K, class V>
inline void BSTMap<K, V>::insert(const K & k, const V & v)
{
	if (root)
	{
		Node<K,V> *r = root;
		while (true)
		{
			if (k < r->key) 
			{ 
				if (r->left) 
				{ 
					r = r->left; continue; 
				} 
				r->left = new Node<K, V>(k, v); 
				++sz;
				return; 
			}

			if (k > r->key)
			{
				if (r->right)
				{
					r = r->right; continue;
				}
				r->right = new Node<K, V>(k, v);
				++sz;
				return;
			}

			throw 1;	//	duplicate key
		}
	}
	else
	{
		root = new Node<K, V>(k, v);
		++sz;
	}
}

template<class K, class V>
inline const V &BSTMap<K, V>::find(const K & k) const
{
	Node<K, V> *r = root;

	while (r)
	{
		if (k < r->key)
		{
			r = r->left;
			continue;
		}

		if (k > r->key)
		{
			r = r->right;
			continue;
		}

		return r->val;
	}
	
	throw 2;	//	not found
}
