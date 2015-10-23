#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


#include "TString.h"

#include "TFile.h"
#include "TTree.h"
#include "TreeSetup/hi.C"
#include "TreeSetup/nt.C"
#include "TreeSetup/t.C"
#include "TreeSetup/HiTree.C"
#include "TreeSetup/trackTree.C"

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
   int            aveNCollBin;
   int            hiBin;
   int            nPart;
   float          pPt[20000]; 
   float          pPhi[20000]; 
   float          pEta[20000]; 
   int            pChg[20000]; 
   int            pPdg[20000]; 
   bool           pVtxComp[20000]; 
   float          pres;
   float          wNColl[6];
   void reset(){
    event = -9;
    jtPt1 = -9;
    jtEta1 = -9;
    jtPhi1 = -9;
    pPtMax = -9;
    pEtaPtMax = -9;
    nColl = -9;
    aveNCollBin = -9;
    hiBin = -9;
    for(int i = 0; i < 20000; i++){
     pPt[i] = -900.;
     pPhi[i] = -900.;
     pEta[i] = -900.;
     pChg[i] = -900.;
     pPdg[i] = -900.;
     pVtxComp[i] = false;
    }
	for(int i = 0; i < 6; i++){
	 wNColl[i] = -900.;
	}
   }
   newEvent(){
    reset();
   }
   
   void setEvent(int fEvent, float fJtPt1,  float fJtEta1,  float fJtPhi1, float fPPtMax, float fPEtaPtMax, float fNColl, int fAveNCollBin, int fHiBin, float fNPart, float *fPPt, float *fPEta, float *fPPhi, int *fPChg, int *fPPdg, bool *fPVtxComp, int fPres, float *fWNColl){
    event = fEvent;
    jtPt1 = fJtPt1;
    jtEta1 = fJtEta1;
    jtPhi1 = fJtPhi1;
    pPtMax = fPPtMax;
    pEtaPtMax = fPEtaPtMax;
    nColl = fNColl;
    nPart = fNPart;
    aveNCollBin = fAveNCollBin;
    hiBin = fHiBin;
    for(int i = 0; i < nPart; i++){
     pPt[i] = fPPt[i];
     pPhi[i] = fPPhi[i];
     pEta[i] = fPEta[i];
     pChg[i] = fPChg[i];
     pPdg[i] = fPPdg[i];
     pVtxComp[i] = fPVtxComp[i];
    } 
    for(int i = 0; i < 6; i++){
     wNColl[i] = fWNColl[i];
	}
	pres = fPres;
   }
};

