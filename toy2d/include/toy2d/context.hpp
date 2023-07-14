#pragma once

#include <memory>
#include <vulkan/vulkan.hpp>

namespace toy2d {
  class Context final {
   public:
    static Context& GetInstance();
    static void Init();
    static void Quit();
    ~Context();
    vk::Instance Instance;

   private:
    Context();
    void ShowLayers();
    static std::unique_ptr<Context> instance_;
  };
}  // namespace toy2d
