#include "texture_atlas.hh"

namespace Sweeppp {
    TextureAtlas::TextureAtlas(int size, SDL_Renderer* r, std::string atlas_path) {
        texture_size = size;
        renderer = r;
        atlas_tex = IMG_LoadTexture(renderer, atlas_path.c_str());
    }

    int TextureAtlas::get_texture_size() {
        return texture_size;
    }

    void TextureAtlas::destroy_atlas_texture() {
        SDL_DestroyTexture(atlas_tex);
    }

    SDL_FRect TextureAtlas::get_texture_source(Vector2 coords) {
        return SDL_FRect {
            .x = coords.x * texture_size,
            .y = coords.y * texture_size,
            .w = (float)texture_size,
            .h = (float)texture_size
        };
    }

    void TextureAtlas::render_texture(Vector2 source_coords, SDL_FRect destination_rect) {
        SDL_FRect source_rect = get_texture_source(source_coords);
        SDL_RenderTexture(renderer, atlas_tex, &source_rect, &destination_rect);
    }
}