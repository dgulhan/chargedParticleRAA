#include <iostream>
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
#include "TString.h"  
#include "TCut.h"
#include "TNtuple.h"
#include "TLine.h" 
#include "hi.C"
#include "nt.C"

struct newEvent{
public :
   int            event;
   float          jtPt1;
   float          jtEta1;
   float          jtPhi1;
   float          pthat;
   float          pPtMax;
   float          pEtaPtMax;
   int            nColl;
   int            nPart;
   float          pPt[20000]; 
   float          pPhi[20000]; 
   float          pEta[20000]; 
 
   void reset(){
    event = -9;
    jtPt1 = -9;
    jtEta1 = -9;
    jtPhi1 = -9;
    pPtMax = -9;
    pEtaPtMax = -9;
    for(int i = 0; i < 20000; i++){
     pPt[i] = -900;
     pPhi[i] = -900;
     pEta[i] = -900;
    }
   }
   newEvent(){
    reset();
   }
   void setEvent(int fEvent, float fJtPt1,  float fJtEta1,  float fJtPhi1, float fPPtMax, float fPEtaPtMax, float fNColl, float fNPart, float *fPPt, float *fPEta, float *fPPhi){
    event = fevent;
    jtPt1 = fJtPt1;
    jtEta1 = fJtEta1;
    jtPhi1 = fJtPhi1;
    pPtMax = fPPtMax;
    pEtaPtMax = fPEtaPtMax;
    nColl = fNColl;
    nPart = fNPart;
    for(int i = 0; i < nTrk; i++){
     pPt[i] = fPPt[i];
     pPhi[i] = fPPhi[i];
     pEta[i] = fPEta[i];
    } 
   }
};

