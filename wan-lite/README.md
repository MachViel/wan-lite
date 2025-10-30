# wan-lite (独立、轻量)

- 目标：独立于 `stable-diffusion.cpp` 的最小工程，仅依赖 `ggml`，为后续实现 WAN 2.2 推理准备。
- 当前：提供最小 CLI 与 `ggml` 初始化占位，可独立构建运行；后续可逐步填入 WAN 2.2 相关模块（文本编码、UNet/DiT、VAE、采样器等）。

## 依赖
- 已安装的 `ggml` 源码目录（默认 `/root/ggml/ggml`）。

## 构建
```bash
cd /root/wan-lite
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DGGML_DIR=/root/ggml/ggml
cmake --build build -j
```

## 运行
```bash
./build/wan --prompt "a lovely cat" -W 480 -H 832 --frames 33 -o output.avi
```

> 说明：当前版本仅输出参数信息并进行 `ggml` 初始化（占位）；后续可按需接入 WAN 2.2 的权重加载与推理实现，仍保持工程轻量与简洁。
