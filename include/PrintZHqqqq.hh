#ifndef _PrintZHqqqq_hh_
#define _PrintZHqqqq_hh_

//#include <RConfigure.h>
#include <string>
#include <iostream>
#include <fstream>
#include <marlin/Processor.h>
#include <TNtuple.h>
#include <TObject.h>
#include <vector>

#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/ReconstructedParticleImpl.h>
#include <EVENT/MCParticle.h>
#include <UTIL/LCRelationNavigator.h>


class TTree;

class PrintZHqqqq  : public marlin::Processor
{
  public:

    Processor*  newProcessor() { return new PrintZHqqqq ; }

    PrintZHqqqq();

    ~PrintZHqqqq() {};

    void init();

    //   void processRunHeader( LCRunHeader* run) { }

    void processEvent( LCEvent * evtP );

    void end();

  protected:

    float getConeEnergy( ReconstructedParticle* pfo, LCCollection* _pfoCol) ;

    std::string _treeFileName;
    std::string _treeName;
    std::string _colName;
    std::string _colAdcVals;

    TFile *tree_file;

    int _overwrite;
    TTree *_outputEvt;
    TTree *_outputMCP;
    TTree *_outputPFO;

    TH1D *h_mjj_reco;
    TH1D *h_mlv_reco;
    TH1D *h_mlvg_reco;
    TH1D *h_mjj_truth;
    TH1D *h_mlv_truth;
    TH1D *h_mlvg_truth;




    int EventIndex;
    unsigned int _eventNr;
    int _PID, _GenStatus, _SimStatus, _parentnum, _daughternum, _Type, _nMCP, _nSelMCP, _nPFOs;
    float _mass, _Charge, _energy, _Px, _Py, _Pz;
    float _Posx, _Posy, _Posz, _Vex_x, _Vex_y, _Vex_z;
    int _hasISR;

    float _TPhotonE;
    int _nTPhoton;


    std::vector<Float_t> v_TPhotonE;
    std::vector<Float_t> v_TPhotonPx;
    std::vector<Float_t> v_TPhotonPy;
    std::vector<Float_t> v_TPhotonPz;

    std::vector<Float_t> v_TPhotonEta;
    std::vector<Float_t> v_TPhotonY;
    std::vector<Float_t> v_TPhotonTheta;
    std::vector<Float_t> v_TPhotonPhi;

    std::vector<Float_t> v_TQuarkE;
    std::vector<Float_t> v_TQuarkPx;
    std::vector<Float_t> v_TQuarkPy;
    std::vector<Float_t> v_TQuarkPz;
    std::vector<Float_t> v_TQuarkP;
    std::vector<Float_t> v_TQuarkPt;


    std::vector<Float_t> v_TQuarkEta;
    std::vector<Float_t> v_TQuarkY;
    std::vector<Float_t> v_TQuarkTheta;
    std::vector<Float_t> v_TQuarkPhi;
    std::vector<Int_t>   v_TQuarkPID;
    std::vector<Float_t> v_TQuarkVTXX;
    std::vector<Float_t> v_TQuarkVTXY;
    std::vector<Float_t> v_TQuarkVTXZ;
    std::vector<Float_t> v_TQuarkEndPX;
    std::vector<Float_t> v_TQuarkEndPY;
    std::vector<Float_t> v_TQuarkEndPZ;


    std::vector<Float_t> v_TLeptonE;
    std::vector<Float_t> v_TLeptonPx;
    std::vector<Float_t> v_TLeptonPy;
    std::vector<Float_t> v_TLeptonPz;

    std::vector<Float_t> v_TLeptonEta;
    std::vector<Float_t> v_TLeptonY;
    std::vector<Float_t> v_TLeptonTheta;
    std::vector<Float_t> v_TLeptonPhi;
    std::vector<Int_t> v_TLeptonPID;
    std::vector<Float_t> v_TLeptonVTXX;
    std::vector<Float_t> v_TLeptonVTXY;
    std::vector<Float_t> v_TLeptonVTXZ;
    std::vector<Float_t> v_TLeptonEndPX;
    std::vector<Float_t> v_TLeptonEndPY;
    std::vector<Float_t> v_TLeptonEndPZ;

    int nTFNeu;
    std::vector<Float_t> v_TFNeuE;
    std::vector<Float_t> v_TFNeuPx;
    std::vector<Float_t> v_TFNeuPy;
    std::vector<Float_t> v_TFNeuPz;
    std::vector<Float_t> v_TFNeuPt;

