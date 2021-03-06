
#ifndef _Run_NDTMVA__
#define _Run_NDTMVA__

#include <bhep/gstore.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <cmath>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TObjString.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TGraph.h>
#include <TCut.h>
#include <TStopwatch.h>

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/Factory.h"
#include "TMVA/MethodCuts.h"

#include <vector>
#include <CLHEP/Units/SystemOfUnits.h>

using namespace CLHEP;

class Run_NDTMVA {

 public:
  Run_NDTMVA(const bhep::gstore& store);
  ~Run_NDTMVA() {};
  void execute();
  void finalize();

 private:

  void set_MVA_methods(const bhep::gstore& store);
  void define_cuts(const bhep::gstore& store);
  void define_variables(const bhep::gstore& store);
  void define_histograms(const bhep::gstore& store);
  void CreateHistogram(std::string Key, int ntBins, double* recEdge, double* trEdge, 
		       int nbins, double min, double max);
  void FillHistogram(std::string Key, double Erec, double Etru, double qPrec, 
		     double qPtru, double cutvar, double limit, int trutype);
  void FillEventHistogram(std::string Key, double Erec, double Etru, double qPrec, 
			  double qPtru, double cutvar, double limit, std::vector<int> npart);
  // void FillHistogram(std::string Key, double Erec, double Etru, int q, 
  //	     double cutvar, double limit, int trutype);
  void plotEventTopology(int ifig, int imu, std::string method,
			 std::vector<std::vector<double> >* xpos,
			 std::vector<std::vector<double> >* ypos,
			 std::vector<std::vector<double> >* zpos);
  void define_rec_binning(const bhep::gstore& store, double* recB, double* truB);
  void SetKinematics();
  bool PassQualityCuts();
  bool fiducial(double vx, double vy, double vz);
  bool fiducial2(int nTraj);
  bool pseudoTimeCut(std::vector<double> XPos,
		     std::vector<double> YPos,
		     std::vector<double> ZPos,
		     double qP, double qPtru);
  void fill_tracks2();

 private:
  TFile* _OutFile;
  std::string _filebaseTree;
  int _firstT;
  int _lastT;

  TRandom3* rand;
  std::map<std::string,int> Use;
  std::map<std::string,TH1F*> hcut;
  std::map<std::string,TH1D*> hEff;
  std::map<std::string,TH2D*> hrecEff;
  std::map<std::string,TH3D*> hrecEff3;

  std::map<std::string,TH1D*> hNhits;
  std::map<std::string,TH1D*> hErrqP;
  std::map<std::string,TH1D*> hRp;
  std::map<std::string,TH1D*> hEngDep;
  std::map<std::string,TH1D*> hEngVar;
  std::map<std::string,TH1D*> hQt;
  std::map<std::string,TH1D*> hmeanHPP;

  std::map<std::string,TH2D*> hrecEffQES;
  std::map<std::string,TH2D*> hrecEffDIS;
  std::map<std::string,TH2D*> hrecEffnQES;
  std::map<std::string,TH2D*> hrecEffnDIS;

  std::map<std::string,TH2D*> hrecEffmuall;
  std::map<std::string,TH2D*> hrecEff1mu;
  std::map<std::string,TH2D*> hrecEff1mu1p;
  std::map<std::string,TH2D*> hrecEff1mu1pi;
  std::map<std::string,TH2D*> hrecEff1mu1pi1p;
  std::map<std::string,TH2D*> hrecEff1mu2pi;
  std::map<std::string,TH2D*> hrecEff1mueshow;
  std::map<std::string,TH2D*> hrecEff1muhshow;
  std::map<std::string,TH2D*> hrecEff1muOther;

  std::map<std::string,TH2D*> hrecEff0mu;
  std::map<std::string,TH2D*> hrecEff0mu1p;
  std::map<std::string,TH2D*> hrecEff0mu1pi;
  std::map<std::string,TH2D*> hrecEff0mu1pi1p;
  std::map<std::string,TH2D*> hrecEff0mu2pi;
  std::map<std::string,TH2D*> hrecEff0mueshow;
  std::map<std::string,TH2D*> hrecEff0muhshow;
  std::map<std::string,TH2D*> hrecEff0muOther;

