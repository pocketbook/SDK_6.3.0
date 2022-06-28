#ifndef SELECTION_LIST_H
#define SELECTION_LIST_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "inkview.h"


typedef struct SSelectionList SelectionList;

typedef struct SSelectionListCallbacks {
    void (*Draw)(void* context, int item_num, irect item_rect, int is_selected, int is_touched);
    /**
      \brief Called when item is changed by user or through call to SelectionList_SetSelectedItem
      */
    void (*SelectedItemChanged)(void* context, int selected_item);

    /**
      \brief Called when user click on item
      */
    void (*ItemClicked)(void* context, int item_num, int x, int y);

    void (*DrawStaticElements)(void* context, irect screen_rect);

    void (*ItemLongClicked)(void* context, int item_num, int x, int y);

    void (*ScrollPositionChanged)(void* context, int page_num, int page_count);

} SelectionListCallbacks;

SelectionList* SelectionList_Init(irect screen_rect, SelectionListCallbacks* cb, void* cb_context, int item_height);
void SelectionList_Destroy(SelectionList* this_);

int SelectionList_SetItemcount(SelectionList* this_, int items_count);
int SelectionList_SetSelectedItem(SelectionList* this_, int n);
int SelectionList_GetSelectedItem(SelectionList* this_);
int SelectionList_Update(SelectionList* this_);
int SelectionList_HandleEvent(SelectionList* this_, int type, int par1, int par2);
int SelectionList_Draw(SelectionList* this_);
void SelectionList_SetVisible(SelectionList* this_, int value);

irect SelectionList_GetVisibleRect(SelectionList* this_);
void SelectionList_SetScrollPos(SelectionList* this_, int pos);

int SelectionList_IsMoving(SelectionList* this_);

void SelectionList_SetUpdateHightlighted(SelectionList* this_, int flag);

void SelectionList_ForceExitA2(SelectionList* this_);
void SelectionListw_SetExitA2Delay(SelectionList* this_, int delay_ms);
void SelectionList_UseDraggableScroller(SelectionList* this_, int use);
void SelectionList_SetScreenRect(SelectionList* this_, irect screen_rect);
void SelectionList_SetBackgroundColor(SelectionList* this_, int color);
void SelectionList_GetHighlightedPoint(SelectionList* this_, int* x, int* y);

void SelectionList_SetScrollerOffset(SelectionList* this_, int top_offset, int bottom_offset);
void SelectionList_SetBotomContentOffset(SelectionList* this_, int offset);
int SelectionList_GetBotomContentOffset(SelectionList* this_);

void SelectionList_SetItemHeight(SelectionList* this_, int item_height);
void SelectionList_SetPageMode(SelectionList* this_, int page_mode);
int  SelectionList_GetPageMode(SelectionList* this_);
void SelectionList_SetDisableScrollOnFit(SelectionList* this_, int value);
void SelectionList_SetDoNotAjustViewport(SelectionList* this_, int value);
void SelectionList_PageDown(SelectionList* this_);
void SelectionList_PageUp(SelectionList* this_);
void SelectionList_Paging(SelectionList* this_, int count);
void SelectionList_UpdatePager(SelectionList* this_);
void SelectionList_ForceDrawVerticalScrollerInPageMode(SelectionList* this_);
#ifdef __cplusplus
}
#endif

#endif // SELECTION_LIST_H
