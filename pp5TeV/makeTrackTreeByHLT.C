#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


#include "TString.h"

#include "TFile.h"
#include "TTree.h"
#include "trackTree.C"
#include "t.C"
#include "getTrkCorr.h"

struct newEvent{
public :
   int            event;
   float          jtPt1;
   float          jtEta1;
   float          jtPhi1;
   float          pthat;
   float          pPtMax;
   float          pEtaPtMax;
   int            nPart;
   float          pPt[20000]; 
   float          pPhi[20000]; 
   float          pEta[20000]; 
   bool           pVtxComp[20000]; 
   float          corr[20000]; 
   float          eff[20000]; 
   float          fake[20000]; 
   float          second[20000]; 
   float          multRec[20000]; 
   int            pres;
   float          fraction;
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
     pVtxComp[i] = false;
    }
    pres = 1;
	fraction = 1;
   }
   newEvent(){
    reset();
   }
   void setEvent(int fEvent, float fJtPt1,  float fJtEta1,  float fJtPhi1, float fPPtMax, float fPEtaPtMax, float fNPart, float *fPPt, float *fPEta, float *fPPhi, float *fCorr, float *fEff, float *fFake, float *fSecond, float *fMultRec, bool *fPVtxComp, int fPres, float fFraction){   
   
    event = fEvent;
    jtPt1 = fJtPt1;
    jtEta1 = fJtEta1;
    jtPhi1 = fJtPhi1;
    pPtMax = fPPtMax;
    pEtaPtMax = fPEtaPtMax;
    nPart = fNPart;
    for(int i = 0; i < nPart; i++){
     pPt[i] = fPPt[i];
     pPhi[i] = fPPhi[i];
     pEta[i] = fPEta[i];
     pVtxComp[i] = fPVtxComp[i]; 
     corr[i] = fCorr[i]; 
     eff[i] = fEff[i]; 
     fake[i] = fFake[i]; 
     second[i] = fSecond[i]; 
     multRec[i] = fMultRec[i]; 
    } 
	pres = fPres;
	fraction = fFraction;
   }
};

