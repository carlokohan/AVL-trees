/**
* Jose Carlo G. Husmillo
* Implementation of an AVL Tree
*/

#include <stdio.h>
#include <malloc.h>

typedef struct node{
	int value;
	int height;
	struct node *left;
	struct node *right;
	struct node *parent;
}AVL;

void menu(){
	printf("\n\t\tAVL Tree\n[1] Insert Element\n[2] Display AVL TREE\n[3] Search element\n[4] Display Maximum\n[5] Display Minimum\n[6] Display Preorder\n[7] Display Postorder\n[8] Display Inorder\n[9] Exit\nOption: ");
}

//returns the height of the node
int height(AVL *root){
	if(root == NULL)
		return -1;
	else
		return root->height;
}

//returns the one with higher height
int max(int left, int right){
	if(left > right)
		return left;
		
	return right;
}

/* SINGLE RIGHT ROTATE */
AVL * rightRotate(AVL **root){
	AVL *tmp;
	
	tmp = (*root)->left;//*root will be the one that will go down
	tmp->parent = (*root)->parent;
	
	(*root)->left = tmp->right;//tmp->right will be the lost child
	if( (*root)->left != NULL)
		((*root)->left)->parent = *root;
	
	tmp->right = *root;
	(*root)->parent = tmp;
	
	(*root)->height = max( height((*root)->left), height((*root)->right) )+1;
	tmp->height = max( height(tmp->right), (*root)->height ) +1;
	return tmp;//tmp is the new root, so that the tree will be printed correctly
}

/* SINGLE LEFT ROTATE */
AVL * leftRotate(AVL **root){
	AVL *tmp;
	
	tmp = (*root)->right;//*root will be the one that will go down
	tmp->parent = (*root)->parent;
	
	(*root)->right = tmp->left;//tmp->left will be the lost child
	if( (*root)->right != NULL)
		((*root)->right)->parent = *root;
	
	tmp->left = *root;
	(*root)->parent = tmp;
	
	(*root)->height = max( height((*root)->left), height((*root)->right) )+1;
	tmp->height = max( height(tmp->left), (*root)->height ) +1;
	
	return tmp;//tmp is the new root, so that the tree will be printed correctly
}



//insert to correct position
void insert(AVL **root, AVL **nodeToInsert){
	
	if(*root == NULL){
		*root = *nodeToInsert;//root is NULL, just assign it
	}
	else{
		if( (*nodeToInsert)->value < (*root)->value ){//insert as the left child
			insert( &((*root)->left) , &(*nodeToInsert));
			((*root)->left)->parent = *root; //left child's parent is the root
			
			/*make adjustments with the height after inserting the node*/
			//height(left) - height(right)
			if( height((*root)->left) - height((*root)->right) == 2 ){
				//double
				if( ((*root)->left) != NULL && (*nodeToInsert)->value > ((*root)->left)->value){
					printf("DOUBLE RIGHT ROTATE!(LR)");
					(*root)->left = leftRotate(&((*root)->left));
					*root = rightRotate(&(*root));
				}
				//single
				else if( (*nodeToInsert)->value < (*root)->value ){
					printf("SINGLE RIGHT ROTATE!(RR)");
					*root = rightRotate(&(*root));
				}	
				
			}
		}
		else if( (*nodeToInsert)->value > (*root)->value ){//insert as the right child
			insert( &((*root)->right) , &(*nodeToInsert));
			((*root)->right)->parent = *root; //right child's parent is the root
			
			/*make adjustments with the height after inserting the node*/
			//height(right) - height(left)
			if( height((*root)->right) - height((*root)->left) == 2 ){
				//double
				if( (*root)->right != NULL &&  (*nodeToInsert)->value < ((*root)->right)->value){
					printf("DOUBLE LEFT ROTATE!(RL)");
					(*root)->right = rightRotate(&((*root)->right));
					*root = leftRotate(&(*root));
				}
				//single
				else if( (*nodeToInsert)->value > (*root)->value ){
					printf("SINGLE LEFT ROTATE!(LL)");
					*root = leftRotate(&(*root));
				}
				
			}
			
		}
		else{
			printf("The value is already on the tree.");
			free(*nodeToInsert);//deallocate the node to insert because the value is already on the tree
		}
	}
	(*root)->height = max( height((*root)->left), height((*root)->right) ) +1;//set the height
}

void createNode(AVL **root, int value){
	AVL *tmp;
	
	tmp = (AVL *)malloc(sizeof(AVL));//create node and store values
	tmp->left = tmp->right = tmp->parent = NULL;
	tmp->value = value;
	tmp->height = 0;
	
	insert(&(*root), &tmp);//insert the newly created node, then make the tree height balanced
	
}

void printAVL(AVL *sroot, int tabs){//printing code given by the instructor
	int i;

	if (sroot != NULL){
		printAVL(sroot->right, tabs+1);

		for(i=0; i< tabs; i++){
			printf("\t");
		}

		printf("%3i\n", sroot->value);
		printAVL(sroot->left, tabs+1);
	}
}

AVL *search(AVL *root, int value){//similar to insert function
	if(root != NULL){
		if(root->value == value){
			return root;//returns the address of root
		}
		else{
			if(root->value > value){//proceed to left subtree
				search(root->left,value);
			}
			else if(root->value < value){//proceed to right subtree
				search(root->right,value);
			}
		}
	}
	else return NULL;//if root is null or empty tree or value not on tree
}

AVL *maximum(AVL *root){//find the largest, return the address
	if(root != NULL){
		if(root->right == NULL){
			return root;//returns the address of root
		}
		else{//proceed to all right child recursively
			maximum(root->right);
		}
	}
	else return NULL;//if root is null or empty tree
}

AVL *minimum(AVL *root){//find the least value, return the address
	if(root != NULL){
		if(root->left == NULL){
			return root;//returns the address of root
		}
		else{//proceed to all left child recursively
			minimum(root->left);
		}
	}
	else return NULL;//if root is null or empty tree
}

void preorder(AVL *root){//print the values of the tree in preorder form
	if(root != NULL){//recursive, Root - left - right
		printf("%3d", root->value);
		preorder(root->left);
		preorder(root->right);
	}
}

void postorder(AVL *root){//print the values of the tree in postorder form
	if(root != NULL){//recursive, left - right - root
		postorder(root->left);
		postorder(root->right);
		printf("%3d", root->value);
	}
}

void inorder(AVL *root){//print the values of the tree in inorder form
	if(root != NULL){//recursive, left - root - right
		inorder(root->left);
		printf("%3d", root->value);
		inorder(root->right);
	}
}

void MakeEmpty(AVL **root){
	if((*root) != NULL){
		MakeEmpty(&((*root)->left));
		MakeEmpty(&((*root)->right));
		free(*root);
	}
}
