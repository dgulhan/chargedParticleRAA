//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 15 12:20:04 2015 by ROOT version 6.02/10
// from TTree trackTree/v1
// found on file: /mnt/hadoop/cms/store/user/dgulhan/HiForest_pp13TeV_JetHT_Run2015D_PromptReco_v3_merged/HiForest_pp13TeV_JetHT_Run2015D_PromptReco_v3_merged_forest_1_0.root
//////////////////////////////////////////////////////////

#ifndef trackTree_h
#define trackTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
using namespace std;


// Header file for the classes stored in the TTree if any.

class trackTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nEv;
   Int_t           nLumi;
   Int_t           nBX;
   Int_t           nRun;
   Int_t           N;
   Int_t           nVtx;
   Int_t           nTrk;
   Int_t           maxPtVtx;
   Int_t           maxMultVtx;
   Int_t           nTrkVtx[40];   //[nVtx]
   Float_t         normChi2Vtx[40];   //[nVtx]
   Float_t         sumPtVtx[40];   //[nVtx]
   Float_t         xVtx[40];   //[nVtx]
   Float_t         yVtx[40];   //[nVtx]
   Float_t         zVtx[40];   //[nVtx]
   Float_t         xVtxErr[40];   //[nVtx]
   Float_t         yVtxErr[40];   //[nVtx]
   Float_t         zVtxErr[40];   //[nVtx]
   Float_t         vtxDist2D[40];   //[nVtx]
   Float_t         vtxDist2DErr[40];   //[nVtx]
   Float_t         vtxDist2DSig[40];   //[nVtx]
   Float_t         vtxDist3DErr[40];   //[nVtx]
   Float_t         vtxDist3DSig[40];   //[nVtx]
   Int_t           nVtxSim;
   Float_t         xVtxSim[1];   //[nVtxSim]
   Float_t         yVtxSim[1];   //[nVtxSim]
   Float_t         zVtxSim[1];   //[nVtxSim]
   Float_t         trkPt[1728];   //[nTrk]
   Float_t         trkPtError[1728];   //[nTrk]
   Int_t           trkNHit[1728];   //[nTrk]
   Int_t           trkNlayer[1728];   //[nTrk]
   Float_t         trkEta[1728];   //[nTrk]
   Float_t         trkPhi[1728];   //[nTrk]
   Int_t           trkCharge[1728];   //[nTrk]
   Int_t           trkNVtx[1728];   //[nTrk]
   Int_t           nTrkTimesnVtx;
   Bool_t          trkAssocVtx[69120];   //[nTrkTimesnVtx]
   Bool_t          highPurity[1728];   //[nTrk]
   Bool_t          highPuritySetWithPV[1728];   //[nTrk]
   Float_t         trkChi2[1728];   //[nTrk]
   Float_t         trkNdof[1728];   //[nTrk]
   Float_t         trkDxy1[1728];   //[nTrk]
   Float_t         trkDxyError1[1728];   //[nTrk]
   Float_t         trkDz1[1728];   //[nTrk]
   Float_t         trkDzError1[1728];   //[nTrk]
   Float_t         trkDzError2[1728];   //[nTrk]
   Float_t         trkDxy2[1728];   //[nTrk]
   Float_t         trkDz2[1728];   //[nTrk]
   Float_t         trkDxyError2[1728];   //[nTrk]
   Bool_t          trkFake[1728];   //[nTrk]
   Int_t           trkAlgo[1728];   //[nTrk]
   Int_t           trkOriginalAlgo[1728];   //[nTrk]
   Int_t           pfType[1728];   //[nTrk]
   Float_t         pfCandPt[1728];   //[nTrk]
   Float_t         pfEcal[1728];   //[nTrk]
   Float_t         pfHcal[1728];   //[nTrk]

   // List of branches
   TBranch        *b_nEv;   //!
   TBranch        *b_nLumi;   //!
   TBranch        *b_nBX;   //!
   TBranch        *b_nRun;   //!
   TBranch        *b_N;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_nTrk;   //!
   TBranch        *b_maxPtVtx;   //!
   TBranch        *b_maxMultVtx;   //!
   TBranch        *b_nTrkVtx;   //!
   TBranch        *b_normChi2Vtx;   //!
   TBranch        *b_sumPtVtx;   //!
   TBranch        *b_xVtx;   //!
   TBranch        *b_yVtx;   //!
   TBranch        *b_zVtx;   //!
   TBranch        *b_xVtxErr;   //!
   TBranch        *b_yVtxErr;   //!
   TBranch        *b_zVtxErr;   //!
   TBranch        *b_vtxDist2D;   //!
   TBranch        *b_vtxDist2DErr;   //!
   TBranch        *b_vtxDist2DSig;   //!
   TBranch        *b_vtxDist3DErr;   //!
   TBranch        *b_vtxDist3DSig;   //!
   TBranch        *b_nVtxSim;   //!
   TBranch        *b_xVtxSim;   //!
   TBranch        *b_yVtxSim;   //!
   TBranch        *b_zVtxSim;   //!
   TBranch        *b_trkPt;   //!
   TBranch        *b_trkPtError;   //!
   TBranch        *b_trkNHit;   //!
   TBranch        *b_trkNlayer;   //!
   TBranch        *b_trkEta;   //!
   TBranch        *b_trkPhi;   //!
   TBranch        *b_trkCharge;   //!
   TBranch        *b_trkNVtx;   //!
   TBranch        *b_nTrkTimesnVtx;   //!
   TBranch        *b_trkAssocVtx;   //!
   TBranch        *b_highPurity;   //!
   TBranch        *b_highPuritySetWithPV;   //!
   TBranch        *b_trkChi2;   //!
   TBranch        *b_trkNdof;   //!
   TBranch        *b_trkDxy1;   //!
   TBranch        *b_trkDxyError1;   //!
   TBranch        *b_trkDz1;   //!
   TBranch        *b_trkDzError1;   //!
   TBranch        *b_trkDzError2;   //!
   TBranch        *b_trkDxy2;   //!
   TBranch        *b_trkDz2;   //!
   TBranch        *b_trkDxyError2;   //!
   TBranch        *b_trkFake;   //!
   TBranch        *b_trkAlgo;   //!
   TBranch        *b_trkOriginalAlgo;   //!
   TBranch        *b_pfType;   //!
   TBranch        *b_pfCandPt;   //!
   TBranch        *b_pfEcal;   //!
   TBranch        *b_pfHcal;   //!

   trackTree(TString infile,TTree *tree=0);
   virtual ~trackTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Int_t    GetEntriesFast();
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   TFile *f;
};

