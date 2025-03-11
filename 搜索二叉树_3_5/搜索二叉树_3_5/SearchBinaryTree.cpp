#include<iostream>
#include<vector>
using namespace std;
//搜索二叉树增删查操作代码
template<class K>
struct BSTNode {
	K _key;
	BSTNode* _left;
	BSTNode* _right;

	BSTNode(const K& key) :_key(key), _left(nullptr), _right(nullptr) {}
};
template<class K>
class BSTree {
	typedef BSTNode<K> Node;
public:
	bool Insert(const K& key) {
		if (_root == nullptr) {
			_root = new Node(key);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur) {
			if (key < cur->_key) {
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key) {
				parent = cur;
				cur = cur->_right;
			}
			else return false;	
		}
		cur = new Node(key);
		if (key > parent->_key) parent->_right = cur;
		else parent->_left = cur;
		return true;
	}
	void Print() {
		Print_p(_root);
		cout << endl;
	}
	bool Find(const K& key) {
		Node* cur = _root;
		while (cur) {
			if (key < cur->_key) cur = cur->_left;
			else if (key > cur->_key) cur = cur->_right;
			else return true;
		}
		return false;
	}
	bool Erase(const K& key) {
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur) {
			if (key < cur->_key) {
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key) {
				parent = cur;
				cur = cur->_right;
			}
			else {
				if (cur->_left == nullptr) {
					if (parent == nullptr) _root = cur->_right;
					else{
						if (parent->_left == cur) parent->_left = cur->_right;
						else parent->_right = cur->_right;
					}
					delete cur;
					return true;
				}
				else if (cur->_right == nullptr) {
					if (parent == nullptr) _root = cur->_left;
					else{
						if (parent->_left == cur) parent->_left = cur->_left;
						else parent->_right = cur->_left;
					}
					delete cur;
					return true;
				}
				else {
					Node* MinRightP = cur;
					Node* MinRight = cur->_right;
					while (MinRight->_left) {
						MinRightP = MinRight;
						MinRight = MinRight->_left;
					}
					cur->_key = MinRight->_key;
					if (MinRightP->_left == MinRight) MinRightP->_left = MinRight->_right;
					else MinRightP->_right = MinRight->_right;
					delete MinRight;
					return true;
				}
			}
		}
		return false;
	}
private:
	void Print_p(Node* _root) {
		if (_root == nullptr) return;
		Print_p(_root->_left);
		if (_root->_key >= 10) cout << _root->_key << " ";
		else cout << "0" << _root->_key << " ";
		Print_p(_root->_right);
	}
	Node* _root = nullptr;
};



int main() {
	vector<int> arr = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	BSTree<int> b;
	for (auto e : arr) {
		b.Insert(e);
	}
	b.Print();
	for (auto e : arr) {
		b.Erase(e);
		b.Print();
	}
	return 0;
}