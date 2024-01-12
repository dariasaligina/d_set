#pragma once
#include "Tree.h"


template<typename T> class d_set {
public:

	~d_set() {
		if (root)
			root->del();
		root = 0;
	}

	d_set() {
		root = 0;
	}

	d_set(const d_set& st) {
		this->root = st.root->copy();
		this->s = st.s;
	}

	void operator=(d_set<T> st) {
		root = st.root->copy();
		s = st.s;
	}

	bool operator == (d_set<T>& r) {
		vector<T> v1 = this->to_vector(), v2 = r.to_vector();
		return (v1 == v2);
	}

	bool operator != (d_set<T>& r) {
		vector<T> v1 = to_vector(), v2 = r.to_vector();
		return v1 != v2;
	}

	bool operator > (d_set<T>& r) {
		vector<T> v1 = to_vector(), v2 = r.to_vector();
		return v1 > v2;
	}

	bool operator >= (d_set<T>& r) {
		vector<T> v1 = to_vector(), v2 = r.to_vector();
		return v1 >= v2;
	}

	bool operator < (d_set<T>& r) {
		vector<T> v1 = to_vector(), v2 = r.to_vector();
		return v1 < v2;
	}

	bool operator <= (d_set<T>& r) {
		vector<T> v1 = to_vector(), v2 = r.to_vector();
		return v1 <= v2;
	}

	void insert(T n) {
		if (!(is_in(n))) {
			insert_nd(root, new Tree<T>(n));
			s++;
		}
	}

	void erase(T n) {
		if (is_in(n)) {
			erase_nd(root, n);
			s--;
		}
	}

	vector<T> to_vector() {
		vector<T>ans;
		if (root)
			to_vector_nd(root, ans);
		return ans;
	}

	operator vector<T>() {
		return to_vector();
	}

	friend vector<T> to_vector(d_set<T>& st) {
		return st.to_vector();
	}

	d_set<T> operator +(d_set<T>& r) {
		d_set<T> ans = this->copy();
		vector<T> v = r.to_vector();
		for (auto i : v) {
			ans.insert(i);
		}
		return ans;
	}

	friend void operator += (d_set<T>& l, d_set<T>& r) {
		vector<T> v = r.to_vector();
		for (auto i : v) {
			l.insert(i);
		}
	}

	d_set<T> operator&(d_set<T>& s2) {
		d_set<T> st;
		vector<T> v = to_vector();
		for (auto i : v) {
			if (s2.is_in(i)) {
				st.insert(i);
			}
		}
		return st;
	}

	friend void operator &= (d_set<T>& s1, d_set<T>& s2) {
		vector<T> v = s1.to_vector();
		for (auto i : v) {
			if (!s2.is_in(i)) {
				s1.erase(i);
			}
		}

	}

	d_set<T> operator-(d_set<T>& r) {
		vector<T> v = r.to_vector();
		d_set<T> ans = this->copy();
		for (auto i : v) {
			ans.erase(i);
		}
		return ans;
	}

	friend void operator -= (d_set<T>& l, d_set<T>& r) {
		vector<T> v = r.to_vector();
		for (auto i : v) {
			l.erase(i);
		}
	}

	int size() {
		return s;
	}

	friend int size(d_set<T>& st) {
		return st.size();
	}

	bool is_in(T n) {
		return is_in_nd(root, n);
	}

	bool is_in(d_set<T>& st) {
		vector<T> v = st.to_vector();
		for (auto i : v) {
			if (!is_in(i)) return 0;
		}
		return 1;
	}

	d_set<T> copy() {
		d_set<T> ans;
		ans.root = root->copy();
		ans.s = s;
		return ans;
	};

	friend d_set<T> copy(d_set<T>& st) {
		return st.copy();
	}

	void clear() {
		if (root) root->del();
		root = 0;
		s = 0;
	}

	friend void clear(d_set<T>& st) {
		st.clear();
	}

	friend void swap(d_set<T>& s1, d_set<T>& s2) {
		Tree<T>* t1 = s1.root;
		s1.root = s2.root;
		s2.root = t1;
		swap(s1.s, s2.s);
	}

private:
	int s = 0;
	Tree<T>* root = 0;
};
