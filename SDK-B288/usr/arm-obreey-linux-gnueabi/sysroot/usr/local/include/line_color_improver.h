#ifndef LINE_COLOR_IMPROVER_H
#define LINE_COLOR_IMPROVER_H

#include "inkview.h"

#ifdef __cplusplus
extern "C"
{
#endif

void ImproveLinesColor(icanvas* fb, int x, int y, int w, int h);
void SetImproveLineColorStatus(int enabled);
#ifdef __cplusplus
}

#endif

#endif
