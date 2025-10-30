#include <cstdio>
#include <string>

namespace wanlite {

bool file_exists(const std::string& p);

bool file_exists(const std::string& p) {
    FILE* f = fopen(p.c_str(), "rb");
    if (!f) return false;
    fclose(f);
    return true;
}

}  // namespace wanlite
