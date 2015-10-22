//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Oct 15 12:23:36 2015 by ROOT version 6.02/10
// from TTree t/ak4CalopatJets Jet Analysis Tree
// found on file: /mnt/hadoop/cms/store/user/dgulhan/HiForest_pp13TeV_JetHT_Run2015D_PromptReco_v3_merged/HiForest_pp13TeV_JetHT_Run2015D_PromptReco_v3_merged_forest_1_0.root
//////////////////////////////////////////////////////////

#ifndef t_h
#define t_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class t {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           evt;
   Float_t         b;
   Int_t           nref;
   Float_t         rawpt[71];   //[nref]
   Float_t         jtpt[71];   //[nref]
   Float_t         jteta[71];   //[nref]
   Float_t         jty[71];   //[nref]
   Float_t         jtphi[71];   //[nref]
   Float_t         jtpu[71];   //[nref]
   Float_t         jtm[71];   //[nref]
   Float_t         discr_fr01[71];   //[nref]
   Float_t         trackMax[71];   //[nref]
   Float_t         trackSum[71];   //[nref]
   Int_t           trackN[71];   //[nref]
   Float_t         trackHardSum[71];   //[nref]
   Int_t           trackHardN[71];   //[nref]
   Float_t         chargedMax[71];   //[nref]
   Float_t         chargedSum[71];   //[nref]
   Int_t           chargedN[71];   //[nref]
   Float_t         chargedHardSum[71];   //[nref]
   Int_t           chargedHardN[71];   //[nref]
   Float_t         photonMax[71];   //[nref]
   Float_t         photonSum[71];   //[nref]
   Int_t           photonN[71];   //[nref]
   Float_t         photonHardSum[71];   //[nref]
   Int_t           photonHardN[71];   //[nref]
   Float_t         neutralMax[71];   //[nref]
   Float_t         neutralSum[71];   //[nref]
   Int_t           neutralN[71];   //[nref]
   Float_t         eMax[71];   //[nref]
   Float_t         eSum[71];   //[nref]
   Int_t           eN[71];   //[nref]
   Float_t         muMax[71];   //[nref]
   Float_t         muSum[71];   //[nref]
   Int_t           muN[71];   //[nref]

   // List of branches
   TBranch        *b_evt;   //!
   TBranch        *b_b;   //!
   TBranch        *b_nref;   //!
   TBranch        *b_rawpt;   //!
   TBranch        *b_jtpt;   //!
   TBranch        *b_jteta;   //!
   TBranch        *b_jty;   //!
   TBranch        *b_jtphi;   //!
   TBranch        *b_jtpu;   //!
   TBranch        *b_jtm;   //!
   TBranch        *b_discr_fr01;   //!
   TBranch        *b_trackMax;   //!
   TBranch        *b_trackSum;   //!
   TBranch        *b_trackN;   //!
   TBranch        *b_trackHardSum;   //!
   TBranch        *b_trackHardN;   //!
   TBranch        *b_chargedMax;   //!
   TBranch        *b_chargedSum;   //!
   TBranch        *b_chargedN;   //!
   TBranch        *b_chargedHardSum;   //!
   TBranch        *b_chargedHardN;   //!
   TBranch        *b_photonMax;   //!
   TBranch        *b_photonSum;   //!
   TBranch        *b_photonN;   //!
   TBranch        *b_photonHardSum;   //!
   TBranch        *b_photonHardN;   //!
   TBranch        *b_neutralMax;   //!
   TBranch        *b_neutralSum;   //!
   TBranch        *b_neutralN;   //!
   TBranch        *b_eMax;   //!
   TBranch        *b_eSum;   //!
   TBranch        *b_eN;   //!
   TBranch        *b_muMax;   //!
   TBranch        *b_muSum;   //!
   TBranch        *b_muN;   //!

   t(TString infile,TTree *tree=0);
   virtual ~t();
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

#ifdef t_cxx
t::t(TString infile,TTree *tree) : fChain(0) 
{
   f = TFile::Open(infile);
   tree = (TTree*) f->Get("ak4CaloJetAnalyzer/t");
   Init(tree);
}

t::~t()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t t::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t t::GetEntriesFast()
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntriesFast();
}
Long64_t t::LoadTree(Long64_t entry)
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

void t::Init(TTree *tree)
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

   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("b", &b, &b_b);
   fChain->SetBranchAddress("nref", &nref, &b_nref);
   fChain->SetBranchAddress("rawpt", rawpt, &b_rawpt);
   fChain->SetBranchAddress("jtpt", jtpt, &b_jtpt);
   fChain->SetBranchAddress("jteta", jteta, &b_jteta);
   fChain->SetBranchAddress("jty", jty, &b_jty);
   fChain->SetBranchAddress("jtphi", jtphi, &b_jtphi);
   fChain->SetBranchAddress("jtpu", jtpu, &b_jtpu);
   fChain->SetBranchAddress("jtm", jtm, &b_jtm);
   fChain->SetBranchAddress("discr_fr01", discr_fr01, &b_discr_fr01);
   fChain->SetBranchAddress("trackMax", trackMax, &b_trackMax);
   fChain->SetBranchAddress("trackSum", trackSum, &b_trackSum);
   fChain->SetBranchAddress("trackN", trackN, &b_trackN);
   fChain->SetBranchAddress("trackHardSum", trackHardSum, &b_trackHardSum);
   fChain->SetBranchAddress("trackHardN", trackHardN, &b_trackHardN);
   fChain->SetBranchAddress("chargedMax", chargedMax, &b_chargedMax);
   fChain->SetBranchAddress("chargedSum", chargedSum, &b_chargedSum);
   fChain->SetBranchAddress("chargedN", chargedN, &b_chargedN);
   fChain->SetBranchAddress("chargedHardSum", chargedHardSum, &b_chargedHardSum);
   fChain->SetBranchAddress("chargedHardN", chargedHardN, &b_chargedHardN);
   fChain->SetBranchAddress("photonMax", photonMax, &b_photonMax);
   fChain->SetBranchAddress("photonSum", photonSum, &b_photonSum);
   fChain->SetBranchAddress("photonN", photonN, &b_photonN);
   fChain->SetBranchAddress("photonHardSum", photonHardSum, &b_photonHardSum);
   fChain->SetBranchAddress("photonHardN", photonHardN, &b_photonHardN);
   fChain->SetBranchAddress("neutralMax", neutralMax, &b_neutralMax);
   fChain->SetBranchAddress("neutralSum", neutralSum, &b_neutralSum);
   fChain->SetBranchAddress("neutralN", neutralN, &b_neutralN);
   fChain->SetBranchAddress("eMax", eMax, &b_eMax);
   fChain->SetBranchAddress("eSum", eSum, &b_eSum);
   fChain->SetBranchAddress("eN", eN, &b_eN);
   fChain->SetBranchAddress("muMax", muMax, &b_muMax);
   fChain->SetBranchAddress("muSum", muSum, &b_muSum);
   fChain->SetBranchAddress("muN", muN, &b_muN);
   Notify();
}

Bool_t t::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void t::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t t::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef t_cxx
