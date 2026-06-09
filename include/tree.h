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
  std::vector<char> getPerm1(int num);
  std::vector<char> getPerm2(int num);
  static int factorial(int n);
  std::vector<char> getOriginalElements() const { return originalElements; }
};
#endif  // INCLUDE_TREE_H_