    std::vector<Float_t> v_TFNeuEta;
    std::vector<Float_t> v_TFNeuY;
    std::vector<Float_t> v_TFNeuTheta;
    std::vector<Float_t> v_TFNeuPhi;
    std::vector<Int_t>   v_TFNeuPID;
    std::vector<Int_t>   v_TFNeuMomPID;
    std::vector<Float_t> v_TFNeuVTXX;
    std::vector<Float_t> v_TFNeuVTXY;
    std::vector<Float_t> v_TFNeuVTXZ;
    std::vector<Float_t> v_TFNeuEndPX;
    std::vector<Float_t> v_TFNeuEndPY;
    std::vector<Float_t> v_TFNeuEndPZ;
    std::vector<Float_t> v_TFNeuMomVTXX;
    std::vector<Float_t> v_TFNeuMomVTXY;
    std::vector<Float_t> v_TFNeuMomVTXZ;
    std::vector<Float_t> v_TFNeuMomEndPX;
    std::vector<Float_t> v_TFNeuMomEndPY;
    std::vector<Float_t> v_TFNeuMomEndPZ;

    int nMC;//add by PZ
    std::vector<Float_t> v_MCE;
    std::vector<Float_t> v_MCPx;
    std::vector<Float_t> v_MCPy;
    std::vector<Float_t> v_MCPz;
    std::vector<Float_t> v_MCPt;

    std::vector<Float_t> v_MCEta;
    std::vector<Float_t> v_MCY;
    std::vector<Float_t> v_MCTheta;
    std::vector<Float_t> v_MCPhi;
    std::vector<Float_t> v_MCCharge;
    std::vector<Int_t> v_MomMCPID;
    std::vector<Int_t> v_MCPID;


    int nhMC;//add by PZ
    std::vector<Float_t> v_hMCE;
    std::vector<Float_t> v_hMCP;
    std::vector<Float_t> v_hMCPx;
    std::vector<Float_t> v_hMCPy;
    std::vector<Float_t> v_hMCPz;
    std::vector<Float_t> v_hMCPt;

    std::vector<Float_t> v_hMCEta;
    std::vector<Float_t> v_hMCY;
    std::vector<Float_t> v_hMCTheta;
    std::vector<Float_t> v_hMCPhi;
    std::vector<Int_t> v_hGrandMomMCPID;
    std::vector<Int_t> v_hMomMCPID;
    std::vector<Int_t> v_hMCPID;


    int nTruthJet, nTJet1Component, nTJet2Component, nTJet3Component, nTJet4Component;
    std::vector<Float_t> v_TJetE;
    std::vector<Float_t> v_TJetPx;
    std::vector<Float_t> v_TJetPy;
    std::vector<Float_t> v_TJetPz;
    std::vector<Float_t> v_TJetP;
    std::vector<Float_t> v_TJetPt;

    std::vector<Float_t> v_TJetEta;
    std::vector<Float_t> v_TJetY;
    std::vector<Float_t> v_TJetTheta;
    std::vector<Float_t> v_TJetPhi;

    std::vector<Float_t> v_TJet1ComponentE;//add by PZ
    std::vector<Float_t> v_TJet1ComponentPx;
    std::vector<Float_t> v_TJet1ComponentPy;
    std::vector<Float_t> v_TJet1ComponentPz;
    std::vector<Float_t> v_TJet1ComponentP;
    std::vector<Float_t> v_TJet1ComponentPt;
    std::vector<Float_t> v_TJet1ComponentEta;
    std::vector<Float_t> v_TJet1ComponentY;
    std::vector<Float_t> v_TJet1ComponentTheta;
    std::vector<Float_t> v_TJet1ComponentPhi;
    std::vector<Int_t>   v_TJet1ComponentPID;
    std::vector<Float_t> v_TJet1ComponentGoodnessOfPID;
    std::vector<Float_t> v_TJet1ComponentCharge;
    std::vector<Float_t> v_TJet1ComponentVtx;
    std::vector<Float_t> v_TJet1ComponentVty;
    std::vector<Float_t> v_TJet1ComponentVtz;


