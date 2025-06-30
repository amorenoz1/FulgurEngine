#pragma once

#include <string>
#include <vector>

namespace Gfx {

class Shader {
  private:
    std::vector<char> m_ShaderBinary;

  public:
    Shader(const std::string& filepath);
    const std::vector<char>& GetShaderBinary();
    ~Shader();
};
}; // namespace Gfx
