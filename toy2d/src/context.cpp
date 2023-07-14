#include "toy2d/context.hpp"

#include <iostream>
#include <vector>
#include <vulkan/vulkan_enums.hpp>

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
  void Context::showPhysicalDevices(vk::Instance instance) {
    std::cout << "DEVICES:" << std::endl;
    auto devices = instance.enumeratePhysicalDevices();
    for (auto& device : devices) {
      auto properties = device.getProperties();
      std::cout << properties.deviceName << std::endl;
    }
  }

  void Context::createInstance() {
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

  void Context::pickupPhysicalDevice() {
    PhysicalDevice = Instance.enumeratePhysicalDevices()[0];
    auto properties = PhysicalDevice.getProperties();
    std::cout << "pickup physical device is " << properties.deviceName
              << std::endl;
  }

  void Context::queryQueueFamliyIndices() {
    auto properties = PhysicalDevice.getQueueFamilyProperties();
    for (int i; i < properties.size(); i++) {
      if (properties[i].queueFlags | vk::QueueFlagBits::eGraphics) {
        QueueFamliyIndices.GraphicsQueue = i;
        break;
      }
    }
  }

  void Context::createDevice() {
    // 1.3.216 必需开启 VK_KHR_portability_subset
    std::vector<const char*> extensions = {"VK_KHR_portability_subset"};

    vk::DeviceCreateInfo deviceCreateInfo;
    vk::DeviceQueueCreateInfo queueCreateInfo;

    float priorities = 1.0;
    queueCreateInfo.setPQueuePriorities(&priorities)
      .setQueueCount(1)
      .setQueueFamilyIndex(QueueFamliyIndices.GraphicsQueue.value());

    deviceCreateInfo.setQueueCreateInfos(queueCreateInfo)
      .setPEnabledExtensionNames(extensions)
      .setEnabledExtensionCount(extensions.size());

    Device = PhysicalDevice.createDevice(deviceCreateInfo);
  }

  void Context::getGraphicsQueue() {
    GraphicsQueue =
      Device.getQueue(QueueFamliyIndices.GraphicsQueue.value(), 0);
  }
  Context::Context() {
    createInstance();
    pickupPhysicalDevice();
    queryQueueFamliyIndices();
    createDevice();
    getGraphicsQueue();
  }
  Context::~Context() {
    Device.destroy();
    Instance.destroy();
  }

}  // namespace toy2d
