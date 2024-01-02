#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<typename T> class Node {
private:
	int prior, size;
	T key;
	Node<T>* l = 0, * r = 0;
public:
	int update_size() {
		int s = 1;
		if (l) s += l->update_size();
		if (r) s += r->update_size();
		size = s;
		return s;
	}
	
	Node(T _key) { key = _key, prior = rand(), l = 0, r = 0; }
	friend void split(Node<T>* t, T key, Node<T>*& l, Node<T>*& r) {
		if (!t)
			l = r = NULL;
		else if (key < t->key)
			split(t->l, key, l, t->l), r = t;
		else
			split(t->r, key, t->r, r), l = t;
	}

	friend void insert_nd(Node<T>*& t, Node<T>* it) {
		if (!t)
			t = it;
		else if (it->prior > t->prior)
			split(t, it->key, it->l, it->r), t = it;
		else
			insert_nd(it->key < t->key ? t->l : t->r, it);
	}

	friend void merge(Node<T>*& t, Node<T>* l, Node<T>* r) {
		if (!l || !r)
			t = l ? l : r;
		else if (l->prior > r->prior)
			merge(l->r, l->r, r), t = l;
		else
			merge(r->l, l, r->l), t = r;
	}

	friend void errase_nd(Node<T>*& t, T key) {
		if (!t) return;
		if (t->key == key)
			merge(t, t->l, t->r);
		else
			errase_nd(key < t->key ? t->l : t->r, key);
	}

	friend Node<T>* unite(Node<T>* l, Node<T>*r) {
		if (!l || !r)  return l ? l : r;
		if (l->prior < r->prior)  swap(l, r);
		Node<T>* lt, rt;
		split(r, l->key, lt, rt);
		l->l = unite(l->l, lt);
		l->r = unite(l->r, rt);
		return l;
	}
	friend bool is_in_nd(Node<T>* t, T key) {
		if (!t) return 0;
		if (t->key == key)
			return 1;
		else
			return is_in_nd(key < t->key ? t->l : t->r, key);
	}

	friend void to_vector_nd(Node<T>* root, vector<T> &  ans) {
		if (root->l) to_vector_nd(root->l, ans);
		ans.push_back(root->key);
		if (root->r) to_vector_nd(root->r, ans);
	}
	Node<T>* copy() {
		Node<T>* ans= new Node(key);
		ans->key = key;
		ans->prior = prior;
		ans->size = size;
		
		if (l) 
			ans->l = l->copy();
		if (r) 
			ans->r = r->copy();
		return ans;
	}

	void del() {
		if (l) l->del();
		if (r) r->del();
		delete l;
		delete r;
		l = 0;
		r = 0;
		
	}
};
/*
Node<T>* unite(Node<T>* l, Node<T>* r) {
	if (!l || !r)  return l ? l : r;
	if (l->prior < r->prior)  swap(l, r);
	pitem lt, rt;
	split(r, l->key, lt, rt);
	l->l = unite(l->l, lt);
	l->r = unite(l->r, rt);
	return l;
}
*/

template<typename T> class myset {
public:
	~myset() {
		for (auto i : to_vector()) {
			cout << i<< ' ';
		}
		cout << "\n";
		if (root) root->del();
		delete root;
		root = 0;
	}
	myset() {
	}
	myset(Node<T>* rt) {
		root = rt;
	}
	void insert(T n) {
		errase_nd(root, n);
		insert_nd(root, new Node<T>(n));
	}
	void errase(T n) {
		errase_nd(root, n);
	}
	vector<T> to_vector() {
		vector<T>ans;
		if (root) 
			to_vector_nd(root, ans);
		return ans;
	}
	friend myset join(myset& l, myset& r) {
		myset st = l.copy();
		vector<T> v = r.to_vector();
		for (auto i : v) {
			st.insert(i);
		}
		return st;
	}
	friend myset intersection(myset s1, myset s2) {
		myset st = s1.copy();
		vector<T> v = (s1 - s2).to_vector();
		for (auto i : v) {
			st.errase(i);
		}
		return st;
	}
	myset operator-(myset r) {
		vector<T> v = r.to_vector();
		myset ans = this->copy();
		for (auto i : v) {
			ans.errase(i);
		}
		return ans;
	}
	int size() {
		return root->update_size();
	}
	bool is_in(T n) {
		return is_in_nd(root, n);
	}
	bool is_in(myset st) {
		vector<T> v = st.to_vector();
		for (auto i : v) {
			if (!is_in(i)) return 0;
		}
		return 1;
	}

	myset copy() {
		
		
		return myset(root->copy());
	};

private:
	Node<T>* root = 0;
};