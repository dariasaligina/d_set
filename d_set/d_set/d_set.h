#pragma once
#include "Tree.h"


template<typename T> class d_set {
public:

	~d_set() {
		if (root)
			root->destruct();
		root = 0;
	}

	d_set() {
		root = 0;
	}

	d_set(const d_set& st) {
		this->root = st.root->copy();
	}

	void operator=(d_set st) {
		root = st.root->copy();
	}

	void insert(T n) {
		if (!(is_in(n))) {
			insert_nd(root, new Tree<T>(n));
		}
	}

	void erase(T n) {
		erase_nd(root, n);
	}

	vector<T> to_vector() {
		vector<T>ans;
		if (root)
			to_vector_nd(root, ans);
		return ans;
	}

	d_set operator +(d_set& r) {
		d_set ans = this->copy();
		vector<T> v = r.to_vector();
		for (auto i : v) {
			ans.insert(i);
		}
		return ans;
	}

	d_set operator&(d_set& s2) {
		d_set st;
		vector<T> v = to_vector();
		for (auto i : v) {
			if (s2.is_in(i)) {
				st.insert(i);
			}
		}
		return st;
	}

	d_set operator-(d_set& r) {
		vector<T> v = r.to_vector();
		d_set ans = this->copy();
		for (auto i : v) {
			ans.erase(i);
		}
		return ans;
	}

	int size() {
		return root->update_size();
	}

	bool is_in(T n) {
		return is_in_nd(root, n);
	}

	bool is_in(d_set& st) {
		vector<T> v = st.to_vector();
		for (auto i : v) {
			if (!is_in(i)) return 0;
		}
		return 1;
	}

	d_set copy() {
		d_set ans;
		ans.root = root->copy();
		return ans;
	};

	void clear() {
		if (root) root->del();
		root = 0;
	}

	friend void swap(d_set& s1, d_set& s2) {
		Tree<T>* t1 = s1.root;
		s1.root = s2.root;
		s2.root = t1;
	}

private:
	Tree<T>* root = 0;
};
