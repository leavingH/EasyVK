#include "Descriptor.hpp"

namespace ezvk {
VkResult DescriptorPool::create(VkDevice                    device,
                                VkDescriptorPoolCreateFlags flags, u32 maxSets,
                                u32                   poolSizeCount,
                                VkDescriptorPoolSize* pPoolSize) {
  VkDescriptorPoolCreateInfo CI{
      .sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
      .pNext         = nullptr,
      .flags         = flags,
      .maxSets       = maxSets,
      .poolSizeCount = poolSizeCount,
      .pPoolSizes    = pPoolSize,
  };
  return vkCreateDescriptorPool(device, &CI, nullptr, &descPool);
}

void DescriptorPool::destroy(VkDevice device) {
  return vkDestroyDescriptorPool(device, descPool, nullptr);
}

std::vector<VkDescriptorSet>
DescriptorPool::allocSets(VkDevice device, u32 setCount,
                          VkDescriptorSetLayout* pSetLayout) {
  VkDescriptorSetAllocateInfo AI{
      .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
      .pNext              = nullptr,
      .descriptorPool     = descPool,
      .descriptorSetCount = setCount,
      .pSetLayouts        = pSetLayout,
  };

  std::vector<VkDescriptorSet> ret(setCount);
  auto result = vkAllocateDescriptorSets(device, &AI, ret.data());
  assert(result == VK_SUCCESS);
  return ret;
}

void DescriptorPool::freeSets(VkDevice                      device,
                              std::vector<VkDescriptorSet>& sets) {
  vkFreeDescriptorSets(device, descPool, (u32)sets.size(), sets.data());
}

VkDescriptorSet DescriptorPool::allocSet(VkDevice              device,
                                         VkDescriptorSetLayout setLayout) {
  VkDescriptorSetAllocateInfo AI{
      .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
      .pNext              = nullptr,
      .descriptorPool     = descPool,
      .descriptorSetCount = 1,
      .pSetLayouts        = &setLayout,
  };
  VkDescriptorSet ret;
  auto            result = vkAllocateDescriptorSets(device, &AI, &ret);
  assert(result == VK_SUCCESS);
  return ret;
}

void DescriptorPool::freeSet(VkDevice device, VkDescriptorSet set) {
  vkFreeDescriptorSets(device, descPool, 1, &set);
}

VkResult DescriptorSetLayout::create(VkDevice device, u32 bindingCount,
                                     VkDescriptorSetLayoutBinding* pBindings) {
  VkDescriptorSetLayoutCreateInfo CI{
      .sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
      .pNext        = nullptr,
      .bindingCount = bindingCount,
      .pBindings    = pBindings,
  };
  return vkCreateDescriptorSetLayout(device, &CI, nullptr, &setLayout);
}

void DescriptorSetLayout::destroy(VkDevice device) {
  return vkDestroyDescriptorSetLayout(device, setLayout, nullptr);
}
/*
  WriteDescriptorSet
 */

WriteDescriptorSet&
WriteDescriptorSet::add(VkDescriptorSet dstSet, uint32_t dstBinding,
                        uint32_t dstArrayElement, uint32_t descriptorCount,
                        VkDescriptorType              descriptorType,
                        const VkDescriptorImageInfo*  pImageInfo,
                        const VkDescriptorBufferInfo* pBufferInfo,
                        const VkBufferView*           pTexelBufferView) {
  VkWriteDescriptorSet writeDS{
      .sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
      .pNext            = nullptr,
      .dstSet           = dstSet,
      .dstBinding       = dstBinding,
      .dstArrayElement  = dstArrayElement,
      .descriptorCount  = descriptorCount,
      .descriptorType   = descriptorType,
      .pImageInfo       = pImageInfo,
      .pBufferInfo      = pBufferInfo,
      .pTexelBufferView = pTexelBufferView,
  };
  writeSets.push_back(writeDS);
  return *this;
}
} // namespace ezvk