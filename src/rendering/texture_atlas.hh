#ifndef TEXTURE_ATLAS_HH
#define TEXTURE_ATLAS_HH

#include <SDL3_image/SDL_image.h>
#include <string>
#include "backend/util.hh"

namespace Sweeppp {
    enum class TextureType;

    class TextureAtlas {
        public:
            /// Holds the texture atlas.
            ///
            /// `size` corresponds to the dimensions of each texture within
            /// the atlas (size = 16 -> a texture in the atlas is 16x16 pixels).
            ///
            /// `renderer` is a reference to the renderer that loads the atlas
            /// texture.
            ///
            /// `atlas_path` is the path to the texture atlas image file.
            TextureAtlas(int size, SDL_Renderer* r, std::string atlas_path);

            int get_texture_size();

            /// Renders the texture at `source_coords` in the atlas at the
            /// `destination_rect` rect.
            void render_texture(Vector2 source_coords, SDL_FRect destination_rect);

            /// Destoys the atlas texture.
            void destroy_atlas_texture();

        private:
            SDL_Renderer* renderer;

            int texture_size;
            SDL_Texture* atlas_tex;

            SDL_FRect* get_texture_source(Vector2 coords);
    };
}

#endif // TEXTURE_ATLAS_HH