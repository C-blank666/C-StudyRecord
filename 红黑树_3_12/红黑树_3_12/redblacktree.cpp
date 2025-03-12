#include<iostream>
#include<map>
#include<assert.h>
using namespace std;

enum Colour{
	RED,
	BLACK
};

template<class K,class V>
struct RBTreeNode {
	pair<K, V> _kv;
	RBTreeNode<K,V>* _left;
	RBTreeNode<K,V>* _right;
	RBTreeNode<K,V>* _parent;
	Colour _col;
	RBTreeNode(pair<K, V> kv) :_kv(kv), _left(nullptr), _right(nullptr), _parent(nullptr){}
};

template<class K,class V>
class RBTree {
	typedef RBTreeNode<K, V> Node;
public:
	void RotateL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* parentP = parent->_parent;

		parent->_parent = subR;
		subR->_left = parent;

		if (parentP == nullptr) {
			subR = nullptr;
			_root = subR;
		}
		else {
			if (parentP->_left == parent)
				parentP->_left = subR;
			else
				parentP->_right = subR;
			subR->_parent = parentP;
		}
	}
	void RotateR(Node* parent) {
		Node* subL = parent->_right;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* parentP = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parentP == nullptr) {
			subL->_parent = nullptr;
			_root = subL;
		}
		else {
			if (parentP->left == parent)
				parentP->_left = subL;
			else
				parent->_right = subL;
			subL->_parent = parentP;
		}
	}
	bool Insert(const pair<K,V>& kv) {
		if (_root == nullptr) {
			_root = new Node(kv);
			_root->_col = BLACK;//根节点必须是黑色节点
			return;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur) {
			if (kv.first > cur->_kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else if (kv.first < cur->_kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				return false;
			}
		}
		cur = new Node(kv);//
		cur->_col = RED;//这里新插入的节点必须是红色节点
		if (kv.first > parent->_kv.first)
			parent->_right = cur;
		else
			parent->_left = cur;
		cur->_parent = parent;
		while (parent&& parent->_col = RED) {
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent) {
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED) {
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}//变色
				else
				{
					if (parent->_left == cur) {
						RotateR(grandfather);
						grandfather->_col = RED;
						parent->_col = BLACK;
					}//单旋，变色
					else {
						RotateL(parent);
						RotateR(grandfather);
						grandfather->_col = RED;
						cur->_col = BLACK;
					}//双旋，变色
					break;
				}
			}
			else {
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED) {
					parent->_col = uncle->_col = RED;
					grandfather->_col = BLACK;

					cur = grandfather;
					parent = cur->_parent;
				}
				else {
					if (parent->_right == cur) {
						RotateL(grandfather);
						grandfather->_col = RED;
						parent->_col = BLACK;
					}
					else {
						RotateR(parent);
						RotateL(grandfather);
						grandfather->_col = RED;
						cur->_col = BLACK;
					}
					break;
				}
			}
			_root->_col = BLACK;
			return true;
		}
	}
private:
	Node* _root = nullptr;
};
int main() {
	return 0;
}