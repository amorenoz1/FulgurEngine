#pragma once
#include "core/FulgurCore.hpp"
#include "utils/Math.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace Fulgur
{
    enum class FGAPI VertexType : std::uint8_t
    {
        FLOAT,
        INT,
        UINT,
        BOOL,
        VEC2,
        VEC3,
        VEC4,
        IVEC2,
        IVEC3,
        IVEC4,
        UVEC2,
        UVEC3,
        UVEC4,
        BVEC2,
        BVEC3,
        BVEC4
    };

    struct FGAPI VertexAttribute
    {
        VertexType  type;
        std::size_t offset;

        VertexAttribute(const VertexAttribute &)                     = default;
        VertexAttribute(VertexAttribute &&)                          = default;
        auto operator=(const VertexAttribute &) -> VertexAttribute & = default;
        auto operator=(VertexAttribute &&) -> VertexAttribute &      = default;
    };

    class FGAPI IVertex
    {
      public:
        virtual auto GetVertexAttributes() -> std::vector<VertexAttribute> & = 0;
    };

    class FGAPI Vertex : public IVertex
    {
      private:
        Vector2 position;
        Vector3 color;

      public:
        auto GetVertexAttributes() -> std::vector<VertexAttribute> & override;
    };
}; // namespace Fulgur
