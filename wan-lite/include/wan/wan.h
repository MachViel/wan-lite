#ifndef WAN_LITE_WAN_H_
#define WAN_LITE_WAN_H_

#include <cstdint>
#include <string>

struct Wan22Paths {
    std::string diffusion_low_path;      // Wan2.2 低噪(或单段)模型
    std::string diffusion_high_path;     // Wan2.2 高噪模型（可选）
    std::string vae_path;                // VAE 权重
    std::string t5xxl_path;              // 文本编码器 UMT5-XXL 权重
};

struct WanGenOptions {
    int width  = 480;
    int height = 832;
    int frames = 33;
    int steps_low  = 10;
    int steps_high = -1;   // -1 表示自动，仅在高噪存在时使用
    float cfg_low  = 6.0f;
    float cfg_high = 3.5f;
    int threads    = -1;
};

// 生成视频，返回 0 表示成功。当前为骨架实现，会返回非0并打印未实现。
int wan22_generate_video(const Wan22Paths& paths,
                         const std::string& prompt,
                         const WanGenOptions& opt,
                         const std::string& output_path);

#endif  // WAN_LITE_WAN_H_
