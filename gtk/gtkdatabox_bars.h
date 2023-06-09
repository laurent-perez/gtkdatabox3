/* $Id: gtkdatabox_bars.h 4 2008-06-22 09:19:11Z rbock $ */
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

/**
 * SECTION:gtkdatabox_bars
 * @short_description: A #GtkDataboxGraph used for displaying xy-values as vertical bars.
 * @include: gtkdatabox_bars.h
 * @see_also: #GtkDatabox, #GtkDataboxGraph, #GtkDataboxPoints, #GtkDataboxLines, #GtkDataboxMarkers
 *
 * #GtkDataboxBars is a #GtkDataboxGraph class for displaying xy-values as vertical bars which rise/drop from y=0.
 *
 */

#ifndef __GTK_DATABOX_BARS_H__
#define __GTK_DATABOX_BARS_H__

#include <gtkdatabox_xyc_graph.h>

G_BEGIN_DECLS
#define GTK_DATABOX_TYPE_BARS		  (gtk_databox_bars_get_type ())
#define GTK_DATABOX_BARS(obj)		  (G_TYPE_CHECK_INSTANCE_CAST ((obj), \
                                           GTK_DATABOX_TYPE_BARS, \
                                           GtkDataboxBars))
#define GTK_DATABOX_BARS_CLASS(klass)	  (G_TYPE_CHECK_CLASS_CAST ((klass), \
                                           GTK_DATABOX_TYPE_BARS, \
                                           GtkDataboxBarsClass))
#define GTK_DATABOX_IS_BARS(obj)	  (G_TYPE_CHECK_INSTANCE_TYPE ((obj), \
                                           GTK_DATABOX_TYPE_BARS))
#define GTK_DATABOX_IS_BARS_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), \
                                           GTK_DATABOX_TYPE_BARS))
#define GTK_DATABOX_BARS_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
                                           GTK_DATABOX_TYPE_BARS, \
                                           GtkDataboxBarsClass))
/**
 * GtkDataboxBars
 * #GtkDataboxBars is a #GtkDataboxGraph class for displaying xy-values as vertical bars which rise/drop from y=0.
 *
 * @see_also: #GtkDatabox, #GtkDataboxGraph, #GtkDataboxPoints, #GtkDataboxLines, #GtkDataboxMarkers
 *
 */
typedef struct _GtkDataboxBars GtkDataboxBars;

/**
 * GtkDataboxBarsClass
 *
 * The object class of #GtkDataboxBars.
 *
 **/
typedef struct _GtkDataboxBarsClass GtkDataboxBarsClass;

struct _GtkDataboxBars
{
   /*< private > */
   GtkDataboxXYCGraph parent;
};

struct _GtkDataboxBarsClass
{
   GtkDataboxXYCGraphClass parent_class;
};

GType gtk_databox_bars_get_type (void);

GtkDataboxGraph *gtk_databox_bars_new (guint len, gfloat * X, gfloat * Y,
				       GdkRGBA * color, guint size);

GtkDataboxGraph *gtk_databox_bars_new_full (guint maxlen, guint len,
					    void *X, guint xstart,
					    guint xstride, GType xtype,
					    void *Y, guint ystart,
					    guint ystride, GType ytype,
					    GdkRGBA * color, guint size);

G_END_DECLS
#endif /* __GTK_DATABOX_BARS_H__ */
