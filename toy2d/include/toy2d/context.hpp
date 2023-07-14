#pragma once

#include <memory>
#include <optional>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_handles.hpp>

namespace toy2d {
  struct QueueFamliyIndices final {
    std::optional<uint32_t> GraphicsQueue;
  };

  class Context final {
   public:
    static Context& GetInstance();
    static void Init();
    static void Quit();
    ~Context();
    vk::Instance Instance;
    vk::PhysicalDevice PhysicalDevice;
    vk::Device Device;
    QueueFamliyIndices QueueFamliyIndices;
    vk::Queue GraphicsQueue;

   private:
    Context();
    void showLayers();
    void showExtensions();
    void showPhysicalDevices(vk::Instance instance);
    void createInstance();
    void pickupPhysicalDevice();
    void queryQueueFamliyIndices();
    void createDevice();
    void getGraphicsQueue();
    static std::unique_ptr<Context> instance_;
  };
}  // namespace toy2d
