//Omar Alshafei
// 11/18/2022

/*
This program builds many binary search trees where each tree has a name. Each node of 
the "treeNameNode" tree will have an "itemNode" binary search tree within itself which 
includes the items name and count. The program then performs a set of operations and 
queries that are scanned in by the user.
*/

// Library functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include	"leak_detector_c.h"

#define MAXLEN 51

// itemNode BST structure
 typedef struct itemNode { 
  char name[MAXLEN]; 
  int count; 
  struct itemNode *left, *right; 
}itemNode; 
// treeNameNode BST structure
typedef struct treeNameNode { 
  char treeName[MAXLEN]; 
  struct treeNameNode *left, *right; 
  itemNode *theTree; 
}treeNameNode; 

// Called by traverse_in_traverse in order to traverse the sub trees
void traverseSubTree(itemNode* root, FILE *fp){ 
  if(root != NULL){
    // recursive call with root left
    traverseSubTree(root->left, fp);
    printf("%s ", root->name);
    fprintf(fp,"%s ", root->name);    
    // recursive call with root right    
    traverseSubTree(root->right, fp);
  }
}

// This function is used to traverse the tree and print out the node names
void traverse_in_traverse(treeNameNode *root, FILE *fp){
  if(root != NULL){
    // recursive call with root left    
    traverse_in_traverse(root->left, fp);
    printf("\n===%s===\n", root->treeName);
    fprintf(fp,"\n===%s===\n", root->treeName);  
    // calls traverseSubTree function in order to traverse sub tree
    traverseSubTree(root->theTree, fp);
    // recursive call with root right        
    traverse_in_traverse(root->right, fp);
  }
}
// This function is used to find a specific treeNameNode
treeNameNode* searchNameNode(treeNameNode* root, char treeNodeName[MAXLEN]){
  if (root == NULL)
    return NULL;
  // Returns root if it is equal to treeNodeName    
  if (strcmp(root->treeName, treeNodeName) == 0)
    return root;
  // Makes recursive call with root left if treeNodeName is less than treeName
  if (strcmp(root->treeName, treeNodeName) > 0)
    return searchNameNode(root->left, treeNodeName);
  // Makes recursive call with root right if treeNodeName is greater than treeName  
  else
    return searchNameNode(root->right, treeNodeName);
}
// This function is used to find a specific itemNode
itemNode* searchItemNode(itemNode* root, char itemName[MAXLEN]){
  if (root == NULL)
    return NULL;
  // Returns root if it is equal to itemName        
  if (strcmp(root->name, itemName) == 0)
    return root;
  // Makes recursive call with root left if itemName is less than name    
  if (strcmp(root->name, itemName) > 0)
    return searchItemNode(root->left, itemName);
  // Makes recursive call with root right if itemName is greater than name      
  else
    return searchItemNode(root->right, itemName);
}
// This function is used to find the parent fot an itemNode
itemNode* itemParent(itemNode* root, itemNode* node) {
  // take care of NULL cases
  if (root == NULL || root == node)
    return NULL;

  // The root is the direct parent of node.
  if (root->left == node || root->right == node)
    return root;

  // look for node's parent in the left side of the tree
  if (strcmp(root->name, node->name) > 0)
    return itemParent(root->left, node);

  // look for node's parent in the right side of the tree
  else if (strcmp(root->name, node->name) < 0)
    return itemParent(root->right, node);

  return NULL; // catch any other extraneous cases
}
// This function finds the minimum value within a itemNode tree
itemNode* itemMinVal(itemNode *root) {
  if (root->left == NULL)
    return root;

  else
    return itemMinVal(root->left);// recursive call with root left
}
// Will delete the Item Node storing name and count in the tree rooted at root. The
// name must be present in the tree in order for this function to work.
// The function returns a pointer to the root of the resulting tree.
itemNode* delete_item(itemNode* root, char value[MAXLEN]) {
  struct itemNode *delnode, *new_del_node, *save_node;
  struct itemNode *par;

  char save_name[MAXLEN];
  int save_val;
  delnode = searchItemNode(root, value);  // Get a pointer to the node to delete.
  par = itemParent(root, delnode);  // Get the parent of this node.
  
  // Take care of the case where the node to delete is a leaf node.
  if (delnode->left == NULL && delnode->right == NULL) {// case 1
    // Deleting the only node in the tree.
    if (par == NULL) {
      free(root); // free the memory for the node.
      return NULL;
    }
    
    // Deletes node if it's a left child
    if(strcmp(par->name, delnode->name) > 0){
      free(par->left); // Free the memory for the node.
      par->left = NULL;
    }
    // Deletes the node if it's a right child.
    else{
      free(par->right); // Free the memory for the node.
      par->right = NULL;
    }
    return root; // Return the root of the new tree.
  }

  // Take care of the case where the node to be deleted only has a left child.
  if (delnode->left != NULL && delnode->right == NULL) {
    // Deleting the root node of the tree.
    if(par  == NULL){
      save_node  = delnode->left;
      free(delnode); // Free the node to delete.
      return save_node; // Return the new root node of the resulting tree.
    }

    // Deletes the node if it's a left child.
    if(strcmp(delnode->name, par->name) < 0){
      save_node  = par->left; // Save the node to delete.
      par->left = par->left->left; // Readjust the parent pointer.
      free(save_node); // Free the memory for the deleted node.
    }

    // Deletes the node if it's a right child.
    else{
      save_node = par->right; // Save the node to delete.
      par->right = par->right->left; // Readjust the parent pointer.
      free(save_node); // Free the memory for the deleted node.
    }
    return root; // Return the root of the tree after the deletion.
  }
  // Takes care of the case where the deleted node only has a right child.
  if (delnode->left == NULL && delnode->right != NULL) {
    // Node to delete is the root node.
    if(par == NULL){
      save_node = delnode->right;
      free(delnode);
      return save_node;
    }

    // Delete's the node if it is a left child.
    if(strcmp(delnode->name, par->name) < 0){
      save_node = par->left;
      par->left = par->left->right;  // introduce parent with grandchild
      free(save_node);
    }
    // Delete's the node if it is a right child.
    else{
      save_node = par->right;
      par->right = par->right->right; // introduce parent with grandchild
      free(save_node);
    }
    return root;
  } 

//if your code reaches hear it means delnode has two children
  // Find the new physical node to delete.
  new_del_node = itemMinVal(delnode->right);
  save_val = new_del_node->count;
  strcpy(save_name, new_del_node->name);
  delete_item(root, new_del_node->name); // Now, delete the proper value.
  // Restore the data to the original node to be deleted.
  strcpy(delnode->name, save_name);
  delnode->count = save_val;

  return root;
}
// This function finds the minimum value within a treeNameNode tree
treeNameNode* nameMinVal(treeNameNode *root) {
  if (root->left == NULL)
    return root;

  else
    return nameMinVal(root->left);// recursive call with root left
}
// This function is used to find the parent for a treeNameNode
treeNameNode* nameParent(treeNameNode* root, treeNameNode* node) {

  // take care of NULL cases
  if (root == NULL || root == node)
    return NULL;

  // The root is the direct parent of node.
  if (root->left == node || root->right == node)
    return root;

  // look for node's parent in the left side of the tree
  if (strcmp(root->treeName, node->treeName) > 0)
    return nameParent(root->left, node);

  // look for node's parent in the right side of the tree
  else if (strcmp(root->treeName, node->treeName) < 0)
    return nameParent(root->right, node);

  return NULL; // catch any other extraneous cases
}
// Will delete the Name Node storing name and item nodes in the tree rooted at root. The
// name must be present in the tree in order for this function to work.
// The function returns a pointer to the root of the resulting tree.
treeNameNode* delete_name(treeNameNode* root, char value[MAXLEN]) {
  struct treeNameNode *delnode, *new_del_node, *save_node;
  struct treeNameNode *par;

  char save_name[MAXLEN];
  delnode = searchNameNode(root, value); // Get a pointer to the node to delete.
  par = nameParent(root, delnode); // Get the parent of this node.

  // Take care of the case where the node to delete is a leaf node.
  if (delnode->left == NULL && delnode->right == NULL) {// case 1
    // Deleting the only node in the tree.
    if (par == NULL) {
      free(root); // free the memory for the node.
      return NULL;
    }
    // Deletes node if it's a left child
    if(strcmp(par->treeName, delnode->treeName) > 0){
      free(par->left); // Free the memory for the node.
      par->left = NULL;
    }
    // Deletes the node if it's a right child.
    else{
      free(par->right); // Free the memory for the node.
      par->right = NULL;
    }
    return root; // Return the root of the new tree.
  }

  // Take care of the case where the node to be deleted only has a left child.
  if (delnode->left != NULL && delnode->right == NULL) {
    // Deleting the root node of the tree.
    if(par  == NULL){
      save_node  = delnode->left;
      free(delnode); // Free the node to delete.
      return save_node; // Return the new root node of the resulting tree.
    }

    // Deletes the node if it's a left child.
    if(strcmp(delnode->treeName, par->treeName) > 0){
      save_node  = par->left; // Save the node to delete.
      par->left = par->left->left; // Readjust the parent pointer.
      free(save_node); // Free the memory for the deleted node.
    }

    // Deletes the node if it's a right child.
    else{
      save_node = par->right; // Save the node to delete.
      par->right = par->right->left;// Readjust the parent pointer.
      free(save_node); // Free the memory for the deleted node.
    }
    return root; // Return the root of the tree after the deletion.
  }
  // Takes care of the case where the deleted node only has a right child.
  if (delnode->left == NULL && delnode->right != NULL) {
    // Node to delete is the root node.
    if(par == NULL){
      save_node = delnode->right;
      free(delnode);
      return save_node;
    }

    // Delete's the node if it is a left child.
    if(strcmp(par->treeName, delnode->treeName) > 0){
      save_node = par->left;
      par->left = par->left->right; // introduce parent with grandchild
      free(save_node);
    }
    // Delete's the node if it is a right child.
    else{
      save_node = par->right;
      par->right = par->right->right; // introduce parent with grandchild
      free(save_node);
    }
    return root;
  
  }

//if your code reaches hear it means delnode has two children
  // Find the new physical node to delete.
  new_del_node = nameMinVal(delnode->right);  
  strcpy(save_name, new_del_node->treeName);
  delete_name(root, new_del_node->treeName); // Now, delete the proper value.
  // Restore the data to the original node to be deleted.
  strcpy(delnode->treeName, save_name);
  return root;
}
// This function takes in the treeNameNode root and a new treeNameNode and inserts the new node into root node
treeNameNode* insertNameNode(treeNameNode* root, treeNameNode* newNode){
  if (root == NULL)
    return newNode;
  else{
    // recursive call with root left if the new node's name is less then root node's name    
    if (strcmp(root->treeName, newNode->treeName) > 0){
      if (root->left != NULL)
        root->left = insertNameNode(root->left, newNode);
      else
        root->left = newNode;
    }
    // recursive call with root left if the new node's name is greater then root node's name
    else{
      if (root->right != NULL)
        root->right = insertNameNode(root->right, newNode);
      else
        root->right = newNode;
    }
  }
  // returns the name root node
  return root;
}
// This function takes in a name and creates a treeNameNode with that name
treeNameNode* createTreeNameNode(char* name){
  treeNameNode* temp = malloc(sizeof(treeNameNode));
  temp->theTree = NULL;
  temp->left = NULL;
  temp->right = NULL;
  // inserts the passed name into the node treename
  strcpy(temp->treeName, name);
  // returns name node
  return temp;
}
// This function scans in the data for a treeNameNode and calls createTreeNameNode and insertNameNode to add it to the tree
treeNameNode* buildNameTree(treeNameNode* root, int numOfTreeNames){
  treeNameNode* nameRoot = NULL;
  char name[MAXLEN];
  for (int i = 0; i < numOfTreeNames; i++){
    // scans in tree name
    scanf("%s", name);
    // calls createTreeNameNode to create node
    treeNameNode* newNameNode = createTreeNameNode(name);
    // calls insertNameNode to insert node into tree
    nameRoot = insertNameNode(nameRoot, newNameNode);
  }
  return nameRoot;
}
// This function takes in the itemNode root and a new itemNode node and inserts the new node into the root node
itemNode* insertItemNode(itemNode* treeRoot, itemNode* newNode){
  if (treeRoot == NULL)
    return newNode;
  else{
    // recursive call with root left if the new node is less then root node's name
    if (strcmp(treeRoot->name, newNode->name) > 0){
      if (treeRoot->left != NULL)
        treeRoot->left = insertItemNode(treeRoot->left, newNode);
      else
        treeRoot->left = newNode;
    }
    // recursive call with root left if the new node is less then root node's name    
    else{
      if (treeRoot->right != NULL)
        treeRoot->right = insertItemNode(treeRoot->right, newNode);
      else
        treeRoot->right = newNode;
    }
  }
  // returns the root item node  
  return treeRoot;
}
// This function is used to create an itemNode
itemNode* createItemNode(char* name, int count){
  itemNode* temp = (itemNode*)malloc(sizeof(itemNode));
  // inserts item name into item node
  strcpy(temp->name, name);
  temp->count = count;
  temp->left = NULL;
  temp->right = NULL;
  // returns itemNode
  return temp;
}
// This function scans in the data for an itemNode and calls createItemNode, searchNameNode, and insertItemNode to add it to the tree
void buildItemTree(treeNameNode* treeNameRoot, int numOfItems){
  int count;
  char treeName[MAXLEN];
  char itemName[MAXLEN];
  for (int i = 0; i < numOfItems; i++){
    // scans in the treeName, itemName, and count for itemNode
    scanf("%s %s %d", treeName, itemName, &count);
    // calls createItemNode to create the node
    itemNode* newItemNode = createItemNode(itemName, count);
    // calls searchNameNode to search for the nodes root name node
    treeNameNode* treeNode = searchNameNode(treeNameRoot, treeName);
    // calls insertItemNode to insert the node
    treeNode->theTree = insertItemNode(treeNode->theTree, newItemNode);
  }
}
// This function scans input
void takeInput(int *numOfTreeNames, int *numOfItems, int *numOfQueries){
  // scans in numOfTreeNames, numOfItems, and numOfQueries
  scanf("%d %d %d", &*numOfTreeNames, &*numOfItems, &*numOfQueries);
}
// This function prints out treeNameNode inorder
void inorder(treeNameNode* treeName, FILE *fp){
  if(treeName != NULL){
    // recursive call with treename left
    inorder(treeName->left, fp);
    // prints tree name
    printf("%s ", treeName->treeName);
    fprintf(fp,"%s ", treeName->treeName);
    //recursive call with treename right
    inorder(treeName->right, fp);
  }
}
// Thsi function searchs for an itemNode within a treeNameNode
void search(treeNameNode* root, char item[MAXLEN], FILE *fp) {
  itemNode* itemTemp;
  // calls searchItemNode to find the itemNode
  itemTemp = searchItemNode(root->theTree, item);
  // if node is null it prints that is is not found
  if (itemTemp == NULL){
    printf("%s not found in %s\n", item, root->treeName);
    fprintf(fp,"%s not found in %s\n", item, root->treeName);
  }    
  // if node is not null it prints where it is found
  else{
    printf("%d %s found in %s\n", itemTemp->count, itemTemp->name, root->treeName);
    fprintf(fp,"%d %s found in %s\n", itemTemp->count, itemTemp->name, root->treeName);
  }
}
// This function finds the number of nodes before a certain itemNode
int item_before(itemNode* root, char item[MAXLEN]){
  if(root==NULL)
    return 0;
  if(strcmp(root->name, item)<0)
    // returns 1 and calls root left and root right if root name is less then the item name
    return 1 + item_before(root->left, item) + item_before(root->right, item);
  else 
    return item_before(root->left, item);
}

