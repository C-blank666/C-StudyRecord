#include<iostream>
#include<map>
#include<vector>
#include<assert.h>
using namespace std;
template<class K,class V>
struct AVLTreeNode {
	pair<K, V> _kv;
	AVLTreeNode<K,V>* _parent;
	AVLTreeNode<K,V>* _left;
	AVLTreeNode<K,V>* _right;
	int _bf;
	AVLTreeNode(const pair<K, V>& kv) :_kv(kv), _parent(nullptr), _left(nullptr), _right(nullptr),_bf(0) {}
};
template<class K,class V>
class AVLTree {
	typedef AVLTreeNode<K,V> Node;
public:
	bool Insert(const pair<K, V>& kv) {
		if (_root == nullptr) {
			_root = new Node(kv);
			return true;
		}
		
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur) {
			if (kv > cur->_kv.first) {
				parent = cur;
				cur = cur->_right;
				cur->_parent = parent;
			}
			else if (kv < cur->_kv.first) {
				parent = cur;
				cur = cur->_left;
				cur->_parent = parent;
			}
			else return false;
		}
		cur = new Node(kv);
		if (cur->_kv.first > parent->_kv.first)
			cur = parent->_right;
		else
			cur = parent->_left;
		cur->_parent = parent;
		while (parent) {
			if (parent->_left == cur)
				parent->_bf--;
			else
				parent->_bf++;
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == 1 || parent->_bf == -1) {
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2) {
				//旋转
			}
			else assert(false);
		}
	}
private:
	Node* _root;
};
int main() {
	return 0;
}