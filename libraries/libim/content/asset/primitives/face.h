#ifndef LIBIM_FACE_H
#define LIBIM_FACE_H

#include <cstdint>
#include <optional>
#include <vector>
#include <tuple>

#include "geomode.h"
#include "light_mode.h"

#include <libim/math/color.h>
#include <libim/math/vector3.h>
#include <libim/types/flags.h>

namespace libim::content::asset {

    struct Face
    {
        enum Flag : uint32_t
        {
            Normal            = 0x00,
            DoubleSided       = 0x01, // Disables face backface culling.
            TexTransparent    = 0x02,  // Face has texture with alpha channel and is put in alpha render queue.
                                      // This flag applies to adjoin surfaces and Thing model surfaces.

            TexClamp_x        = 0x04, // Mapped texture is clamped in x instead of being repeated.
            TexClamp_y        = 0x08, // Mapped texture is clamped in y instead of being repeated.
            TexFilterNone     = 0x10, // Disables bilinear texture filtering for the polygon texture. (Sets to point filter aka nearest)
            ZWriteDisabled    = 0x20, // Disables ZWrite for the polygon face.
            FogdEnabled       = 0x100 // Enable fog blending for the face polygon. Note: This flag is set by default for all surfaces but sky surfaces
        };

        struct VertexIdx
        {
            std::size_t vertIdx;
            std::optional<std::size_t> uvIdx;  // index in UV list
        };

        Flags<Flag> flags;
        GeoMode geoMode;
        LightMode lightMode;
        std::optional<std::size_t> matIdx;
        std::size_t matCelIdx = 0; // material texture to use (material mipmap idx)
        LinearColor extraLight;    // face additional light color
        Vector3f normal;
        std::vector<VertexIdx> verts;
    };


    inline bool operator == (const Face::VertexIdx& lhs, const Face::VertexIdx& rhs) {
        return lhs.vertIdx == rhs.vertIdx && lhs.uvIdx == rhs.uvIdx;
    }

    inline bool operator != (const Face::VertexIdx& lhs, const Face::VertexIdx& rhs) {
        return !(lhs == rhs);
    }

    inline bool operator == (const Face& lhs, const Face& rhs)
    {
        return lhs.flags      == rhs.flags      &&
               lhs.geoMode    == rhs.geoMode    &&
               lhs.lightMode  == rhs.lightMode  &&
               lhs.matIdx     == rhs.matIdx     &&
               lhs.matCelIdx  == rhs.matCelIdx  &&
               lhs.extraLight == rhs.extraLight &&
               lhs.normal     == rhs.normal     &&
               lhs.verts      == rhs.verts;
    }

    inline bool operator != (const Face& lhs, const Face& rhs) {
        return !(lhs == rhs);
    }
}
#endif // LIBIM_FACE_H