void print_item_before(char item[MAXLEN], int x, FILE *fp){
  printf("item before %s: %d\n",item, x);        
  fprintf(fp,"item before %s: %d\n",item, x);        

}
// This function finds the height of a root
int findHeight(itemNode* nameRoot){
  if(nameRoot==NULL)
    return 0;    
  // recursive call with root left
  int leftHeight = findHeight(nameRoot->left);
  // recursive call with root right
  int rightHeight = findHeight(nameRoot->right);

  if(leftHeight > rightHeight)
    return leftHeight + 1;

  else
  return rightHeight + 1;
}
// Thsi function checks if a root's height is balanced
void height_balance(treeNameNode* root,char name[MAXLEN], FILE *fp){
  int diff;
  // calls findHeight function to find the height with the left child
  int leftHeight = findHeight(root->theTree->left) -1;
  // calls findHeight function to find the height with the left child
  int rightHeight = findHeight(root->theTree->right) -1;
    
  if (leftHeight > rightHeight)
    diff = leftHeight-rightHeight;
  else if (leftHeight < rightHeight)
    diff = rightHeight-leftHeight; 
  else  
    diff = 0;
  // prints they are balanced if both leftHeight and rightHeight are equal
  if (leftHeight == rightHeight){
    printf("%s: left height %d, right height %d, difference %d, balanced\n", root->treeName, leftHeight, rightHeight, diff);
    fprintf(fp,"%s: left height %d, right height %d, difference %d, balanced\n", root->treeName, leftHeight, rightHeight, diff);
  }
  // prints they are not balanced if they are not equal
  else{
    printf("%s: left height %d, right height %d, difference %d, not balanced\n", root->treeName, leftHeight, rightHeight, diff);
    fprintf(fp,"%s: left height %d, right height %d, difference %d, not balanced\n", root->treeName, leftHeight, rightHeight, diff);  
  }
}
// This function finds the count of an item node
int count(itemNode* root){
  if(root==NULL)
    return 0;    
  else
    // returns the count and recursivley calls itself with root left and root right
    return root->count + count(root->left) + count(root->right);
}
// This function reduced the count of an itemNode
itemNode* reduce(itemNode* root, char item[MAXLEN], int val) {
  
  itemNode *tempNode = searchItemNode(root, item);
  if((tempNode->count - val) <= 0) {
    // deleted node if val is greater then the nodes count
    root = delete_item(root, item);
    return root;   
  }

  else{
    // returns count - val if val is not greater then the count
    tempNode->count = tempNode->count - val;
    return root;
  }
}
// This function frees itemNode memory
void freeItems(itemNode *root){
  if(root == NULL)
    return;
  // recursive call with root left and right
  freeItems(root->left);
  freeItems(root->right);
  // frees the root
  free(root);
}
// This function frees treeNameNode memory
void freeRoots(treeNameNode *root){
  if(root == NULL)
    return;
  // recursive call with root left and right  
  freeRoots(root->left); 
  freeRoots(root->right);
  // calls freeItems function to free the items within the treeNameNode
  freeItems(root->theTree);
  // frees the root
  free(root);
}
// This function is a menu that is used for queries
void menu(treeNameNode* root, int numOfQueries, FILE *fp){
  printf("\n");
  fprintf(fp,"\n");
  for(int i = 0; i < numOfQueries; i++){
    
    char item[MAXLEN];
    char action[MAXLEN];
    char name[MAXLEN];
    int val;        
    scanf("%s", action);
    // if statement for when the queiry scanned in is search
    if(strcmp(action, "search")==0){
      scanf("%s", name);
      scanf("%s", item);    
      treeNameNode* nameRoot;
      nameRoot = searchNameNode(root, name);          
      if (nameRoot == NULL){
        printf("%s does not exist\n", name);
        fprintf(fp,"%s does not exist\n", name);
        continue;
      }
      else
      search(nameRoot, item, fp);
    }
    // if statement for when the queiry scanned in is item_before
    else if(strcmp(action, "item_before")==0){
      scanf("%s", name);
      scanf("%s", item);    
      treeNameNode* nameRoot;
      nameRoot = searchNameNode(root, name);
      int x = item_before(nameRoot->theTree, item);
      print_item_before(item, x, fp);
    } 
    // if statement for when the queiry scanned in is height_balance
    else if(strcmp(action, "height_balance")==0){ 
      scanf("%s", name);
      treeNameNode* nameRoot;
      nameRoot = searchNameNode(root, name);
      height_balance(nameRoot, name, fp);        
    }
    // if statement for when the queiry scanned in is count
    else if(strcmp(action, "count")==0){
      scanf("%s", name);
      treeNameNode* nameRoot;
      nameRoot = searchNameNode(root, name);
      int total = count(nameRoot->theTree);
      printf("%s count %d\n", nameRoot->treeName, total);
      fprintf(fp,"%s count %d\n", nameRoot->treeName, total);

    }
    // if statement for when the queiry scanned in is reduce
    else if(strcmp(action, "reduce")==0){    
      scanf("%s", name);
      scanf("%s %d", item, &val);  
      treeNameNode* nameRoot;
      nameRoot = searchNameNode(root, name);
      nameRoot->theTree = reduce(nameRoot->theTree, item, val);
      printf("%s reduced\n", item);
      fprintf(fp,"%s reduced\n", item);

    }
    // if statement for when the queiry scanned in is delete
    else if(strcmp(action, "delete")==0){     
      scanf("%s", name);
      scanf("%s", item);  
      treeNameNode* nameRoot;
      nameRoot = searchNameNode(root, name);
      itemNode* itemRoot = searchItemNode(nameRoot->theTree, item);        
      if(itemRoot!=NULL){
        printf("%s deleted from %s\n", itemRoot->name, nameRoot->treeName);
        fprintf(fp,"%s deleted from %s\n", itemRoot->name, nameRoot->treeName);        
        nameRoot->theTree = delete_item(nameRoot->theTree , item);
      }       
    }
    // if statement for when the queiry scanned in is delete_name
    else if(strcmp(action, "delete_name")==0){
      scanf("%s", name);
      treeNameNode* nameRoot;
      nameRoot = searchNameNode(root, name);     
      itemNode* itemRoot = nameRoot->theTree;
      if(nameRoot!=NULL){
        
        while(itemRoot!=NULL)
          itemRoot = delete_item(itemRoot, itemRoot->name);
      
      printf("%s deleted\n", nameRoot->treeName);
      fprintf(fp,"%s deleted\n", nameRoot->treeName);      
      root = delete_name(root, name);
      }
    }
  }
}

// The main function calls all the other functions of the program
int main(){
  atexit(report_mem_leak);
  // opening out.txt file
  FILE *fp = fopen("out.txt", "w");
  // defining integer variables
  int numOfTreeNames, numOfItems, numOfQueries;
  // calls takeInput function to take user input
  takeInput(&numOfTreeNames, &numOfItems, &numOfQueries);
  // calls buildNameTree function to create a treeNameNode bst
  treeNameNode* treeNameRoot = buildNameTree(treeNameRoot, numOfTreeNames);
  // calls buildItemTree function to create a itemTree bst        
  buildItemTree(treeNameRoot, numOfItems);
  // calls inorder function to display treeNameNode tree inorder
  inorder(treeNameRoot, fp);
  // calls traverse_in_traverse to traverse and display trees
  traverse_in_traverse(treeNameRoot, fp);
  // calls menu function to scan in and carry out queries
  menu(treeNameRoot, numOfQueries, fp);
  // calls freeRoots function to free the trees
  freeRoots(treeNameRoot);
  // closing out.txt file
  fclose(fp);
        
  return 0;
}
