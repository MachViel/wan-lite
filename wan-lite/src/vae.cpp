#include <cstdio>
#include <string>

namespace wanlite {

struct VaeContext { int dummy; };

VaeContext* vae_load(const std::string& path) {
    (void)path;
    return nullptr; // 占位：返回空表示未实现
}

void vae_free(VaeContext* ctx) {
    (void)ctx;
}

}  // namespace wanlite
