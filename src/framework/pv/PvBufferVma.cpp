#include "pv/PvBufferVma.h"
#include "pv/PvBootstrap.h"
#include "pv/PvCommon.h"
#include <cstdint>
#include <volk.h>

namespace Pyra {

void PvBufferVmaCreateInfo::assign() {
  info = {.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
          .flags = flags,
          .size = size,
          .usage = usage,
          .sharingMode = sharingMode,
          .queueFamilyIndexCount = (uint32_t)queueFamilyIndices.size(),
          .pQueueFamilyIndices = NULLPTR_IF_EMPTY(queueFamilyIndices)};
}

bool PvBufferVma::init(PvBufferVmaCreateInfo &info) {
  table = info.table;
  handle = new VkBufferVma{};
  if (vmaCreateBuffer(info.table->allocator, &info.info, &info.allocInfo,
                      &handle->Buffer, &handle->meomry,
                      nullptr) != VK_SUCCESS) {
    ERROR("Failed to create vmaBuffer!");
    return false;
  }

  if (!setDctor)
    setDeconstructor(vmaDestroyBuffer);

  manage(handle,
         std::make_tuple(info.table->allocator, handle->Buffer, handle->meomry),
         info.operation, {info.table->device.device});
  return true;
}

} // namespace Pyra