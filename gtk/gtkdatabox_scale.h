/* $Id: gtkdatabox_scale.h 4 2008-06-22 09:19:11Z rbock $ */
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

#ifndef __GTK_DATABOX_SCALE_H__
#define __GTK_DATABOX_SCALE_H__

#include <glib-object.h>

/**
 * SECTION:gtkdatabox_scale
 * @short_description: scale type enumeration
 * @include: gtkdatabox_scale.h
 * @see_also: #GtkDatabox, #GtkDataboxRuler
 *
 * This file adds the #GtkDataboxScaleType enumeration used in several places.
 */

G_BEGIN_DECLS
/**
 * GtkDataboxScaleType
 * @GTK_DATABOX_SCALE_LINEAR:           Linear scale
 * @GTK_DATABOX_SCALE_LOG2:             Logarithmic scale (base 2)
 * @GTK_DATABOX_SCALE_LOG:              Logarithmic scale (base 10)
 *
 * Scale type for #GtkDatabox and #GtkDataboxRuler objects.
 *
 * See also: #GtkDatabox:scale_type_x, #GtkDatabox:scale_type_y
 */
   typedef enum
{
   GTK_DATABOX_SCALE_LINEAR = 0,
   GTK_DATABOX_SCALE_LOG2,
   GTK_DATABOX_SCALE_LOG
}
GtkDataboxScaleType;

GType gtk_databox_scale_type_get_type (void);

G_END_DECLS
#endif /* __GTK_DATABOX_SCALE_H__ */
