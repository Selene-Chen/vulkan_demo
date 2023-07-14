#pragma once

#include <memory>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_handles.hpp>

namespace toy2d {
  class Context final {
   public:
    static Context& GetInstance();
    static void Init();
    static void Quit();
    ~Context();
    vk::Instance Instance;
    vk::PhysicalDevice PhysicalDevice;

   private:
    Context();
    void showLayers();
    void showExtensions();
    void showPhysicalDevices(vk::Instance instance);
    void createInstance();
    void pickupPhysicalDevice();
    static std::unique_ptr<Context> instance_;
  };
}  // namespace toy2d
