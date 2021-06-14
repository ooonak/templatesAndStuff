#include "githash.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

// This string is replaced first time replace function is called,
// and written into the binary file on disk.
const std::string s("#-.:wqdabcddcbadcba");

void replace(const std::string &fileName, std::string r) {
  int x = 17;
  // '#' is 35 ^ 17 = 50, '-' is 45 ^ 18 = 63, '.' is 46 ^ 19 = 61
  if (!((s[0] ^ x++) == 50 && (s[1] ^ x++) == 63 && (s[2] ^ x) == 61))
    return;

  r.resize(s.length(), ' ');

  std::ifstream inFile(fileName, std::ios::binary | std::ios::ate);
  std::streamsize size = inFile.tellg();
  inFile.seekg(0, std::ios::beg);

  std::vector<char> buffer(size);
  if (inFile.read(buffer.data(), size)) {
    inFile.close();
    size_t count = 0;
    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
      if (*it == s[count])
        count++;
      else
        count = 0;

      if (count == s.length()) {
        std::cout << "Found it :-)\n" << std::endl;
        std::cout << "Will replace string '" << s << "' in binary with '" << r
                  << "'." << std::endl;
        it -= (count - 1);

        for (auto i = r.begin(); i != r.end(); ++i) {
          *it = *i;
          it++;
        }

        // For test, remove "_"
        std::ofstream outFile(fileName + "_", std::ios::binary);
        outFile.write(buffer.data(), size);
        outFile.close();

        break;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  std::cout << "Compile date: " << compileDate << std::endl;
  std::cout << "GitHash: " << gitHash << "\n" << std::endl;

  if (argc == 3 && strlen(argv[0]) > 0 &&
      strncmp(argv[1], "--setKey", strlen("--setKey")) == 0 &&
      strlen(argv[2]) > 0) {
    replace(std::string(argv[0]), std::string(argv[2]));
  }

  return 0;
}
