#include <iostream>

#include "FccStyle.h"

#include "TROOT.h"

void SetFCCStyle ()
{
  static TStyle* fccStyle = 0;
  std::cout << "\nApplying FCC style settings...\n" << std::endl ;
  if ( fccStyle==0 ) fccStyle = FccStyle();
  gROOT->SetStyle("FCC");
  gROOT->ForceStyle();
}

TStyle* FccStyle() 
{
  TStyle *fccStyle = new TStyle("FCC","FCC style");

  // use plain black on white colors
  Int_t icol=0; // WHITE
  fccStyle->SetFrameBorderMode(icol);
  fccStyle->SetFrameFillColor(icol);
  fccStyle->SetCanvasBorderMode(icol);
  fccStyle->SetCanvasColor(icol);
  fccStyle->SetPadBorderMode(icol);
  fccStyle->SetPadColor(icol);
  fccStyle->SetStatColor(icol);
  //fccStyle->SetFillColor(icol); // don't use: white fill color for *all* objects

  // set the paper & margin sizes
  fccStyle->SetPaperSize(20,26);

  // set margin sizes
  fccStyle->SetPadTopMargin(0.05);
  fccStyle->SetPadRightMargin(0.05);
  fccStyle->SetPadBottomMargin(0.16);
  fccStyle->SetPadLeftMargin(0.16);

  // set title offsets (for axis label)
  fccStyle->SetTitleXOffset(1.4);
  fccStyle->SetTitleYOffset(1.4);

  // use large fonts
  //Int_t font=72; // Helvetica italics
//   Int_t font=42; // Helvetica
//   Double_t tsize=0.05;
  // --- Michele
  Int_t font=43;
//   Double_t tsize=24;
  Double_t tsize=21;
  // ---
  fccStyle->SetTextFont(font);

  fccStyle->SetTextSize(tsize);
  fccStyle->SetLabelFont(font,"x");
  fccStyle->SetTitleFont(font,"x");
  fccStyle->SetLabelFont(font,"y");
  fccStyle->SetTitleFont(font,"y");
  fccStyle->SetLabelFont(font,"z");
  fccStyle->SetTitleFont(font,"z");
  
  fccStyle->SetLabelSize(tsize,"x");
  fccStyle->SetTitleSize(tsize,"x");
  fccStyle->SetLabelSize(tsize,"y");
  fccStyle->SetTitleSize(tsize,"y");
  fccStyle->SetLabelSize(tsize,"z");
  fccStyle->SetTitleSize(tsize,"z");

  // --- Michele
  fccStyle->SetLegendFont(font);
  // ---
  
  // use bold lines and markers
  fccStyle->SetMarkerStyle(20);
  fccStyle->SetMarkerSize(1.2);
  fccStyle->SetHistLineWidth(2.);
  fccStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

  // get rid of X error bars 
  //fccStyle->SetErrorX(0.001);
  // get rid of error bar caps
  fccStyle->SetEndErrorSize(0.);

  // do not display any of the standard histogram decorations
  fccStyle->SetOptTitle(0);
  //fccStyle->SetOptStat(1111);
  fccStyle->SetOptStat(0);
  //fccStyle->SetOptFit(1111);
  fccStyle->SetOptFit(0);

  // put tick marks on top and RHS of plots
  fccStyle->SetPadTickX(1);
  fccStyle->SetPadTickY(1);

  return fccStyle;

}

