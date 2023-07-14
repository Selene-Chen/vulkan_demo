#include "toy2d/context.hpp"

#include <vulkan/vulkan_core.h>

#include <iostream>
#include <vector>

namespace toy2d {
  std::unique_ptr<Context> Context::instance_ = nullptr;

  Context& Context::GetInstance() { return *instance_; }
  void Context::Init() { instance_.reset(new Context); }
  void Context::Quit() { instance_.reset(); }

  void Context::ShowLayers() {
    std::cout << "LAYERS:" << std::endl;
    auto layers = vk::enumerateInstanceLayerProperties();
    for (auto& layer : layers) {
      std::cout << layer.layerName << std::endl;
    }
  }

  Context::Context() {
    std::vector<const char*> layers = {"VK_LAYER_KHRONOS_validation"};

    vk::InstanceCreateInfo createInfo;
    vk::ApplicationInfo appInfo;
    appInfo.setApiVersion(VK_API_VERSION_1_2);
    createInfo.setPApplicationInfo(&appInfo).setPEnabledLayerNames(layers);

    Instance = vk::createInstance(createInfo);
  }
  Context::~Context() { Instance.destroy(); }

}  // namespace toy2d
