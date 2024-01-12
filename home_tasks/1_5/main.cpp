#include <cstdint>
#include <iostream>
#include <stack>
#include <stdbool.h>
using namespace std;

template<typename T>
struct BinaryTree {
    T value;
    BinaryTree<T> *left = nullptr;
    BinaryTree<T> *right = nullptr;
};

template<typename T>
BinaryTree<T> *binaryTreeCreate(T value) {
    auto *root = new BinaryTree<T>;
    root->value = value;
    return root;
}

template<typename T>
void binaryTreeAddLeft(BinaryTree<T> *tree, T value) {
    tree->left = binaryTreeCreate(value);
}

template<typename T>
void binaryTreeAddRight(BinaryTree<T> *tree, T value) {
    tree->right = binaryTreeCreate(value);
}


int64_t findMinimumWeightDifference(
    stack<int32_t> *packet,
    BinaryTree<int64_t> *differenceTree,
    int64_t *minimumDifference
) {
    if (packet->empty()) {
        *minimumDifference = min(differenceTree->value, *minimumDifference);

        return *minimumDifference;
    }


    int32_t topValue = packet->top();
    binaryTreeAddLeft(differenceTree, differenceTree->value + topValue);
    binaryTreeAddRight(differenceTree, abs(differenceTree->value - topValue));
    packet->pop();


    findMinimumWeightDifference(packet, differenceTree->left, minimumDifference);
    findMinimumWeightDifference(packet, differenceTree->right, minimumDifference);
    packet->push(topValue);
    return *minimumDifference;
}

int main() {
    stack<int32_t> packet;

    size_t packetSize;
    cin >> packetSize;

    for (size_t i = 0; i < packetSize; i++) {
        int32_t weight;
        cin >> weight;
        packet.push(weight);
    }
    BinaryTree<int64_t> differenceTree = {packet.top()};
    packet.pop();
    int64_t minimumDifference = INT64_MAX;
    cout << findMinimumWeightDifference(&packet, &differenceTree, &minimumDifference);
    return 0;
}
