#pragma once
#include "common.hpp"

#include <initializer_list>
#include <span>
namespace ezvk {

struct DescriptorPoolSizeList {
  std::vector<VkDescriptorPoolSize> list;
  DescriptorPoolSizeList() = default;
  DescriptorPoolSizeList(std::vector<VkDescriptorPoolSize> lists)
      : list(std::move(lists)) {}

  DescriptorPoolSizeList& add(VkDescriptorType type, u32 descriptorCount) {
    list.push_back({type, descriptorCount});
    return *this;
  }
};
struct DescriptorPool {
  VkDescriptorPool descPool;

  VkResult create(VkDevice device, VkDescriptorPoolCreateFlags flags,
                  u32 maxSets, u32 poolSizeCount,
                  VkDescriptorPoolSize* pPoolSize);

  VkResult create(VkDevice device, VkDescriptorPoolCreateFlags flags,
                  u32 maxSets, std::vector<VkDescriptorPoolSize>& poolSizes) {
    return create(device, flags, maxSets, u32(poolSizes.size()),
                  poolSizes.data());
  }

  void destroy(VkDevice device);

  [[nodiscard]] VkDescriptorSet allocSet(VkDevice              device,
                                         VkDescriptorSetLayout setLayout);
  void                          freeSet(VkDevice device, VkDescriptorSet set);

  [[nodiscard]] std::vector<VkDescriptorSet>
  allocSets(VkDevice device, u32 setCount, VkDescriptorSetLayout* pSetLayout);
  [[nodiscard]] std::vector<VkDescriptorSet>
  allocSets(VkDevice device, std::vector<VkDescriptorSetLayout>& setLayouts) {
    return allocSets(device, u32(setLayouts.size()), setLayouts.data());
  }

  void freeSets(VkDevice device, u32 setCount,
                VkDescriptorSetLayout* pSetLayout);
  void freeSets(VkDevice device, std::vector<VkDescriptorSet>& sets);
};
struct DescriptorSetLayoutBindingList {
  std::vector<VkDescriptorSetLayoutBinding> bindings;

  DescriptorSetLayoutBindingList&
  add(u32 binding, VkDescriptorType descriptorType, u32 descriptorCount,
      VkShaderStageFlags stageFlags,
      const VkSampler*   pImmutableSampler = nullptr) {
    bindings.push_back({binding, descriptorType, descriptorCount, stageFlags,
                        pImmutableSampler});
    return *this;
  }
};

struct WriteDescriptorSet {
  std::vector<VkWriteDescriptorSet> writeSets;

  WriteDescriptorSet& addBuffer(VkDescriptorSet dstSet, u32 dstBinding,
                                u32 dstArrayElement, u32 descriptorCount,
                                VkDescriptorType              descriptorType,
                                const VkDescriptorBufferInfo* pBufferInfo) {
    return add(dstSet, dstBinding, dstArrayElement, descriptorCount,
               descriptorType, nullptr, pBufferInfo, nullptr);
  }
  WriteDescriptorSet& addImage(VkDescriptorSet dstSet, u32 dstBinding,
                               u32 dstArrayElement, u32 descriptorCount,
                               VkDescriptorType             descriptorType,
                               const VkDescriptorImageInfo* pImageInfo) {
    return add(dstSet, dstBinding, dstArrayElement, descriptorCount,
               descriptorType, pImageInfo, nullptr, nullptr);
  }
  WriteDescriptorSet& addTexelBufferView(VkDescriptorSet dstSet, u32 dstBinding,
                                         u32                 dstArrayElement,
                                         u32                 descriptorCount,
                                         VkDescriptorType    descriptorType,
                                         const VkBufferView* pTexelBufferView) {
    return add(dstSet, dstBinding, dstArrayElement, descriptorCount,
               descriptorType, nullptr, nullptr, pTexelBufferView);
  }

  WriteDescriptorSet& add(VkDescriptorSet dstSet, u32 dstBinding,
                          u32 dstArrayElement, u32 descriptorCount,
                          VkDescriptorType              descriptorType,
                          const VkDescriptorImageInfo*  pImageInfo,
                          const VkDescriptorBufferInfo* pBufferInfo,
                          const VkBufferView*           pTexelBufferView);
};

struct DescriptorSetLayout {
  VkDescriptorSetLayout setLayout;

  VkResult create(VkDevice device, u32 bindingCount,
                  VkDescriptorSetLayoutBinding* pBindings);

  VkResult create(VkDevice                                   device,
                  std::vector<VkDescriptorSetLayoutBinding>& bindings) {
    return create(device, u32(bindings.size()), bindings.data());
  }

  void destroy(VkDevice device);

  EZVK_CONVERT_OP(VkDescriptorSetLayout, setLayout);
  EZVK_ADDRESS_OP(VkDescriptorSetLayout, setLayout);
};

} // namespace ezvk