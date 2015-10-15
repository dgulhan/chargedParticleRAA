#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


#include "TString.h"

#include "TFile.h"
#include "TTree.h"
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
   int            pres;
   float          wNColl[6];
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
   void setEvent(int fEvent, float fJtPt1,  float fJtEta1,  float fJtPhi1, float fPPtMax, float fPEtaPtMax, float fNColl, float fNPart, float *fPPt, float *fPEta, float *fPPhi, int fPres, float *fWNColl){
    event = fEvent;
    jtPt1 = fJtPt1;
    jtEta1 = fJtEta1;
    jtPhi1 = fJtPhi1;
    pPtMax = fPPtMax;
    pEtaPtMax = fPEtaPtMax;
    nColl = fNColl;
    nPart = fNPart;
    for(int i = 0; i < nPart; i++){
     pPt[i] = fPPt[i];
     pPhi[i] = fPPhi[i];
     pEta[i] = fPEta[i];
    } 
    for(int i = 0; i < 6; i++){
     wNColl[i] = fWNColl[i];
	}
	pres = fPres;
   }
};

void makeTrackTreeByHLT(){ 
 TH1D::SetDefaultSumw2();   
 TString infname="HLT_20151014_PyquenUnquenched_Dijet_pthat80.root";
 cout<<"file:"<<infname.Data()<<endl;
 //parse trigger names and prescales
 cout<<"parse trigger names and prescales"<<endl;
 std::stringstream ftriggers;
 ftriggers <<"list_triggers.txt";   
 
 ifstream input_file(ftriggers.str().c_str());

 string line;
 
 std::vector<std::string> nameHLT;//hlt paths
 std::vector<std::string> nameL1;//corresponding l1 paths
 std::vector<int> prescalesHLT;
 std::vector<int> prescalesL1;
 std::vector<bool> cutJet; //if !cutjet track pt cut is applied
 std::vector<float> ptCut;
 
 int numHLT = 0;
 while(getline(input_file,line)){
  stringstream line_s;
  std::string stringHLT;
  std::string stringL1;
  int presHLT;
  int presL1;
  bool cutJetTmp;
  float JetorTrackPt;
  line_s << line;
  line_s >> stringHLT >> stringL1 >> presHLT >> presL1 >> cutJetTmp >> JetorTrackPt;	
  nameHLT.push_back(stringHLT);
  nameL1.push_back(stringL1);
  prescalesHLT.push_back(presHLT);
  prescalesL1.push_back(presL1);
  cutJet.push_back(cutJetTmp);
  ptCut.push_back(JetorTrackPt);
  cout<< stringHLT << stringL1 << presHLT << presL1 << cutJetTmp << JetorTrackPt << endl;
  numHLT++;
 }

 //define branches for each hlt tree
 cout<<"define branches for each hlt tree"<<endl;

 newEvent evnt; 
 TFile * outf = new TFile(Form("out%s",infname.Data()),"recreate");//output file
    
 TTree * hltTrackTree[numHLT];
 for(int iHLT = 0; iHLT < numHLT; iHLT++){
  hltTrackTree[iHLT] = new TTree(Form("%s_TrackTree",nameHLT[iHLT].data()),"a tree with HIJING events");
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
 cout<<"tree variables"<<endl;
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

 int fHLT[100];
 int fPresHLT[100];
 int fL1[100];
 int fPresL1[100];
 
 //read ncoll distributions
 TFile *fileNcoll = new TFile("../centrality/Ncoll_dists_percent.root");
 TH1D *histNcoll[6];
 for(int icent = 0; icent < 6; icent++){
  histNcoll[icent] = (TH1D*)fileNcoll->Get(Form("histNcollDist%d",icent));
 }
 
 //read openhlt file
 cout<<"read openhlt file"<<endl;

 hi * fgen = new hi(infname.Data());
 nt * fdijet = new nt(infname.Data());

 TFile *infile = TFile::Open(infname.Data());
 TTree* fhlt = (TTree*) infile->Get("hltbitanalysis/HltTree");
 for(int iHLT = 0; iHLT < numHLT; iHLT++ ){
  cout << "iHLT = " << iHLT << " numHLT = "<< numHLT<<endl;
  fhlt->SetBranchStatus(nameHLT[iHLT].data(), 1);
  fhlt->SetBranchAddress(nameHLT[iHLT].data(), &(fHLT[iHLT]));
  fhlt->SetBranchStatus(nameL1[iHLT].data(), 1);
  fhlt->SetBranchAddress(nameL1[iHLT].data(), &(fL1[iHLT]));
 
  //loop over events
  cout<<"loop over events"<<endl;

  int nentries = fgen->GetEntriesFast();

  for(int jentry=0;jentry<nentries;jentry++){
   if((jentry%1000)==0) std::cout<<jentry<<"/"<<nentries<<std::endl;

   fgen->GetEntry(jentry);
   fhlt->GetEntry(jentry);
   if(!fL1[iHLT] || !fHLT[iHLT]) continue;

   fdijet->GetEntry(jentry);
  
   fJtPt1 = fdijet->pt1;
   if(cutJet[iHLT] && (fJtPt1 < ptCut[iHLT])) continue;
   int fPres = prescalesHLT[iHLT]*prescalesL1[iHLT];
   
   fJtEta1 = fdijet->eta1;
   fJtPhi1 = fdijet->phi1;
   fNColl = fgen->ncoll;
   
   float fWNColl[6];
   for(int icent = 0; icent < 6; icent++){
    fWNColl[icent] = histNcoll[icent]->GetBinContent(histNcoll[icent]->FindBin(fNColl));
   }
   
   fNPart = 0;
   float fPPtMax = 0;
   float fPEtaPtMax = -99;
   for(int ipart = 0; ipart < fgen->mult; ipart++){
    // int pdg = abs(fgen->pdg[ipart]);
    // int pdg = abs(fgen->pdg[ipart]);
    int pdg = abs((*(fgen->pdg)).at(ipart));
    if(!((*(fgen->chg)).at(ipart) != 0 && (pdg==211 || pdg==2212 || pdg==3312 || pdg==321|| pdg==3112 || pdg==11 || pdg==13 || pdg==3222 || pdg==3334))) continue;
    fPPt[ipart] = (*(fgen->pt)).at(ipart);
    fPEta[ipart] = (*(fgen->eta)).at(ipart);
    fPPhi[ipart] = (*(fgen->phi)).at(ipart);
    if(fPPt[ipart] > fPPtMax){
     fPPtMax = fPPt[ipart];
     fPEtaPtMax = fPEta[ipart];
    }
    fNPart++;
   }
   if(!cutJet[iHLT] && (fPPtMax < ptCut[iHLT])) continue;
   
   evnt.setEvent(fEvent, fJtPt1,  fJtEta1,  fJtPhi1, fPPtMax, fPEtaPtMax, fNColl, fNPart, fPPt, fPEta, fPPhi, fPres, fWNColl);
  
   fEvent++;
   // cout<<evnt.beta<<endl;
   hltTrackTree[iHLT]->Fill();
   evnt.reset();
  }
  outf->cd();
  hltTrackTree[iHLT]->Write();
  cout<<numHLT<<endl;
 }
 outf->Close();
}
 
 int main(int argc, char *argv[])
{
  makeTrackTreeByHLT();
  return 0;
}