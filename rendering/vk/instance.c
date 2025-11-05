/* SPDX-License-Identifier:BSD-3-Clause */
#include "instance.h"
#include "../../core/log.h"
#include "vk.h"

const char *extensions[] = {
#ifdef PLATFORM_MACOS
	VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
	VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
#endif
	NULL
};

#ifdef DEBUG
const char *layers[] = {
	"VK_LAYER_KHRONOS_validation"
};
#define LAYER_COUNT (sizeof(layers)/sizeof(layers[0]))
#else
#define LAYER_COUNT 0
const char *layers[] = {NULL};
#endif

/*
 * Vulkan is modular by design. This means that some features that might not be
 * always needed are not enabled by default. To enable those features (like
 * macOS platform compatibility or windowing) extensions are needed. This
 * function checks which extensions are required by RGFW and adds extensions
 * required by the game itself.
 */
const char **vk_instance_extensions(usize * count)
{
	usize rgfw_extension_count = 0;
	const char **rgfw_extensions = RGFW_getRequiredInstanceExtensions_Vulkan(&rgfw_extension_count);

	usize extension_count = sizeof(extensions) / sizeof(extensions[0]) - 1;
	*count = rgfw_extension_count + extension_count;
	const char **instance_extensions = malloc(*count * sizeof(char *));

	log_info("Required Vulkan extensions: ");

	for (usize i = 0; i < rgfw_extension_count; i++) {
		printf("%s ", rgfw_extensions[i]);
		instance_extensions[i] = rgfw_extensions[i];
	}

	for (usize i = 0; i < extension_count; i++) {
		printf("%s ", extensions[i]);
		instance_extensions[rgfw_extension_count + i] = extensions[i];
	}

	printf("\n");

	return instance_extensions;
}

void vk_instance_init(struct renderer_context *context)
{
	VkApplicationInfo application_info = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "topaz",
		.applicationVersion = 0,
		.pEngineName = "topaz",
		.engineVersion = 0,
		.apiVersion = VK_API_VERSION_1_4
	};

	usize extension_count = 0;
	const char **extension_names = vk_instance_extensions(&extension_count);

	VkInstanceCreateInfo instance_info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &application_info,
		.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
		.enabledLayerCount = LAYER_COUNT,
		.ppEnabledLayerNames = layers,
		.enabledExtensionCount = extension_count,
		.ppEnabledExtensionNames = extension_names,
	};

	VkResult result = vkCreateInstance(&instance_info, NULL, &context->instance);
	switch (result) {
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		free(extension_names);
		fatal("Incompatible driver.\n");
	case VK_ERROR_LAYER_NOT_PRESENT:
		free(extension_names);
		fatal("Requested vulkan layers are not present.\n");
	case VK_SUCCESS:
		log_info("Vulkan instance created.\n");
		break;
	default:
		fatal("Can't create Vulkan instance.\n");
	}

	free(extension_names);
}

void vk_instance_deinit(struct renderer_context *context)
{
	vkDestroyInstance(context->instance, NULL);
}
