#include "Shader.hpp"
#include "utils/FulgurUtils.hpp"

Gfx::Shader::Shader(const std::string& filepath) {
    m_ShaderBinary = Utils::ReadBinaryFileToByteVector(filepath);
}

const std::vector<char>& Gfx::Shader::GetShaderBinary() { return m_ShaderBinary; }

Gfx::Shader::~Shader() {}
