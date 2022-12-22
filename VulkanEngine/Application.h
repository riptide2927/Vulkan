#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <optional>
#include <limits>
#include <algorithm>

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() 
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}

};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capablities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentMode;
};

class Application
{
public:
	Application();
	void run();
private:
	void initVulkan();
	void initWindow();
	void mainLoop();
	void cleanup();
	void createInstance();
	bool checkValidationLayerSupport();
	void pickPhysicalDevice();
	bool isDeviceSutable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice& device);
	void createLogicalDevice();
	void createSurface();
	bool checkDeviceExtensionSupport(VkPhysicalDevice& device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice& device);
	VkSurfaceFormatKHR chooseSwapChainFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapChainPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();
	void createImageViews();
	void createGraphicsPipeline();
	void createRenderPass();
	static std::vector<char> readFile(const std::string& filename);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createFrameBuffers();
	void createCommandPool();
	void createCommandBuffer();
	void recordCommnadBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	void createSyncObjects();
	void drawFrame();
	void recreateSwapChain();
	void cleanupSwapChain();
private:
#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
	const std::vector<const char*> deviceExtension = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFrameBuffers;
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	QueueFamilyIndices indices;
	GLFWwindow* window;
	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;
	const int MAX_FRAMES_IN_FLIGHT = 2;
	uint32_t currentFrame = 0;
private:
	VkPhysicalDevice physicalDevice;
	VkInstance instance;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkSurfaceKHR surface;
	VkSwapchainKHR swapChain;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	VkPipelineLayout pipelineLayout;
	VkRenderPass renderPass;
	VkPipeline graphicsPipeline;
	VkCommandPool commandPool;
};