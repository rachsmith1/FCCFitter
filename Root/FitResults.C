#include "TtHFitter/FitResults.h"

//__________________________________________________________________________________
//
FitResults::FitResults(){
    fNuisParNames.clear();
    fNuisParIdx.clear();
    fNuisParIsThere.clear();
    fCorrMatrix = 0;
    fNuisPar.clear();
}

//__________________________________________________________________________________
//
FitResults::~FitResults(){
    fNuisParNames.clear();
    fNuisParIdx.clear();
    fNuisParIsThere.clear();
    if(fCorrMatrix) delete fCorrMatrix;
    for(unsigned int i = 0; i<fNuisPar.size(); ++i){
        if(fNuisPar[i]) delete fNuisPar[i];
    }
    fNuisPar.clear();
}

//__________________________________________________________________________________
//
void FitResults::AddNuisPar(NuisParameter *par){
    fNuisPar.push_back(par);
    string p = par->fName;
    fNuisParIdx[p] = (int)fNuisParNames.size();
    fNuisParNames.push_back(p);
    fNuisParIsThere[p] = true;
}

//__________________________________________________________________________________
//
float FitResults::GetNuisParValue(string p){
    int idx = -1;
    if(fNuisParIsThere[p]){
        idx = fNuisParIdx[p];
    }
    else{
        if(TtHFitter::DEBUGLEVEL>0) cout << "  WARNING: NP " << p << " not found... Returning 0." << endl;
        return 0.;
    }
    return fNuisPar[idx]->fFitValue;
}

//__________________________________________________________________________________
//
float FitResults::GetNuisParErrUp(string p){
    int idx = -1;
    if(fNuisParIsThere[p]){
        idx = fNuisParIdx[p];
    }
    else{
        if(TtHFitter::DEBUGLEVEL>0) cout << "  WARNING: NP " << p << " not found... Returning error = 1." << endl;
        return 1.;
    }
    return fNuisPar[idx]->fPostFitUp;
}

//__________________________________________________________________________________
//
float FitResults::GetNuisParErrDown(string p){
    int idx = -1;
    if(fNuisParIsThere[p]){
        idx = fNuisParIdx[p];
    }
    else{
        if(TtHFitter::DEBUGLEVEL>0) cout << "  WARNING: NP " << p << " not found... Returning error = 1." << endl;
        return 1.;
    }
    return fNuisPar[idx]->fPostFitDown;
}

//__________________________________________________________________________________
//
void FitResults::ReadFromTXT(string fileName){
    bool includeCorrelations = true;
    bool invertedCorrMatrix = true;
    bool print = true;
    //
    CorrelationMatrix* matrix = new CorrelationMatrix();
    NuisParameter *np;
    //
    // get fitted NP's
    std::ifstream in;
    in.open(fileName.c_str());
    string input;
    string line;
    bool readingNP = false;
    bool readingCM = false;
    int i = 0;
    int j = 0;
    int Nsyst_corr = 0;
    //
    string name;
    float value, up, down;
    float corr;
    //
    // read file line by line
    while(std::getline(in, line)){
        if(line=="") continue;
        if(line=="NUISANCE_PARAMETERS"){
            if(TtHFitter::DEBUGLEVEL>0){
                cout << "--------------------" << endl;
                cout << "Reading Nuisance Parameters..." << endl;
                cout << "--------------------" << endl;
            }
            readingNP = true;
            continue;
        }
        else if(line=="CORRELATION_MATRIX"){
            if(TtHFitter::DEBUGLEVEL>0){
                cout << "--------------------" << endl;
                cout << "Reading Correlation Matrix..." << endl;
                cout << "--------------------" << endl;
            }
            readingNP = false;
            readingCM = true;
            std::getline(in, line); // skip 1 line
            Nsyst_corr = atof(line.substr(0,line.find(" ")).c_str());
            continue;
        }
        std::istringstream iss(line);
        if(readingNP){
            iss >> input;
            if(input=="" || input=="CORRELATION_MATRIX"){
                readingNP = false;
            }
            while(input.find("\\")!=string::npos) input = input.replace(input.find("\\"),1,"");
            name = input;
            // clean the syst name...
            name = ReplaceString(name,"alpha_","");
            name = ReplaceString(name,"gamma_","");
            AddNuisPar(new NuisParameter(name));
            iss >> value >> up >> down;
            np = fNuisPar[fNuisParIdx[name]];
            // set the title of this NP if there in the stored map
            //if(TtHFitter::SYSTMAP[name]!="") np->fTitle = TtHFitter::SYSTMAP[name];
            //
            np->fFitValue = value;
            np->fPostFitUp = up;
            np->fPostFitDown = down;
            if(TtHFitter::DEBUGLEVEL>0){
                if(print) cout << name << ": " << value << " +" << up << " " << down << endl;
            }
            i++;
        }
        if(readingCM){
            if(!includeCorrelations) break;
            for(int i_sys=0;i_sys<Nsyst_corr;i_sys++){
                iss >> corr;
                if(invertedCorrMatrix){
                    matrix->SetCorrelation(fNuisParNames[Nsyst_corr-i_sys-1],fNuisParNames[j],corr);
                }
                else matrix->SetCorrelation(fNuisParNames[i_sys],fNuisParNames[j],corr);
            }
            j++;
        }
    }
    if(includeCorrelations){
        if(TtHFitter::DEBUGLEVEL>0){
          if(print){
              for(int j_sys=0;j_sys<Nsyst_corr;j_sys++){
                  cout << "\t " << fNuisParNames[j_sys];
              }
              cout << endl;
              for(int i_sys=0;i_sys<Nsyst_corr;i_sys++){
                  cout << fNuisParNames[i_sys];
                  for(int j_sys=0;j_sys<Nsyst_corr;j_sys++){
                      cout << Form("\t%.4f",matrix->GetCorrelation(fNuisParNames[i_sys],fNuisParNames[j_sys]));
                  }
                  cout << endl;
              }
          }
        }
    }
    fCorrMatrix = matrix;
    //
    int TOTsyst = fNuisParNames.size();
    cout << "Found " << TOTsyst << " systematics." << endl;
    if(TOTsyst<=0) cout << "WARNING: No systematics found in fit result file..." << endl;
}