void makeTrackTreeByHLT(TString infname="merged_openHLT_HLT_20151013_HydjetMB_5020GeV.root"){ 
 TH1D::SetDefaultSumw2();   
  
 //parse trigger names and prescales

 ifstream input_file("list_triggers.txt");
 string line;
 
 std::vector<std::string> nameHlt;//hlt paths
 std::vector<std::string> nameL1;//corresponding l1 paths
 std::vector<int> prescalesHLT;
 std::vector<int> prescalesL1;
 std::vector<bool> cutJet; //if !cutjet track pt cut is applied
 std::vector<float> ptCut;
 
 int numHLT = 0;
 while(getline(input_file,line)){
  stringstream line_s;
  string stringHLT;
  string stringL1;
  bool cutJetTmp;
  bool JetorTrackPt;
  line_s << line;
  line_s >> stringHLT >> stringL1 >> presHLT >> presL1 >> cutJetTmp >> JetorTrackPt;	
  nameHLT.pushback(stingHLT);
  nameL1.pushback(stingL1);
  prescalesHLT.pushback(presHLT);
  prescalesL1.pushback(presL1);
  cutJet.pushback(cutJetTmp);
  ptCut.pushback(JetorTrackPt);
  numHLT++;
 }

 //define branches for each hlt tree
 newEvent evnt; 
 TFile * outf = new TFile("out.root","recreate");//output file
    
 TTree * hltTrackTree[numHLT];
 for(int iHLT = 0; iHLT < numHLT; iHLT++){
  hltTrackTree[iHLT] = new TTree(Form("%s_TrackTree",nameHLT.data()),"a tree with HIJING events");
  hltTrackTree[iHLT]->Branch("event", &evnt.event, "event/I");
  hltTrackTree[iHLT]->Branch("jtPt1", &evnt.jtPt1, "jtPt1/F");
  hltTrackTree[iHLT]->Branch("jtEta1", &evnt.jtEta1, "jtEta1/F");
  hltTrackTree[iHLT]->Branch("jtPhi1", &evnt.jtPhi1, "jtPhi1/F");
  hltTrackTree[iHLT]->Branch("pthat", &evnt.pthat, "pthat/F");
  hltTrackTree[iHLT]->Branch("pPtMax", &evnt.pPtMax, "pPtMax/F");
  hltTrackTree[iHLT]->Branch("pEtaPtMax", &evnt.pEtaPtMax, "pEtaPtMax/F");
  hltTrackTree[iHLT]->Branch("nColl", &evnt.nColl, "nColl/I");
  hltTrackTree[iHLT]->Branch("nPart", &evnt.nPart, "nPart/I");
  hltTrackTree[iHLT]->Branch("pPt", evnt.pPt, "pPt[nPart]/F");
  hltTrackTree[iHLT]->Branch("pPhi", evnt.pPhi, "pPhi[nPart]/F");
  hltTrackTree[iHLT]->Branch("pEta", evnt.pEta, "pEta[nPart]/F");
 }
 
  // for(int iHLT = 0; iHLT < nameHlt.size(); iHLT++ ){
   // hltTrackTree->Branch(nameHlt[iHLT].data(), &evnt.HLT[iHLT].data(), (nameHlt[iHLT]+"/O").data());
   // hltTrackTree->Branch(("pres"+nameHlt[iHLT]).data(), &evnt.presHLT[iHLT],("pres"+nameHlt[iHLT]+"/I").data());
   // hltTrackTree->Branch(nameL1[iHLT].data(), &evnt.L1[iHLT].data(), (nameL1[iHLT]+"/O").data());
   // hltTrackTree->Branch(("pres"+nameL1[iHLT]).data(), &evnt.presL1[iHLT],("pres"+nameL1[iHLT]+"/I").data());
  // } 
 
  //tree variables
 int fEvent = 0;
 float fJtPt1;
 float fJtEta1;
 float fJtPhi1;
 float fPPtMax;
 float fPEtaPtMax;
 int fNColl;
 int fNPart;
 float fPPt[20000];
 float fPEta[20000];
 float fPPhi[20000];

 bool fHLT[100];
 int fPresHLT[100];
 bool fL1[100];
 int fPresL1[100];
 
 //read openhlt file
 hi * fgen = new hi(Form("%s",infname.Data()));
 nt * fdijet = new nt(Form("%s",infname.Data()));

 TFile infile = TFile::Open(infname);
 fhlt = (TTree*) infile->Get("hltbitanalysis/HltTree");
 for(int iHLT = 0; iHLT < nameHLT.size(); iHLT++ ){
  fhlt->SetBranchStatus(nameHLT[iHLT].data(), 1);
  fhlt->SetBranchAddress(nameHLT[iHLT].data(), &(fHLT[iHLT]));
  fhlt->SetBranchStatus(nameL1[iHLT].data(), 1);
  fhlt->SetBranchAddress(nameL1[iHLT].data(), &(fL1[iHLT]));
 
 
  //loop over events
  int nentries = fgen->GetEntriesFast();

  for(int jentry=0;jentry<nentries;jentry++){
   if((jentry%1000)==0) std::cout<<jentry<<"/"<<nentries<<std::endl;

   fgen->GetEntry(jentry);
   fhlt->GetEntry(jentry);
   fdijet->GetEntry(jentry);
  
   fJtPt1 = fdijet->pt1;
   if(cutJet[iHLT] && fJtPt1 < ptCut) continue;
   fJtEta1 = fdijet->eta1;
   fJtPhi1 = fdijet->phi1;
   fNColl = fgen->ncoll;
  
  
   fNPart = 0;
   float fPPtMax = 0;
   float fPEtaPtMax = -99;
   for(int ipart = 0; ipart < fgen->mult; ipart++){
    int pdg = abs(fgen->pdg[ipart]);
    if(!(fgen->cha[ipart] != 0 && (pdg==211 || pdg==2212 || pdg==3312 || pdg==321|| pdg==3112 || pdg==11 || pdg==13 || pdg==3222 || pdg==3334))) continue;
    fPPt[ipart] = fgen->pt[ipart];
    fPEta[ipart] = fgen->eta[ipart];
    fPPhi[ipart] = fgen->phi[ipart];
    if(fPPt[ipart] > fPPtMax){
     fPPtMax = fPPt[ipart];
     fPEtaPtMax = fPEta[ipart];
    }
    fNPart++;
   }
   if(!cutJet[iHLT] && fPPtMax < ptCut) continue;
   
   evnt.setEvent(fEvent, fJtPt1,  fJtEta1,  fJtPhi1, fPPtMax, fPEtaPtMax, fNColl, fNPart, fPPt, fPEta, fPPhi);
  
   fEvent++;
   // cout<<evnt.beta<<endl;
   hltTrackTree->Fill();
   evnt.reset();
  }
  outf->cd();
  hltTrackTree[iHLT]->Write();
 }
 outf->Close();
}
 
 int main(int argc, char *argv[])
{
  makeTrackTreeByHLT(atoi(argv[1]));
  return 0;
}