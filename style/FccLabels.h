#ifndef __FCCLABELS_H
#define __FCCLABELS_H

#include "Rtypes.h"

void FCCLabel(Double_t x,Double_t y,const char* text=NULL,Color_t color=1); 

void FCCLabelNew(Double_t x,Double_t y, char* text=NULL, Color_t color=1, float text_size=0);

#endif // __FCCLABELS_H
