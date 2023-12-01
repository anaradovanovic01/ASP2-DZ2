#include "BinaryNode.h"

BinaryNode::BinaryNode() {
	key = 0;
	action = nullptr;
	black = false;
	left = right = parent = nullptr;
}

BinaryNode::~BinaryNode() {
	action = nullptr;
	left = right = parent = nullptr;
}

