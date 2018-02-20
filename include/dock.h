/*
 * vim:ts=4:sw=4:expandtab
 *
 * i3 - an improved dynamic tiling window manager
 * © 2009 Michael Stapelberg and contributors (see also: LICENSE)
 *
 * dock.h: Functions for dock clients.
 *
 */

#include <data.h>

void update_dock_type(struct Window *dock_win, struct Rect dock_geom, struct Rect output_geom);
