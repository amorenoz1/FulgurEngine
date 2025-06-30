#include "VulkanGraphicsPipeline.hpp"
#include "Shader.hpp"

#include "utils/FulgurUtils.hpp"
#include "utils/Logger.hpp"
#include <vulkan/vulkan_core.h>

VkShaderModule Gfx::VulkanGraphicsPipeline::CreateShaderModule(VkDevice& device,
                                                               const std::vector<char>& shaderBin) {
    VkShaderModuleCreateInfo createInfo{
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .pNext = nullptr,
        .codeSize = shaderBin.size(),
        .pCode = reinterpret_cast<const std::uint32_t*>(shaderBin.data()),
    };

    VkShaderModule shaderModule;

    VkResult shaderModuleCreationRes =
        vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);

    Utils::Assert(shaderModuleCreationRes == VK_SUCCESS, "VkShadeModule failed to be created!");

    LOG_INFO("VkShaderModule creation was successful!");

    return shaderModule;
}

void Gfx::VulkanGraphicsPipeline::CreateRenderPass(VkDevice& device, VkFormat& format) {
    VkAttachmentDescription colorAttachmentDescription{
        .flags = 0,
        .format = format,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
    };

    VkAttachmentReference colorAttachmentReference{
        .attachment = 0,
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
    };

    VkSubpassDescription subpassDescription{.flags = 0,
                                            .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
                                            .inputAttachmentCount = 0,
                                            .pInputAttachments = nullptr,
                                            .colorAttachmentCount = 1,
                                            .pColorAttachments = &colorAttachmentReference,
                                            .pDepthStencilAttachment = nullptr,
                                            .preserveAttachmentCount = 0,
                                            .pPreserveAttachments = nullptr};

    VkSubpassDependency subpassDependency{
        .srcSubpass = VK_SUBPASS_EXTERNAL,
        .dstSubpass = 0,
        .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
        .srcAccessMask = 0,
        .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
    };

    VkRenderPassCreateInfo createInfo{.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
                                      .pNext = nullptr,
                                      .flags = 0,
                                      .attachmentCount = 1,
                                      .pAttachments = &colorAttachmentDescription,
                                      .subpassCount = 1,
                                      .pSubpasses = &subpassDescription,
                                      .dependencyCount = 1,
                                      .pDependencies = &subpassDependency};

    VkResult renderPassCreationRes =
        vkCreateRenderPass(device, &createInfo, nullptr, &m_RenderPass);

    Utils::Assert(renderPassCreationRes == VK_SUCCESS, "VkRenderPass creation failed!");

    LOG_INFO("VkRenderPass creation was successful!");
}