    std::vector<Float_t> v_TJet2ComponentE;
    std::vector<Float_t> v_TJet2ComponentPx;
    std::vector<Float_t> v_TJet2ComponentPy;
    std::vector<Float_t> v_TJet2ComponentPz;
    std::vector<Float_t> v_TJet2ComponentP;
    std::vector<Float_t> v_TJet2ComponentPt;
    std::vector<Float_t> v_TJet2ComponentEta;
    std::vector<Float_t> v_TJet2ComponentY;
    std::vector<Float_t> v_TJet2ComponentTheta;
    std::vector<Float_t> v_TJet2ComponentPhi;//add by PZ
    std::vector<Int_t>   v_TJet2ComponentPID;
    std::vector<Float_t> v_TJet2ComponentGoodnessOfPID;
    std::vector<Float_t> v_TJet2ComponentCharge;
    std::vector<Float_t> v_TJet2ComponentVtx;
    std::vector<Float_t> v_TJet2ComponentVty;
    std::vector<Float_t> v_TJet2ComponentVtz;


    std::vector<Float_t> v_TJet3ComponentE;//add by PZ
    std::vector<Float_t> v_TJet3ComponentPx;
    std::vector<Float_t> v_TJet3ComponentPy;
    std::vector<Float_t> v_TJet3ComponentPz;
    std::vector<Float_t> v_TJet3ComponentP;
    std::vector<Float_t> v_TJet3ComponentPt;
    std::vector<Float_t> v_TJet3ComponentEta;
    std::vector<Float_t> v_TJet3ComponentY;
    std::vector<Float_t> v_TJet3ComponentTheta;
    std::vector<Float_t> v_TJet3ComponentPhi;
    std::vector<Int_t>   v_TJet3ComponentPID;
    std::vector<Float_t> v_TJet3ComponentGoodnessOfPID;
    std::vector<Float_t> v_TJet3ComponentCharge;
    std::vector<Float_t> v_TJet3ComponentVtx;
    std::vector<Float_t> v_TJet3ComponentVty;
    std::vector<Float_t> v_TJet3ComponentVtz;


    std::vector<Float_t> v_TJet4ComponentE;
    std::vector<Float_t> v_TJet4ComponentPx;
    std::vector<Float_t> v_TJet4ComponentPy;
    std::vector<Float_t> v_TJet4ComponentPz;
    std::vector<Float_t> v_TJet4ComponentP;
    std::vector<Float_t> v_TJet4ComponentPt;
    std::vector<Float_t> v_TJet4ComponentEta;
    std::vector<Float_t> v_TJet4ComponentY;
    std::vector<Float_t> v_TJet4ComponentTheta;
    std::vector<Float_t> v_TJet4ComponentPhi;//add by PZ
    std::vector<Int_t>   v_TJet4ComponentPID;
    std::vector<Float_t> v_TJet4ComponentGoodnessOfPID;
    std::vector<Float_t> v_TJet4ComponentCharge;
    std::vector<Float_t> v_TJet4ComponentVtx;
    std::vector<Float_t> v_TJet4ComponentVty;
    std::vector<Float_t> v_TJet4ComponentVtz;
    std::vector<Float_t> v_TRJetdE;
    std::vector<Float_t> v_TRJetAngle;
    std::vector<Float_t> v_TRJetdR;

    float TMjj_Tjet;

    int nRecoJet, nJet1Component, nJet2Component, nJet3Component, nJet4Component;//add by PZ
    std::vector<Float_t> v_JetE;
    std::vector<Float_t> v_JetPx;
    std::vector<Float_t> v_JetPy;
    std::vector<Float_t> v_JetPz;
    std::vector<Float_t> v_JetP;
    std::vector<Float_t> v_JetPt;

    std::vector<Float_t> v_JetEta;
    std::vector<Float_t> v_JetY;
    std::vector<Float_t> v_JetTheta;
    std::vector<Float_t> v_JetPhi;

    std::vector<Float_t> v_Jet_bTag_LCFIPlus;
    std::vector<Float_t> v_Jet_cTag_LCFIPlus;