void makeTrackTreeByHLT(bool doGen = false){ 
 TH1D::SetDefaultSumw2();   
 TString infname="openHLT_HF.root";
 std::cout<<"file:"<<infname.Data()<<std::endl;
 
 //parse trigger names and prescales
 std::cout<<"parse trigger names and prescales"<<std::endl;
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
  std::cout<< stringHLT << stringL1 << presHLT << presL1 << cutJetTmp << JetorTrackPt << std::endl;
  numHLT++;
 }

 //define branches for each hlt tree
 std::cout<<"define branches for each hlt tree"<<std::endl;

 newEvent evnt; 
 TFile * outf = new TFile(Form("out%s",infname.Data()),"recreate");//output file
    
 TTree * hltTrackTree[numHLT];
 for(int iHLT = 0; iHLT < numHLT; iHLT++){
  hltTrackTree[iHLT] = new TTree(Form("%s_TrackTree",nameHLT[iHLT].data()),"lead jet and track info per trigger");
  hltTrackTree[iHLT]->Branch("event", &evnt.event, "event/I");
  hltTrackTree[iHLT]->Branch("jtPt1", &evnt.jtPt1, "jtPt1/F");
  hltTrackTree[iHLT]->Branch("jtEta1", &evnt.jtEta1, "jtEta1/F");
  hltTrackTree[iHLT]->Branch("jtPhi1", &evnt.jtPhi1, "jtPhi1/F");
  hltTrackTree[iHLT]->Branch("pthat", &evnt.pthat, "pthat/F");
  hltTrackTree[iHLT]->Branch("pPtMax", &evnt.pPtMax, "pPtMax/F");
  hltTrackTree[iHLT]->Branch("pEtaPtMax", &evnt.pEtaPtMax, "pEtaPtMax/F");
  if(doGen) hltTrackTree[iHLT]->Branch("nColl", &evnt.nColl, "nColl/I");
  else hltTrackTree[iHLT]->Branch("hiBin", &evnt.hiBin, "hiBin/I");
  hltTrackTree[iHLT]->Branch("aveNCollBin", &evnt.aveNCollBin, "aveNCollBin/I");
  hltTrackTree[iHLT]->Branch("nPart", &evnt.nPart, "nPart/I");
  hltTrackTree[iHLT]->Branch("pPt", evnt.pPt, "pPt[nPart]/F");
  hltTrackTree[iHLT]->Branch("pPhi", evnt.pPhi, "pPhi[nPart]/F");
  hltTrackTree[iHLT]->Branch("pEta", evnt.pEta, "pEta[nPart]/F");
  hltTrackTree[iHLT]->Branch("pVtxComp", evnt.pVtxComp, "pVtxComp[nPart]/O");
  if(doGen){
   hltTrackTree[iHLT]->Branch("pChg", evnt.pChg, "pChg[nPart]/I");
   hltTrackTree[iHLT]->Branch("pPdg", evnt.pPdg, "pPdg[nPart]/I");
   hltTrackTree[iHLT]->Branch("wNColl", evnt.wNColl, "wNColl[6]/F");
  }else{
  
  }
  hltTrackTree[iHLT]->Branch("pres", &evnt.pres, "pres/F");
 }
 
 
 //initialize tree variables
 std::cout<<"tree variables"<<std::endl;
 int fEvent = 0;
 float fJtPt1 = -99;
 float fJtEta1 = -99;
 float fJtPhi1 = -99;
 float fPPtMax = -99;
 float fPEtaPtMax = -99;
 int fNColl = -99;
 int fNPart = -99;
 int fAveNCollBin = -99;
 int fHiBin = -99;
 float fPPt[20000];
 float fPEta[20000];
 float fPPhi[20000];
 int fPChg[20000];
 int fPPdg[20000];
 bool fPVtxComp[20000];
 
 for(int ipart = 0; ipart < 20000; ipart++){
  fPPt[ipart] = -99; 
  fPEta[ipart] = -99; 
  fPPhi[ipart] = -99; 
  fPChg[ipart] = -99; 
  fPPdg[ipart] = -99; 
  fPVtxComp[ipart] = -99; 
 }
 
 int fHLT[100];
 int fPresHLT[100];
 int fL1[100];
 int fPresL1[100];
 
 for(int ipart = 0; ipart < 100; ipart++){
  fHLT[ipart] = -99; 
  fPresHLT[ipart] = -99; 
  fL1[ipart] = -99; 
  fPresL1[ipart] = -99; 
 }

 //read ncoll distributions and define centrality binning
 TFile *fileNcoll = new TFile("../centrality/Ncoll_dists_percent.root");
 TH1D *histNcoll[6];
 int aveNColl[6];
 for(int icent = 0; icent < 6; icent++){
  histNcoll[icent] = (TH1D*)fileNcoll->Get(Form("histNcollDist%d",icent));
  aveNColl[icent] = histNcoll[icent]->GetMean();
 }
 int centMin[] = {0, 10, 20, 60, 100, 140};
 int centMax[] = {10, 20, 60, 100, 140, 180};
 
 //read openhlt file
 std::cout<<"read openhlt file"<<std::endl;

 hi * fgen = new hi(infname.Data());
 nt * fdijet = new nt(infname.Data());
 t *  fjet = new t(infname.Data());
 HiTree *  fhi = new HiTree(infname.Data());
 trackTree *  ftrk = new trackTree(infname.Data());

 TFile *infile = TFile::Open(infname.Data());
 TTree* fhlt = (TTree*) infile->Get("hltbitanalysis/HltTree");
 for(int iHLT = 0; iHLT < numHLT; iHLT++ ){
  std::cout << "iHLT = " << iHLT << " numHLT = "<< numHLT<<std::endl;
  fhlt->SetBranchStatus(nameHLT[iHLT].data(), 1);
  fhlt->SetBranchAddress(nameHLT[iHLT].data(), &(fHLT[iHLT]));
  fhlt->SetBranchStatus(nameL1[iHLT].data(), 1);
  fhlt->SetBranchAddress(nameL1[iHLT].data(), &(fL1[iHLT]));
 
  //loop over events
  std::cout<<"loop over events"<<std::endl;

  int nentries = fgen->GetEntriesFast();
  // int nentries = 100;

  for(int jentry=0;jentry<nentries;jentry++){
   if((jentry%1000)==0) std::cout<<jentry<<"/"<<nentries<<std::endl;
   fhlt->GetEntry(jentry);
   // if(!fL1[iHLT] || !fHLT[iHLT]) continue;
    
   if(doGen){
    fgen->GetEntry(jentry);
    fdijet->GetEntry(jentry);
   
  
    fJtPt1 = fdijet->pt1;
    if(cutJet[iHLT] && (fJtPt1 < ptCut[iHLT])) continue;
    float fPres = (float)(prescalesHLT[iHLT]*prescalesL1[iHLT]);
   
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
     // if(!((*(fgen->chg)).at(ipart)!=0 && (pdg==211 || pdg==2212 || pdg==3312 || pdg==321|| pdg==3112 || pdg==11 || pdg==13 || pdg==3222 || pdg==3334))) continue;
     // if((*(fgen->chg)).at(ipart)==0) continue;
     fPChg[ipart] = (*(fgen->chg)).at(ipart);
     fPPdg[ipart] = (*(fgen->pdg)).at(ipart);
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
   
    evnt.setEvent(fEvent, fJtPt1,  fJtEta1,  fJtPhi1, fPPtMax, fPEtaPtMax, fNColl, fAveNCollBin, fHiBin, fNPart, fPPt, fPEta, fPPhi, fPChg, fPPdg, fPVtxComp, fPres, fWNColl);
  
    fEvent++;
    // std::cout<<evnt.beta<<std::endl;
    hltTrackTree[iHLT]->Fill();
    evnt.reset();
   }else{
    ftrk->GetEntry(jentry);
    fjet->GetEntry(jentry);
    fhi->GetEntry(jentry);
	
    std::vector<std::pair<double, std::pair<double,double> > > jets;
    int njet = 0;
    for(int ijet=0;ijet<fjet->nref;ijet++){
     if(fabs(fjet->jteta[ijet])>2) continue;
     njet++;
     jets.push_back(std::make_pair(fjet->jtpt[ijet],std::make_pair(fjet->jteta[ijet],fjet->jtphi[ijet])));
    }

    std::sort(jets.begin(),jets.end());
    if(njet > 1){
     fJtPt1 = jets[njet-1].first;
     fJtEta1 = jets[njet-1].second.first;
     fJtPhi1 = jets[njet-1].second.second;
    }
   
    if(fJtPt1 < ptCut[iHLT]) continue;
  
    int fPres = 1;
     
    fNPart = 0;
    float fPPtMax = 0;
    float fPEtaPtMax = -99;
    for(int ipart = 0; ipart < ftrk->nTrk; ipart++){
     if(!ftrk->highPurity[ipart]) continue;
     fPPt[ipart] = ftrk->trkPt[ipart];
     fPEta[ipart] = ftrk->trkEta[ipart];
     fPPhi[ipart] = ftrk->trkPhi[ipart];
     fPVtxComp[ipart] = (fabs(ftrk->trkDxy1[ipart]/ftrk->trkDxyError1[ipart])<3.0 && fabs(ftrk->trkDz1[ipart]/ftrk->trkDzError1[ipart])<3.0);
     if(fPPt[ipart] > fPPtMax){
      fPPtMax = fPPt[ipart];
      fPEtaPtMax = fPEta[ipart];
     }
     fNPart++;
    }
    fHiBin = fhi->hiBin;

    float fWNColl[6];
    for(int icent = 0; icent < 6; icent++){
     fWNColl[icent] = 1;
	 if(fHiBin>=(2*centMin[icent]) && fHiBin<(2*centMax[icent])) fAveNCollBin = aveNColl[icent];
    }     
	 
    evnt.setEvent(fEvent, fJtPt1,  fJtEta1,  fJtPhi1, fPPtMax, fPEtaPtMax, fNColl, fAveNCollBin, fHiBin, fNPart, fPPt, fPEta, fPPhi, fPChg, fPPdg, fPVtxComp, fPres, fWNColl);

    fEvent++;
    // cout<<evnt.beta<<endl;
    hltTrackTree[iHLT]->Fill();
    evnt.reset();
   }
   outf->cd();
   hltTrackTree[iHLT]->Write();
  }
  outf->cd();
  hltTrackTree[iHLT]->Write();
  std::cout<<numHLT<<std::endl;
 }
 outf->Close();
}
 
 int main(int argc, char *argv[])
{
  makeTrackTreeByHLT();
  return 0;
}