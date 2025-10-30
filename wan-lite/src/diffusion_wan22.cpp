#include <cstdio>
#include <string>

namespace wanlite {

struct Wan22Context { int dummy; };

Wan22Context* wan22_load(const std::string& low, const std::string& high) {
    (void)low; (void)high;
    return nullptr; // 占位
}

void wan22_free(Wan22Context* ctx) {
    (void)ctx;
}

}  // namespace wanlite
