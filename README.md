# AVL-Project
AVL tree C++ implementation

This implementation of an AVL tree was designed to store student names and IDs. 
The balanced AVL tree format allows for quick lookup to rapidly get information about the student.

Documentation & Time Complexity Analysis

1. Insert NAME ID

Usage:
Inserts a new student string NAME and string ID into the tree.

Complexity:
The worst case complexity is O(log n), where n represents the number of nodes in the
AVL tree. The longest possible path for an element to travel to be inserted in an AVL tree
has length log2n+1 nodes. After insertion, O(1) rotation operations are applied; therefore,
the overall complexity is O(log n).

2. remove ID

Usage:
Removes a specified string ID from the AVL tree.

Complexity:
The worst case complexity is O(log n), where n represents the number of nodes in the
AVL tree. Since deletion of the node itself and reconnection operations are O(1), the
worst case occurs when the node to be removed is at the lowest leaf node of the tree,
whose path has length log2n+1 nodes. The worst case complexity is then O(log n).

3. search ID, search NAME

Usage:
Calling search with string ID returns the corresponding student's ID.

Complexity:
Calling search with string NAME returns a list of student IDs corresponding to the NAME.
The worst case complexity is O(log n), where n represents the number of nodes in the
AVL tree. Like insert and remove, the worst case occurs when the element is the lowest
leaf in the tree, which must be reached through a path of length log2n+1 nodes. The
worst case complexity is O(log n).

4. printInorder

Usage:
Prints every node following an inorder traversal.

Complexity:
O(n), where n is the number of nodes in the AVL tree, because inorder traversal contacts
and prints every node in the tree.

5. printPreorder

Usage:
Prints every node following an preorder traversal.

Complexity:
O(n), where n is the number of nodes in the AVL tree, because preorder traversal
contacts and prints every node in the tree.

6. printPostorder

Usage:
Prints every node following an postorder traversal.

Complexity:
O(n), where n is the number of nodes in the AVL tree, because postorder traversal
contacts and prints every node in the tree.

7. printLevelCount

Usage:
Prints the height of the tree.

Complexity:
O(1) because the function simply returns the value of height stored by the root node of
the AVL tree.

8. removeInorder N

Usage:
Removes the nth node from the tree, where n is the node's position in an inorder traversal.

Complexity:
O(n), where n is the number of nodes in the AVL tree. The worst case occurs when n is
the last node in the inorder traversal. First, the traversal must reach every node, which
takes O(n) time; second, the node is removed by calling the remove function, which
takes O(log n) time (see part 2). Therefore, the total time complexity is O(n) + O(log n),
which simplifies to O(n)
