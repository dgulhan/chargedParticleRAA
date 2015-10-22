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

void drawText(const char *text, float xp, float yp, int size=22){
  TLatex *tex = new TLatex(xp,yp,text);
  tex->SetTextFont(43);
  tex->SetTextSize(size); 
  tex->SetTextColor(kBlack); 
  tex->SetLineWidth(1);
  tex->SetNDC();
  tex->Draw("same");
}

void plot(){
 TH1D::SetDefaultSumw2();
 
 float cutEta = 2.;
 
 TFile * file = new TFile(Form("hltTree20151019merged.root"));
 
 std::cout<<"parse trigger names and prescales"<<std::endl;
 std::stringstream ftriggers;
 ftriggers <<"list_triggers.txt";   
 
 std::ifstream input_file(ftriggers.str().c_str());

 std::string line;
 
 std::vector<std::string> nameHLT;//hlt paths
 std::vector<float> ptCut;
 
 int numHLT = 0; 
 while(getline(input_file,line)){
  std::stringstream line_s;
  std::string stringHLT;
  float jetPtCut;
  line_s << line;
  line_s >> stringHLT >> jetPtCut;	
  nameHLT.push_back(stringHLT);
  ptCut.push_back(jetPtCut);
  std::cout<< stringHLT << jetPtCut << std::endl;
  numHLT++;
 }
 std::cout<<1<<std::endl;
 ptCut.push_back(9999); //for the last trigger
 
 std::cout<<2<<std::endl;
 
 const int nPtBins=50;
 double ptBins[nPtBins+1];  
 
 std::cout<<3<<std::endl;  
 double ptMin = 10;
 double ptMax = 1000;
 double inix = log(ptMin)/log(10);
 double step = (log(ptMax)-log(ptMin))/(nPtBins*log(10));
 std::cout<<4<<std::endl;  

 for(int ix = 0; ix < nPtBins+1;ix++){
  ptBins[ix] = pow(10,inix);
  inix += step; 
 } 
 
 std::cout<<5<<std::endl;  

 //calculate scales taking into account total event numbers
 TTree * tree[numHLT];
 float nEvt[numHLT];
 float nEvtPrev[numHLT];
 nEvtPrev[0] = 1;
 float fraction[numHLT];
 fraction[0]=1;
 for(int iHLT = 0; iHLT < numHLT ; iHLT++){
  tree[iHLT] = (TTree*) file->Get(Form("%s_TrackTree",nameHLT[iHLT].data())); 
  nEvt[iHLT] = (float)tree[iHLT]->GetEntries(Form("jtPt1>%.1f && jtPt1<=%.1f", ptCut[iHLT], ptCut[iHLT+1]));
  if(iHLT>0){
   nEvtPrev[iHLT] = (float)tree[iHLT-1]->GetEntries(Form("jtPt1>%.1f && jtPt1<=%.1f", ptCut[iHLT], ptCut[iHLT+1]));
   fraction[iHLT] = nEvtPrev[iHLT]/nEvt[iHLT];
   std::cout<< "iHLT = "<<iHLT<<" fraction = "<<fraction[iHLT]<<std::endl;
  }
 }
 std::cout<<6<<std::endl;  

 float fractionCum[numHLT];
 fractionCum[numHLT-1] = 1;
 
 for(int iHLT = 1; iHLT < numHLT; iHLT++){
  fractionCum[numHLT-iHLT-1] = fractionCum[numHLT-iHLT]*fraction[numHLT-iHLT];
  std::cout<< "iHLT = "<<numHLT-iHLT-1<<" fractionCum = "<<fractionCum[numHLT-iHLT-1]<<" "<<fraction[numHLT-iHLT]<<std::endl;
 }
 
 std::cout<<7<<std::endl;  

 TH1F * histPt[numHLT];
 TH1F * hisPtSum = new TH1F("hisPtSum",";particle p_{T} (GeV);", nPtBins, ptBins);
 TH1F * hisJtPt[numHLT];
 TH1F * hisJtPtSum = new TH1F("hisJtPtSum",";jet p_{T} (GeV);",  nPtBins, ptBins);
 int col[] = {kOrange-3, kRed+1, kPink+9, kViolet+1, kBlue-9, kAzure+6, kBlue,  kGreen+3, kTeal+2, kYellow};
 std::cout<<8<<std::endl;  

 
 TLegend *leg = new TLegend(0.6,0.6,0.9,0.99);
 leg->SetBorderSize(0);
 leg->SetFillStyle(0);

 for(int iHLT = 0; iHLT < numHLT; iHLT++){
  histPt[iHLT] = new TH1F(Form("hist_pt_%s",nameHLT[iHLT].data()),";raw track p_{T} (GeV);", nPtBins, ptBins);
  hisJtPt[iHLT] = new TH1F(Form("hist_jtpt_%s",nameHLT[iHLT].data()),";jet p_{T} (GeV);", nPtBins, ptBins);
  
  tree[iHLT]->Draw(Form("pPt>>hist_pt_%s",nameHLT[iHLT].data()),Form("(abs(pEta)<%f  && jtPt1>%.1f && jtPt1<%.1f && pPt<jtPt1 && pVtxComp)", cutEta, ptCut[iHLT], ptCut[iHLT+1]));
  tree[iHLT]->Draw(Form("jtPt1>>hist_jtpt_%s",nameHLT[iHLT].data()),Form("jtPt1>%.1f && jtPt1<%.1f", ptCut[iHLT], ptCut[iHLT+1]));
  
  histPt[iHLT]->Scale(1./fractionCum[iHLT]);
  hisJtPt[iHLT]->Scale(1./fractionCum[iHLT]);
  
  //combine different triggers
  hisPtSum->Add(histPt[iHLT]);
  hisJtPtSum->Add(hisJtPt[iHLT]);
    
  //cosmetics
  histPt[iHLT]->SetLineColor(col[iHLT]);
  hisJtPt[iHLT]->SetFillColor(col[iHLT]);
  leg->AddEntry(histPt[iHLT],Form("%s",nameHLT[iHLT].data()),"l");
 } 
 
 //normalize with bin width
 for(int ibin = 0; ibin < hisPtSum->GetNbinsX(); ibin++){
  hisPtSum->SetBinContent(ibin+1, hisPtSum->GetBinContent(ibin+1)/hisPtSum->GetBinWidth(ibin+1));  
  hisPtSum->SetBinError(ibin+1, hisPtSum->GetBinError(ibin+1)/hisPtSum->GetBinWidth(ibin+1));  
  hisJtPtSum->SetBinContent(ibin+1, hisJtPtSum->GetBinContent(ibin+1)/hisJtPtSum->GetBinWidth(ibin+1));  
  hisJtPtSum->SetBinError(ibin+1, hisJtPtSum->GetBinError(ibin+1)/hisJtPtSum->GetBinWidth(ibin+1));  
  for(int iHLT = 0; iHLT < numHLT; iHLT++){
   histPt[iHLT]->SetBinContent(ibin+1, histPt[iHLT]->GetBinContent(ibin+1)/histPt[iHLT]->GetBinWidth(ibin+1));  
   histPt[iHLT]->SetBinError(ibin+1, histPt[iHLT]->GetBinError(ibin+1)/histPt[iHLT]->GetBinWidth(ibin+1));  
   hisJtPt[iHLT]->SetBinContent(ibin+1, hisJtPt[iHLT]->GetBinContent(ibin+1)/hisJtPt[iHLT]->GetBinWidth(ibin+1));  
   hisJtPt[iHLT]->SetBinError(ibin+1, hisJtPt[iHLT]->GetBinError(ibin+1)/hisJtPt[iHLT]->GetBinWidth(ibin+1));  
  }
 } 
 
 
 TH1F * histPtLowest =  new TH1F("histPtLowest","", nPtBins, ptBins);
 // tree[0]->Draw("pPt>>histPtLowest",Form("abs(pEta)<%.1f && pPt<jtPt1*1.2",cutEta));
 tree[0]->Draw("pPt>>histPtLowest",Form("abs(pEta)<%.1f && pPt<jtPt1 && pVtxComp", cutEta));
 histPtLowest->Scale(1./fractionCum[0]);
 for(int ibin = 0; ibin < histPtLowest->GetNbinsX(); ibin++){
  histPtLowest->SetBinContent(ibin+1, histPtLowest->GetBinContent(ibin+1)/histPtLowest->GetBinWidth(ibin+1));  
  histPtLowest->SetBinError(ibin+1, histPtLowest->GetBinError(ibin+1)/histPtLowest->GetBinWidth(ibin+1));   
 }
 
 TH1F * histJtPtLowest =  new TH1F("histJtPtLowest","", nPtBins, ptBins);
 tree[0]->Draw("jtPt1>>histJtPtLowest");
 histJtPtLowest->Scale(1./fractionCum[0]);
 for(int ibin = 0; ibin < histJtPtLowest->GetNbinsX(); ibin++){
  histJtPtLowest->SetBinContent(ibin+1, histJtPtLowest->GetBinContent(ibin+1)/histJtPtLowest->GetBinWidth(ibin+1));  
  histJtPtLowest->SetBinError(ibin+1, histJtPtLowest->GetBinError(ibin+1)/histJtPtLowest->GetBinWidth(ibin+1));   
 }
 
 //write the output
 TFile * outf = new TFile(Form("hists_pPt_doJet_merged.root"), "recreate");
 for(int iHLT = 0; iHLT < numHLT; iHLT++){
  histPt[iHLT]->Write();
  hisJtPt[iHLT]->Write();
 }
 histPtLowest->Write();
 histJtPtLowest->Write();
 hisPtSum->Write();
 TH1F * histRatLowestComb = (TH1F*)histPtLowest->Clone("histRatLowestComb");
 histRatLowestComb->Divide(hisPtSum);
 histRatLowestComb->Write(); 
 TH1F * histRatJtLowestComb = (TH1F*)histJtPtLowest->Clone("histRatJtLowestComb");
 histRatJtLowestComb->Divide(hisJtPtSum);
 histRatJtLowestComb->Write();
 // outf->Close();
 
 //plotting
 TCanvas * c1 = new TCanvas("c1","",600,600);
 TH1F * empty = new TH1F("empty",";p_{T};(dN_{trk raw}/dp_{T})", nPtBins, ptBins);
 empty->GetXaxis()->CenterTitle();
 empty->GetYaxis()->CenterTitle();
 empty->Fill(10,-9);
 empty->SetMaximum(1000000000);
 empty->SetMinimum(0.01);
 empty->Draw();
 c1->SetLogy();
 c1->SetLogx();
 for(int iHLT = 0; iHLT < numHLT; iHLT++){
  histPt[iHLT]->Draw("same hist");
 } 
 hisPtSum->SetLineWidth(2);
 hisPtSum->Draw("same hist"); 
 histPtLowest->Draw("same"); 
 histPtLowest->SetMarkerColor(col[0]); 
 histPtLowest->SetLineColor(col[0]); 
 histJtPtLowest->SetMarkerColor(col[0]); 
 histJtPtLowest->SetLineColor(col[0]); 
 leg->AddEntry(hisPtSum,"combination","l");
 leg->AddEntry(histPtLowest, (nameHLT[0]+=" no cut").data(),"p");
 leg->Draw("same");
 drawText("pp 13 TeV run D",0.2,0.9); 
 c1->RedrawAxis();
 c1->SaveAs(Form("trackCount_doJet_2_nohp.pdf"));
 c1->SaveAs(Form("trackCount_doJet_2_nohp.png"));
 
 TCanvas * c2 = new TCanvas("c2","",600,600);
 TH1F * empty2 = (TH1F*)empty->Clone("empty2");
 empty2->GetYaxis()->SetTitle("(dN_{jet}/dp_{T})");

 empty2->SetMaximum(1000000000);
 empty2->SetMinimum(0.1); empty2->Draw();
 c2->SetLogy();
 c2->SetLogx();
 for(int iHLT = 0; iHLT < numHLT; iHLT++){
  hisJtPt[iHLT]->Draw("same hist");
 } 
 hisJtPtSum->SetLineWidth(2);
 hisJtPtSum->Draw("same hist");
 histJtPtLowest->Draw("same");
 leg->Draw("same");
 drawText("pp 13 TeV run D",0.2,0.9);
 c2->RedrawAxis();
 c2->SaveAs(Form("jetCount_doJet_2.pdf"));
 c2->SaveAs(Form("jetCount_doJet_2.png"));
 
 std::cout<<1<<std::endl;
 TCanvas *c3 = new TCanvas("c3","",600,600);
 
 std::cout<<2<<std::endl;
 histRatJtLowestComb->SetMaximum(1.5);
 
 std::cout<<3<<std::endl;
 histRatJtLowestComb->SetMinimum(0.5);
 
 std::cout<<4<<std::endl;
 histRatJtLowestComb->GetYaxis()->SetTitle(Form("Ratio %s/combined", nameHLT[0].data()));
 
 std::cout<<5<<std::endl;
 histRatJtLowestComb->Draw();
 std::cout<<6<<std::endl;
 c3->SetLogx();
 c3->SaveAs("ratioJtPt.png"); 
 c3->SaveAs("ratioJtPt.pdf");
 
 TCanvas *c4 = new TCanvas("c4","",600,600);
 histRatLowestComb->SetMaximum(1.5);
 histRatLowestComb->SetMinimum(0.5); 
 histRatLowestComb->GetYaxis()->SetTitle(Form("Ratio %s/combined", nameHLT[0].data()));
 histRatLowestComb->Draw();
 
 c4->SetLogx();
 c4->SaveAs("ratioPPt.png");
 c4->SaveAs("ratioPPt.pdf");
} 