#endif

#ifdef trackTree_cxx
trackTree::trackTree(TString infile,TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   f = TFile::Open(infile);
   tree = (TTree*) f->Get("ppTrack/trackTree");
   Init(tree);
}

trackTree::~trackTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t trackTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t trackTree::GetEntriesFast()
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntriesFast();
}

Long64_t trackTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void trackTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("nEv", &nEv, &b_nEv);
   fChain->SetBranchAddress("nLumi", &nLumi, &b_nLumi);
   fChain->SetBranchAddress("nBX", &nBX, &b_nBX);
   fChain->SetBranchAddress("nRun", &nRun, &b_nRun);
   fChain->SetBranchAddress("N", &N, &b_N);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("nTrk", &nTrk, &b_nTrk);
   fChain->SetBranchAddress("maxPtVtx", &maxPtVtx, &b_maxPtVtx);
   fChain->SetBranchAddress("maxMultVtx", &maxMultVtx, &b_maxMultVtx);
   fChain->SetBranchAddress("nTrkVtx", nTrkVtx, &b_nTrkVtx);
   fChain->SetBranchAddress("normChi2Vtx", normChi2Vtx, &b_normChi2Vtx);
   fChain->SetBranchAddress("sumPtVtx", sumPtVtx, &b_sumPtVtx);
   fChain->SetBranchAddress("xVtx", xVtx, &b_xVtx);
   fChain->SetBranchAddress("yVtx", yVtx, &b_yVtx);
   fChain->SetBranchAddress("zVtx", zVtx, &b_zVtx);
   fChain->SetBranchAddress("xVtxErr", xVtxErr, &b_xVtxErr);
   fChain->SetBranchAddress("yVtxErr", yVtxErr, &b_yVtxErr);
   fChain->SetBranchAddress("zVtxErr", zVtxErr, &b_zVtxErr);
   fChain->SetBranchAddress("vtxDist2D", vtxDist2D, &b_vtxDist2D);
   fChain->SetBranchAddress("vtxDist2DErr", vtxDist2DErr, &b_vtxDist2DErr);
   fChain->SetBranchAddress("vtxDist2DSig", vtxDist2DSig, &b_vtxDist2DSig);