    std::vector<Float_t> v_Jet1ComponentE;
    std::vector<Float_t> v_Jet1ComponentPx;
    std::vector<Float_t> v_Jet1ComponentPy;
    std::vector<Float_t> v_Jet1ComponentPz;
    std::vector<Float_t> v_Jet1ComponentP;
    std::vector<Float_t> v_Jet1ComponentPt;
    std::vector<Float_t> v_Jet1ComponentD0;
    std::vector<Float_t> v_Jet1ComponentZ0;
    std::vector<Float_t> v_Jet1ComponentR0;
    std::vector<Float_t> v_Jet1ComponentD0Sig;
    std::vector<Float_t> v_Jet1ComponentZ0Sig;
    std::vector<Float_t> v_Jet1ComponentR0Sig;
    std::vector<Float_t> v_Jet1ComponentConeE;
    std::vector<Float_t> v_Jet1ComponentEta;
    std::vector<Float_t> v_Jet1ComponentY;
    std::vector<Float_t> v_Jet1ComponentTheta;
    std::vector<Float_t> v_Jet1ComponentPhi;
    std::vector<Int_t>   v_Jet1ComponentPID;
    std::vector<Float_t> v_Jet1ComponentGoodnessOfPID;
    std::vector<Float_t> v_Jet1ComponentCharge;
    std::vector<Float_t> v_Jet1ComponentVtx;
    std::vector<Float_t> v_Jet1ComponentVty;
    std::vector<Float_t> v_Jet1ComponentVtz;


    std::vector<Float_t> v_Jet2ComponentE;
    std::vector<Float_t> v_Jet2ComponentPx;
    std::vector<Float_t> v_Jet2ComponentPy;
    std::vector<Float_t> v_Jet2ComponentPz;
    std::vector<Float_t> v_Jet2ComponentP;
    std::vector<Float_t> v_Jet2ComponentPt;
    std::vector<Float_t> v_Jet2ComponentD0;
    std::vector<Float_t> v_Jet2ComponentZ0;
    std::vector<Float_t> v_Jet2ComponentR0;
    std::vector<Float_t> v_Jet2ComponentD0Sig;
    std::vector<Float_t> v_Jet2ComponentZ0Sig;
    std::vector<Float_t> v_Jet2ComponentR0Sig;
    std::vector<Float_t> v_Jet2ComponentConeE;
    std::vector<Float_t> v_Jet2ComponentEta;
    std::vector<Float_t> v_Jet2ComponentY;
    std::vector<Float_t> v_Jet2ComponentTheta;
    std::vector<Float_t> v_Jet2ComponentPhi;//add by PZ
    std::vector<Int_t>   v_Jet2ComponentPID;
    std::vector<Float_t> v_Jet2ComponentGoodnessOfPID;
    std::vector<Float_t> v_Jet2ComponentCharge;
    std::vector<Float_t> v_Jet2ComponentVtx;
    std::vector<Float_t> v_Jet2ComponentVty;
    std::vector<Float_t> v_Jet2ComponentVtz;


    std::vector<Float_t> v_Jet3ComponentE;
    std::vector<Float_t> v_Jet3ComponentPx;
    std::vector<Float_t> v_Jet3ComponentPy;
    std::vector<Float_t> v_Jet3ComponentPz;
    std::vector<Float_t> v_Jet3ComponentP;
    std::vector<Float_t> v_Jet3ComponentPt;
    std::vector<Float_t> v_Jet3ComponentD0;
    std::vector<Float_t> v_Jet3ComponentZ0;
    std::vector<Float_t> v_Jet3ComponentR0;
    std::vector<Float_t> v_Jet3ComponentD0Sig;
    std::vector<Float_t> v_Jet3ComponentZ0Sig;
    std::vector<Float_t> v_Jet3ComponentR0Sig;
    std::vector<Float_t> v_Jet3ComponentConeE;
    std::vector<Float_t> v_Jet3ComponentEta;
    std::vector<Float_t> v_Jet3ComponentY;
    std::vector<Float_t> v_Jet3ComponentTheta;
    std::vector<Float_t> v_Jet3ComponentPhi;
    std::vector<Int_t>   v_Jet3ComponentPID;
    std::vector<Float_t> v_Jet3ComponentGoodnessOfPID;
    std::vector<Float_t> v_Jet3ComponentCharge;
    std::vector<Float_t> v_Jet3ComponentVtx;
    std::vector<Float_t> v_Jet3ComponentVty;
    std::vector<Float_t> v_Jet3ComponentVtz;


