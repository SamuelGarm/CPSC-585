#include "engine/ecs.hpp"
#include "engine/int_types.hpp"

namespace ecs {
    ComponentFlags componentMaskFromGuid(Guid componentGuid)
    {
        return (static_cast<u64>(1) << componentGuid);
    }
}
