# ADSA_CodingAssignment

This repository contains my coding assignments for ADSA.

1.  -> BST Operations (Search, Insert, Delete) and Traversals
2.  -> AVL Tree Operations(Search, Insert{handeling Rotations RR, RL, LR, LL}, Delete) and Traversals
3.  -> Red Black tree has few important points:
    1. Node can only be of two colors red or black
    2. Root and NIL(they are node Node but we consider them as Black Node) node is always black
    3. All Path from a node to NILL discedent has equal number of black nodes
    4. Red node can't have red children
    5. The longest path(root to furtherest NILL) <= 2 x The shortlest path(Root to nearest NIL) Shortest path: all black nodes, Longest path: Black mixed with red nodes.

              RBT INSERT
                   ↓
             Color new node RED
                   ↓
             Is it root?
              /          \
            YES           NO
             ↓             ↓
          BLACK       Is parent RED?
                         /       \
                       NO         YES
                       ↓           ↓
                      DONE    Find uncle
                                  |
                         ┌────────┴────────┐
                         ↓                 ↓
                    Uncle RED         Uncle BLACK
                         ↓                 ↓
                     Recolor         Rotation(s)
                         ↓                 ↓
                   Move upward        Recolor