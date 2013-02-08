/*
 * gst-editing-services
 * Copyright (C) <2013> Thibault Saunier <thibault.saunier@collabora.com>
 *               <2013> Collabora Ltd.
 *
 * gst-editing-services is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * gst-editing-services is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _GES_TIMELINE_ELEMENT_H_
#define _GES_TIMELINE_ELEMENT_H_

#include <glib-object.h>
#include <gst/gst.h>
#include "ges-enums.h"
#include "ges-types.h"

G_BEGIN_DECLS

#define GES_TYPE_TIMELINE_ELEMENT             (ges_timeline_element_get_type ())
#define GES_TIMELINE_ELEMENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), GES_TYPE_TIMELINE_ELEMENT, GESTimelineElement))
#define GES_TIMELINE_ELEMENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), GES_TYPE_TIMELINE_ELEMENT, GESTimelineElementClass))
#define GES_IS_TIMELINE_ELEMENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GES_TYPE_TIMELINE_ELEMENT))
#define GES_IS_TIMELINE_ELEMENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), GES_TYPE_TIMELINE_ELEMENT))
#define GES_TIMELINE_ELEMENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), GES_TYPE_TIMELINE_ELEMENT, GESTimelineElementClass))

typedef struct _GESTimelineElementPrivate GESTimelineElementPrivate;

/**
 * GES_TIMELINE_ELEMENT_START:
 * @obj: a #GESTimelineElement
 *
 * The start position of the object (in nanoseconds).
 */
#define GES_TIMELINE_ELEMENT_START(obj) (((GESTimelineElement*)obj)->start)

/**
 * GES_TIMELINE_ELEMENT_INPOINT:
 * @obj: a #GESTimelineElement
 *
 * The in-point of the object (in nanoseconds).
 */
#define GES_TIMELINE_ELEMENT_INPOINT(obj) (((GESTimelineElement*)obj)->inpoint)

/**
 * GES_TIMELINE_ELEMENT_DURATION:
 * @obj: a #GESTimelineElement
 *
 * The duration of the object (in nanoseconds).
 */
#define GES_TIMELINE_ELEMENT_DURATION(obj) (((GESTimelineElement*)obj)->duration)

/**
 * GES_TIMELINE_ELEMENT_MAX_DURATION:
 * @obj: a #GESTimelineElement
 *
 * The maximun duration of the object (in nanoseconds).
 */
#define GES_TIMELINE_ELEMENT_MAX_DURATION(obj) (((GESTimelineElement*)obj)->maxduration)

/**
 * GES_TIMELINE_ELEMENT_PRIORITY:
 * @obj: a #GESTimelineElement
 *
 * The priority of the object.
 */
#define GES_TIMELINE_ELEMENT_PRIORITY(obj) (((GESTimelineElement*)obj)->priority)

/**
 * GES_TIMELINE_ELEMENT_PARENT:
 * @obj: a #GESTimelineElement
 *
 * The parent of the object.
 */
#define GES_TIMELINE_ELEMENT_PARENT(obj) (((GESTimelineElement*)obj)->parent)

/**
 * GESTimelineElementClass:
 * @set_start: method to set the start of a #GESTimelineElement
 * @set_duration: method to set the duration of a #GESTimelineElement
 * @set_inpoint: method to set the inpoint of a #GESTimelineElement
 * @set_max_duration: method to set the maximun duration of a #GESTimelineElement
 * @set_priority: method to set the priority of a #GESTimelineElement
 * @ripple: method to ripple an object
 * @ripple_end: method to ripple an object on its #GES_EDGE_END edge
 * @roll_start: method to roll an object on its #GES_EDGE_START edge
 * @roll_end: method to roll an object on its #GES_EDGE_END edge
 * @trim: method to trim an object
 * @deep_copy: Copy the children properties of @self into @copy
 *
 * The GESTimelineElement base class. Subclasses should override at least
 * @set_start @set_inpoint @set_duration @ripple @ripple_end @roll_start
 * @roll_end and @trim
 */
