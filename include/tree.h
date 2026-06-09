// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>
#include <algorithm>

class PMTree {
 private:
  struct Node {
    char value;
    std::vector<std::shared_ptr<Node>> children;
    explicit Node(char val) : value(val) {}
  };
  std::shared_ptr<Node> root;
  std::vector<char> originalElements;
  void buildTree(std::shared_ptr<Node> node, std::vector<char> remaining);
  void getAllPermutations(std::shared_ptr<Node> node, std::vector<char>& current,
                          std::vector<std::vector<char>>& result);
 public:
  explicit PMTree(const std::vector<char>& elements);
  ~PMTree() = default;
  std::vector<std::vector<char>> getAllPerms();
  static int factorial(int n);
  std::vector<char> getOriginalElements() const { return originalElements; }
  friend std::vector<std::vector<char>> getAllPerms(PMTree& tree);
  friend std::vector<char> getPerm1(PMTree& tree, int num);
  friend std::vector<char> getPerm2(PMTree& tree, int num);
  friend bool navigateToPermutation(std::shared_ptr<Node> node,
                                    std::vector<char>& result,
                                    int& remainingNum,
                                    const std::vector<char>& originalElements);
};
std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);
#endif  // INCLUDE_TREE_H_
