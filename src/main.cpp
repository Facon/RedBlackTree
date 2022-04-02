#include <iostream>

#include <set>
#include "RedBlackTree.h"

int main(int argc, char** argv)
{
    {
        RedBlackTree redBlackTree;
        Set& tree = redBlackTree;

        tree.insert(50);
        tree.insert(5);
        tree.insert(100);
        tree.insert(25);
        tree.insert(30);
        tree.insert(1);
        tree.insert(200);

        tree.contains(1);
        tree.contains(5);

        tree.remove(5);
        tree.remove(50);
        tree.remove(100);
        tree.remove(1);
        tree.remove(25);
        tree.remove(30);
    }

    return 0;
}
