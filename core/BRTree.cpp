#include "BRTree.h"

namespace red_black_tree {

bool isRed(Node* root) {
	return root != nullptr && root->isRed;
}

void rotateRight(Node* &root) {
	if (root == nullptr || root->left == nullptr) return;

	Node* newRoot = root->left;
	Node* subtree = newRoot->right;

	newRoot->right = root;
	root->left = subtree;
	root = newRoot;
}

void rotateLeft(Node* &root) {
	if (root == nullptr || root->right == nullptr) return;

	Node* newRoot = root->right;
	Node* subtree =	newRoot->left;

	newRoot->left = root;
	root->right = subtree;
	root = newRoot;
}

void balance(Node* &root) {
	if (root == nullptr || isRed(root)) return;

	if (isRed(root->left) && isRed(root->left->left)) {
		rotateRight(root);
	} else if (isRed(root->left) && isRed(root->left->right)) {
		rotateLeft(root->left);
		rotateRight(root);
	} else if (isRed(root->right) && isRed(root->right->right)) {
		rotateLeft(root);
	} else if (isRed(root->right) && isRed(root->right->left)) {
		rotateRight(root->right);
		rotateLeft(root);
	} else {
		return;
	}

	root->isRed = true;
	root->left->isRed = false;
	root->right->isRed = false;
}

void insertRecursive(Node*& root, int value) {
	if (root == nullptr) {
		Node* newNode = new Node{value, true, nullptr, nullptr};
		root = newNode;
		return;
	}

	if (value < root->value) {
		if (root->left == nullptr) {
			Node* newNode = new Node{value, true, nullptr, nullptr};
			root->left = newNode;
		} else {
			insertRecursive(root->left, value);
		}
	} else if (value > root->value) {
		if (root->right == nullptr) {
			Node* newNode = new Node{value, true, nullptr, nullptr};
			root->right = newNode;
		} else {
			insertRecursive(root->right, value);
		}
	} else {
		return;
	}

	balance(root);
}

void insert(Node* &root, int value) {
	insertRecursive(root, value);
	root->isRed = false;
}

bool balanceAfterDeleteLeft(Node*& root) {
	Node* sibling = root->right;

	if (isRed(sibling)) {
		sibling->isRed = false;
		root->isRed = true;
		rotateLeft(root);

		balanceAfterDeleteLeft(root->left);
		return false;
	}

	if (sibling == nullptr ||
		(!isRed(sibling->left) && !isRed(sibling->right))) {

		if (sibling != nullptr) {
			sibling->isRed = true;
		}

		if (isRed(root)) {
			root->isRed = false;
			return false;
		}

		return true;
	}

	if (!isRed(sibling->right)) {
		sibling->left->isRed = false;
		sibling->isRed = true;
		rotateRight(root->right);
		sibling = root->right;
	}

	sibling->isRed = root->isRed;
	root->isRed = false;
	sibling->right->isRed = false;
	rotateLeft(root);

	return false;
}

bool balanceAfterDeleteRight(Node* &root) {
	Node* sibling = root->left;

	if (isRed(sibling)) {
		sibling->isRed = false;
		root->isRed = true;
		rotateRight(root);

		balanceAfterDeleteRight(root->right);
		return false;
	}

	if (sibling == nullptr ||
		(!isRed(sibling->left) && !isRed(sibling->right))) {
		if (sibling != nullptr) {
			sibling->isRed = true;
		}

		if (isRed(root)) {
			root->isRed = false;
			return false;
		}

		return true;
	}

	if (!isRed(sibling->left)) {
		sibling->right->isRed = false;
		sibling->isRed = true;
		rotateLeft(root->left);
		sibling = root->left;
	}

	sibling->isRed = root->isRed;
	root->isRed = false;
	sibling->left->isRed = false;
	rotateRight(root);

	return false;
}

bool removeRecursive(Node* &root, int val, bool &blackHeightDecreased) {
	if (root == nullptr) {
		blackHeightDecreased = false;
		return false;
	}

	bool removed;

	if (val < root->value) {
		removed = removeRecursive(root->left, val, blackHeightDecreased);

		if (blackHeightDecreased) {
			blackHeightDecreased = balanceAfterDeleteLeft(root);
		}
	} else if (val > root->value) {
		removed = removeRecursive(root->right, val, blackHeightDecreased);

		if (blackHeightDecreased) {
			blackHeightDecreased = balanceAfterDeleteRight(root);
		}
	} else if (root->left != nullptr && root->right != nullptr) {
		Node* next = root->right;

		while (next->left != nullptr) {
			next = next->left;
		}

		root->value = next->value;

		removed = removeRecursive(root->right, next->value, blackHeightDecreased);

		if (blackHeightDecreased) {
			blackHeightDecreased = balanceAfterDeleteRight(root);
		}
	} else {
		Node* oldRoot = root;

    root = (root->left != nullptr) ? root->left : root->right;
		blackHeightDecreased = !oldRoot->isRed;

		if (blackHeightDecreased && isRed(root)) {
			root->isRed = false;
			blackHeightDecreased = false;
		}

		delete oldRoot;
		return true;
	}

	return removed;
}

bool removeElement(Node*& root, int value) {
	bool blackHeightDecreased = false;

	bool removed = removeRecursive(root, value, blackHeightDecreased);

	if (root != nullptr) {
		root->isRed = false;
	}

	return removed;
}

Node* searchElement(Node* root, int val) {
	if (root == nullptr) return nullptr;

	if (root->value == val) return root;

	if (val < root->value) return searchElement(root->left, val);
	return searchElement(root->right, val);
}

void printTree(Node* root) {
  if (root == nullptr) return;

  cout << root->value << (root->isRed ? "(R) " : "(B) ");
  printTree(root->left);
  printTree(root->right);
}

void init(Node* &root) {
	root = nullptr;
}

}