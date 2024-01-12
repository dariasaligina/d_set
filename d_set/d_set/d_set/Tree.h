#pragma once
#include<vector>

using namespace std;

template < typename T > class d_set;

template < typename T > class Tree {
private:

    int prior;
    T key;
    Tree < T >* l = 0, * r = 0;

    friend class d_set < T >;

    Tree() {}

    Tree(T _key) {
        key = _key, prior = rand(), l = 0, r = 0;
    }

    friend void split(Tree < T >* t, T key, Tree < T >*& l, Tree < T >*& r) {
        if (!t)
            l = r = NULL;
        else if (key < t->key) {
            split(t->l, key, l, t->l);
            r = t;
        }
        else {
            split(t->r, key, t->r, r);
            l = t;
        }
    }

    friend void insert_nd(Tree < T >*& t, Tree < T >* it) {
        if (!t)
            t = it;
        else if (it->prior > t->prior) {
            split(t, it->key, it->l, it->r);
            t = it;
        }
        else
            insert_nd(it->key < t->key ? t->l : t->r, it);
    }

    friend void merge(Tree < T >*& t, Tree < T >* l, Tree < T >* r) {
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior > r->prior) {
            merge(l->r, l->r, r);
            t = l;
        }
        else {
            merge(r->l, l, r->l);
            t = r;
        }
    }

    friend void erase_nd(Tree < T >*& t, T key) {
        if (!t) return;
        if (t->key == key) {
            merge(t, t->l, t->r);
            return;
        }
        else
            erase_nd(key < t->key ? t->l : t->r, key);
    }

    friend bool is_in_nd(Tree < T >* t, T key) {
        if (!t) return 0;
        if (t->key == key)
            return 1;
        else
            return is_in_nd(key < t->key ? t->l : t->r, key);
    }

    friend void to_vector_nd(Tree < T >* root, vector < T >& ans) {
        if (root->l) to_vector_nd(root->l, ans);
        ans.push_back(root->key);
        if (root->r) to_vector_nd(root->r, ans);
    }

    Tree < T >* copy() {
        Tree < T >* ans = new Tree(key);
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
        if (this) {
            if (l) {
                l->del();
                l = 0;
            }
            if (r) {
                r->del();
                r = 0;
            }
            free(this);
        }
    }

};
