#include <cstdio>
#include <string>

#include "wan/wan.h"

#include "ggml/ggml.h"

static bool path_ok(const std::string& p) {
    FILE* f = fopen(p.c_str(), "rb");
    if (!f) return false;
    fclose(f);
    return true;
}

int wan22_generate_video(const Wan22Paths& paths,
                         const std::string& prompt,
                         const WanGenOptions& opt,
                         const std::string& output_path) {
    if (prompt.empty()) {
        fprintf(stderr, "prompt 为空\n");
        return 2;
    }
    if (!path_ok(paths.diffusion_low_path)) {
        fprintf(stderr, "找不到 diffusion 低噪模型: %s\n", paths.diffusion_low_path.c_str());
        return 3;
    }
    if (!paths.diffusion_high_path.empty() && !path_ok(paths.diffusion_high_path)) {
        fprintf(stderr, "找不到 diffusion 高噪模型: %s\n", paths.diffusion_high_path.c_str());
        return 4;
    }
    if (!path_ok(paths.vae_path)) {
        fprintf(stderr, "找不到 VAE: %s\n", paths.vae_path.c_str());
        return 5;
    }
    if (!path_ok(paths.t5xxl_path)) {
        fprintf(stderr, "找不到 T5XXL: %s\n", paths.t5xxl_path.c_str());
        return 6;
    }

    printf("[wan-lite] 运行参数\n");
    printf("prompt: %s\n", prompt.c_str());
    printf("size: %dx%d, frames: %d, output: %s\n", opt.width, opt.height, opt.frames, output_path.c_str());
    printf("low model: %s\n", paths.diffusion_low_path.c_str());
    if (!paths.diffusion_high_path.empty()) printf("high model: %s\n", paths.diffusion_high_path.c_str());
    printf("vae: %s\n", paths.vae_path.c_str());
    printf("t5xxl: %s\n", paths.t5xxl_path.c_str());

    fprintf(stderr, "[wan-lite] Wan2.2 推理主体未实现（当前是骨架）。\n");
    return 10;
}
