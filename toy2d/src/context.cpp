#include "toy2d/context.hpp"

#include <iostream>
#include <vector>

namespace toy2d {
  std::unique_ptr<Context> Context::instance_ = nullptr;

  Context& Context::GetInstance() { return *instance_; }
  void Context::Init() { instance_.reset(new Context); }
  void Context::Quit() { instance_.reset(); }

  void Context::showLayers() {
    std::cout << "LAYERS: " << std::endl;
    auto layers = vk::enumerateInstanceLayerProperties();
    for (auto& layer : layers) {
      std::cout << layer.layerName << std::endl;
    }
  }
  void Context::showExtensions() {
    std::cout << "EXTENSIONS: " << std::endl;
    auto extensions = vk::enumerateInstanceExtensionProperties();
    for (auto& extension : extensions) {
      std::cout << extension.extensionName << std::endl;
    }
  }
  Context::Context() {
    // fixed error:VK_ERROR_INCOMPATIBLE_DRIVER for mac
    std::vector<const char*> extensions = {"VK_KHR_portability_enumeration"};
    vk::InstanceCreateFlagBits flags =
      vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;

    // layer
    std::vector<const char*> layers = {"VK_LAYER_KHRONOS_validation"};

    vk::InstanceCreateInfo createInfo;
    vk::ApplicationInfo appInfo;
    appInfo.setApiVersion(VK_API_VERSION_1_3);
    createInfo.setPApplicationInfo(&appInfo)
      .setPEnabledLayerNames(layers)
      .setPEnabledExtensionNames(extensions)
      .setEnabledExtensionCount(extensions.size())
      .setFlags(flags);

    Instance = vk::createInstance(createInfo);
  }
  Context::~Context() { Instance.destroy(); }

}  // namespace toy2d