//__________________________________________________________________________________
//
void FitResults::DrawNormFactors( const string &path, const std::vector < NormFactor* > &normFactors ){
    float xmin = 1000;
    float xmax = -1000;
    float max = 0;

    TGraphAsymmErrors *g = new TGraphAsymmErrors();

    NuisParameter *par;
    std::vector< NuisParameter* > selected_norm_factors;

    for(unsigned int i = 0; i<fNuisPar.size(); ++i){
      par = fNuisPar[i];
      bool isNorm = false;
      for( const auto *norm : normFactors ){
        if(norm->fName==par->fName){
          isNorm = true;
          break;
        }
      }
      if ( !isNorm ) continue;
      g->SetPoint(selected_norm_factors.size(),par->fFitValue,2*selected_norm_factors.size()+1);
      g->SetPointEXhigh(selected_norm_factors.size(), par->fPostFitUp);
      g->SetPointEXlow( selected_norm_factors.size(),-par->fPostFitDown);

      if( par->fFitValue+par->fPostFitUp > xmax ) xmax = par->fFitValue+par->fPostFitUp;
      if( par->fFitValue+par->fPostFitDown < xmin ) xmin = par->fFitValue+par->fPostFitDown;

      NuisParameter* nuis= new NuisParameter(par->fName);
      nuis -> fFitValue =    par -> fFitValue;
      nuis -> fPostFitUp =   par -> fPostFitUp;
      nuis -> fPostFitDown = par -> fPostFitDown;
      nuis -> fTitle =       par -> fTitle;
      selected_norm_factors.push_back(nuis);
      if(2*selected_norm_factors.size() > max)  max = 2*selected_norm_factors.size();
    }
//     xmax *= (xmax<0 ? 0.5 : 1.5)*2;
    xmax *= (xmax<0 ? 0.5 : 1.5);
    xmin *= (xmin>0 ? 0.5 : 1.5);
    if(xmin>0) xmin = 0.;
    xmax += (xmax-xmin)*0.25;

    int lineHeight = 40;
    int offsetUp = 40;
    int offsetDown = 40;
    int offset = offsetUp + offsetDown;
    int newHeight = offset + max*lineHeight;
    TCanvas *c = new TCanvas("c","c",800,newHeight);
    c->SetTicks(1,0);
    gPad->SetLeftMargin(0.05/(8./6.));
    gPad->SetRightMargin(0.5);
    gPad->SetTopMargin(1.*offsetUp/newHeight);
    gPad->SetBottomMargin(1.*offsetDown/newHeight);

    TH1F *h_dummy = new TH1F( "h_dummy_norm","h_dummy_norm",10,xmin,xmax);
    h_dummy->SetMaximum(max);
    h_dummy->SetLineWidth(0);
    h_dummy->SetFillStyle(0);
    h_dummy->SetLineColor(kWhite);
    h_dummy->SetFillColor(kWhite);
    h_dummy->SetMinimum(0.);
    h_dummy->GetYaxis()->SetLabelSize(0);
    h_dummy->Draw();
    h_dummy->GetYaxis()->SetNdivisions(0);

    TLine l0;
    TBox b1, b2;
    l0 = TLine(1,0,1,max);
    l0.SetLineStyle(7);
    l0.SetLineColor(kBlack);
    l0.Draw("same");
    g->Draw("psame");

    TLatex *systs = new TLatex();
    systs->SetTextSize( systs->GetTextSize()*0.8 );
    for(int i=0;i<selected_norm_factors.size();i++){
      systs->DrawLatex(xmax*1.05,2*i+0.75,(selected_norm_factors[i]->fTitle).c_str());
      systs->DrawLatex(xmax*0.7,2*i+0.75,
        Form("%.2f ^{%.2f}_{%.2f}",selected_norm_factors[i]->fFitValue, selected_norm_factors[i]->fPostFitUp, selected_norm_factors[i]->fPostFitDown ) );
    }
    h_dummy->GetXaxis()->SetLabelSize( h_dummy->GetXaxis()->GetLabelSize()*0.9 );
    gPad->RedrawAxis();

    c->SaveAs(path.c_str());
    delete c;
}

