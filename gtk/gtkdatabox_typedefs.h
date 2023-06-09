/* $Id: gtkdatabox_typedefs.h 4 2008-06-22 09:19:11Z rbock $ */
/* GtkDatabox - An extension to the gtk+ library
 * Copyright (C) 1998 - 2008  Dr. Roland Bock
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __GTK_DATABOX_TYPEDEFS_H__
#define __GTK_DATABOX_TYPEDEFS_H__

#include <gdk/gdk.h>

/**
 * SECTION:gtkdatabox_typedefs
 * @short_description: GtkDatabox type definitions for cross reference.
 * @include: gtkdatabox_typedefs.h
 * @see_also: #GtkDatabox, #GtkDataboxGraph
 *
 * This file is just used to resolve cross reference in the implementation
 * of the objects GtkDatabox and GtkDataboxGraph.
 */

G_BEGIN_DECLS
/**
* GtkDatabox
*
* A GTK+ widget to display large amounts of numerical data quickly and easily. 
* The numerical data is represented/displayed by #GtkDataboxGraph objects, e.g.
* #GtkDataboxPoints.
*
* Implemented by #_GtkDatabox;
*
* @box: the parent object
**/
typedef struct _GtkDatabox GtkDatabox;

   /**
    * GtkDataboxGraph
    * The GtkDataboxGraph is the base class for all kinds of graphs 
    * (e.g. lines, points, decorations like coordinate crosses) 
    * to be shown in a #GtkDatabox wiget.
    *
    * Implemented by #_GtkDataboxGraph
    *
    * @parent: the parent object 
    **/
typedef struct _GtkDataboxGraph GtkDataboxGraph;

G_END_DECLS
#endif /* __GTK_DATABOX_TYPEDEFS_H__ */
