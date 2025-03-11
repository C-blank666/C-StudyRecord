#include<assert.h>
#include<iostream>
#include<vector>
#include<map>
using namespace std;
template<class K, class V>
struct AVLTreeNode {
	pair<K, V> _kv;
	AVLTreeNode* _parent;
	AVLTreeNode* _left;
	AVLTreeNode* _right;
	int _bf;
	AVLTreeNode(const pair<K, V>& kv) :_kv(kv), _parent(nullptr), _left(nullptr), _right(nullptr), _bf(0) {}
};
template<class K, class V>
class AVLTree {
	typedef AVLTreeNode<K, V> Node;
public:
	void RotateR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* parentParent = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;

		if (parentParent == nullptr) {
			subL->_parent = nullptr;
			_root = subL;
		}
		else {
			if (parent == parentParent->_left)
				parentParent->_left = subL;
			else
				parentParent->_right = subL;
		}
		subL->_bf = parent->_bf = 0;
	}
	void RotateL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* parentParent = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (parentParent == nullptr) {
			_root = subR;
			subR->_parent = nullptr;
		}
		else {
			if (parent == parentParent->_left)
				parentParent->_left = subR;
			else
				parentParent->_right = subR;
		}
		parent->_bf = subR->_bf = 0;
	}
	void RotateLR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(subL);
		RotateR(parent);

		if (bf == 0) {
			subL->_bf = 0;
			subLR->_bf = 0;
			parent->_bf = 0;
		}
		else if (bf == -1) {
			subL->_bf = 0;
			subLR->_bf = 0;
			parent->_bf = 1;
		}
		else if (bf == 1) {
			subL->_bf = -1;
			subLR->_bf = 0;
			parent->_bf = 0;
		}
		else assert(false);
	}
	void RotateRL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(subR);
		RotateL(parent);

		if (bf == 0) {
			subR->_bf = 0;
			subRL->_bf = 0;
			parent->_bf = 0;
		}
		else if (bf == 1) {
			subR->_bf = 0;
			subRL->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1) {
			subR->_bf = 1;
			subRL->_bf = 0;
			parent->_bf = 0;
		}
		else assert(false);
	}
	bool Insert(const pair<K, V>& kv) {
		if (_root == nullptr) {
			_root = new Node(kv);
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (kv.first < cur->_kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				return false;
			}
		}
		cur = new Node(kv);
		if (parent->_kv.first < kv.first) {
			parent->_right = cur;
		}
		else {
			parent->_left = cur;
		}
		cur->_parent = parent;

		while (parent) {
			if (parent->_left == cur) parent->_bf--;
			else parent->_bf++;
			if (parent->_bf == 0) break;
			else if (parent->_bf == 1 || parent->_bf == -1) {
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2) {
				//旋转
				if (parent->_bf == -2 && cur->_bf == -1)
					RotateR(parent);//右单旋
				else if (parent->_bf == 2 && cur->_bf == 1)
					RotateL(parent);//左单旋
				else if (parent->_bf == -2 && cur->_bf == 1)
					RotateLR(parent);//左右双旋
				else if (parent->_bf == 2 && cur->_bf == -1)
					RotateRL(parent);//右左双旋
				else assert(false);
				break;
			}
			else assert(false);
		}
		return true;
	}
	Node* find(const K& key) {
		Node* cur = _root;
		while (cur) {
			if (key > cur->_kv.first) {
				cur = cur->_right;
			}
			else if (key < cur->_kv.first) {
				cur = cur->_left;
			}
			else return cur;
		}
		return nullptr;
	}
	void GetInorderPrint() {
		inorderPrint(_root);
	}
private:
	void inorderPrint(Node* root) {
		if (root == nullptr) return;
		inorderPrint(root->_left);
		cout << root->_kv.first << ":" << root->_kv.first << endl;
		inorderPrint(root->_right);
	}
	Node* _root = nullptr;
};
int main() {
	AVLTree<int, int> t;
	int a1[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	//int a2[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	/*for (auto e : a1) {
		t.Insert({e,e});
	}*/
	for (auto e : a2) {
		t.Insert({ e,e });
	}
	t.GetInorderPrint();
	return 0;
}