//__________________________________________________________________________________
//
void FitResults::DrawGammaPulls( const string &path ){
    float xmin = 10;
    float xmax = -10;
    float max = 0;

    TGraphAsymmErrors *g = new TGraphAsymmErrors();

    NuisParameter *par;
    int idx = 0;
    std::vector< string > Names;
    Names.clear();

    for(unsigned int i = 0; i<fNuisPar.size(); ++i){
        par = fNuisPar[i];
        if ( par->fName.find("stat_") == std::string::npos ) continue;
        g->SetPoint(idx,par->fFitValue,idx+0.5);
        g->SetPointEXhigh(idx, par->fPostFitUp);
        g->SetPointEXlow( idx,-par->fPostFitDown);
        if( par->fFitValue+par->fPostFitUp > xmax ) xmax = par->fFitValue+par->fPostFitUp;
        if( par->fFitValue+par->fPostFitDown < xmin ) xmin = par->fFitValue+par->fPostFitDown;

        std::string clean_name = par->fTitle;
        clean_name = ReplaceString( clean_name, "stat_", "#gamma " );
        clean_name = ReplaceString( clean_name, "_", " " );
        Names.push_back(clean_name);
        idx ++;
        if(idx > max)  max = idx;
    }
//     xmax *= (1.5-(xmax<0));
//     xmin *= (0.5+(xmin<0));
    xmax *= (1.2-(xmax<0));
    xmin *= (0.8+(xmin<0));

    int lineHeight = 20;
    int offsetUp = 40;
    int offsetDown = 40;
    int offset = offsetUp + offsetDown;
    int newHeight = offset + max*lineHeight;
    TCanvas *c = new TCanvas("c","c",800,newHeight);
    c->SetTicks(1,0);
    gPad->SetLeftMargin(0.05/(8./6.));
    gPad->SetRightMargin(0.5);
    gPad->SetTopMargin(1.*offsetUp/newHeight);
    gPad->SetBottomMargin(1.*offsetDown/newHeight);

    TH1F *h_dummy = new TH1F( "h_dummy_gamma","h_dummy_gamma",10,xmin,xmax);
    h_dummy->SetMaximum(max);
    h_dummy->SetLineWidth(0);
    h_dummy->SetFillStyle(0);
    h_dummy->SetLineColor(kWhite);
    h_dummy->SetFillColor(kWhite);
    h_dummy->SetMinimum(0.);
    h_dummy->GetYaxis()->SetLabelSize(0);
    h_dummy->Draw();
    h_dummy->GetYaxis()->SetNdivisions(0);

    TLine l0;
    TBox b1, b2;
    l0 = TLine(1,0,1,max);
    l0.SetLineStyle(7);
    l0.SetLineColor(kBlack);
    l0.Draw("same");
    g->Draw("psame");

    TLatex *systs = new TLatex();
    systs->SetTextSize( systs->GetTextSize()*0.8 );
    for(int i=0;i<max;i++){
        systs->DrawLatex(xmax*1.05,i+0.25,Names[i].c_str());
    }
    h_dummy->GetXaxis()->SetLabelSize( h_dummy->GetXaxis()->GetLabelSize()*0.9 );
    gPad->RedrawAxis();

    c->SaveAs(path.c_str());
    delete c;
}

