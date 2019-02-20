/**
* Jose Carlo G. Husmillo
* AVL tree
*/
#include "avl.h"

main(){
	AVL *root = NULL, *tmp = NULL;
	int option,x;
	
	do{
		menu();//display menu
		scanf("%d", &option);
		
		switch(option){
			case 1: printf("\nInsert element: ");
					  scanf("%d",&x);
					  createNode(&root, x);//insert to avl tree
					  break;
					  
			case 2: if(root != NULL)
						printAVL(root,0);//print tree
					  else{
					  	printf("Empty Tree.\n");
					  }
					  break;
					  
			case 3: printf("\nSearch element: ");//search element
					  scanf("%d",&x);
					  tmp = search(root,x);
					  
					  if(tmp == NULL)
					  	printf("%d is not on the tree.",x);
					  else
					  	printf("%d Found.\n", tmp->value);
					  	
					  break;
					  
			case 4: tmp = maximum(root);//max
					  if(tmp == NULL)
					  	printf("No Maximum");
					  else
					  	printf("Maximum is %d\n", tmp->value);
					  
					  break;
			
			case 5: tmp = minimum(root);//least element
					  if(tmp == NULL)
					  	printf("No Minimum");
					  else
					  	printf("Minimum is %d\n", tmp->value);
					  
					  break;
			
			case 6: if(root == NULL) printf("Tree Empty.\n");//will not print
					  else{
						  printf("\nPreorder: \n");
					  	  preorder(root);//preorder printing
					  }
					  break;
			
			case 7: if(root == NULL) printf("Tree Empty.\n");
					  else{
						  printf("\nPostorder: \n");
						  postorder(root);
					  }
					  break;
					  
			case 8: if(root == NULL) printf("Tree Empty.\n");
					  else{
						  printf("\nInorder: \n");
					  	  inorder(root);
					  }
					  break;
					  
			case 9: MakeEmpty(&root);//deallocate all nodes in the tree
						break;
		}
	}while(option != 9);
}
