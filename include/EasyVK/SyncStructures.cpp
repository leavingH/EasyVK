
#include "SyncStructures.hpp"

namespace ezvk {
void Fence::createSignaled(VkDevice device) {
  create(device, VK_FENCE_CREATE_SIGNALED_BIT);
}

void Fence::create(VkDevice device, VkFenceCreateFlags flag) {
  VkFenceCreateInfo CI{
      .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = flag,
  };
  vkCreateFence(device, &CI, nullptr, &fence);
}

void Fence::destroy(VkDevice device) {
  vkDestroyFence(device, fence, nullptr);
}

VkResult Fence::reset(VkDevice device) {
  return vkResetFences(device, 1, &fence);
}

void Semaphore::create(VkDevice device) {
  VkSemaphoreCreateInfo CI{
      .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
      .pNext = nullptr,
      .flags = 0,
  };
  vkCreateSemaphore(device, &CI, nullptr, &semaphore);
}

void Semaphore::destroy(VkDevice device) {
  vkDestroySemaphore(device, semaphore, nullptr);
}

} // namespace ezvk