struct _GESTimelineElementClass
{
  GInitiallyUnownedClass parent_class;

  gboolean (*set_start)        (GESTimelineElement * self, GstClockTime start);
  gboolean (*set_inpoint)      (GESTimelineElement * self, GstClockTime inpoint);
  gboolean (*set_duration)     (GESTimelineElement * self, GstClockTime duration);
  gboolean (*set_max_duration) (GESTimelineElement * self, GstClockTime maxduration);
  gboolean (*set_priority)     (GESTimelineElement * self, guint32 priority);

  gboolean (*ripple)           (GESTimelineElement *self, guint64  start);
  gboolean (*ripple_end)       (GESTimelineElement *self, guint64  end);
  gboolean (*roll_start)       (GESTimelineElement *self, guint64  start);
  gboolean (*roll_end)         (GESTimelineElement *self, guint64  end);
  gboolean (*trim)             (GESTimelineElement *self, guint64  start);
  void (*deep_copy)            (GESTimelineElement *self, GESTimelineElement *copy);

  /* Padding for API extension */
  gpointer _ges_reserved[GES_PADDING_LARGE];
};

/**
 * GESTimelineElement:
 * @start: position (in time) of the object
 * @inpoint: Position in the media from which the object should be used
 * @duration: duration of the object to be used
 * @maxduration: The maximum duration the object can have
 * @priority: priority of the object in the layer (0:top priority)
 *
 * Those filed can be accessed from outside but in no case should
 * be changed from there. Subclasses can write them but should make
 * sure to properly call g_object_notify.
 */
struct _GESTimelineElement
{
  GInitiallyUnowned parent_instance;

  /*< read only >*/
  GESTimelineElement *parent;
  GESAsset *asset;
  GstClockTime start;
  GstClockTime inpoint;
  GstClockTime duration;
  GstClockTime maxduration;
  guint32 priority;

  /*< private >*/
  GESTimelineElementPrivate *priv;

  /* Padding for API extension */
  gpointer _ges_reserved[GES_PADDING_LARGE];
};

GType ges_timeline_element_get_type (void) G_GNUC_CONST;

GESTimelineElement * ges_timeline_element_get_parent (GESTimelineElement * self);
gboolean ges_timeline_element_set_parent             (GESTimelineElement *self, GESTimelineElement *parent);
void ges_timeline_element_set_start                  (GESTimelineElement *self, GstClockTime start);
void ges_timeline_element_set_inpoint                (GESTimelineElement *self, GstClockTime inpoint);
void ges_timeline_element_set_duration               (GESTimelineElement *self, GstClockTime duration);
void ges_timeline_element_set_max_duration           (GESTimelineElement *self, GstClockTime duration);
void ges_timeline_element_set_priority               (GESTimelineElement *self, guint32 priority);

GstClockTime ges_timeline_element_get_start          (GESTimelineElement *self);
GstClockTime ges_timeline_element_get_inpoint        (GESTimelineElement *self);
GstClockTime ges_timeline_element_get_duration       (GESTimelineElement *self);
GstClockTime ges_timeline_element_get_max_duration   (GESTimelineElement *self);
guint32 ges_timeline_element_get_priority            (GESTimelineElement *self);

gboolean ges_timeline_element_ripple                 (GESTimelineElement *self, GstClockTime  start);
gboolean ges_timeline_element_ripple_end             (GESTimelineElement *self, GstClockTime  end);
gboolean ges_timeline_element_roll_start             (GESTimelineElement *self, GstClockTime  start);
gboolean ges_timeline_element_roll_end               (GESTimelineElement *self, GstClockTime  end);
gboolean ges_timeline_element_trim                   (GESTimelineElement *self, GstClockTime  start);
GESTimelineElement * ges_timeline_element_copy       (GESTimelineElement *self, gboolean deep);

G_END_DECLS

#endif /* _GES_TIMELINE_ELEMENT_H_ */