    std::vector<Float_t> v_Jet4ComponentE;
    std::vector<Float_t> v_Jet4ComponentPx;
    std::vector<Float_t> v_Jet4ComponentPy;
    std::vector<Float_t> v_Jet4ComponentPz;
    std::vector<Float_t> v_Jet4ComponentP;
    std::vector<Float_t> v_Jet4ComponentPt;
    std::vector<Float_t> v_Jet4ComponentD0;
    std::vector<Float_t> v_Jet4ComponentZ0;
    std::vector<Float_t> v_Jet4ComponentR0;
    std::vector<Float_t> v_Jet4ComponentD0Sig;
    std::vector<Float_t> v_Jet4ComponentZ0Sig;
    std::vector<Float_t> v_Jet4ComponentR0Sig;
    std::vector<Float_t> v_Jet4ComponentConeE;
    std::vector<Float_t> v_Jet4ComponentEta;
    std::vector<Float_t> v_Jet4ComponentY;
    std::vector<Float_t> v_Jet4ComponentTheta;
    std::vector<Float_t> v_Jet4ComponentPhi;//add by PZ
    std::vector<Int_t>   v_Jet4ComponentPID;
    std::vector<Float_t> v_Jet4ComponentGoodnessOfPID;
    std::vector<Float_t> v_Jet4ComponentCharge;
    std::vector<Float_t> v_Jet4ComponentVtx;
    std::vector<Float_t> v_Jet4ComponentVty;
    std::vector<Float_t> v_Jet4ComponentVtz;

    float TMjj_jet;//add by PZ

    int _nRecoPhoton;
    std::vector<Float_t> v_RecoPhotonE;
    std::vector<Float_t> v_RecoPhotonPx;
    std::vector<Float_t> v_RecoPhotonPy;
    std::vector<Float_t> v_RecoPhotonPz;

    std::vector<Float_t> v_RecoPhotonEta;
    std::vector<Float_t> v_RecoPhotonY;
    std::vector<Float_t> v_RecoPhotonTheta;
    std::vector<Float_t> v_RecoPhotonPhi;


    int _nRecoLepton;
    std::vector<Float_t> v_RecoLeptonE;
    std::vector<Float_t> v_RecoLeptonPx;
    std::vector<Float_t> v_RecoLeptonPy;
    std::vector<Float_t> v_RecoLeptonPz;

    std::vector<Float_t> v_RecoLeptonEta;
    std::vector<Float_t> v_RecoLeptonY;
    std::vector<Float_t> v_RecoLeptonTheta;
    std::vector<Float_t> v_RecoLeptonPhi;
    std::vector<Int_t> v_RecoLeptonPID;


    int _nRecoPFO;
    std::vector<Float_t> v_RecoPFOE;
    std::vector<Float_t> v_RecoPFOPx;
    std::vector<Float_t> v_RecoPFOPy;
    std::vector<Float_t> v_RecoPFOPz;
    std::vector<Float_t> v_RecoPFOD0;
    std::vector<Float_t> v_RecoPFOZ0;
    std::vector<Float_t> v_RecoPFOR0;
    std::vector<Float_t> v_RecoPFOD0Sig;
    std::vector<Float_t> v_RecoPFOZ0Sig;
    std::vector<Float_t> v_RecoPFOR0Sig;
    std::vector<Float_t> v_RecoPFOConeE;

    std::vector<Float_t> v_RecoPFOEta;
    std::vector<Float_t> v_RecoPFOY;
    std::vector<Float_t> v_RecoPFOTheta;
    std::vector<Float_t> v_RecoPFOPhi;
    std::vector<Int_t>   v_RecoPFOPID;
    std::vector<Float_t> v_RecoPFOCharge;



    float _TotalEnRecoP, _TotalEnMCP, _Mass_MCP, _Mass_RecoP;
    float _P_RecoP[3], _P_MCP[3];
    float _Plv[4], _Plp[4], _Pjj[4], _Pll[4];
    float _PjjP[4];
    float _Mjj, _Mlv, _TMjj, _TMlv, _TMlvG;

    float _MjjP, _MlvP;
    // _TMjj, _TMlv, _TMlvG;

    float _Neumass, _MlvC, _MlvC_J;
    float _Pisr[4], _Pisr_J[4];
    float _MjjReco;
    float _MjjC;

    int _LeptonType, _ISRFlag;
    int _nJets;
    int _channel;
    int _nElectronReco;
    int _nMuonReco;

    int count;
    int jet_PID;
    std::string _fileName;
    std::ostream *_output;

    std::string _histFileName;

};



#endif
