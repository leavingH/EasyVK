#pragma once
#include "common.hpp"

#include <string>

namespace ezvk {
class Shader {
public:
  VkPipelineShaderStageCreateInfo m_shaderInfo;
  std::string                     m_name;

  void create(VkDevice device, std::string name, VkShaderStageFlagBits stage,
              u32* code, size_t size, ccstr entryName = "main",
              const VkSpecializationInfo* pSpecializationInfo = nullptr);

  template <typename T, typename = std::void_t<std::is_arithmetic<T>>>
  void create(VkDevice device, std::string name, VkShaderStageFlagBits stage,
              std::vector<T>& vec, ccstr entryName = "main",
              const VkSpecializationInfo* pSpecializationInfo = nullptr) {
    this->create(device, std::move(name), stage,
                 reinterpret_cast<u32*>(vec.data()), vec.size(), entryName,
                 pSpecializationInfo);
  }

  void destroy(VkDevice device);

  EZVK_CONVERT_OP(VkPipelineShaderStageCreateInfo, m_shaderInfo);
};
} // namespace ezvk