  std::map<std::string,TH2D*> htimeRev;

  std::map<std::string,std::vector<TGraph*> > geventDisplayRZ;
  std::map<std::string,std::vector<TGraph*> > geventDisplayYX;

  // Data manipulation
  TMVA::Reader* _reader;
  TMVA::Reader* _piTrackreader;
  TMVA::Reader* _electronShowerreader;
  TMVA::Reader* _piShowerreader;

  // Parameters for cuts
  int         _Vtype;
  int         _doVary;
  int         _beamCharge;
  double      _maxE;
  double      _maxOver;
  double      _minNodes;
  double      _smearRoot;
  double      _smearConst;
  double      _smearPr;
  double      _smearPp;
  double      _smearPc;
  double      _smearPk;
  bool        _UseTimeCut;
  std::vector<double> _edges;
  
  // Tree Variables

  Int_t planes, nallhits, imu;
  Int_t   fit[10], no_traj, truInt;
  Int_t inmu[10], fitn[10], Q[10], hadhits;
  Double_t qP[10], errqP[10], rangqP[10], initqP[10], NeuEng, visibleEng, qPtru[10];
  Double_t visEngTraj[10], trajEngDep[10], trajLowDep[10], trajHighDep[10];
  Double_t QESEng[2], truHad, hadMom[3], hadRdirP[2][3], muXdir[10], muYdir[10];
  Double_t nonmuEDep, recShowerDir[3];
  Double_t vertX[10], vertY[10], vertZ[10], truvert[3];

  TBranch *b_XPositions;
  TBranch *b_YPositions;
  TBranch *b_ZPositions;
  TBranch *b_HTime;

  
  std::vector<std::string> _myMethodList;
  std::vector<double> _MVAcut;
  std::vector<double> _piMVAcut;
  std::vector<double> _showerMVAcut;
  
  TH1D* _xsecErr;
  TFile* _xsecF;
  // A set of fixed cuts on the analysis.
  TCut _cuts;

  std::vector<vector<double> >* _XPos;
  std::vector<vector<double> >* _YPos;
  std::vector<vector<double> >* _ZPos;
  std::vector<vector<double> >* _HTime;

  // Pointers for analysis variables
  Float_t nuEnergy;
  Float_t ErrqP;
  Float_t trHits;
  Float_t Rp;
  Float_t engfrac;
  Float_t meanDep;
  Float_t EngVar;
  Float_t recMom;
  Float_t Qt;
  Float_t meanHPP;
  Float_t showerHits;
  Float_t rngMom;
  Float_t fitted;

  double recEng;

  TChain* theTree;
  TH2D *alltracks2;
  TH1D *alltracks;
  TH1D* pcuts;
  TH1D* rcuts;
  TH1D* ntrajectories;
 

  // Output histograms
  /*
  TH1F   *histLk, *histLkD, *histLkPCA, *histLkKDE, *histLkMIX, *histPD, *histPDD;
  TH1F   *histPDPCA, *histPDEFoam, *histPDEFoamErr, *histPDEFoamSig, *histKNN, *histHm;
  TH1F   *histFi, *histFiG, *histFiB, *histLD, *histNn,*histNnbfgs,*histNnbnn;
  TH1F   *histNnC, *histNnT, *histBdt, *histBdtG, *histBdtD, *histRf, *histSVMG;
  TH1F   *histSVMP, *histSVML, *histFDAMT, *histFDAGA, *histCat, *histPBdt;

  TH2D *recEffKNN, *recEffNn, *recEffBdt;
  TH2D *recBackKNN, *recBackNn, *recBackBdt;
  TH3D *recEffKNNe, *recEffNne, *recEffBdte;
  TH3D *recBackKNNe, *recBackNne, *recBackBdte;
  
  */
};

#endif