//    fChain->SetBranchAddress("vtxDist2D", vtxDist2D, &b_vtxDist2D);
   fChain->SetBranchAddress("vtxDist3DErr", vtxDist3DErr, &b_vtxDist3DErr);
   fChain->SetBranchAddress("vtxDist3DSig", vtxDist3DSig, &b_vtxDist3DSig);
   fChain->SetBranchAddress("nVtxSim", &nVtxSim, &b_nVtxSim);
   fChain->SetBranchAddress("xVtxSim", &xVtxSim, &b_xVtxSim);
   fChain->SetBranchAddress("yVtxSim", &yVtxSim, &b_yVtxSim);
   fChain->SetBranchAddress("zVtxSim", &zVtxSim, &b_zVtxSim);
   fChain->SetBranchAddress("trkPt", trkPt, &b_trkPt);
   fChain->SetBranchAddress("trkPtError", trkPtError, &b_trkPtError);
   fChain->SetBranchAddress("trkNHit", trkNHit, &b_trkNHit);
   fChain->SetBranchAddress("trkNlayer", trkNlayer, &b_trkNlayer);
   fChain->SetBranchAddress("trkEta", trkEta, &b_trkEta);
   fChain->SetBranchAddress("trkPhi", trkPhi, &b_trkPhi);
   fChain->SetBranchAddress("trkCharge", trkCharge, &b_trkCharge);
   fChain->SetBranchAddress("trkNVtx", trkNVtx, &b_trkNVtx);
   fChain->SetBranchAddress("nTrkTimesnVtx", &nTrkTimesnVtx, &b_nTrkTimesnVtx);
   fChain->SetBranchAddress("trkAssocVtx", trkAssocVtx, &b_trkAssocVtx);
   fChain->SetBranchAddress("highPurity", highPurity, &b_highPurity);
   fChain->SetBranchAddress("highPuritySetWithPV", highPuritySetWithPV, &b_highPuritySetWithPV);
   fChain->SetBranchAddress("trkChi2", trkChi2, &b_trkChi2);
   fChain->SetBranchAddress("trkNdof", trkNdof, &b_trkNdof);
   fChain->SetBranchAddress("trkDxy1", trkDxy1, &b_trkDxy1);
   fChain->SetBranchAddress("trkDxyError1", trkDxyError1, &b_trkDxyError1);
   fChain->SetBranchAddress("trkDz1", trkDz1, &b_trkDz1);
   fChain->SetBranchAddress("trkDzError1", trkDzError1, &b_trkDzError1);
   fChain->SetBranchAddress("trkDzError2", trkDzError2, &b_trkDzError2);
   fChain->SetBranchAddress("trkDxy2", trkDxy2, &b_trkDxy2);
   fChain->SetBranchAddress("trkDz2", trkDz2, &b_trkDz2);
   fChain->SetBranchAddress("trkDxyError2", trkDxyError2, &b_trkDxyError2);
   fChain->SetBranchAddress("trkFake", trkFake, &b_trkFake);
   fChain->SetBranchAddress("trkAlgo", trkAlgo, &b_trkAlgo);
   fChain->SetBranchAddress("trkOriginalAlgo", trkOriginalAlgo, &b_trkOriginalAlgo);
   fChain->SetBranchAddress("pfType", pfType, &b_pfType);
   fChain->SetBranchAddress("pfCandPt", pfCandPt, &b_pfCandPt);
   fChain->SetBranchAddress("pfEcal", pfEcal, &b_pfEcal);
   fChain->SetBranchAddress("pfHcal", pfHcal, &b_pfHcal);
   Notify();
}

Bool_t trackTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void trackTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t trackTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef trackTree_cxx
