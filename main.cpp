#include <iostream>
#include <vector>
#include "assignment.h"
#include "INode.h"

class Node : public INode {
public:
    Node(int val) : val_(val) {}

    int value() const override {
        return val_;
    }

    const std::vector<std::unique_ptr<INode>>& children() const override {
        return children_;
    }

    void addChild(std::unique_ptr<INode> child) {
        children_.push_back(std::move(child));
    }

private:
    int val_;
    std::vector<std::unique_ptr<INode>> children_;
};

int main() {
    //Test getClosestToZero
    std::vector<int> arr1 = {5, -2, 2, -3, 4, -2};
    std::cout << "Closest to zero: " << getClosestToZero(arr1) << std::endl;

    //Test countChunks
    std::vector<int> arr2 = {5, 4, 0, 0, -1, 0, 2, 0, 0, 1};
    std::cout << "Number of chunks: " << countChunks(arr2) << std::endl;

    //Test getLevelSum
    Node root(10);
    auto child1 = std::make_unique<Node>(5);
    auto child2 = std::make_unique<Node>(8);
    root.addChild(std::move(child1));
    root.addChild(std::move(child2));
    std::cout << "Sum of level 1: " << getLevelSum(root, 1) << std::endl;

    //Test getReversalsToSort
    std::vector<int> arr3 = {12, 13, 15, 14};
    std::vector<std::size_t> reversals;
    reversals = getReversalsToSort(arr3);
    std::cout << "Reversals: ";
    for (std::size_t rev : reversals) {
        std::cout << rev << " ";
    }
    std::cout << std::endl;

    return 0;
}
