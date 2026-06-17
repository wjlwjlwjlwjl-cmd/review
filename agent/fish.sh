#! /usr/bin/bash
cat >>~/.config/fish/config.fish <<EOF
set -x OPENAI_API_KEY "463c85d7-3b2c-4f8d-8427-716c83a6dbce"
set -x OPENAI_BASE_URL "https://ark.cn-beijing.volces.com/api/coding/v3"
EOF
source ~/.config/fish/config.fish
echo "火山引擎模型包配置导入完成"
