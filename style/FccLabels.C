#include "FccLabels.h"

#include "TLatex.h"
#include "TLine.h"
#include "TPave.h"
#include "TPad.h"
#include "TMarker.h"


void FCCLabel(Double_t x,Double_t y,const char* text,Color_t color) 
{
  TLatex l; //l.SetTextAlign(12); l.SetTextSize(tsize); 
  l.SetNDC();
//   l.SetTextFont(72);
  l.SetTextFont(73);
  l.SetTextColor(color);

  double delx = 0.115*696*gPad->GetWh()/(472*gPad->GetWw());

  l.DrawLatex(x,y,"FCC");
  if (text) {
    TLatex p;
    p.SetNDC();
//     p.SetTextFont(42);
    p.SetTextFont(43);
    p.SetTextColor(color);
    p.DrawLatex(x+delx,y,text);
    //    p.DrawLatex(x,y,"#sqrt{s}=900GeV");
  }
}



void FCCLabelNew(Double_t x,Double_t y, char* text, Color_t color, float text_size)
{

  TLatex l;
  l.SetNDC();
  l.SetTextFont(73);
  l.SetTextColor(color);
  l.SetTextSize(text_size);

  double delx = 0.16;

  l.DrawLatex(x,y,"FCC");
  if (text) {
    TLatex p;
    p.SetNDC();
    p.SetTextFont(43);
    p.SetTextColor(color);
    p.SetTextSize(text_size);
    p.DrawLatex(x+delx,y,text);
  }
  return;

}



