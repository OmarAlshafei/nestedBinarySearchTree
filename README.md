## Binary Search Tree Program

This program builds a nested binary search tree data structure where every node in the main binary search tree contains another binary search tree. Each node of the `treeNameNode` tree contains a binary search tree named `itemNode`, which includes the item's name and count. The program allows users to perform various operations and queries.

### Structures

- `itemNode`: Represents a node in the `itemNode` binary search tree.
  - `name`: Name of the item.
  - `count`: Count of the item.
  - `left`, `right`: Pointers to the left and right child nodes.

- `treeNameNode`: Represents a node in the `treeNameNode` binary search tree.
  - `treeName`: Name of the tree.
  - `left`, `right`: Pointers to the left and right child nodes.
  - `theTree`: Pointer to the root node of the `itemNode` binary search tree.

### Functions

- `traverseSubTree(root, fp)`: Recursively traverses the `itemNode` subtree and prints the node names.

- `traverse_in_traverse(root, fp)`: Traverses the `treeNameNode` tree and calls `traverseSubTree` to print the node names.

- `searchNameNode(root, treeNodeName)`: Searches for a specific `treeNameNode` by name.

- `searchItemNode(root, itemName)`: Searches for a specific `itemNode` by name.

- `itemParent(root, node)`: Finds the parent node of an `itemNode`.

- `itemMinVal(root)`: Finds the minimum value within an `itemNode` subtree.

- `delete_item(root, value)`: Deletes an `itemNode` from the tree.

- `nameMinVal(root)`: Finds the minimum value within a `treeNameNode` subtree.

- `nameParent(root, node)`: Finds the parent node of a `treeNameNode`.

- `delete_name(root, value)`: Deletes a `treeNameNode` from the tree.

- `insertNameNode(root, newNode)`: Inserts a new `treeNameNode` into the tree.

- `createTreeNameNode(name)`: Creates a `treeNameNode` with the given name.

## How to Use

1. To compile & run this code, first download the main.c file and any requisite input files to the same directory.

2. Use "gcc -g main.c" to generate a program file from the .c file.

3. You can now run the program while passing in your input file with this command: "./a.out < in.txt > out.txt".

4. The expected output will be shown in the "out.txt" file.

## Author

This project is created by Omar Alshafei.
