// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <fstream>
#include "tree.h"

int main() {
  std::cout << "Experiment\n";
  std::vector<char> data1 = { '1', '2', '3' };
  PMTree tree1(data1);
  std::cout << "Input: {1,2,3}\n";
  std::cout << "All permutations:\n";
  std::vector<std::vector<char>> allPerms = getAllPerms(tree1);
  for (size_t i = 0; i < allPerms.size(); i++) {
    std::cout << "  " << i + 1 << ": ";
    for (char c : allPerms[i]) std::cout << c;
    std::cout << "\n";
  }
  std::cout << "\nGetting permutations by number:\n";
  std::vector<char> perm1 = getPerm1(tree1, 1);
  std::cout << "getPerm1(1): ";
  for (char c : perm1) std::cout << c;
  std::cout << "\n";
  std::vector<char> perm2 = getPerm2(tree1, 2);
  std::cout << "getPerm2(2): ";
  for (char c : perm2) std::cout << c;
  std::cout << "\n";
  std::cout << "PERFORMANCE EXPERIMENT:\n";
  std::cout << "----------------------\n";
  std::cout << std::setw(10) << "n"
        << std::setw(20) << "getAllPerms (s)"
        << std::setw(20) << "getPerm1 (s)"
        << std::setw(20) << "getPerm2 (s)\n";
  std::cout << std::string(70, '-') << "\n";
  std::vector<int> sizes;
  std::vector<double> getAllPermsTimes;
  std::vector<double> getPerm1Times;
  std::vector<double> getPerm2Times;
  std::random_device rd;
  std::mt19937 gen(rd());
  for (int n = 1; n <= 10; n++) {
    std::vector<char> testData;
    for (int i = 0; i < n; i++) {
      testData.push_back('0' + (i % 10));
    }
    PMTree tree(testData);
    int totalPerms = PMTree::factorial(n);
    std::uniform_int_distribution<> dis(1, totalPerms);
    int randomPermNum = dis(gen);
    std::cout << std::setw(10) << n;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time1 = end - start;
    getAllPermsTimes.push_back(time1.count());
    std::cout << std::setw(20) << std::fixed << std::setprecision(6) << time1.count();
    start = std::chrono::high_resolution_clock::now();
    std::vector<char> p1 = getPerm1(tree, randomPermNum);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time2 = end - start;
    getPerm1Times.push_back(time2.count());
    std::cout << std::setw(20) << time2.count();
    start = std::chrono::high_resolution_clock::now();
    std::vector<char> p2 = getPerm2(tree, randomPermNum);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time3 = end - start;
    getPerm2Times.push_back(time3.count());
    std::cout << std::setw(20) << time3.count() << "\n";
    sizes.push_back(n);
    if (time1.count() > 10.0 && n >= 8) {
      std::cout << "\nStopping - time exceeds 10 seconds\n";
      break;
    }
  }
  system("mkdir -p result");
  std::ofstream csv("result/data.csv");
  csv << "n,getAllPerms_us,getPerm1_us,getPerm2_us\n";
  for (size_t i = 0; i < sizes.size(); i++) {
    csv << sizes[i] << ","
            << std::fixed << std::setprecision(3)
            << getAllPermsTimes[i] * 1000000 << ","
            << getPerm1Times[i] * 1000000 << ","
            << getPerm2Times[i] * 1000000 << "\n";
  }
  csv.close();
  std::cout << "Data saved to result/data.csv (values in microseconds)\n";
  return 0;
}
