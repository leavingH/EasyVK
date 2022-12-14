#pragma once
#include "common.hpp"

#include "Command.hpp"
#include "SyncStructures.hpp"

namespace ezvk {
class Framebuffer {
public:
  struct FrameData {
    Semaphore     presentSemaphore, renderSemaphore;
    Fence         renderFence;
    CommandPool   mainCmdPool;
    CommandBuffer cmdBuffer;

    void create(VkDevice device, u32 graphicIndex);
    void destroy(VkDevice device);
  };

  static constexpr u32 DATA_COUNT = 1;

  u64       frameCount{0};
  FrameData frameData[DATA_COUNT];

  std::vector<VkFramebuffer> framebuffers;

  void create(VkDevice device, vkb::Swapchain& swapchain,
              VkRenderPass renderPass, VkExtent2D windowExtent,
              std::vector<VkImageView>& swapchainImageViews,
              VkImageView depthImageView, VkImageView imageViews,
              u32 graphicIndex, u32 transferIndex);
  void destroy(VkDevice device);

  // using present semaphore
  VkResult acquireNextImage(VkDevice device, VkSwapchainKHR swapchain,
                            u64 timeout, u32* index);
  void     freeCmdBuffer(VkDevice device);

  FrameData& currentFrameData() {
    FrameData& frame = frameData[frameCount % DATA_COUNT];
    return frame;
  }
};
} // namespace ezvk