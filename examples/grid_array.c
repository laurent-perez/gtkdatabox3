/* $Id: grid.c 4 2008-06-22 09:19:11Z rbock $ */
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
#include <gtkdatabox_grid.h>
#include <math.h>

#define POINTS 2000

/*----------------------------------------------------------------
 *  databox grid
 *----------------------------------------------------------------*/

static gfloat gridVert[] =
   { 100.0, 300.0, 500.0, 700.0, 900.0, 1100.0, 1300.0, 1500.0, 1700.0,
1900.0 };
static gfloat gridHoriz[] =
   { -100.0, -80.0, -60.0, -40.0, -20.0, 0.0, 20.0, 40.0, 60.0, 80.0, 100.0 };

static void
create_grid (void)
{
   GtkWidget *window = NULL;
   GtkWidget *box1;
   GtkWidget *box2;
   GtkWidget *close_button;
   GtkWidget *box;
   GtkWidget *label;
   GtkWidget *table;
   GtkWidget *separator;
   GtkDataboxGraph *graph;
   gfloat *X;
   gfloat *Y;
   GdkRGBA color;
   gint i;

   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_widget_set_size_request (window, 500, 500);

   g_signal_connect (G_OBJECT (window), "destroy",
		     G_CALLBACK (gtk_main_quit), NULL);

   gtk_window_set_title (GTK_WINDOW (window),
			 "GtkDatabox: Grid Array Example");
   gtk_container_set_border_width (GTK_CONTAINER (window), 0);

   box1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
   gtk_container_add (GTK_CONTAINER (window), box1);

   label = gtk_label_new ("This is an example of grid value arrays");
   gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);
   separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
   gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, FALSE, 0);

   /* Create a GtkDatabox widget along with scrollbars and rulers */
   gtk_databox_create_box_with_scrollbars_and_rulers (&box, &table,
						      TRUE, TRUE, TRUE, TRUE);
   gtk_box_pack_start (GTK_BOX (box1), table, TRUE, TRUE, 0);

   gtk_databox_set_bg_color (GTK_DATABOX (box), "#272727");

   X = g_new0 (gfloat, POINTS);
   Y = g_new0 (gfloat, POINTS);

   for (i = 0; i < POINTS; i++)
   {
      X[i] = i;
      Y[i] = 100. * sin (i * 2 * G_PI / POINTS);
   }
   color.red = 0;
   color.green = 1;
   color.blue = 0;
   color.alpha = 1;

   graph = gtk_databox_points_new (POINTS, X, Y, &color, 3);
   gtk_databox_graph_add (GTK_DATABOX (box), graph);

   Y = g_new0 (gfloat, POINTS);

   for (i = 0; i < POINTS; i++)
   {
      Y[i] = 100. * cos (i * 2 * G_PI / POINTS);
   }
   color.red = 1;
   color.green = 0;
   color.blue = 0;
   color.alpha = 1;

   graph = gtk_databox_points_new (POINTS, X, Y, &color, 3);
   gtk_databox_graph_add (GTK_DATABOX (box), graph);

   /* Here we start with the first grid */
   color.red = 0;
   color.green = 0;
   color.blue = 1;
   color.alpha = 1;

   graph =
      gtk_databox_grid_array_new (11, 10, gridHoriz, gridVert, &color, 1);
   gtk_databox_graph_add (GTK_DATABOX (box), graph);

   color.red = 51000;
   color.green = 0;
   color.blue = 0;
   color.alpha = 1;


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

   create_grid ();
   gtk_main ();

   return 0;
}
