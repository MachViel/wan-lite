#include <cstdio>
#include <string>

namespace wanlite {

struct T5Context { int dummy; };

T5Context* t5_load(const std::string& path) {
    (void)path;
    return nullptr; // 占位
}

void t5_free(T5Context* ctx) {
    (void)ctx;
}

}  // namespace wanlite
