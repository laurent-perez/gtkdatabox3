/* $Id: markers.c 4 2008-06-22 09:19:11Z rbock $ */
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
#include <stdio.h>

#include <gtk/gtk.h>
#include <gtkdatabox.h>
#include <gtkdatabox_points.h>
#include <gtkdatabox_markers.h>
#include <math.h>

#define POINTS 24

/*----------------------------------------------------------------
 *  databox markerss
 *----------------------------------------------------------------*/

void
setM (GtkDataboxGraph * graph,
      guint index,
      GtkDataboxMarkersPosition position,
      GtkDataboxMarkersTextPosition label_position, gchar * label,
      gboolean boxed)
{
   GtkDataboxMarkers *markers = GTK_DATABOX_MARKERS (graph);

   g_return_if_fail (GTK_DATABOX_IS_MARKERS (markers));

   gtk_databox_markers_set_position (markers, index, position);
   gtk_databox_markers_set_label (markers, index, label_position, label,
				  boxed);
}

void
setL (GtkDataboxGraph * graph,
      guint index,
      GtkDataboxMarkersPosition position,
      GtkDataboxMarkersTextPosition label_position, gchar * label,
      gboolean boxed)
{
   GtkDataboxMarkers *markers = GTK_DATABOX_MARKERS (graph);

   g_return_if_fail (GTK_DATABOX_IS_MARKERS (markers));

   gtk_databox_markers_set_position (markers, index, position);
   gtk_databox_markers_set_label (markers, index, label_position, label,
				  boxed);
}

void
setT (GtkDataboxGraph * graph,
      guint index,
      GtkDataboxMarkersTextPosition label_position, gchar * label,
      gboolean boxed)
{
   GtkDataboxMarkers *markers = GTK_DATABOX_MARKERS (graph);

   g_return_if_fail (GTK_DATABOX_IS_MARKERS (markers));

   gtk_databox_markers_set_label (markers, index, label_position, label,
				  boxed);
}

