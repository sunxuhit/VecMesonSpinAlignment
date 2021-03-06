#include <string>
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "../../../Utility/draw.h"
// #include "../../Utility/StSpinAlignmentCons.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TBox.h"
#include "TStyle.h"
#include "TF1.h"

using namespace std;

void plotSysErrors(TGraphAsymmErrors *g_rho, int plot_color);

void plotFig8_rho00CentPhi(int energy = 4)
{
  gStyle->SetOptDate(0);
  const int style_phi_1st = 21;
  const int color_phi_1st = kGray+2;
  const int style_phi_2nd = 29;
  const int color_phi_2nd = kRed;

  const float size_marker = 1.4;
  
  int const NumBeamEnergy = 7;
  std::string const mBeamEnergy[NumBeamEnergy] = {"7GeV","11GeV","19GeV","27GeV_Run18","39GeV","62GeV","200GeV_Run14"};
  std::string const mLegEnergy[NumBeamEnergy] = {"7 GeV","11 GeV","19 GeV","27 GeV (Run18)","39 GeV","62.4 GeV","200 GeV (Run14)"};

  string inputfile = Form("/Users/xusun/WorkSpace/STAR/Data/SpinAlignment/PaperDraft/Nature/Phi/rhoCent_%s_LXaxis.root",mBeamEnergy[energy].c_str());
  TFile *File_InPut = TFile::Open(inputfile.c_str());


  string GraName_1st_stat = Form("g_rhoCent_%s_1st_stat",mBeamEnergy[energy].c_str());
  TGraphAsymmErrors *g_rhoCent_1st_stat = (TGraphAsymmErrors*)File_InPut->Get(GraName_1st_stat.c_str());

  string GraName_1st_sys = Form("g_rhoCent_%s_1st_sys",mBeamEnergy[energy].c_str());
  TGraphAsymmErrors *g_rhoCent_1st_sys = (TGraphAsymmErrors*)File_InPut->Get(GraName_1st_sys.c_str());

  string GraName_2nd_stat = Form("g_rhoCent_%s_2nd_stat",mBeamEnergy[energy].c_str());
  TGraphAsymmErrors *g_rhoCent_2nd_stat = (TGraphAsymmErrors*)File_InPut->Get(GraName_2nd_stat.c_str());

  string GraName_2nd_sys = Form("g_rhoCent_%s_2nd_sys",mBeamEnergy[energy].c_str());
  TGraphAsymmErrors *g_rhoCent_2nd_sys = (TGraphAsymmErrors*)File_InPut->Get(GraName_2nd_sys.c_str());

  TH1F *h_frame = new TH1F("h_frame","h_frame",100,0,100);
  for(int i_bin = 0; i_bin < 100; ++i_bin)
  {
    h_frame->SetBinContent(i_bin+1,-10.0);
    h_frame->SetBinError(i_bin+1,-10.0);
  }
  TCanvas *c_rho00 = new TCanvas("c_rho00","c_rho00",10,10,800,800);
  c_rho00->cd();
  c_rho00->cd()->SetLeftMargin(0.15);
  c_rho00->cd()->SetBottomMargin(0.15);
  c_rho00->cd()->SetTicks(1,1);
  c_rho00->cd()->SetGrid(0,0);
  // c_rho00->cd()->SetLogx();
  h_frame->SetTitle("");
  h_frame->SetStats(0);
  h_frame->GetXaxis()->SetRangeUser(0.0,80.0);
  h_frame->GetXaxis()->SetNdivisions(510,'N');
  h_frame->GetXaxis()->SetLabelSize(0.04);
  h_frame->GetXaxis()->SetTitle("Centrality (%)");
  h_frame->GetXaxis()->SetTitleSize(0.06);
  h_frame->GetXaxis()->SetTitleOffset(1.1);
  h_frame->GetXaxis()->CenterTitle();

  h_frame->GetYaxis()->SetRangeUser(0.22,0.44);
  // if(energy == 3) h_frame->GetYaxis()->SetRangeUser(0.301,0.44);
  // if(energy == 6) h_frame->GetYaxis()->SetRangeUser(0.22,0.4);
  h_frame->GetYaxis()->SetNdivisions(505,'N');
  // h_frame->GetYaxis()->SetTitle("#rho_{00} (Out-of-Plane)");
  h_frame->GetYaxis()->SetTitle("#rho_{00}");
  h_frame->GetYaxis()->SetTitleSize(0.06);
  h_frame->GetYaxis()->SetTitleOffset(1.1);
  h_frame->GetYaxis()->SetLabelSize(0.04);
  h_frame->GetYaxis()->CenterTitle();
  h_frame->DrawCopy("pE");
  PlotLine(0.0,80.0,1.0/3.0,1.0/3.0,1,3,2);

  Draw_TGAE_new_Symbol((TGraphAsymmErrors*)g_rhoCent_1st_stat,style_phi_1st,color_phi_1st,size_marker-0.2);
  plotSysErrors(g_rhoCent_1st_sys,color_phi_1st);

  Draw_TGAE_new_Symbol((TGraphAsymmErrors*)g_rhoCent_2nd_stat,style_phi_2nd,color_phi_2nd,size_marker+0.2);
  plotSysErrors(g_rhoCent_2nd_sys,color_phi_2nd);

  Draw_TGAE_Point_new_Symbol(10,0.42,0.0,0.0,0.0,0.0,style_phi_1st,color_phi_1st,size_marker-0.2);
  plotTopLegend((char*)"#phi (1^{st}-order EP)",13,0.4175,0.04,1,0.0,42,0);

  Draw_TGAE_Point_new_Symbol(10,0.40,0.0,0.0,0.0,0.0,style_phi_2nd,color_phi_2nd,size_marker+0.2);
  plotTopLegend((char*)"#phi (2^{nd}-order EP)",13,0.3975,0.04,1,0.0,42,0);

  string leg_energy = Form("AuAu %s (|y| < 1)", mLegEnergy[energy].c_str());
  plotTopLegend((char*)leg_energy.c_str(),0.38,0.25,0.04,1,0.0,42,1);
  plotTopLegend((char*)"1.2 < p_{T}< 5.4 GeV/c",0.38,0.20,0.04,1,0.0,42,1);

  string FigName = Form("/Users/xusun/WorkSpace/STAR/figures/SpinAlignment/PaperDraft/Nature/fig8_rhoCentPhi_%s.eps",mBeamEnergy[energy].c_str());
  c_rho00->SaveAs(FigName.c_str());
  FigName = Form("/Users/xusun/WorkSpace/STAR/figures/SpinAlignment/PaperDraft/Nature/fig8_rhoCentPhi_%s.png",mBeamEnergy[energy].c_str());
  c_rho00->SaveAs(FigName.c_str());
}

void plotSysErrors(TGraphAsymmErrors *g_rho, int plot_color)
{
  for(int i_energy = 0; i_energy < g_rho->GetN(); ++i_energy) // plot sys errors
  {
    double energy, rho;
    g_rho->GetPoint(i_energy,energy,rho);
    double err = g_rho->GetErrorYhigh(i_energy);

    PlotLine(energy-1,energy+1,rho+err,rho+err,plot_color,2,1);
    PlotLine(energy-1,energy-1,rho+err-0.001,rho+err,plot_color,2,1);
    PlotLine(energy+1,energy+1,rho+err-0.001,rho+err,plot_color,2,1);
    PlotLine(energy-1,energy+1,rho-err,rho-err,plot_color,2,1);
    PlotLine(energy-1,energy-1,rho-err+0.001,rho-err,plot_color,2,1);
    PlotLine(energy+1,energy+1,rho-err+0.001,rho-err,plot_color,2,1);
  }
}
