#include <vector>
#include <queue>
#include <algorithm>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <stdexcept>

#include "INode.h"

/**
 * Implement a method that returns number that is closest to zero in a given vector.
 * If there are two equally close to zero elements like 2 and -2,
 * then consider the positive element to be "closer" to zero.
 */
int getClosestToZero(const std::vector<int>& arr) {
    if (arr.empty()) {
        throw std::invalid_argument("Input array is empty.");
    }
    int closest = arr[0];

    for (int num : arr) {
        if (std::abs(num) < std::abs(closest) || 
           (std::abs(num) == std::abs(closest) && num > closest)) {
            closest = num;
        }
    }
    return closest;
}

/**
 * Please implement this method to return count of chunks in given array.
 *
 * Chunk is defined as continuous sequence of one or more non-zero numbers separated by one or more zeroes.
 * Input can contain leading and trailing zeroes.
 *
 * Example: [5, 4, 0, 0, -1, 0, 2, 0, 0] contains 3 chunks
 */
std::size_t countChunks(const std::vector<int>& arr) {
    std::size_t chunkCount = 0;
    bool inChunk = false;

    for (int num : arr) {
        if (num != 0) {
            if (!inChunk) {
                ++chunkCount;
                inChunk = true;
            }
        } else {
            inChunk = false;
        }
    }

    return chunkCount;
}

/**
 * Open INode.h to see the INode interface.
 *
 * Implement following function that shall traverse the tree,
 * and return the sum of the values (INode.value()) of all nodes
 * at the level 'n' in the tree.
 * 
 * Node root is assumed to be at the level 0. All its children are level 1, etc.
 */
int getLevelSum(const INode& root, std::size_t n) {
    if (n == 0) {
        return root.value();
    }
    std::queue<const INode*> nodeQueue;
    nodeQueue.push(&root);
    std::size_t currentLevel = 0;

    while (!nodeQueue.empty()) {
        std::size_t levelSize = nodeQueue.size();  //Number of nodes at the current level
        //Process all nodes at the current level
        if (currentLevel == n) {
            int levelSum = 0;
            for (std::size_t i = 0; i < levelSize; ++i) {
                const INode* node = nodeQueue.front();
                nodeQueue.pop();
                levelSum += node->value();
            }
            return levelSum;
        }
        //Move to the next level, adding all children of current level's nodes
        for (std::size_t i = 0; i < levelSize; ++i) {
            const INode* node = nodeQueue.front();
            nodeQueue.pop();
            for (const auto& child : node->children()) {
                nodeQueue.push(child.get());
            }
        }

        ++currentLevel;
    }

    return 0;
}

/**
 * Imagine a sort algorithm, that sorts array of integers by repeatedly reversing
 * the order of the first several elements of it.
 *
 * For example, to sort [12,13,11,14], you need to reverse the order of the first two (2)
 * elements. You will get [13,12,11,14].
 * Then you shall reverse the order of the first three (3) elements,
 * and you will get [11,12,13,14]
 *
 * For this assignment you shall implement function
 * that returns list of integers corresponding to the required reversals.
 * E.g. for given vector [12,13,11,14]
 * the function should return [2, 3].
 */
std::vector<std::size_t> getReversalsToSort(const std::vector<int>& arr) {
    std::vector<int> workingArr = arr;  // Make a copy of the original array to sort
    std::vector<std::size_t> reversals; // To store the sequence of reversals

    for (std::size_t size = workingArr.size(); size > 1; --size) {
        auto maxElementIter = std::max_element(workingArr.begin(), workingArr.begin() + size);
        std::size_t maxIndex = std::distance(workingArr.begin(), maxElementIter);

        if (maxIndex + 1 == size) {
            //If the largest element is already in the correct position, skip
            continue;
        }
        //If the max element is not at the beginning, reverse it to bring it to the front
        if (maxIndex != 0) {
            reversals.push_back(maxIndex + 1);
            std::reverse(workingArr.begin(), workingArr.begin() + maxIndex + 1);
        }
        reversals.push_back(size);
        std::reverse(workingArr.begin(), workingArr.begin() + size);
    }

    return reversals;
}
