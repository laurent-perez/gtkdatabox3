/* $Id: logarithmic.c 4 2008-06-22 09:19:11Z rbock $ */
/* GtkDatabox - An extension to the gtk+ library
 * Copyright (C) 2011 - 2012  Dr. Matt Flax <flatmax@>
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
#include <gtkdatabox_ruler.h>
#include <math.h>

#define POINTS 100000
/*
#define STEPS 50
#define BARS 25
#define MARKER 10
*/
#define NO_BOXES 4

/*----------------------------------------------------------------
 *  databox rulers
 *----------------------------------------------------------------*/

static void
create_rulers (void)
{
   GtkWidget *window = NULL;
   GtkWidget *hbox;
   GtkWidget *vbox;
   GtkWidget *close_button;
   GtkWidget *box[NO_BOXES];
   GtkWidget *label;
   GtkWidget *separator;
   GtkWidget *table;
   GtkDataboxGraph *graph;
   gfloat min_x, max_x;
   gfloat min_y, max_y;
   gfloat *X;
   gfloat *Y;
   GdkRGBA color;
   gint i;
   GtkDataboxRuler *ruler;

   guint manual_tick_cnt = 4;
   gfloat manual_ticks[] = { 100., 300., 500., 700. };

   guint manual_tick_cnt_box2 = 5;
   gfloat manual_ticks_box2[] = { .01, .1, 1., 10., 100. };
   gchar *manual_tick_labels_box2[] =
      { "these", "are", "manual", "tick", "labels" };


   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_widget_set_size_request (window, 1000, 500);

   g_signal_connect (G_OBJECT (window), "destroy",
		     G_CALLBACK (gtk_main_quit), NULL);

   gtk_window_set_title (GTK_WINDOW (window),
			 "GtkDatabox: Ruler option example plots");
   gtk_container_set_border_width (GTK_CONTAINER (window), 0);

   vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
   gtk_container_add (GTK_CONTAINER (window), vbox);

   label = gtk_label_new ("demonstrates diferent ruler settings\n");
   gtk_box_pack_start (GTK_BOX (vbox), label, FALSE, FALSE, 0);
   separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
   gtk_box_pack_start (GTK_BOX (vbox), separator, FALSE, FALSE, 0);

   hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
   gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);

   label = gtk_label_new ("Rulers on the other side:");
   gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

   label =
      gtk_label_new
      ("Horizontal y axis text\n manual x axis ticks example\n right aligned y text:");
   gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

   label =
      gtk_label_new
      ("Subticks turned off on x and y,\n manual tick labels on x:");
   gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

   label =
      gtk_label_new
      ("X ticks turned off, no shadow\n horizontal y axis text,\n altered y label format example:");
   gtk_box_pack_start (GTK_BOX (hbox), label, TRUE, TRUE, 0);

   separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
   gtk_box_pack_start (GTK_BOX (vbox), separator, FALSE, FALSE, 0);

   /* Create the databoxes */
   hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
   gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, TRUE, 0);

   for (i = 0; i < NO_BOXES; ++i)
   {
      if ((i == 0) || (i == NO_BOXES - 1))	/* the first is normal but with the rulers on opposite sides to the default */
	 gtk_databox_create_box_with_scrollbars_and_rulers_positioned (&box
								       [i],
								       &table,
								       TRUE,
								       TRUE,
								       TRUE,
								       TRUE,
								       FALSE,
								       FALSE);
      else
	 gtk_databox_create_box_with_scrollbars_and_rulers (&box[i], &table,
							    TRUE, TRUE, TRUE,
							    TRUE);
      gtk_box_pack_start (GTK_BOX (hbox), table, TRUE, TRUE, 0);
   }

   /* set box 1's y ruler to have horizontal text */
   ruler = gtk_databox_get_ruler_y (GTK_DATABOX (box[1]));
   gtk_databox_ruler_set_text_orientation (ruler, GTK_ORIENTATION_HORIZONTAL);
   gtk_databox_ruler_set_box_shadow (ruler, GTK_SHADOW_ETCHED_OUT);
   gtk_databox_ruler_set_text_alignment (ruler, PANGO_ALIGN_RIGHT);
   gtk_databox_set_ruler_y (GTK_DATABOX (box[1]), ruler);
   ruler = gtk_databox_get_ruler_x (GTK_DATABOX (box[1]));	/* set box 1's x ruler to have manual ticks */
   gtk_databox_ruler_set_manual_tick_cnt (ruler, manual_tick_cnt);
   gtk_databox_ruler_set_manual_ticks (ruler, manual_ticks);
   gtk_databox_set_ruler_x (GTK_DATABOX (box[1]), ruler);

   /* set box 2 to have no subticks */
   ruler = gtk_databox_get_ruler_y (GTK_DATABOX (box[2]));
   gtk_databox_ruler_set_draw_subticks (ruler, FALSE);
   gtk_databox_set_ruler_y (GTK_DATABOX (box[2]), ruler);
   ruler = gtk_databox_get_ruler_x (GTK_DATABOX (box[2]));	/* put manual labels on x */
   gtk_databox_ruler_set_draw_subticks (ruler, FALSE);
   gtk_databox_ruler_set_manual_tick_cnt (ruler, manual_tick_cnt_box2);
   gtk_databox_ruler_set_manual_ticks (ruler, manual_ticks_box2);
   gtk_databox_ruler_set_manual_tick_labels (ruler, manual_tick_labels_box2);
   gtk_databox_set_ruler_x (GTK_DATABOX (box[2]), ruler);

   /* set box 3's y ruler to have horizontal text */
   ruler = gtk_databox_get_ruler_y (GTK_DATABOX (box[3]));
   gtk_databox_ruler_set_text_orientation (ruler, GTK_ORIENTATION_HORIZONTAL);
   gtk_databox_set_ruler_y (GTK_DATABOX (box[3]), ruler);
   /* set box 3 to have no x ticks */
   ruler = gtk_databox_get_ruler_x (GTK_DATABOX (box[3]));
   gtk_databox_ruler_set_draw_ticks (ruler, FALSE);
   /* box[3] to have different shadow on the ruler */
   gtk_databox_ruler_set_box_shadow (ruler, GTK_SHADOW_NONE);
   gtk_databox_set_ruler_x (GTK_DATABOX (box[3]), ruler);
   ruler = gtk_databox_get_ruler_y (GTK_DATABOX (box[3]));
   gtk_databox_ruler_set_draw_subticks (ruler, FALSE);
   /* set box[3] to have different formatting */
   gtk_databox_ruler_set_linear_label_format (ruler, "%%-%dg");
   gtk_databox_set_ruler_y (GTK_DATABOX (box[3]), ruler);

   /* set the background */
   for (i = 0; i < NO_BOXES; ++i)
      gtk_databox_set_bg_color (GTK_DATABOX (box[i]), "#555");

   /* add a sinus^2 */
   X = g_new0 (gfloat, POINTS);
   Y = g_new0 (gfloat, POINTS);

   for (i = 0; i < POINTS; i++)
   {
      X[i] = i / 100.;
      Y[i] = 0.01 + 1000 * pow (sin (i * G_PI / POINTS), 2);
   }

   color.red = 0;
   color.green = 1;
   color.blue = 0;
   color.alpha = 1;

   graph = gtk_databox_points_new (POINTS, X, Y, &color, 1);
   for (i = 0; i < NO_BOXES; ++i)
      gtk_databox_graph_add (GTK_DATABOX (box[i]), graph);

   /* add an exp function */
   X = g_new0 (gfloat, POINTS);
   Y = g_new0 (gfloat, POINTS);

   for (i = 0; i < POINTS; i++)
   {
      X[i] = i / 100.;
      Y[i] = exp (log (1000) * i / ((gfloat) POINTS));
   }

   color.red = 1;
   color.green = 0;
   color.blue = 0;
   color.alpha = 1;

   graph = gtk_databox_points_new (POINTS, X, Y, &color, 1);
   for (i = 0; i < NO_BOXES; ++i)
      gtk_databox_graph_add (GTK_DATABOX (box[i]), graph);

   /* add an 1/x function */
   X = g_new0 (gfloat, POINTS);
   Y = g_new0 (gfloat, POINTS);

   for (i = 0; i < POINTS; i++)
   {
      X[i] = i / 100.;
      Y[i] = 1000. / (100. * (gfloat) i / POINTS);
   }

   color.red = 1;
   color.green = 0;
   color.blue = 1;
   color.alpha = 1;

   graph = gtk_databox_points_new (POINTS, X, Y, &color, 1);
   for (i = 0; i < NO_BOXES; ++i)
      gtk_databox_graph_add (GTK_DATABOX (box[i]), graph);

   /* add an x^2 function */
   X = g_new0 (gfloat, POINTS);
   Y = g_new0 (gfloat, POINTS);

   for (i = 0; i < POINTS; i++)
   {
      X[i] = i / 100.;
      Y[i] = 1000. * (gfloat) i / POINTS * (gfloat) i / POINTS;
   }

   color.red = 1;
   color.green = 1;
   color.blue = 0;
   color.alpha = 1;

   graph = gtk_databox_points_new (POINTS, X, Y, &color, 1);
   for (i = 0; i < NO_BOXES; ++i)
      gtk_databox_graph_add (GTK_DATABOX (box[i]), graph);

   /* set the extrema */
   min_x = 0.01;
   max_x = 1000.;
   min_y = 1000.;
   max_y = 0.01;

   for (i = 0; i < NO_BOXES - 1; ++i)
      gtk_databox_set_total_limits (GTK_DATABOX (box[i]), min_x, max_x, min_y,
				    max_y);
   gtk_databox_set_total_limits (GTK_DATABOX (box[i]), 8, max_x, min_y,
				 max_y);

   gtk_databox_set_scale_type_y (GTK_DATABOX (box[1]), GTK_DATABOX_SCALE_LOG);
   gtk_databox_set_scale_type_x (GTK_DATABOX (box[2]), GTK_DATABOX_SCALE_LOG);
   gtk_databox_set_scale_type_y (GTK_DATABOX (box[2]), GTK_DATABOX_SCALE_LOG);
   gtk_databox_set_scale_type_x (GTK_DATABOX (box[3]),
				 GTK_DATABOX_SCALE_LOG2);

   separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
   gtk_box_pack_start (GTK_BOX (vbox), separator, FALSE, TRUE, 0);

   close_button = gtk_button_new_with_label ("close");
   g_signal_connect (G_OBJECT (close_button), "clicked",
		     G_CALLBACK (gtk_main_quit), NULL);
   gtk_box_pack_start (GTK_BOX (vbox), close_button, FALSE, FALSE, 0);
   gtk_widget_set_can_default (close_button, TRUE);
   gtk_widget_grab_default (close_button);
   gtk_widget_grab_focus (close_button);

   gtk_widget_show_all (window);
   for (i = 0; i < NO_BOXES; ++i)
      gdk_window_set_cursor (gtk_widget_get_window (box[i]),
			     gdk_cursor_new_for_display
			     (gdk_display_get_default (), GDK_CROSS));

}

gint
main (gint argc, char *argv[])
{
   gtk_init (&argc, &argv);

   create_rulers ();
   gtk_main ();

   return 0;
}
