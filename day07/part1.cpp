#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <regex>

const long long int MOD = 1e9 + 7;

struct Dir {
  long long int hash_name = 0;
  long long int size = 0;
  std::vector<Dir*> children = {};

  Dir() {}
  Dir(long long int hash) : hash_name(hash) {}
  ~Dir() {
    for (auto &child : children) {
      delete child;
    }
    children.clear();
  }
};

long long int get_hash(const std::string &str, int pow = 29) {
  long long int result = 0;
  long long int curr_pow = 1;
  for (unsigned int i = 0; i < str.length(); i++) {
    result += curr_pow * (str[i] - 'a' + 1);
    curr_pow *= pow;
    if (result >= MOD) result %= MOD;
    if (curr_pow >= MOD) curr_pow %= MOD;
  }
  return result;
}

void dfs(Dir *&node, long long int &sum, long long int max_size) {
  for (auto &child: node->children) {
    dfs(child, sum, max_size);
    node->size += child->size;
  }
  if (node->size <= max_size) sum += node->size;
}

int main(int argc, char *argv[]) {
  if (argc > 0) {
    std::fstream file;
    file.open(argv[1], std::ios::in);

    if (file.is_open()) {
      std::string input;
      long long int sum = 0, max_size = 1e5;
      std::stack<Dir*> st;
      Dir *root = new Dir();

      while (std::getline(file, input)) {
        if (input == "") continue;

        if (input[0] == '$') {
          if (input[2] == 'l') continue;

          std::string dirname = input.substr(5);
          if (dirname == "..") {
            st.pop();
          } else if (st.empty()) {
            st.push(root);
          } else {
            long long int hash = get_hash(dirname);
            Dir *curr_dir = st.top();
            for (auto &child : curr_dir->children) {
              if (child->hash_name == hash) {
                st.push(child);
                break;
              }
            }
          }
        } else if (input[0] == 'd') {
          Dir *child = new Dir(get_hash(input.substr(4)));
          Dir *curr_dir = st.top();
          curr_dir->children.push_back(child);
        } else {
          std::regex str_pattern("[0-9]+");
          std::regex_token_iterator<std::string::iterator> a(input.begin(), input.end(), str_pattern);

          long long int size = atoi(&((std::string)*a)[0]);
          Dir *curr_dir = st.top();
          curr_dir->size += size;
        }
      }
      dfs(root, sum, max_size);
      std::cout << sum << std::endl;
      file.close();
      delete root;
    }
  }
  return 0;
}