void Gfx::VulkanGraphicsPipeline::CreateGraphicsPipeline(VkDevice& device, VkExtent2D& extent,
                                                         VkFormat& format) {
    CreateRenderPass(device, format);

    Gfx::Shader vertShader("src/shaders/triangle_vert.spv");
    Gfx::Shader fragShader("src/shaders/triangle_frag.spv");

    VkShaderModule vertShaderModule = CreateShaderModule(device, vertShader.GetShaderBinary());
    VkShaderModule fragShaderModule = CreateShaderModule(device, fragShader.GetShaderBinary());

    VkPipelineShaderStageCreateInfo vertCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .stage = VK_SHADER_STAGE_VERTEX_BIT,
        .module = vertShaderModule,
        .pName = "main",
        .pSpecializationInfo = nullptr};

    VkPipelineShaderStageCreateInfo fragCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
        .module = fragShaderModule,
        .pName = "main",
        .pSpecializationInfo = nullptr};

    VkPipelineShaderStageCreateInfo shaderStages[] = {
        vertCreateInfo,
        fragCreateInfo,
    };

    std::vector<VkDynamicState> dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT,
                                                 VK_DYNAMIC_STATE_SCISSOR};

    VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .dynamicStateCount = static_cast<std::uint32_t>(dynamicStates.size()),
        .pDynamicStates = dynamicStates.data()};

    VkPipelineVertexInputStateCreateInfo vertexInputStateCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .vertexBindingDescriptionCount = 0,
        .pVertexBindingDescriptions = nullptr,
        .vertexAttributeDescriptionCount = 0,
        .pVertexAttributeDescriptions = nullptr};

    VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE};

    VkViewport viewport{.x = 0.0f,
                        .y = 0.0f,
                        .width = static_cast<float>(extent.width),
                        .height = static_cast<float>(extent.height),
                        .minDepth = 0.0f,
                        .maxDepth = 1.0f};

    VkRect2D scissor{.offset = {0, 0}, .extent = extent};

    VkPipelineViewportStateCreateInfo viewportStateCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .viewportCount = 1,
        .pViewports = &viewport,
        .scissorCount = 1,
        .pScissors = &scissor};

    VkPipelineRasterizationStateCreateInfo rasterizationStateCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .cullMode = VK_CULL_MODE_NONE,
        .depthBiasEnable = VK_FALSE,
        .depthBiasConstantFactor = 0.0f,
        .depthBiasClamp = 0.0f,
        .depthBiasSlopeFactor = 0.0f,
        .lineWidth = 1.0f};

    VkPipelineMultisampleStateCreateInfo multisampleStateCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
        .sampleShadingEnable = VK_FALSE,
        .minSampleShading = 1.0f,
        .pSampleMask = nullptr,
        .alphaToCoverageEnable = VK_FALSE,
        .alphaToOneEnable = VK_FALSE,
    };

    VkPipelineColorBlendAttachmentState colorBlendAttachmentState{
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                          VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
        .blendEnable = VK_FALSE,
        .srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
        .colorBlendOp = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp = VK_BLEND_OP_ADD};

    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .logicOpEnable = VK_FALSE,
        .logicOp = VK_LOGIC_OP_COPY,
        .attachmentCount = 1,
        .pAttachments = &colorBlendAttachmentState,
        .blendConstants[0] = 0.0f,
        .blendConstants[1] = 0.0f,
        .blendConstants[2] = 0.0f,
        .blendConstants[3] = 0.0f};

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .setLayoutCount = 0,
        .pSetLayouts = nullptr,
        .pushConstantRangeCount = 0,
        .pPushConstantRanges = nullptr};

    VkResult pipelineLayoutCreationRes =
        vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &m_PipelineLayout);

    Utils::Assert(pipelineLayoutCreationRes == VK_SUCCESS, "VkPipelineLayout creation failed!");

    LOG_INFO("VkPipelineLayout creation was successful!");

    VkGraphicsPipelineCreateInfo createInfo{.sType =
                                                VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                                            .pNext = nullptr,
                                            .flags = 0,
                                            .stageCount = 2,
                                            .pStages = shaderStages,
                                            .pVertexInputState = &vertexInputStateCreateInfo,
                                            .pInputAssemblyState = &inputAssemblyStateCreateInfo,
                                            .pTessellationState = nullptr,
                                            .pViewportState = &viewportStateCreateInfo,
                                            .pRasterizationState = &rasterizationStateCreateInfo,
                                            .pMultisampleState = &multisampleStateCreateInfo,
                                            .pDepthStencilState = nullptr,
                                            .pColorBlendState = &colorBlendStateCreateInfo,
                                            .pDynamicState = &dynamicStateCreateInfo,
                                            .layout = m_PipelineLayout,
                                            .renderPass = m_RenderPass,
                                            .subpass = 0,
                                            .basePipelineHandle = VK_NULL_HANDLE,
                                            .basePipelineIndex = 0};

    VkResult graphicPipelineCreationRes = vkCreateGraphicsPipelines(
        device, VK_NULL_HANDLE, 1, &createInfo, nullptr, &m_GraphicsPipeline);

    Utils::Assert(graphicPipelineCreationRes == VK_SUCCESS, "VkGraphicsPipeline creation falied!");

    LOG_INFO("VkGraphicsPipeline creation was successful!");

    vkDestroyShaderModule(device, vertShaderModule, nullptr);
    vkDestroyShaderModule(device, fragShaderModule, nullptr);
}

VkPipelineLayout& Gfx::VulkanGraphicsPipeline::GetPipelineLayout() { return m_PipelineLayout; }

VkRenderPass& Gfx::VulkanGraphicsPipeline::GetRenderPass() { return m_RenderPass; }

VkPipeline& Gfx::VulkanGraphicsPipeline::GetGraphicsPipeline() { return m_GraphicsPipeline; }

void Gfx::VulkanGraphicsPipeline::CleanupGraphicsPipeline(VkDevice& device) {
    vkDestroyPipeline(device, m_GraphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device, m_PipelineLayout, nullptr);
    vkDestroyRenderPass(device, m_RenderPass, nullptr);
}
