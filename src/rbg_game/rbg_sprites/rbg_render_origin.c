#include "rbg_render_origin.h"

Vector2 rbg_get_render_origin(rbg_render_pivot pivot, float width, float height)
{
	Vector2 origin = { 0.0f, 0.0f };

	switch (pivot)
	{
		case RENDER_PIVOT_CENTER:
			origin = (Vector2){ width * 0.5f, height * 0.5f };
			break;

		case RENDER_PIVOT_BOTTOM_CENTER:
			origin = (Vector2){ width * 0.5f, height };          // bottom edge
			break;

		default:
			origin = (Vector2){ width * 0.5f, height * 0.5f };
			break;
	}

	return origin;
}
