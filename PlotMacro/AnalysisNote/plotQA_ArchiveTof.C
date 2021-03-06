#include <string>
#include <TString.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLegend.h>
#include <map>

typedef std::map<std::string,TH1D*> TH1DMap;

using namespace std;

void plotQA_ArchiveTof(int mEnergy = 6, int mPID = 0)
{
  string const mBeamEnergy[7] = {"7GeV","11GeV","19GeV","27GeV","39GeV","62GeV","200GeV"};
  string const mParType[2] = {"Kplus","Kminus"};
  string const mParTex[2] = {"K^{+}","K^{-}"};
  string const Centrality[10] = {"70%-80%","60%-70%","50%-60%","40%-50%","30%-40%","20%-30%","10%-20%","5%-10%","0%-5%","20%-60%"}; // Centrality bin
  int const mPlotStyle[10] = {0,0,1,1,1,1,0,0,0,1};
  int const mPlotColor[10] = {0,0,kGray+3,kAzure+4,kOrange+1,kCyan+1,0,0,0,kRed};

  string inputfile = Form("/Users/xusun/WorkSpace/STAR/Data/SpinAlignment/AuAu%s/ToFMatch/Eff_%s_ToFMatch_2060.root",mBeamEnergy[mEnergy].c_str(),mBeamEnergy[mEnergy].c_str());
  cout << "open input file: " << inputfile.c_str() << endl;
  TFile *File_InPut = TFile::Open(inputfile.c_str());

  TH1DMap h_mEfficiency;
  for(int i_cent = 0; i_cent < 10; ++i_cent)
  {
    string HistName;
    HistName = Form("h_mEfficiency_%s_Cent_%d",mParType[mPID].c_str(),i_cent);
    h_mEfficiency[HistName] = (TH1D*)File_InPut->Get(HistName.c_str());
    cout << "read in => " << HistName.c_str() << endl;
    for(int i_eta = 0; i_eta < 12; ++i_eta)
    {
      HistName = Form("h_mEfficiency_%s_Cent_%d_Eta_%d",mParType[mPID].c_str(),i_cent,i_eta);
      h_mEfficiency[HistName] = (TH1D*)File_InPut->Get(HistName.c_str());
      cout << "read in => " << HistName.c_str() << endl;
      for(int i_phi = 0; i_phi < 12; ++i_phi)
      {
	HistName = Form("h_mEfficiency_%s_Cent_%d_Eta_%d_Phi_%d",mParType[mPID].c_str(),i_cent,i_eta,i_phi);
	h_mEfficiency[HistName] = (TH1D*)File_InPut->Get(HistName.c_str());
	cout << "read in => " << HistName.c_str() << endl;
      }
    }
  }

  string outputname = Form("/Users/xusun/WorkSpace/Papers/VecMesonSpinAlignment/figures/Efficiency/ToF/QAs/EffTof_AuAu%s_%s_QA.pdf",mBeamEnergy[mEnergy].c_str(),mParType[mPID].c_str());

  TCanvas *c_play = new TCanvas("c_play","c_play",10,10,800,800);
  c_play->SetLeftMargin(0.15);
  c_play->SetBottomMargin(0.15);
  c_play->SetGrid(0,0);
  c_play->SetTicks(1,1);

  string output_start = Form("/Users/xusun/WorkSpace/Papers/VecMesonSpinAlignment/figures/Efficiency/ToF/QAs/EffTof_AuAu%s_%s_QA.pdf[",mBeamEnergy[mEnergy].c_str(),mParType[mPID].c_str());
  c_play->Print(output_start.c_str()); // open pdf file

  string HistNameEff = Form("h_mEfficiency_%s_Cent_9",mParType[mPID].c_str());
  string title = Form("%s @ Au+Au %s",mParTex[mPID].c_str(),mBeamEnergy[mEnergy].c_str());
  h_mEfficiency[HistNameEff]->SetTitle(title.c_str());
  h_mEfficiency[HistNameEff]->SetStats(0);

  h_mEfficiency[HistNameEff]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  h_mEfficiency[HistNameEff]->GetXaxis()->CenterTitle();

  h_mEfficiency[HistNameEff]->GetYaxis()->SetTitle("Efficiency");
  h_mEfficiency[HistNameEff]->GetYaxis()->CenterTitle();
  h_mEfficiency[HistNameEff]->GetYaxis()->SetRangeUser(0.0,1.05);
  h_mEfficiency[HistNameEff]->SetLineColor(mPlotColor[9]);
  h_mEfficiency[HistNameEff]->SetLineWidth(4);
  h_mEfficiency[HistNameEff]->DrawCopy("HIST");

  for(int i_cent = 2; i_cent <= 5; ++i_cent)
  {
    HistNameEff = Form("h_mEfficiency_%s_Cent_%d",mParType[mPID].c_str(),i_cent);
    h_mEfficiency[HistNameEff]->SetLineColor(mPlotColor[i_cent]);
    h_mEfficiency[HistNameEff]->SetLineWidth(2);
    h_mEfficiency[HistNameEff]->DrawCopy("HIST same");
  }
  HistNameEff = Form("h_mEfficiency_%s_Cent_9",mParType[mPID].c_str());
  h_mEfficiency[HistNameEff]->DrawCopy("HIST same");

  TLegend *leg = new TLegend(0.5,0.2,0.8,0.5);
  leg->SetFillColor(10);
  leg->SetBorderSize(0);
  for(int i_cent = 0; i_cent < 10; ++i_cent)
  {
    if(mPlotStyle[i_cent] > 0)
    {
      HistNameEff = Form("h_mEfficiency_%s_Cent_%d",mParType[mPID].c_str(),i_cent);
      leg->AddEntry(h_mEfficiency[HistNameEff],Centrality[i_cent].c_str());
    }
  }
  leg->Draw("same");

  c_play->Print(outputname.c_str()); // print integrated efficiency

  TCanvas *c_diff = new TCanvas("c_diff","c_diff",10,10,1600,1200);
  c_diff->Divide(4,3);
  for(int i_pad = 0; i_pad < 12; ++i_pad)
  {
    c_diff->cd(i_pad+1)->SetLeftMargin(0.15);
    c_diff->cd(i_pad+1)->SetBottomMargin(0.15);
    c_diff->cd(i_pad+1)->SetGrid(0,0);
    c_diff->cd(i_pad+1)->SetTicks(1,1);
  }

  for(int i_eta = 0; i_eta < 12; ++i_eta)
  {
    for(int i_phi = 0; i_phi < 12; ++i_phi)
    {
      c_diff->cd(i_phi+1);
      string HistName = Form("h_mEfficiency_%s_Cent_9_Eta_%d_Phi_%d",mParType[mPID].c_str(),i_eta,i_phi);

      h_mEfficiency[HistName]->SetTitle(HistName.c_str());
      h_mEfficiency[HistName]->SetStats(0);

      h_mEfficiency[HistName]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
      h_mEfficiency[HistName]->GetXaxis()->CenterTitle();

      h_mEfficiency[HistName]->GetYaxis()->SetTitle("Efficiency");
      h_mEfficiency[HistName]->GetYaxis()->CenterTitle();
      h_mEfficiency[HistName]->GetYaxis()->SetRangeUser(0.0,1.05);
      h_mEfficiency[HistName]->SetLineColor(mPlotColor[9]);
      h_mEfficiency[HistName]->SetLineWidth(2);
      h_mEfficiency[HistName]->DrawCopy("HIST");

      for(int i_cent = 2; i_cent <= 5; ++i_cent)
      {
	HistName = Form("h_mEfficiency_%s_Cent_%d_Eta_%d_Phi_%d",mParType[mPID].c_str(),i_cent,i_eta,i_phi);
	h_mEfficiency[HistName]->SetLineColor(mPlotColor[i_cent]);
	h_mEfficiency[HistName]->SetLineWidth(1);
	h_mEfficiency[HistName]->DrawCopy("HIST same");
      }
      HistName = Form("h_mEfficiency_%s_Cent_9_Eta_%d_Phi_%d",mParType[mPID].c_str(),i_eta,i_phi);
      h_mEfficiency[HistName]->DrawCopy("HIST same");
    }
    c_diff->Update();
    c_diff->Print(outputname.c_str()); // print differential efficiency
  }

  string output_stop = Form("/Users/xusun/WorkSpace/Papers/VecMesonSpinAlignment/figures/Efficiency/ToF/QAs/EffTof_AuAu%s_%s_QA.pdf]",mBeamEnergy[mEnergy].c_str(),mParType[mPID].c_str());
  c_play->Print(output_stop.c_str()); // close pdf file
}
