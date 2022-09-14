#include "bst.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>


bool isBalanced(Node *root) {
	//Get the heights of the left and right subtrees - helper func?
	//Determine if this node is balanced! If not ret false!

	//Check if there are subtrees under us
	//Are they balanced?

	//If all nodes are balanced return true!

	int lheight, rheight;

	if(root == NULL){
		return true;
	}

	lheight = height(root->left);
	rheight = height(root->right);

	if(lheight-rheight >= -1 && lheight-rheight <= 1){
		if(isBalanced(root->right) && isBalanced(root->left)){
			return true;
		}
	}
		
	return false;

}

int height(Node* root){
	if(root == NULL){
		return 0;
	}

	if(height(root->right) >= height(root->left)){
		return 1 + height(root->right);
	}
	else{
		return 1 + height(root->left);
	}
}
