// Puzzle is available at https://adventofcode.com/2022/day/7
// Keywords:
#include "../../../src/utils.hpp"
#include "../2022.hpp"
using namespace std;

class FileTree {
  unordered_map<string, FileTree *> children;
  int fileSize = 0;
  int totalSize = 0;

 public:
  FileTree *parent = nullptr;
  bool viewed = false;

  int count() {
    if (totalSize > 0) {
      return totalSize;
    }
    int size = fileSize;
    for (auto &[name, ptr] : children) {
      size += ptr->count();
    }
    totalSize = size;
    return size;
  }

  int countWithLimit(int limit) {
    int size = 0;
    if (totalSize < limit) {
      size += totalSize;
    }
    for (auto &[name, ptr] : children) {
      size += ptr->countWithLimit(limit);
    }
    return size;
  }

  int findSmallestSizeGreaterThanLimit(int limit) {
    if (totalSize < limit) {
      return 0;
    }
    int min_size = totalSize;
    for (auto &[name, ptr] : children) {
      int curSize = ptr->findSmallestSizeGreaterThanLimit(limit);
      if (curSize > 0 && curSize < min_size) {
        min_size = curSize;
      }
    }
    return min_size;
  }

  FileTree *getChild(const string &name) {
    if (!children.contains(name)) {
      children[name] = new FileTree();
      children[name]->parent = this;
    }
    return children[name];
  }

  void addFile(int size) {
    if (!viewed) {
      fileSize += size;
    }
  }

  FileTree *getParent() const { return parent; }

  void deleteTree() {
    for (const auto &[name, ptr] : children) {
      ptr->deleteTree();
    }
    delete this;
  }
};

FileTree *generateFileTree(const std::vector<std::string> &input) {
  auto root = new FileTree();
  FileTree *cur;
  int i = 0;
  while (i < input.size()) {
    string s = input[i];
    if (s.starts_with("$ cd")) {
      string nextDir = s.substr(5);
      if (nextDir == "/") {
        cur = root;
      } else if (nextDir == "..") {
        cur = cur->getParent();
      } else {
        cur = cur->getChild(nextDir);
      }
      ++i;
    } else if (s.starts_with("$ ls")) {
      while (++i < input.size() && input[i][0] != '$') {
        if (cur->viewed) {
          continue;
        }
        if (input[i].substr(0, 3) == "dir") {
          cur->getChild(input[i].substr(4));
        } else {
          int pos = input[i].find(' ');
          cur->addFile(stoi(input[i].substr(0, pos)));
        }
      }
      cur->viewed = true;
    }
  }
  return root;
}

std::string y2022::solve_07a(const std::vector<std::string> &input) {
  auto root = generateFileTree(input);
  root->count();
  int smallDirsSize = root->countWithLimit(100000);
  root->deleteTree();
  return to_string(smallDirsSize);
}

std::string y2022::solve_07b(const std::vector<std::string> &input) {
  auto root = generateFileTree(input);
  int minAmountToFree = root->count() - 40000000;
  int sizeToFree = root->findSmallestSizeGreaterThanLimit(minAmountToFree);
  root->deleteTree();
  return to_string(sizeToFree);
}
