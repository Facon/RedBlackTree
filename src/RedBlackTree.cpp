#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() : root(nullptr)
{}

RedBlackTree::~RedBlackTree()
{
	removeAll(root);
}

void RedBlackTree::removeAll(Node* node)
{
	if (node->left != nullptr)
	{
		removeAll(node->left);
	}

	if (node->right != nullptr)
	{
		removeAll(node->right);
	}

	delete node;
	node = nullptr;
}

bool RedBlackTree::isRed(const Node* const node) const
{
	if (node == nullptr)
	{
		return false;
	}

	return node->isRed;
}

RedBlackTree::Node* RedBlackTree::rotateLeft(Node* node) const
{
	Node* right = node->right;
	node->right = right->left;
	right->left = node;
	right->isRed = right->left->isRed;
	right->left->isRed = true;
	right->size = node->size;
	node->size = 1 + size(node->left) + size(node->right);

	return right;
}

size_t RedBlackTree::size() const
{
	return size(root);
}

size_t RedBlackTree::size(const Node* const node) const
{
	if (node == nullptr)
	{
		return 0u;
	}
	
	return node->size;
}

RedBlackTree::Node* RedBlackTree::rotateRight(Node* node) const
{
	Node* left = node->left;
	node->left = left->right;
	left->right = node;
	left->isRed = left->right->isRed;
	left->right->isRed = true;
	left->size = node->size;
	node->size = 1 + size(node->left) + size(node->right);

	return left;
}

void RedBlackTree::flipColors(Node* node) const
{
	node->isRed = !node->isRed;
	node->left->isRed = !node->left->isRed;
	node->right->isRed = !node->right->isRed;
}

void RedBlackTree::insert(int32_t key)
{
	root = insert(root, key);
	root->isRed = false;
}

RedBlackTree::Node* RedBlackTree::insert(Node* node, int32_t key) const
{
	if (node == nullptr)
	{
		return createNode(key);
	}
	
	insertAsChild(node, key);
	return rebalanceNode(node);
}

RedBlackTree::Node* RedBlackTree::createNode(int32_t key) const
{
	return new Node{ key, true, 1 };
}

void RedBlackTree::insertAsChild(Node* node, int32_t key) const
{
	if (key < node->key)
	{
		node->left = insert(node->left, key);
	}
	else if (key > node->key)
	{
		node->right = insert(node->right, key);
	}
	else
	{
		node->key = key;
	}
}

RedBlackTree::Node* RedBlackTree::rebalanceNode(Node* node) const
{
	auto isLeftNodeRed = isRed(node->left);
	auto isRightNodeRed = isRed(node->right);

	if (!isLeftNodeRed && isRightNodeRed)
	{
		node = rotateLeft(node);
	}
	if (isLeftNodeRed && isRed(node->left->left))
	{
		node = rotateRight(node);
	}
	if (isLeftNodeRed && isRightNodeRed)
	{
		flipColors(node);
	}

	node->size = size(node->left) + size(node->right) + 1;

	return node;
}

bool RedBlackTree::contains(int32_t key) const
{
	return contains(root, key);
}

bool RedBlackTree::contains(Node* node, int32_t key) const
{
	while (node != nullptr)
	{
		if (key < node->key)
		{
			node = node->left;
		}
		else if (key > node->key)
		{
			node = node->right;
		}
		else
		{
			return true;
		}
	}

	return false;
}

void RedBlackTree::remove(int32_t key)
{
	if (!contains(key))
	{
		return;
	}

	recolorRootAsRed();
	root = remove(root, key);
	recolorRootAsBlack();
}

void RedBlackTree::recolorRootAsRed()
{
	if (!isRed(root->left) && !isRed(root->right))
	{
		root->isRed = true;
	}
}

RedBlackTree::Node* RedBlackTree::remove(Node* node, int32_t key)
{
	if (key < node->key) {
		if (!isRed(node->left) && !isRed(node->left->left))
		{
			node = moveRedLeft(node);
		}
		
		node->left = remove(node->left, key);
	}
	else
	{
		if (isRed(node->left))
		{
			node = rotateRight(node);
		}
		if (key == node->key && node->right == nullptr)
		{
			delete node;
			return nullptr;
		}
		if (!isRed(node->right) && !isRed(node->right->left))
		{
			node = moveRedRight(node);
		}
		if (key == node->key)
		{
			Node* minimumNode = findMinimumNode(node->right);
			node->key = minimumNode->key;
			node->right = findMinimumNodeToDelete(node->right);
			delete minimumNode;
		}
		else
		{
			node->right = remove(node->right, key);
		}
	}

	return balance(node);
}

RedBlackTree::Node* RedBlackTree::moveRedLeft(Node* node)
{
	flipColors(node);

	if (isRed(node->right->left))
	{
		node->right = rotateRight(node->right);
		node = rotateLeft(node);
		flipColors(node);
	}

	return node;
}

RedBlackTree::Node* RedBlackTree::moveRedRight(Node* node)
{
	flipColors(node);

	if (isRed(node->left->left))
	{
		node = rotateRight(node);
		flipColors(node);
	}

	return node;
}

RedBlackTree::Node* RedBlackTree::findMinimumNodeToDelete(Node* node)
{
	if (node->left == nullptr)
	{
		return nullptr;
	}

	if (!isRed(node->left) && !isRed(node->left->left))
	{
		node = moveRedLeft(node);
	}

	node->left = findMinimumNodeToDelete(node->left);
	
	return balance(node);
}

RedBlackTree::Node* RedBlackTree::balance(Node* node)
{
	auto isNodeLeftRed = isRed(node->left);
	auto isNodeRightRed = isRed(node->right);

	if (isNodeRightRed)
	{
		node = rotateLeft(node);
	}
	if (isNodeLeftRed && isRed(node->left->left))
	{
		node = rotateRight(node);
	}
	if (isNodeLeftRed && isNodeRightRed)
	{
		flipColors(node);
	}

	node->size = size(node->left) + size(node->right) + 1;
	
	return node;
}

RedBlackTree::Node* RedBlackTree::findMinimumNode(Node* node) const
{
	if (node->left == nullptr)
	{
		return node;
	}
	else
	{
		return findMinimumNode(node->left);
	}
}

void RedBlackTree::recolorRootAsBlack()
{
	if (!isEmpty())
	{
		root->isRed = false;
	}
}
