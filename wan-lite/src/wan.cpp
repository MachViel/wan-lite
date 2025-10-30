#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <string>

#include "ggml/ggml.h"
#include "wan/wan.h"

static void usage(const char* prog) {
    printf("Usage: %s --prompt <text> --diffusion-model <low> [--high-noise-diffusion-model <high>] \\\n", prog);
    printf("              --vae <vae> --t5xxl <t5> [-o output] [-W w] [-H h] [--frames n] [--steps s] [--cfg c]\n");
}

int main(int argc, const char** argv) {
    std::string prompt;
    std::string output = "output.avi";
    int width = 480, height = 832, frames = 33;
    int steps = 10;
    float cfg = 6.0f;

    Wan22Paths paths;
    WanGenOptions opt;

    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        auto need = [&](int n){ return i + n < argc; };
        if ((a == "-p" || a == "--prompt") && need(1)) prompt = argv[++i];
        else if (a == "--diffusion-model" && need(1)) paths.diffusion_low_path = argv[++i];
        else if (a == "--high-noise-diffusion-model" && need(1)) paths.diffusion_high_path = argv[++i];
        else if (a == "--vae" && need(1)) paths.vae_path = argv[++i];
        else if (a == "--t5xxl" && need(1)) paths.t5xxl_path = argv[++i];
        else if ((a == "-o" || a == "--output") && need(1)) output = argv[++i];
        else if ((a == "-W" || a == "--width") && need(1)) width = std::atoi(argv[++i]);
        else if ((a == "-H" || a == "--height") && need(1)) height = std::atoi(argv[++i]);
        else if (a == "--frames" && need(1)) frames = std::atoi(argv[++i]);
        else if (a == "--steps" && need(1)) steps = std::atoi(argv[++i]);
        else if (a == "--cfg" && need(1)) cfg = std::atof(argv[++i]);
        else if (a == "-h" || a == "--help") { usage(argv[0]); return 0; }
        else { fprintf(stderr, "Unknown arg: %s\n", a.c_str()); usage(argv[0]); return 1; }
    }

    if (prompt.empty() || paths.diffusion_low_path.empty() || paths.vae_path.empty() || paths.t5xxl_path.empty()) {
        fprintf(stderr, "缺少必要参数\n");
        usage(argv[0]);
        return 1;
    }

    opt.width = width; opt.height = height; opt.frames = frames;
    opt.steps_low = steps; opt.cfg_low = cfg;

    // 占位ggml初始化，确保工程可运行
    struct ggml_init_params gg = { 16*1024*1024, nullptr, true };
    ggml_context* ctx = ggml_init(gg);
    if (!ctx) { fprintf(stderr, "ggml_init 失败\n"); return 1; }

    int rc = wan22_generate_video(paths, prompt, opt, output);
    ggml_free(ctx);
    return rc;
}