//__________________________________________________________________________________
//
void FitResults::DrawNPPulls( const string &path, const string &category, const std::vector < NormFactor* > &normFactors ){
    float xmin = -2.9;
    float xmax = 2.9;
    float max = 0;
//     string npToExclude[] = {"SigXsecOverSM","gamma_","stat_"};
    string npToExclude[] = {"gamma_","stat_"};
    bool brazilian = true;
    bool grayLines = false;

    TGraphAsymmErrors *g = new TGraphAsymmErrors();

    NuisParameter *par;
    int idx = 0;
    std::vector< string > Names;
    Names.clear();

    for(unsigned int i = 0; i<fNuisPar.size(); ++i){
        par = fNuisPar[i];

        if( category != "all" && category != par->fCategory ) continue;
        if( FindInStringVector(fNuisParToHide,par->fName)>=0 ) continue;

        bool skip = false;
        for(int ii=0; ii<sizeof(npToExclude)/sizeof(string); ii++){
            if(par->fName.find(npToExclude[ii])!=string::npos){
                skip = true;
                break;
            }
        }
        for( const auto *norm : normFactors ){
          if(norm->fName==par->fName){
            skip = true;
            break;
          }
        }
        if(skip) continue;

        g->SetPoint(idx,par->fFitValue,idx+0.5);
        g->SetPointEXhigh(idx, par->fPostFitUp);
        g->SetPointEXlow( idx,-par->fPostFitDown);

        Names.push_back(par->fTitle);

        idx ++;
        if(idx > max)  max = idx;
    }

    int lineHeight = 20;
    int offsetUp = 40;
    int offsetDown = 40;
    int offset = offsetUp + offsetDown;
    int newHeight = offset + max*lineHeight;
//     TCanvas *c = new TCanvas("c","c",600,newHeight);
    TCanvas *c = new TCanvas("c","c",800,newHeight);
    c->SetTicks(1,0);
//     gPad->SetLeftMargin(0.05);
    gPad->SetLeftMargin(0.05/(8./6.));
//     gPad->SetRightMargin(0.33);
    gPad->SetRightMargin(0.5);
    gPad->SetTopMargin(1.*offsetUp/newHeight);
    gPad->SetBottomMargin(1.*offsetDown/newHeight);

    TH1F *h_dummy = new TH1F( ("h_dummy"+category).c_str(),("h_dummy"+category).c_str(),10,xmin,xmax);
    h_dummy->SetMaximum(max);
    h_dummy->SetLineWidth(0);
    h_dummy->SetFillStyle(0);
    h_dummy->SetLineColor(kWhite);
    h_dummy->SetFillColor(kWhite);
    h_dummy->SetMinimum(0.);
    h_dummy->GetYaxis()->SetLabelSize(0);
    h_dummy->Draw();
    h_dummy->GetYaxis()->SetNdivisions(0);

    TLine l0;
    TBox b1, b2;
    if(brazilian){
        l0 = TLine(0,0,0,max);
        l0.SetLineStyle(7);
        l0.SetLineColor(kBlack);
        b1 = TBox(-1,0,1,max);
        b2 = TBox(-2,0,2,max);
        b1.SetFillColor(kGreen);
        b2.SetFillColor(kYellow);
        b2.Draw("same");
        b1.Draw("same");
        l0.Draw("same");
    }

    g->Draw("psame");

    TLatex *systs = new TLatex();
    systs->SetTextSize( systs->GetTextSize()*0.8 );
    for(int i=0;i<max;i++){
        systs->DrawLatex(3.,i+0.25,Names[i].c_str());
    }
    h_dummy->GetXaxis()->SetLabelSize( h_dummy->GetXaxis()->GetLabelSize()*0.9 );

    gPad->RedrawAxis();

    if(category!="all"){
        TLatex *cat_legend = new TLatex();
//         cat_legend -> DrawLatexNDC(0.5,0.8,category.c_str());
        cat_legend -> DrawLatexNDC(0.5,1-0.8*offsetUp/newHeight,category.c_str());
    }

    c->SaveAs(path.c_str());
    delete c;
}

//__________________________________________________________________________________
//
void FitResults::DrawCorrelationMatrix(string path, const double corrMin){
    if(fCorrMatrix){
        fCorrMatrix->fNuisParToHide = fNuisParToHide;
        fCorrMatrix->Draw(path, corrMin);
    }
}