void makeTrackTreeByHLT(TString dataset = "", TString infile = "", TString outfname = ""){ 
 TH1D::SetDefaultSumw2();   
 // TString infname="HiForest_1001_1_87G.root";

 TString infname = Form("%s/%s",dataset.Data(), infile.Data());
 std::cout<<"file:"<<infname.Data()<<std::endl;
 //parse trigger names and prescales
 std::cout<<"parse trigger names and prescales"<<std::endl;
 std::stringstream ftriggers;
 ftriggers <<"list_triggers.txt";   
 
 std::ifstream input_file(ftriggers.str().c_str());

 std::string line;
 
 std::vector<std::string> nameHLT;//hlt paths
 std::vector<float> ptCut;
 std::vector<float> fraction;
 
 int numHLT = 0;
 float cumFraction = 1;
 while(getline(input_file,line)){
  std::stringstream line_s;
  std::string stringHLT;
  float jetPtCut;
  float evtFraction;
  line_s << line;
  line_s >> stringHLT >> jetPtCut >> evtFraction;	
  cumFraction*=evtFraction;
  nameHLT.push_back(stringHLT);
  ptCut.push_back(jetPtCut);
  fraction.push_back(cumFraction);
  std::cout<< stringHLT << jetPtCut << evtFraction << std::endl;
  numHLT++;
 }

 //define branches for each hlt tree
 std::cout<<"define branches for each hlt tree"<<std::endl;

 newEvent evnt; 
 TFile * outf = new TFile(Form("%s",outfname.Data()),"recreate");//output file
    
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
  hltTrackTree[iHLT]->Branch("nPart", &evnt.nPart, "nPart/I");
  hltTrackTree[iHLT]->Branch("pPt", evnt.pPt, "pPt[nPart]/F");
  hltTrackTree[iHLT]->Branch("pPhi", evnt.pPhi, "pPhi[nPart]/F");
  hltTrackTree[iHLT]->Branch("pEta", evnt.pEta, "pEta[nPart]/F");
  hltTrackTree[iHLT]->Branch("pVtxComp", evnt.pVtxComp, "pVtxComp[nPart]/O");
  hltTrackTree[iHLT]->Branch("corr", evnt.corr, "corr[nPart]/F");
  hltTrackTree[iHLT]->Branch("eff", evnt.eff, "eff[nPart]/F");
  hltTrackTree[iHLT]->Branch("fake", evnt.fake, "fake[nPart]/F");
  hltTrackTree[iHLT]->Branch("second", evnt.second, "second[nPart]/F");
  hltTrackTree[iHLT]->Branch("multRec", evnt.multRec, "multRec[nPart]/F");
 }
 
 //tree variables
 std::cout<<"tree variables"<<std::endl;
 int fEvent = 0;
 float fJtPt1;
 float fJtEta1;
 float fJtPhi1;
 float fPPtMax;
 float fPEtaPtMax;
 int fNPart;
 float fPPt[20000];
 float fPEta[20000];
 float fPPhi[20000];
 float fCorr[20000];
 float fFake[20000];
 float fEff[20000];
 float fSecond[20000];
 float fMultRec[20000];
 bool fPVtxComp[20000];

 int fHLT[100];
 int fPresHLT[100];
 int fL1[100];
 int fPresL1[100];
  
 //read openhlt file
 std::cout<<"read openhlt file"<<std::endl;

 trackTree * ftrk = new trackTree(infname.Data());
 t * fjet = new t(infname.Data());

 TFile *file = TFile::Open(infname.Data());
 TTree* fhlt = (TTree*) file->Get("hltanalysis/HltTree");
 for(int iHLT = 0; iHLT < numHLT; iHLT++ ){
  std::cout << "iHLT = " << iHLT << " numHLT = "<< numHLT << std::endl;
  fhlt->SetBranchStatus(nameHLT[iHLT].data(), 1);
  fhlt->SetBranchAddress(nameHLT[iHLT].data(), &(fHLT[iHLT]));
 }
 
 TrkCorr * trkCorr = new TrkCorr();

 for(int iHLT = 0; iHLT < numHLT; iHLT++ ){

  //loop over events
  std::cout<<"loop over events"<<std::endl;

  int nentries = ftrk->GetEntriesFast();

  for(int jentry=0;jentry<nentries;jentry++){
  // for(int jentry=0;jentry<100;jentry++){
  
   fEvent = 0;
   fJtPt1 = -99;
   fJtEta1 = -99;
   fJtPhi1 = -99;
   fPPtMax = -99;
   fPEtaPtMax = -99;
   fNPart = -99;
   for(int i = 0; i < 20000; i++){
    fPPt[i] = -99;
    fPEta[i] = -99;
    fPPhi[i] = -99;
    fCorr[i] = -99;
    fFake[i] = -99;
    fEff[i] = -99;
    fSecond[i] = -99;
    fMultRec[i] = -99;
    fPVtxComp[i] = false;
   }
   
   for(int i = 0; i < 100; i++){
    fHLT[i] = 0;
    fPresHLT[i] = 0;
    fL1[i] = 0;
    fPresL1[i] = 0;
   }
   
   if((jentry%1000)==0) std::cout<<jentry<<"/"<<nentries<<std::endl;

   ftrk->GetEntry(jentry);
   fhlt->GetEntry(jentry);
   if(!fHLT[iHLT]) continue;
   bool higherThres = false;
   for(int jHLT = iHLT+1; jHLT < numHLT; jHLT++){
    if(fHLT[jHLT]){
 	 higherThres = true;
	 break;
	}
   }
   // if(higherThres) continue;
   
   fjet->GetEntry(jentry);
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
	if(fPPt[ipart]<0.5) continue;
	if(fPPt[ipart]>300) continue;
	if(fabs(fPEta[ipart])>2.4) continue;
	fCorr[ipart] = trkCorr->getTrkCorr(fPPt[ipart], fPEta[ipart], fPPhi[ipart], 0);
	fFake[ipart] = trkCorr->getTrkCorr(fPPt[ipart], fPEta[ipart], fPPhi[ipart], 1);
	fEff[ipart] = trkCorr->getTrkCorr(fPPt[ipart], fPEta[ipart], fPPhi[ipart], 2);
	fSecond[ipart] = trkCorr->getTrkCorr(fPPt[ipart], fPEta[ipart], fPPhi[ipart], 3);
	fMultRec[ipart] = trkCorr->getTrkCorr(fPPt[ipart], fPEta[ipart], fPPhi[ipart], 4);

    fPVtxComp[ipart] = (fabs(ftrk->trkDxy1[ipart]/ftrk->trkDxyError1[ipart])<3.0 && fabs(ftrk->trkDz1[ipart]/ftrk->trkDzError1[ipart])<3.0);
    if(fPPt[ipart] > fPPtMax){
     fPPtMax = fPPt[ipart];
     fPEtaPtMax = fPEta[ipart];
    }
    fNPart++;
   }
   
   evnt.setEvent(fEvent, fJtPt1,  fJtEta1,  fJtPhi1, fPPtMax, fPEtaPtMax, fNPart, fPPt, fPEta, fPPhi, fCorr, fEff, fFake, fSecond, fMultRec, fPVtxComp, fPres, fraction[iHLT]);
  
   fEvent++;
   // cout<<evnt.beta<<endl;
   hltTrackTree[iHLT]->Fill();
   evnt.reset();
  }
  outf->cd();
  hltTrackTree[iHLT]->Write();
  std::cout<<numHLT<<std::endl;
 }
 outf->Close();
}
 
 int main(int argc, char *argv[])
{ 
  makeTrackTreeByHLT(argv[1],argv[2],argv[3]);
  return 0;
}