static void
create_markerss (void)
{
   GtkWidget *window = NULL;
   GtkWidget *box1;
   GtkWidget *box2;
   GtkWidget *close_button;
   GtkWidget *box;
   GtkWidget *table;
   GtkWidget *label;
   GtkWidget *separator;
   gfloat *X;
   gfloat *Y;
   gint i;
   GtkDataboxGraph *graph;
   GdkRGBA color;

   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_widget_set_size_request (window, 600, 600);

   g_signal_connect (G_OBJECT (window), "destroy",
		     G_CALLBACK (gtk_main_quit), NULL);

   gtk_window_set_title (GTK_WINDOW (window), "GtkDatabox: Markers");
   gtk_container_set_border_width (GTK_CONTAINER (window), 0);

   box1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
   gtk_container_add (GTK_CONTAINER (window), box1);

   label =
      gtk_label_new
      ("Some markers (green) are shown below.\nThe text corresponds to the position of the text, relative to the markers.\n\nThere are also some texts (yellow).\n\nData points are red\n");
   gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
   separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
   gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, FALSE, 0);

   gtk_databox_create_box_with_scrollbars_and_rulers (&box, &table,
						      TRUE, TRUE, TRUE, TRUE);
   gtk_box_pack_start (GTK_BOX (box1), table, TRUE, TRUE, 0);

   gtk_databox_set_bg_color (GTK_DATABOX (box), "#545454");

   X = g_new0 (gfloat, 20 + 4 + 5);
   Y = g_new0 (gfloat, 20 + 4 + 5);

   for (i = 0; i < 20 + 4 + 5; ++i)
   {
      X[i] = i % 4;
      Y[i] = i / 4;
   }
   X[20] = -0.5;
   Y[20] = -0.5;
   X[21] = -0.5;
   Y[21] = 4.5;
   X[22] = 3.5;
   Y[22] = -0.5;
   X[23] = 3.5;
   Y[23] = 4.5;

   X[24] = -1.;
   Y[24] = -1.;
   X[25] = -1.;
   Y[25] = +5.;
   X[26] = +4.;
   Y[26] = -1.;
   X[27] = +4.;
   Y[27] = +5.;
   X[28] = +1.5;
   Y[28] = +2.;

   color.red = 1;
   color.green = 0;
   color.blue = 0;
   color.alpha = 1;

   graph = gtk_databox_points_new (20 + 4 + 5, X, Y, &color, 3);
   gtk_databox_graph_add (GTK_DATABOX (box), graph);

   color.red = 0;
   color.green = 1;
   color.blue = 0;
   color.alpha = 1;

   graph = gtk_databox_markers_new (20, X, Y, &color, 15,
				    GTK_DATABOX_MARKERS_TRIANGLE);

   gtk_databox_graph_add (GTK_DATABOX (box), graph);
   setM (graph, 0, GTK_DATABOX_MARKERS_W, GTK_DATABOX_MARKERS_TEXT_W, "West",
	 FALSE);
   setM (graph, 1, GTK_DATABOX_MARKERS_N, GTK_DATABOX_MARKERS_TEXT_N, "North",
	 FALSE);
   setM (graph, 2, GTK_DATABOX_MARKERS_S, GTK_DATABOX_MARKERS_TEXT_S, "South",
	 FALSE);
   setM (graph, 3, GTK_DATABOX_MARKERS_E, GTK_DATABOX_MARKERS_TEXT_E, "East",
	 FALSE);

   setM (graph, 4, GTK_DATABOX_MARKERS_W, GTK_DATABOX_MARKERS_TEXT_W, "West",
	 TRUE);
   setM (graph, 5, GTK_DATABOX_MARKERS_N, GTK_DATABOX_MARKERS_TEXT_N, "North",
	 TRUE);
   setM (graph, 6, GTK_DATABOX_MARKERS_S, GTK_DATABOX_MARKERS_TEXT_S, "South",
	 TRUE);
   setM (graph, 7, GTK_DATABOX_MARKERS_E, GTK_DATABOX_MARKERS_TEXT_E, "East",
	 TRUE);

   setM (graph, 8, GTK_DATABOX_MARKERS_E, GTK_DATABOX_MARKERS_TEXT_W, "West",
	 TRUE);
   setM (graph, 9, GTK_DATABOX_MARKERS_S, GTK_DATABOX_MARKERS_TEXT_N, "North",
	 TRUE);
   setM (graph, 10, GTK_DATABOX_MARKERS_N, GTK_DATABOX_MARKERS_TEXT_S,
	 "South", TRUE);
   setM (graph, 11, GTK_DATABOX_MARKERS_W, GTK_DATABOX_MARKERS_TEXT_E, "East",
	 TRUE);

   setM (graph, 12, GTK_DATABOX_MARKERS_W, GTK_DATABOX_MARKERS_TEXT_S,
	 "South", TRUE);
   setM (graph, 13, GTK_DATABOX_MARKERS_N, GTK_DATABOX_MARKERS_TEXT_W, "West",
	 TRUE);
   setM (graph, 14, GTK_DATABOX_MARKERS_S, GTK_DATABOX_MARKERS_TEXT_E, "East",
	 TRUE);
   setM (graph, 15, GTK_DATABOX_MARKERS_E, GTK_DATABOX_MARKERS_TEXT_N,
	 "North", TRUE);

   setM (graph, 16, GTK_DATABOX_MARKERS_W, GTK_DATABOX_MARKERS_TEXT_SW, "SW",
	 TRUE);
   setM (graph, 17, GTK_DATABOX_MARKERS_N, GTK_DATABOX_MARKERS_TEXT_NW, "NW",
	 TRUE);
   setM (graph, 18, GTK_DATABOX_MARKERS_S, GTK_DATABOX_MARKERS_TEXT_SE, "SE",
	 TRUE);
   setM (graph, 19, GTK_DATABOX_MARKERS_E, GTK_DATABOX_MARKERS_TEXT_NE, "NE",
	 TRUE);


   graph = gtk_databox_markers_new (4, X + 20, Y + 20, &color, 1,
				    GTK_DATABOX_MARKERS_DASHED_LINE);

   gtk_databox_graph_add (GTK_DATABOX (box), graph);
   setL (graph, 0, GTK_DATABOX_MARKERS_N, GTK_DATABOX_MARKERS_TEXT_W, "West",
	 TRUE);
   setL (graph, 1, GTK_DATABOX_MARKERS_E, GTK_DATABOX_MARKERS_TEXT_S, "South",
	 TRUE);
   setL (graph, 2, GTK_DATABOX_MARKERS_W, GTK_DATABOX_MARKERS_TEXT_N, "North",
	 TRUE);
   setL (graph, 3, GTK_DATABOX_MARKERS_S, GTK_DATABOX_MARKERS_TEXT_E, "East",
	 TRUE);

   color.red = 1;
   color.green = 1;
   color.blue = 0;
   color.alpha = 1;

   graph = gtk_databox_markers_new (5, X + 20 + 4, Y + 20 + 4, &color, 1,
				    GTK_DATABOX_MARKERS_NONE);

   gtk_databox_graph_add (GTK_DATABOX (box), graph);
   setT (graph, 0, GTK_DATABOX_MARKERS_TEXT_N, "North", FALSE);
   setT (graph, 1, GTK_DATABOX_MARKERS_TEXT_E, "East", FALSE);
   setT (graph, 2, GTK_DATABOX_MARKERS_TEXT_S, "South", FALSE);
   setT (graph, 3, GTK_DATABOX_MARKERS_TEXT_W, "West", FALSE);
   setT (graph, 4, GTK_DATABOX_MARKERS_TEXT_CENTER, "Centered", TRUE);


   gtk_databox_auto_rescale (GTK_DATABOX (box), 0.05);

   separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
   gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 0);

   box2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
   gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
   gtk_box_pack_end (GTK_BOX (box1), box2, FALSE, TRUE, 0);
   close_button = gtk_button_new_with_label ("close");
   g_signal_connect_swapped (G_OBJECT (close_button), "clicked",
			     G_CALLBACK (gtk_main_quit), G_OBJECT (box));
   gtk_box_pack_start (GTK_BOX (box2), close_button, TRUE, TRUE, 0);
   gtk_widget_set_can_default (close_button, TRUE);
   gtk_widget_grab_default (close_button);

   gtk_widget_show_all (window);

}

gint
main (gint argc, char *argv[])
{
   gtk_init (&argc, &argv);

   create_markerss ();
   gtk_main ();

   return 0;
}
