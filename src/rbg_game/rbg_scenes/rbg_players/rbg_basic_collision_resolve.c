#include "rbg_basic_collision_resolve.h"
#include "rbg_player_boxes.h"
#include "rbg_players.h"
#include <raylib.h>
#include <math.h>

void rbg_update_basic_collision_resolve(void)
{
    rbg_player* p1 = rbg_get_player(1);
    rbg_player* p2 = rbg_get_player(2);
    rbg_player_col_box* b1 = rbg_get_player_box(1);
    rbg_player_col_box* b2 = rbg_get_player_box(2);

    if (p1 == NULL || p2 == NULL || b1 == NULL || b2 == NULL)
    {
        return;
    }

    if (!b1->is_colliding_with_other_player)
    {
        return;
    }

    // Recompute effective rectangles (mirroring offset_x based on facing, bottom-center origin)
    float effective_offset_x1 = b1->offset_x;
    if (!p1->is_facing_right_side)
    {
        effective_offset_x1 = -b1->offset_x;
    }
    float box1_cx = p1->position.x + effective_offset_x1;
    float box1_by = p1->position.y + b1->offset_y;

    Rectangle rect1 =
    {
        .x = box1_cx - (b1->width * 0.5f),
        .y = box1_by - b1->height,
        .width = b1->width,
        .height = b1->height
    };

    float effective_offset_x2 = b2->offset_x;
    if (!p2->is_facing_right_side)
    {
        effective_offset_x2 = -b2->offset_x;
    }
    float box2_cx = p2->position.x + effective_offset_x2;
    float box2_by = p2->position.y + b2->offset_y;

    Rectangle rect2 =
    {
        .x = box2_cx - (b2->width * 0.5f),
        .y = box2_by - b2->height,
        .width = b2->width,
        .height = b2->height
    };

    // Calculate horizontal overlap (primary axis for 2D side-view fighters)
    float overlap_left = fmaxf(rect1.x, rect2.x);
    float overlap_right = fminf(rect1.x + rect1.width, rect2.x + rect2.width);
    float overlap_x = overlap_right - overlap_left;

    if (overlap_x <= 0.0f)
    {
        b1->is_colliding_with_other_player = false;
        b2->is_colliding_with_other_player = false;
        return;
    }

    // Determine centers for direction
    float center1_x = box1_cx;
    float center2_x = box2_cx;

    // Split the overlap equally for basic resolution (fair push)
    float push_amount = overlap_x * 0.5f;

    if (center1_x < center2_x)
    {
        // Player 1 is on the left side
        p1->position.x -= push_amount;
        p2->position.x += push_amount;
    }
    else
    {
        // Player 2 is on the left side (or centers equal)
        p1->position.x += push_amount;
        p2->position.x -= push_amount;
    }

    // Clear flags after resolution (next frame's check_collision will re-evaluate if still overlapping)
    b1->is_colliding_with_other_player = false;
    b2->is_colliding_with_other_player = false;

    // Note: For more advanced resolution, consider:
    // - Velocity-based resolution (push more the faster-moving character)
    // - State priority (attacking character may have push advantage or be unpushable)
    // - Minimum separation distance or friction-like behavior
    // - Y-axis resolution for jumping/anti-air scenarios
}