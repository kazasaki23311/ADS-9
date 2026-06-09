// Copyright 2022 NNTU-CS
#include <algorithm>
#include <memory>
#include <vector>
#include "tree.h"

int PMTree::factorial(int n) {
  if (n <= 1) return 1;
  int result = 1;
  for (int i = 2; i <= n; i++) {
    result *= i;
  }
  return result;
}

PMTree::PMTree(const std::vector<char>& elements) : originalElements(elements) {
  if (elements.empty()) {
    root = nullptr;
    return;
  }
  std::vector<char> sorted = elements;
  std::sort(sorted.begin(), sorted.end());
  root = std::make_shared<Node>('\0');
  buildTree(root, sorted);
}

void PMTree::buildTree(std::shared_ptr<Node> node,
                       std::vector<char> remaining) {
  if (remaining.empty()) {
    return;
  }
  for (char c : remaining) {
    auto child = std::make_shared<Node>(c);
    node->children.push_back(child);
    std::vector<char> newRemaining;
    for (char ch : remaining) {
      if (ch != c) {
        newRemaining.push_back(ch);
      }
    }
    buildTree(child, newRemaining);
  }
}

void PMTree::getAllPermutations(std::shared_ptr<Node> node, std::vector<char>& current,
                                std::vector<std::vector<char>>& result) {
  if (!node) return;
  if (node->value != '\0') {
    current.push_back(node->value);
  }
  if (node->children.empty() && node->value != '\0') {
    result.push_back(current);
  } else {
    for (auto& child : node->children) {
      getAllPermutations(child, current, result);
    }
  }
  if (node->value != '\0') {
    current.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  if (!tree.root || tree.root->children.empty()) {
    return result;
  }
  std::vector<char> current;
  for (auto& child : tree.root->children) {
    tree.getAllPermutations(child, current, result);
  }
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  if (num < 1) return std::vector<char>();
  int totalPerms = PMTree::factorial(tree.originalElements.size());
  if (num > totalPerms) return std::vector<char>();
  std::vector<std::vector<char>> allPerms = getAllPerms(tree);
  if (num <= static_cast<int>(allPerms.size())) {
    return allPerms[num - 1];
  }
  return std::vector<char>();
}

bool navigateToPermutation(std::shared_ptr<PMTree::Node> node,
                           std::vector<char>& result,
                           int& remainingNum,
                           const std::vector<char>& originalElements) {
  if (!node) return false;
  if (node->value != '\0') {
    result.push_back(node->value);
  }
  if (node->children.empty()) {
    return true;
  }
  int remainingPositions = originalElements.size() - result.size();
  int blockSize = PMTree::factorial(remainingPositions - 1);
  int childIndex = (remainingNum - 1) / blockSize;
  if (childIndex >= static_cast<int>(node->children.size())) {
    return false;
  }
  remainingNum = (remainingNum - 1) % blockSize + 1;
  return navigateToPermutation(node->children[childIndex], result,
                               remainingNum, originalElements);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  if (num < 1) return std::vector<char>();
  int n = tree.originalElements.size();
  int totalPerms = PMTree::factorial(n);
  if (num > totalPerms) return std::vector<char>();
  std::vector<char> result;
  int currentNum = num;
  int blockSize = PMTree::factorial(n - 1);
  int childIndex = (num - 1) / blockSize;
  if (childIndex >= static_cast<int>(tree.root->children.size())) {
    return std::vector<char>();
  }
  currentNum = (num - 1) % blockSize + 1;
  if (navigateToPermutation(tree.root->children[childIndex], result,
                            currentNum, tree.originalElements)) {
    return result;
  }
  return std::vector<char>();
}
