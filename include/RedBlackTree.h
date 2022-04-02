#pragma once

#include "Set.h"
#include <optional>

class RedBlackTree : public Set
{
public:
	RedBlackTree();
	~RedBlackTree();

	size_t size() const override;
	void insert(int32_t key) override;
	bool contains(int32_t key) const override;
	void remove(int32_t key) override;

private:
	struct Node
	{
		int32_t key;
		bool isRed;
		uint32_t size;
		Node* left;
		Node* right;
	};

	void RedBlackTree::removeAll(Node* node);
	Node* insert(Node* node, int32_t key) const;
	Node* createNode(int32_t key) const;
	void insertAsChild(Node* node, int32_t key) const;
	Node* rebalanceNode(Node* node) const;
	bool isRed(const Node* const node) const;
	Node* rotateLeft(Node* node) const;
	size_t size(const Node* const node) const;
	Node* rotateRight(Node* node) const;
	void flipColors(Node* node) const;
	bool contains(Node* node, int32_t key) const;
	Node* remove(Node* node, int32_t key);
	void recolorRootAsRed();
	Node* findMinimumNode(Node* node) const;
	void recolorRootAsBlack();
	Node* moveRedLeft(Node* node);
	Node* moveRedRight(Node* node);
	Node* findMinimumNodeToDelete(Node* node);
	Node* balance(Node* node);

	Node* root;
};
