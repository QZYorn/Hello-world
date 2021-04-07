#pragma once

#include<iostream>
#include<string>
using namespace std;


class TreeNode
{
public:
	TreeNode()
		:value(string()), count(0), left(nullptr), right(nullptr), use(new int(1)){}
	TreeNode(const TreeNode& tn)
		:value(tn.value), count(tn.count), left(tn.left), right(tn.right), use(tn.use)
	{
		++*use;
	}

	TreeNode& operator=(const TreeNode& tn)
	{
		++*tn.use;
		if (--*this->use == 0)
		{
			delete left;
			left = nullptr;
			delete right;
			right = nullptr;
			delete use;
		}
		value = tn.value;
		count = tn.count;
		left = tn.left;
		right = tn.right;
		use = tn.use;
	}

	~TreeNode()
	{
		if (--*use == 0)
		{
			if (left != nullptr)
				delete left;
			if (right != nullptr)
				delete right;
			delete use;
		}
	}

private:
	string value;
	int count;
	TreeNode *left;
	TreeNode *right;
	int *use;
};


class BinStrTree
{
public:
	BinStrTree() :root(nullptr){}
	BinStrTree(const BinStrTree& bst) :root(new TreeNode(*bst.root)){}
	BinStrTree& operator=(const BinStrTree& bst)
	{
		if (&bst == this)
		{
			return *this;
		}
		delete root;
		root = new TreeNode(*bst.root);
	}
	~BinStrTree()
	{
		delete root;
	}
private:
	TreeNode *root;
};