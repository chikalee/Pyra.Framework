#include "pv/PvRenderPass.h"
#include "pv/PvBootstrap.h"
#include "pv/PvCommon.h"
#include <cstdint>
#include <vector>

namespace Pyra {

void PvRenderPassCreateInfo::assign() {
  spInfos.resize(subpasses.size());
  for (uint32_t i = 0; i < subpasses.size(); i++) {
    spInfos[i] = {
        .flags = subpasses[i].flags,
        .pipelineBindPoint = subpasses[i].pipelineBindPoint,
        .inputAttachmentCount = (uint32_t)subpasses[i].inputAttachments.size(),
        .pInputAttachments = NULLPTR_IF_EMPTY(subpasses[i].inputAttachments),
        .colorAttachmentCount = (uint32_t)subpasses[i].ColorAttachments.size(),
        .pColorAttachments = NULLPTR_IF_EMPTY(subpasses[i].ColorAttachments),
        .pResolveAttachments =
            NULLPTR_IF_EMPTY(subpasses[i].resolveAttachments),
        .pDepthStencilAttachment =
            NULLPTR_IF_EMPTY(subpasses[i].depthStencilAttachment),
        .preserveAttachmentCount =
            (uint32_t)subpasses[i].preserveAttachments.size(),
        .pPreserveAttachments =
            NULLPTR_IF_EMPTY(subpasses[i].preserveAttachments),
    };
  }

  info = {.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
          .flags = flags,
          .attachmentCount = (uint32_t)attachments.size(),
          .pAttachments = NULLPTR_IF_EMPTY(attachments),
          .subpassCount = (uint32_t)spInfos.size(),
          .pSubpasses = NULLPTR_IF_EMPTY(spInfos),
          .dependencyCount = (uint32_t)dependencies.size(),
          .pDependencies = NULLPTR_IF_EMPTY(dependencies)};
}

bool PvRenderPass::init(PvRenderPassCreateInfo &info) {
  if (info.table->disp.createRenderPass(&info.info, info.callback, &handle) !=
      VK_SUCCESS) {
    ERROR("Failed to create vkrenderpass!");
    return false;
  }
  if (deconstuctor == nullptr)
    deconstuctor = info.table->disp.fp_vkDestroyRenderPass;
  manage(handle,
         std::make_tuple(info.table->device.device, handle, info.callback),
         info.operation);
  return true;
}

} // namespace Pyra