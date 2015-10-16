#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "TCanvas.h"
#include "TError.h"
#include "TPad.h"
#include "TString.h"
#include "TRandom1.h"
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TF1.h"
 
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TComplex.h"
#include "TString.h"  
#include "TCut.h"
#include "TNtuple.h"
#include "TLine.h" 

void plot(bool doJetComb = true){
 TH1D::SetDefaultSumw2();
 
 float cutEta = 2.4;
 int nFile = 3;
 int nCent = 6; 
 int centMin[] = {0, 5, 10, 30, 50, 70};
 int centMax[] = {5, 10, 30, 50, 70, 90};
 
 TFile * file[nFile];
 
 file[0] = new TFile("outHLT_20151014_HydjetMB_5020GeV.root");
 file[1] = new TFile("outPyquen_DiJet_pt40_5020GeV_GEN_SIM_PU_20150813.root");
 file[2] = new TFile("outHLT_20151014_PyquenUnquenched_Dijet_pthat80.root");

 float ptCutMC[] = {0, 50, 90, 999};
 
  //parse trigger names and prescales
 std::cout<<"parse trigger names and prescales"<<std::endl;
 std::stringstream ftriggers;
 ftriggers <<"list_test.txt";   
 
 std::ifstream input_file(ftriggers.str().c_str());

 std::string line;
 
 std::vector<std::string> nameHLT;//hlt paths
 std::vector<std::string> nameL1;//corresponding l1 paths
 std::vector<int> prescalesHLT;
 std::vector<int> prescalesL1;
 std::vector<float> ptCut;
 
 int numHLT = 0;
 while(getline(input_file,line)){
  std::stringstream line_s;
  std::string stringHLT;
  std::string stringL1;
  int presHLT;
  int presL1;
  bool cutJetTmp;
  float JetorTrackPt;
  line_s << line;
  line_s >> stringHLT >> stringL1 >> presHLT >> presL1 >> cutJetTmp >> JetorTrackPt;	
  if((doJetComb && cutJetTmp) || (!doJetComb && !cutJetTmp)){
   nameHLT.push_back(stringHLT);
   nameL1.push_back(stringL1);
   prescalesHLT.push_back(presHLT);
   prescalesL1.push_back(presL1);
   ptCut.push_back(JetorTrackPt);
   numHLT++;
  }
 }
 ptCut.push_back(999); //for the last trigger
 
 TFile * fileForStats[nFile];
 TTree * treeJet[nFile];
 TTree * treeGen[nFile];
 fileForStats[0] = new TFile("HLT_20151014_HydjetMB_5020GeV.root");
 fileForStats[1] = new TFile("Pyquen_DiJet_pt40_5020GeV_GEN_SIM_PU_20150813.root");
 fileForStats[2] = new TFile("HLT_20151014_PyquenUnquenched_Dijet_pthat80.root");

 for(int iFile = 0; iFile < nFile; iFile++){
  treeJet[iFile] = (TTree*) fileForStats[iFile]->Get("dijet/nt");
  treeGen[iFile] = (TTree*) fileForStats[iFile]->Get("HiGenParticleAna/hi");
  treeJet[iFile]->AddFriend(treeGen[iFile]);
 }
 
 //calculate fractions for matching the samples from different files, pthat 40 has no ncoll weighting
 int iFile = 0;
 float fraction[numHLT];
 float cumFraction[numHLT];
 fraction[0] = 1;
 cumFraction[0] = 1;
 bool isFrom40[numHLT];
 
 for(int iHLT = 1; iHLT < numHLT; iHLT++){
  if(ptCut[iHLT-1] > ptCutMC[iFile+1]) iFile++; 
  isFrom40[iHLT] = false;
  if(iFile!=1) fraction[iHLT] = (float)treeJet[iFile]->GetEntries(Form("pt1>%.1f", ptCut[iHLT]))/((float)treeJet[iFile]->GetEntries(Form("pt1>%.1f", ptCut[iHLT-1])));
  else{
   fraction[iHLT] = ((float)(treeJet[iFile]->GetEntries(Form("ncoll*(pt1>%.1f)", ptCut[iHLT]))))/((float)(treeJet[iFile]->GetEntries(Form("ncoll*(pt1>%.1f)", ptCut[iHLT-1]))));
   isFrom40[iHLT] = true;
  }
  std::cout<< nameHLT[iHLT].data() << " fraction = " << fraction[iHLT] << " iFile = "<< iFile << " pt " << ptCut[iHLT] << " " << ptCut[iHLT-1] << std::endl;
  cumFraction[iHLT] = fraction[iHLT]*cumFraction[iHLT-1];
 }
 
 
 //calculate scales taking into account total event numbers
 TTree * tree[numHLT];
 iFile = 0;
 float scale[numHLT];
 scale[0] = 1;
 for(int iHLT = 0; iHLT < numHLT; iHLT++){
  if(ptCut[iHLT] > ptCutMC[iFile+1]) iFile++; 
  tree[iHLT] = (TTree*) file[iFile]->Get(Form("%s_TrackTree",nameHLT[iHLT].data()));  
  
  if(iHLT > 0){
   float fractionTmp;
   if(isFrom40[iHLT]) fractionTmp = ((float)(tree[iHLT]->GetEntries("nColl*(jtPt1>0)")))/((float)(tree[0]->GetEntries()));
   else fractionTmp = ((float)(tree[iHLT]->GetEntries()))/((float)(tree[0]->GetEntries()));
   scale[iHLT] = cumFraction[iHLT]/fractionTmp;
  }
 }
 float scaleOverall = 24000000000./((float)(tree[0]->GetEntries())); //scale MB events to the number of total interactions

 TH1F * hist_pt[numHLT];
 TH1F * hist_pt_centbinned[numHLT][nCent];
 iFile = 0;
 int col[] = {kOrange-3, kRed+1, kPink+9, kViolet+1, kBlue, kAzure+6, kTeal+2, kYellow};
 
 const int nPtBins=15;
 double ptBins[nPtBins+1];  
   
 double ptMin = 0.5;
 double ptMax = 300;
 double inix = log(ptMin)/log(10);
 double step = (log(ptMax)-log(ptMin))/(nPtBins*log(10));

 for(int ix = 0; ix < nPtBins+1;ix++){
  ptBins[ix] = pow(10,inix);
  inix += step; 
 } 
 
 for(int iHLT = 0; iHLT < numHLT; iHLT++){
  if(ptCut[iHLT] > ptCutMC[iFile+1]) iFile++; 
  hist_pt[iHLT] = new TH1F(Form("hist_pt_%s",nameHLT[iHLT].data()),";particle p_{T} (GeV);", nPtBins, ptBins);
  tree[iHLT]->Draw(Form("pPt>>hist_pt_%s",nameHLT[iHLT].data()),Form("(abs(pEta)<%f  && jtPt1<%.1f)", cutEta, ptCut[iHLT+1]));
  float nEvents = ((float)tree[iHLT]->GetEntries(Form("jtPt1 < %.1f",ptCut[iHLT+1])));
  hist_pt[iHLT]->Scale((scaleOverall*scale[iHLT])/(nEvents*((float)(prescalesHLT[iHLT]*prescalesL1[iHLT]))));
  // hist_pt[iHLT]->SetFillColor(col[iHLT]);
  hist_pt[iHLT]->SetLineColor(col[iHLT]);
  std::cout<< scaleOverall << " "<< scale[iHLT] << " " << nEvents << " " << prescalesHLT[iHLT] << " " <<  prescalesL1[iHLT] <<std::endl;
  for(int iCent = 0; iCent < nCent; iCent++){ 
   hist_pt_centbinned[iHLT][iCent] = new TH1F(Form("hist_pt_%s_%d_%d",nameHLT[iHLT].data(),centMin[iCent],centMax[iCent]),";particle p_{T};", nPtBins, ptBins);
   // tree[iHLT]->Draw(Form("pPt>>hist_pt_%s_%d_%d",nameHLT[iHLT].data(),centMin[iCent],centMax[iCent]),Form("wNColl[%d]*(abs(pEta)<%f  && jtPt1<%.1f)",iCent, cutEta, ptCut[iHLT+1]));	
   tree[iHLT]->Draw(Form("pPt>>hist_pt_%s_%d_%d",nameHLT[iHLT].data(),centMin[iCent],centMax[iCent]),Form("(abs(pEta)<%f  && jtPt1<%.1f)",iCent, cutEta, ptCut[iHLT+1]));	
  }
 }
 
 TFile * outf = new TFile(Form("hists_pPt_doJet%d.root", doJetComb), "recreate");
 for(int iHLT = 0; iHLT < numHLT; iHLT++){
  hist_pt[iHLT]->Write();
 }
 outf->Close();
 
 TCanvas * c1 = new TCanvas("c1","",600,600);
 TH1F * empty = new TH1F("empty",";p_{T};(dN_{particle}/dp_{T})", nPtBins, ptBins);
 empty->GetXaxis()->CenterTitle();
 empty->GetYaxis()->CenterTitle();
 empty->Fill(10,-9);
 empty->SetMinimum(0.);
 empty->SetMaximum(100000);
 empty->SetMinimum(1);
 empty->Draw();
 c1->SetLogy();
 c1->SetLogx();
 for(int iHLT = 0; iHLT < numHLT; iHLT++){
  hist_pt[iHLT]->Draw("same hist");
 } 
 c1->SaveAs(Form("trackCount_doJet%d.pdf", doJetComb));
 c1->SaveAs(Form("trackCount_doJet%d.png", doJetComb));
}

int main(int argc, char *argv[])
{
  plot(atoi(argv[1]));
  return 0;
}