#include "board_renderer.hh"
#include "SDL3/SDL_render.h"
#include "rendering/texture_atlas.hh"
#include "rendering/texture_shorthands.hh"
#include <cmath>
#include <iostream>

namespace Sweeppp {
    BoardRenderer::BoardRenderer() {}

    Vector2 BoardRenderer::adjacent_mine_count_to_number_texture_coords(int adjacent_mine_count) {
        return Vector2(adjacent_mine_count - 1, 1);
    }

    void BoardRenderer::initialize_cell_buttons() {
        for (size_t i = 0; i < board->board_config.size_x * board->board_config.size_y; i++) {
            CellButton cell_button = CellButton();
            cell_button.cell = &(board->cells[i]);

            cell_buttons.push_back(cell_button);
        }
    }

    void BoardRenderer::render_border(SDL_Renderer* renderer, TextureAtlas* atlas) {
        SDL_FRect border_bottom_src {
            .x = (float)atlas->get_texture_size() * 4,
            .y = (float)atlas->get_texture_size() * 2,
            .w = (float)atlas->get_texture_size() * 2,
            .h = (float)atlas->get_texture_size() * 2
        };

        SDL_FRect border_bottom_dst {
            .x = 0,
            .y = 0,
            .w = (float)(board->board_config.size_x * cell_size + border_thickness * 2),
            .h = (float)(board->board_config.size_y * cell_size + border_thickness * 2)
        };

        SDL_FRect full_atlas_src {
            0, 0, 256, 256
        };

        SDL_RenderTexture9Grid(
            renderer,
            atlas->get_atlas_texture(),
            &border_bottom_src,
            8, 8, 8, 8,
            2,
            &border_bottom_dst
        );
    }

    void BoardRenderer::render_board(SDL_Renderer* renderer, TextureAtlas* atlas, bool is_game_over) {
        // Render cell buttons
        for (size_t i = 0; i < cell_buttons.size(); i++) {
            SDL_FRect destination = {
                .x = (float)cell_size * (i % board->board_config.size_x) + border_thickness,
                .y = (float)cell_size * std::floor((float)i / board->board_config.size_x) + border_thickness,
                .w = (float)cell_size,
                .h = (float)cell_size,
            };

            cell_buttons[i].screen_rect = destination;

            if (cell_buttons[i].cell->is_revealed) {
                atlas->render_texture(CELL_EMPTY, destination);

                // Number
                if (cell_buttons[i].cell->adjacent_mine_count > 0) {
                    atlas->render_texture(adjacent_mine_count_to_number_texture_coords(cell_buttons[i].cell->adjacent_mine_count), destination);
                    continue;
                }

                // Mine (incl. trigger mine BG)
                if (cell_buttons[i].cell->is_mine) {
                    if (cell_buttons[i].cell->is_trigger_mine) atlas->render_texture(MINE_TRGGER_BG, destination);
                    if (!cell_buttons[i].cell->is_flagged) {
                        atlas->render_texture(MINE, destination);
                        continue;
                    }

                    // Game over flag (correct)
                    if (is_game_over && cell_buttons[i].cell->is_flagged && cell_buttons[i].cell->is_mine) {
                        atlas->render_texture(CELL_COVER, destination);
                        atlas->render_texture(FLAG, destination);
                        continue;
                    }
                }

                continue; // DO NOT REMOVE THIS UNDER ANY CIRCUMSTANCE
            }

            // Cell button held
            if (cell_buttons[i].is_held) {
                atlas->render_texture(CELL_EMPTY, destination);
                continue;
            } else {
                atlas->render_texture(CELL_COVER, destination);
            }

            // Flag
            if (cell_buttons[i].cell->is_flagged) {
                atlas->render_texture(FLAG, destination);
                if (!cell_buttons[i].cell->is_mine && is_game_over) atlas->render_texture(FLAG_WRONG, destination); // Wrong flag
            }


        }
    }
}