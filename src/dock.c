/*
 * vim:ts=4:sw=4:expandtab
 *
 * i3 - an improved dynamic tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * dock.c: Functions for dock clients.
 *
 */
#include "all.h"

/* Find out the desired position of dock window and updates window->dock */
void update_dock_type(struct Window *dock_win, struct Rect dock_geom, struct Rect output_geom) {
    int16_t top = dock_win->reserved.top;
    int16_t bottom = dock_win->reserved.bottom;
    int16_t left = dock_win->reserved.left;
    int16_t right = dock_win->reserved.right;

    if (top > 0 && bottom == 0 && left == 0 && right == 0) {
        DLOG("Top dock client\n");
        dock_win->dock = W_DOCK_TOP;
    } else if (top == 0 && bottom > 0 && left == 0 && right == 0) {
        DLOG("Bottom dock client\n");
        dock_win->dock = W_DOCK_BOTTOM;
    } else if (top == 0 && bottom == 0 && left > 0 && right == 0) {
        DLOG("Left dock client\n");
        dock_win->dock = W_DOCK_LEFT;
    } else if (top == 0 && bottom == 0 && left == 0 && right > 0) {
        DLOG("Right dock client\n");
        dock_win->dock = W_DOCK_RIGHT;
    } else {
        DLOG("Ignoring invalid reserved edges (_NET_WM_STRUT_PARTIAL), "
                "using width/height ratio and position as fallback:\n");
        bool likey_horizontal = dock_geom.height <= dock_geom.width;
        int16_t vertical_center = output_geom.y + output_geom.height / 2;
        int16_t horizontal_center = output_geom.x + output_geom.width / 2;
        if (likey_horizontal && dock_geom.y < vertical_center) {
                DLOG("dock_geom.y = %d < %d, it is a top dock client\n",
                     dock_geom.y, vertical_center);
                dock_win->dock = W_DOCK_TOP;
        } else if (likey_horizontal && dock_geom.y >= vertical_center) {
                DLOG("dock_geom.y = %d >= %d, it is a bottom dock client\n",
                     dock_geom.y, vertical_center);
                dock_win->dock = W_DOCK_BOTTOM;
        } else if (!likey_horizontal && dock_geom.x < horizontal_center) {
                DLOG("dock_geom.y = %d < %d, it is a left dock client\n",
                     dock_geom.x, horizontal_center);
                dock_win->dock = W_DOCK_LEFT;
        } else if (!likey_horizontal && dock_geom.x >= horizontal_center) {
                DLOG("dock_geom.y = %d >= %d, it is a right dock client\n",
                     dock_geom.x, horizontal_center);
                dock_win->dock = W_DOCK_RIGHT;
        }
    }
}
