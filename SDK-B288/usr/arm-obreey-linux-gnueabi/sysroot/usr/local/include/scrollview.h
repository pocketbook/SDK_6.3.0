/**
  \brief This file contains scroll view widget functionality.
  The widget is responsible for handling pointer down/drag/up events, calculating coordinates
  drawing scroll bars and visual effects. User should provide widget with content which able
  to draw itself. Also user should pass pointer related events to widget

  \author Yuriy Lisovyy
  */
#ifndef _SCROLL_VIEW_H_
#define _SCROLL_VIEW_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "inkview.h"

// Forward declaration
typedef struct SScrollView_Content ScrollView_Content;

/**
  \brief Opaque structure to represent widget for clients
  */
typedef struct SScrollView ScrollView;


#define SCROLL_VIEW_POINTER_DOWN_EVENT 1    /// Event is sent when pointer down on scrollview screen rectangle
#define SCROLL_VIEW_POINTER_UP_EVENT 2      /// Event is sent when pointer up on scrollview screen rectangle
#define SCROOL_VIEW_START_SCROLL_EVENT 3    /// Widget begin to move its content
#define SCROLL_VIEW_END_SCROLL_EVENT 4      /// Widget stop to move its content
#define SCROLL_VIEW_CLICK_EVENT 5           /// User make pointer down/ pointer up at some point of the widget
#define SCROLL_VIEW_LONG_PRESS_EVENT 6      /// Long press event
#define SCROLL_VIEW_TOUCH_EVENT 7    /// Event is sent when pointer down and not move for some timeout on scrollview screen rectangle


#define SCROLL_VIEW_FLAG_DRAW_VERT_SCROLLER 1   /// Enable vertical scroller
#define SCROLL_VIEW_FLAG_DRAW_HORIZONTAL_SCROLLER 2 /// Enable horizontal scroller
#define SCROLL_VIEW_FLAG_NO_A2_ON_CONTENT_FIT 4     /// disable scroll and update in a2 if content fit in viewport

/**
  \brief Structure with callback which content shoud provide for scrollview widget
  */
struct SScrollView_Content 
{
    /**
      \brief Function which draw content. It draws part of the content specified by content_rect parameter
        to the screen rect which top-left is at (to_x, to_y) point
      \param context content context (as passed to ScrollView_Init function)
      \param content_rect rectangle on content which should be drawed
      \param to_x x coordinate on the screen to draw from
      \param to_y y coordinate on the screen to draw from
      */
    void (*Draw)(void* context, irect content_rect, int to_x, int to_y);
    /**
      \brief Function to be called when event occurs
      \param context content context (as passed to ScrollView_Init function)
      \param event_type type of the event (one of value defined by SCROLL_VIEW_*_EVENT macros)
      \param x coordinate of event (if applicable)
      \param y coordinate of event (if applicable)
      */
    void (*ProcessEvent)(void* context, int event_type, int x, int y);

    void (*DrawStaticElements)(void* context, irect screen_rect);
};

/**
  \brief Initialize scroll view widget. To destroy widget and free resources ScrollView_Destroy function shoud be called
  \param screen_rect rectangle of the screen widget shoud be placed on
  \param content_handler content callbacks
  \param content_context value to be passed to content callbacks
  \param flags flags which control widget behaviour (should be value defined by SCROLL_VIEW_FLAG_* define)
  \return pointer to scroll view widget instance (should be passed to ScrollView_* function as first parameter)
    on fail it returns NULL
  */
ScrollView* ScrollView_Init(irect screen_rect, ScrollView_Content* content_handler, void * content_context, int flags);

/**
  \brief Destroy scroll view widget
  */
void ScrollView_Destroy(ScrollView* sv);

/**
  \brief Set new values for widget place on the screen
  */
int ScrollView_SetScreenWindows(ScrollView* this_, irect screen_rect);

/**
  \brief Set size of content widget should allow to scroll
  */
int ScrollView_SetContentSize(ScrollView* this_, int w, int h);

/**
  \brief Set view position for the windows
  */
int ScrollView_SetViewport(ScrollView* this_, int x, int y);

/**
  \brief Pass system event to widget to allow them to be handled
  */
int ScrollView_HandleEvent(ScrollView* this_, int type, int par1, int par2);

/**
  \brief Force widget update
  */
int ScrollView_Update(ScrollView* this_);

/**
  \brief Set margin to allow to scroll widget beyond the content on some value during scrolling operation
   After finishing draging widget scroll content back to edge position.
  */
int ScrollView_SetMargins(ScrollView* this_, int horizontal_margin, int vertical_margin);

irect ScrollView_GetVisibleRect(ScrollView* this_);

int ScrollView_Draw(ScrollView* this_);

void ScrollView_SetVisible(ScrollView* this_, int value);

int ScrollView_IsMoving(ScrollView* this_);

irect ScrollView_GetScreenRect(ScrollView* this_);

void ScrollView_ForceExitA2(ScrollView* this_);
void ScrollView_SetExitA2Delay(ScrollView* this_, int delay_ms);
void ScrollView_UseDraggableScroller(ScrollView* this_, int use);
void ScrollView_SetBackgroundColor(ScrollView* this_, int bcolor);

void ScrollView_SetScrollerOffset(ScrollView* this_, int top_offset, int bottom_offset);
void ScrollView_SetFlags(ScrollView* this_, int flags);
int ScrollView_GetFlags(ScrollView* this_);
#ifdef __cplusplus
}
#endif
#endif //_SCROLL_VIEW_H_

