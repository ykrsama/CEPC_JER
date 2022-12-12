#include <PrintZHqqqq.hh>
#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/ParticleID.h>
#include <UTIL/PIDHandler.h>
//#include <LCFIPlus/lcfiplus.h>
//#include <lcfiplus.h>
#include <values.h>
#include <string>
#include <iostream>
#include <EVENT/LCFloatVec.h>
#include <EVENT/LCParameters.h>
#include <stdexcept>
#include <TFile.h>
#include <TTree.h>
#include <Rtypes.h>
#include <sstream>
#include <cmath>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <Vertex.h>

PrintZHqqqq a_PrintZHqqqq_instance;

PrintZHqqqq::PrintZHqqqq()
  : Processor("PrintZHqqqq"),
  _output(0)
{
  _description = "Print MC Truth" ;



  _treeFileName="MCTruth.root";
  registerProcessorParameter( "TreeOutputFile" ,
      "The name of the file to which the ROOT tree will be written" ,
      _treeFileName ,
      _treeFileName);


  _colName="ArborPFOs";
  registerProcessorParameter( "ParticleFlowObject" ,
      "The name of the PFOs" ,
      _colName ,
      _colName);


  _treeName="MCPart";
  registerProcessorParameter( "TreeName" ,
      "The name of the ROOT tree" ,
      _treeName ,
      _treeName);


  _overwrite=0;
  registerProcessorParameter( "OverwriteFile" ,
      "If zero an already existing file will not be overwritten." ,
      _overwrite ,
      _overwrite);

}

void PrintZHqqqq::init() {

  printParameters();

  // TFile *tree_file=new TFile(_treeFileName.c_str(),(_overwrite ? "RECREATE" : "UPDATE"));
  tree_file=new TFile(_treeFileName.c_str(),(_overwrite ? "RECREATE" : "UPDATE"));


  if (!tree_file->IsOpen()) {
    delete tree_file;
    tree_file=new TFile(_treeFileName.c_str(),"NEW");
  }

  EventIndex=0;
  _outputEvt = new TTree("Evt", "Evt");
  _outputEvt->SetAutoSave(32*1024*1024);  // autosave every 32MB
  _outputEvt->Branch("EventNr", &_eventNr, "EventNr/I");
  _outputEvt->Branch("EventIndex", &EventIndex, "EventIndex/I");
  _outputEvt->Branch("NMCP",&_nMCP,"NMCP/I");
  _outputEvt->Branch("NPFOs",&_nPFOs,"NPFOs/I");
  _outputEvt->Branch("NSelMCP", &_nSelMCP, "NSelMCP/I");
  _outputEvt->Branch("TotalEn_MCP", &_TotalEnMCP, "TotalEnMCP/F");
  _outputEvt->Branch("P_MCP", &_P_MCP, "P_MCP[3]/F");
  _outputEvt->Branch("Mass_MCP", &_Mass_MCP, "Mass_MCP/F");
  _outputEvt->Branch("HasISR", &_hasISR, "HasISR/I");
  _outputEvt->Branch("NJets", &_nJets, "NJets/I");
  _outputEvt->Branch("Channel", &_channel, "Channel/I");

  _outputEvt->Branch("NElectronReco", &_nElectronReco, "NElectronReco/I");
  _outputEvt->Branch("NMuonReco", &_nMuonReco, "NMuonReco/I");

  _outputEvt->Branch("TPhotonE", &_TPhotonE, "TPhotonE/F");
  _outputEvt->Branch("NTPhoton", &_nTPhoton, "NTPhoton/I");

  // _outputEvt->Branch("v_TPhotonE", &v_TPhotonE, "v_TPhotonE/F");
  // _outputEvt->Branch("v_TPhotonPx", &v_TPhotonPx, "v_TPhotonPx/F");
  // _outputEvt->Branch("v_TPhotonPy", &v_TPhotonPy, "v_TPhotonPy/F");
  // _outputEvt->Branch("v_TPhotonPz", &v_TPhotonPz, "v_TPhotonPz/F");
  //
  // _outputEvt->Branch("v_TPhotonEta", &v_TPhotonEta, "v_TPhotonEta/F");
  // _outputEvt->Branch("v_TPhotonTheta", &v_TPhotonTheta, "v_TPhotonTheta/F");
  // _outputEvt->Branch("v_TPhotonPhi", &v_TPhotonPhi, "v_TPhotonPhi/F");

  _outputEvt->Branch("v_TPhotonE", &v_TPhotonE );
  _outputEvt->Branch("v_TPhotonPx", &v_TPhotonPx);
  _outputEvt->Branch("v_TPhotonPy", &v_TPhotonPy);
  _outputEvt->Branch("v_TPhotonPz", &v_TPhotonPz);
  _outputEvt->Branch("v_TPhotonEta", &v_TPhotonEta);
  _outputEvt->Branch("v_TPhotonY", &v_TPhotonY);
  _outputEvt->Branch("v_TPhotonTheta", &v_TPhotonTheta);
  _outputEvt->Branch("v_TPhotonPhi", &v_TPhotonPhi);


  _outputEvt->Branch("v_TQuarkE", &v_TQuarkE );
  _outputEvt->Branch("v_TQuarkPx", &v_TQuarkPx);
  _outputEvt->Branch("v_TQuarkPy", &v_TQuarkPy);
  _outputEvt->Branch("v_TQuarkPz", &v_TQuarkPz);
  _outputEvt->Branch("v_TQuarkP", &v_TQuarkP);
  _outputEvt->Branch("v_TQuarkPt", &v_TQuarkPt);
  _outputEvt->Branch("v_TQuarkEta", &v_TQuarkEta);
  _outputEvt->Branch("v_TQuarkY", &v_TQuarkY);
  _outputEvt->Branch("v_TQuarkTheta", &v_TQuarkTheta);
  _outputEvt->Branch("v_TQuarkPhi", &v_TQuarkPhi);
  _outputEvt->Branch("v_TQuarkPID", &v_TQuarkPID);
  _outputEvt->Branch("v_TQuarkVTXX", &v_TQuarkVTXX);
  _outputEvt->Branch("v_TQuarkVTXY", &v_TQuarkVTXY);
  _outputEvt->Branch("v_TQuarkVTXZ", &v_TQuarkVTXZ);
  _outputEvt->Branch("v_TQuarkEndPX", &v_TQuarkEndPX);
  _outputEvt->Branch("v_TQuarkEndPY", &v_TQuarkEndPY);
  _outputEvt->Branch("v_TQuarkEndPZ", &v_TQuarkEndPZ);


  _outputEvt->Branch("v_TLeptonE", &v_TLeptonE );
  _outputEvt->Branch("v_TLeptonPx", &v_TLeptonPx);
  _outputEvt->Branch("v_TLeptonPy", &v_TLeptonPy);
  _outputEvt->Branch("v_TLeptonPz", &v_TLeptonPz);
  _outputEvt->Branch("v_TLeptonEta", &v_TLeptonEta);
  _outputEvt->Branch("v_TLeptonY", &v_TLeptonY);
  _outputEvt->Branch("v_TLeptonTheta", &v_TLeptonTheta);
  _outputEvt->Branch("v_TLeptonPhi", &v_TLeptonPhi);
  _outputEvt->Branch("v_TLeptonPID", &v_TLeptonPID);
  _outputEvt->Branch("v_TLeptonVTXX", &v_TLeptonVTXX);
  _outputEvt->Branch("v_TLeptonVTXY", &v_TLeptonVTXY);
  _outputEvt->Branch("v_TLeptonVTXZ", &v_TLeptonVTXZ);
  _outputEvt->Branch("v_TLeptonEndPX", &v_TLeptonEndPX);
  _outputEvt->Branch("v_TLeptonEndPY", &v_TLeptonEndPY);
  _outputEvt->Branch("v_TLeptonEndPZ", &v_TLeptonEndPZ);


  _outputEvt->Branch("nTFNeu", &nTFNeu);
  _outputEvt->Branch("v_TFNeuE", &v_TFNeuE);
  _outputEvt->Branch("v_TFNeuPx", &v_TFNeuPx);
  _outputEvt->Branch("v_TFNeuPy", &v_TFNeuPy);
  _outputEvt->Branch("v_TFNeuPz", &v_TFNeuPz);
  _outputEvt->Branch("v_TFNeuPt", &v_TFNeuPt);
  _outputEvt->Branch("v_TFNeuEta", &v_TFNeuEta);
  _outputEvt->Branch("v_TFNeuY", &v_TFNeuY);
  _outputEvt->Branch("v_TFNeuTheta", &v_TFNeuTheta);
  _outputEvt->Branch("v_TFNeuPhi", &v_TFNeuPhi);
  _outputEvt->Branch("v_TFNeuPID", &v_TFNeuPID);
  _outputEvt->Branch("v_TFNeuMomPID", &v_TFNeuMomPID);
  _outputEvt->Branch("v_TFNeuVTXX", &v_TFNeuVTXX);
  _outputEvt->Branch("v_TFNeuVTXY", &v_TFNeuVTXY);
  _outputEvt->Branch("v_TFNeuVTXZ", &v_TFNeuVTXZ);
  _outputEvt->Branch("v_TFNeuEndPX", &v_TFNeuEndPX);
  _outputEvt->Branch("v_TFNeuEndPY", &v_TFNeuEndPY);
  _outputEvt->Branch("v_TFNeuEndPZ", &v_TFNeuEndPZ);
  _outputEvt->Branch("v_TFNeuMomVTXX", &v_TFNeuMomVTXX);
  _outputEvt->Branch("v_TFNeuMomVTXY", &v_TFNeuMomVTXY);
  _outputEvt->Branch("v_TFNeuMomVTXZ", &v_TFNeuMomVTXZ);
  _outputEvt->Branch("v_TFNeuMomEndPX", &v_TFNeuMomEndPX);
  _outputEvt->Branch("v_TFNeuMomEndPY", &v_TFNeuMomEndPY);
  _outputEvt->Branch("v_TFNeuMomEndPZ", &v_TFNeuMomEndPZ);


  _outputEvt->Branch("nMC", &nMC);
  _outputEvt->Branch("v_MCE", &v_MCE);
  _outputEvt->Branch("v_MCPx", &v_MCPx);
  _outputEvt->Branch("v_MCPy", &v_MCPy);
  _outputEvt->Branch("v_MCPz", &v_MCPz);
  _outputEvt->Branch("v_MCPt", &v_MCPt);
  _outputEvt->Branch("v_MCEta", &v_MCEta);
  _outputEvt->Branch("v_MCY", &v_MCY);
  _outputEvt->Branch("v_MCTheta", &v_MCTheta);
  _outputEvt->Branch("v_MCPhi", &v_MCPhi);
  _outputEvt->Branch("v_MCCharge", &v_MCCharge);
  _outputEvt->Branch("v_MomMCPID", &v_MomMCPID);
  _outputEvt->Branch("v_MCPID", &v_MCPID);

  _outputEvt->Branch("nhMC", &nhMC);
  _outputEvt->Branch("v_hMCE", &v_hMCE );
  _outputEvt->Branch("v_hMCP", &v_hMCP);
  _outputEvt->Branch("v_hMCPx", &v_hMCPx);
  _outputEvt->Branch("v_hMCPy", &v_hMCPy);
  _outputEvt->Branch("v_hMCPz", &v_hMCPz);
  _outputEvt->Branch("v_hMCPt", &v_hMCPt);
  _outputEvt->Branch("v_hMCEta", &v_hMCEta);
  _outputEvt->Branch("v_hMCY", &v_hMCY);
  _outputEvt->Branch("v_hMCTheta", &v_hMCTheta);
  _outputEvt->Branch("v_hMCPhi", &v_hMCPhi);
  _outputEvt->Branch("v_hGrandMomMCPID", &v_hGrandMomMCPID);
  _outputEvt->Branch("v_hMomMCPID", &v_hMomMCPID);
  _outputEvt->Branch("v_hMCPID", &v_hMCPID);

  _outputEvt->Branch("nTruthJet", &nTruthJet);
  _outputEvt->Branch("v_TJetE", &v_TJetE );
  _outputEvt->Branch("v_TJetPx", &v_TJetPx);
  _outputEvt->Branch("v_TJetPy", &v_TJetPy);
  _outputEvt->Branch("v_TJetPz", &v_TJetPz);
  _outputEvt->Branch("v_TJetP", &v_TJetP);
  _outputEvt->Branch("v_TJetPt", &v_TJetPt);
  _outputEvt->Branch("v_TJetEta", &v_TJetEta);
  _outputEvt->Branch("v_TJetY", &v_TJetY);
  _outputEvt->Branch("v_TJetTheta", &v_TJetTheta);
  _outputEvt->Branch("v_TJetPhi", &v_TJetPhi);

  _outputEvt->Branch("v_Jet_bTag_LCFIPlus", &v_Jet_bTag_LCFIPlus);
  _outputEvt->Branch("v_Jet_cTag_LCFIPlus", &v_Jet_cTag_LCFIPlus);

  _outputEvt->Branch("nTJet1Component", &nTJet1Component);
  _outputEvt->Branch("v_TJet1ComponentE", &v_TJet1ComponentE);
  _outputEvt->Branch("v_TJet1ComponentPx", &v_TJet1ComponentPx);
  _outputEvt->Branch("v_TJet1ComponentPy", &v_TJet1ComponentPy);
  _outputEvt->Branch("v_TJet1ComponentPz", &v_TJet1ComponentPz);
  _outputEvt->Branch("v_TJet1ComponentP", &v_TJet1ComponentP);
  _outputEvt->Branch("v_TJet1ComponentPt", &v_TJet1ComponentPt);
  _outputEvt->Branch("v_TJet1ComponentEta", &v_TJet1ComponentEta);
  _outputEvt->Branch("v_TJet1ComponentY", &v_TJet1ComponentY);
  _outputEvt->Branch("v_TJet1ComponentTheta", &v_TJet1ComponentTheta);
  _outputEvt->Branch("v_TJet1ComponentPhi", &v_TJet1ComponentPhi);
  _outputEvt->Branch("v_TJet1ComponentPID", &v_TJet1ComponentPID);
  _outputEvt->Branch("v_TJet1ComponentGoodnessOfPID", &v_TJet1ComponentGoodnessOfPID);
  _outputEvt->Branch("v_TJet1ComponentCharge", &v_TJet1ComponentCharge);


  _outputEvt->Branch("nTJet2Component", &nTJet2Component);
  _outputEvt->Branch("v_TJet2ComponentE", &v_TJet2ComponentE);
  _outputEvt->Branch("v_TJet2ComponentPx", &v_TJet2ComponentPx);
  _outputEvt->Branch("v_TJet2ComponentPy", &v_TJet2ComponentPy);
  _outputEvt->Branch("v_TJet2ComponentPz", &v_TJet2ComponentPz);
  _outputEvt->Branch("v_TJet2ComponentP", &v_TJet2ComponentP);
  _outputEvt->Branch("v_TJet2ComponentPt", &v_TJet2ComponentPt);
  _outputEvt->Branch("v_TJet2ComponentEta", &v_TJet2ComponentEta);
  _outputEvt->Branch("v_TJet2ComponentY", &v_TJet2ComponentY);
  _outputEvt->Branch("v_TJet2ComponentTheta", &v_TJet2ComponentTheta);
  _outputEvt->Branch("v_TJet2ComponentPhi", &v_TJet2ComponentPhi);
  _outputEvt->Branch("v_TJet2ComponentPID", &v_TJet2ComponentPID);
  _outputEvt->Branch("v_TJet2ComponentGoodnessOfPID", &v_TJet2ComponentGoodnessOfPID);
  _outputEvt->Branch("v_TJet2ComponentCharge", &v_TJet2ComponentCharge);


  _outputEvt->Branch("nTJet3Component", &nTJet3Component);
  _outputEvt->Branch("v_TJet3ComponentE", &v_TJet3ComponentE);
  _outputEvt->Branch("v_TJet3ComponentPx", &v_TJet3ComponentPx);
  _outputEvt->Branch("v_TJet3ComponentPy", &v_TJet3ComponentPy);
  _outputEvt->Branch("v_TJet3ComponentPz", &v_TJet3ComponentPz);
  _outputEvt->Branch("v_TJet3ComponentP", &v_TJet3ComponentP);
  _outputEvt->Branch("v_TJet3ComponentPt", &v_TJet3ComponentPt);
  _outputEvt->Branch("v_TJet3ComponentEta", &v_TJet3ComponentEta);
  _outputEvt->Branch("v_TJet3ComponentY", &v_TJet3ComponentY);
  _outputEvt->Branch("v_TJet3ComponentTheta", &v_TJet3ComponentTheta);
  _outputEvt->Branch("v_TJet3ComponentPhi", &v_TJet3ComponentPhi);
  _outputEvt->Branch("v_TJet3ComponentPID", &v_TJet3ComponentPID);
  _outputEvt->Branch("v_TJet3ComponentGoodnessOfPID", &v_TJet3ComponentGoodnessOfPID);
  _outputEvt->Branch("v_TJet3ComponentCharge", &v_TJet3ComponentCharge);


  _outputEvt->Branch("nTJet4Component", &nTJet4Component);
  _outputEvt->Branch("v_TJet4ComponentE", &v_TJet4ComponentE);
  _outputEvt->Branch("v_TJet4ComponentPx", &v_TJet4ComponentPx);
  _outputEvt->Branch("v_TJet4ComponentPy", &v_TJet4ComponentPy);
  _outputEvt->Branch("v_TJet4ComponentPz", &v_TJet4ComponentPz);
  _outputEvt->Branch("v_TJet4ComponentP", &v_TJet4ComponentP);
  _outputEvt->Branch("v_TJet4ComponentPt", &v_TJet4ComponentPt);
  _outputEvt->Branch("v_TJet4ComponentEta", &v_TJet4ComponentEta);
  _outputEvt->Branch("v_TJet4ComponentY", &v_TJet4ComponentY);
  _outputEvt->Branch("v_TJet4ComponentTheta", &v_TJet4ComponentTheta);
  _outputEvt->Branch("v_TJet4ComponentPhi", &v_TJet4ComponentPhi);
  _outputEvt->Branch("v_TJet4ComponentPID", &v_TJet4ComponentPID);
  _outputEvt->Branch("v_TJet4ComponentGoodnessOfPID", &v_TJet4ComponentGoodnessOfPID);
  _outputEvt->Branch("v_TJet4ComponentCharge", &v_TJet4ComponentCharge);


  _outputEvt->Branch("nFastJet", &nFastJet);
  _outputEvt->Branch("v_FastJetE", &v_TJetE );
  _outputEvt->Branch("v_FastJetPx", &v_TJetPx);
  _outputEvt->Branch("v_FastJetPy", &v_TJetPy);
  _outputEvt->Branch("v_FastJetPz", &v_TJetPz);
  _outputEvt->Branch("v_FastJetP", &v_TJetP);
  _outputEvt->Branch("v_FastJetPt", &v_TJetPt);
  _outputEvt->Branch("v_FastJetEta", &v_TJetEta);
  _outputEvt->Branch("v_FastJetY", &v_TJetY);
  _outputEvt->Branch("v_FastJetTheta", &v_TJetTheta);
  _outputEvt->Branch("v_FastJetPhi", &v_TJetPhi);


  _outputEvt->Branch("v_TRJetdE", &v_TRJetdE);
  _outputEvt->Branch("v_TRJetAngle", &v_TRJetAngle);
  _outputEvt->Branch("v_TRJetdR", &v_TRJetdR);


  _outputEvt->Branch("nRecoJet", &nRecoJet);
  _outputEvt->Branch("v_JetE", &v_JetE );
  _outputEvt->Branch("v_JetPx", &v_JetPx);
  _outputEvt->Branch("v_JetPy", &v_JetPy);
  _outputEvt->Branch("v_JetPz", &v_JetPz);
  _outputEvt->Branch("v_JetP", &v_JetP);
  _outputEvt->Branch("v_JetPt", &v_JetPt);

  _outputEvt->Branch("v_JetEta", &v_JetEta);
  _outputEvt->Branch("v_JetY", &v_JetY);
  _outputEvt->Branch("v_JetTheta", &v_JetTheta);
  _outputEvt->Branch("v_JetPhi", &v_JetPhi);

  _outputEvt->Branch("v_Jet_bTag_LCFIPlus", &v_Jet_bTag_LCFIPlus);
  _outputEvt->Branch("v_Jet_cTag_LCFIPlus", &v_Jet_cTag_LCFIPlus);


  _outputEvt->Branch("nJet1Component", &nJet1Component);
  _outputEvt->Branch("v_Jet1ComponentE", &v_Jet1ComponentE);
  _outputEvt->Branch("v_Jet1ComponentPx", &v_Jet1ComponentPx);
  _outputEvt->Branch("v_Jet1ComponentPy", &v_Jet1ComponentPy);
  _outputEvt->Branch("v_Jet1ComponentPz", &v_Jet1ComponentPz);
  _outputEvt->Branch("v_Jet1ComponentP", &v_Jet1ComponentP);
  _outputEvt->Branch("v_Jet1ComponentPt", &v_Jet1ComponentPt);
  _outputEvt->Branch("v_Jet1ComponentD0", &v_Jet1ComponentD0);
  _outputEvt->Branch("v_Jet1ComponentZ0", &v_Jet1ComponentZ0);
  _outputEvt->Branch("v_Jet1ComponentR0", &v_Jet1ComponentR0);
  _outputEvt->Branch("v_Jet1ComponentD0Sig", &v_Jet1ComponentD0Sig);
  _outputEvt->Branch("v_Jet1ComponentZ0Sig", &v_Jet1ComponentZ0Sig);
  _outputEvt->Branch("v_Jet1ComponentR0Sig", &v_Jet1ComponentR0Sig);
  _outputEvt->Branch("v_Jet1ComponentConeE", &v_Jet1ComponentConeE);
  _outputEvt->Branch("v_Jet1ComponentEta", &v_Jet1ComponentEta);
  _outputEvt->Branch("v_Jet1ComponentY", &v_Jet1ComponentY);
  _outputEvt->Branch("v_Jet1ComponentTheta", &v_Jet1ComponentTheta);
  _outputEvt->Branch("v_Jet1ComponentPhi", &v_Jet1ComponentPhi);
  _outputEvt->Branch("v_Jet1ComponentPID", &v_Jet1ComponentPID);
  _outputEvt->Branch("v_Jet1ComponentGoodnessOfPID", &v_Jet1ComponentGoodnessOfPID);
  _outputEvt->Branch("v_Jet1ComponentCharge", &v_Jet1ComponentCharge);
  _outputEvt->Branch("v_Jet1ComponentVtx", &v_Jet1ComponentVtx);
  _outputEvt->Branch("v_Jet1ComponentVty", &v_Jet1ComponentVty);
  _outputEvt->Branch("v_Jet1ComponentVtz", &v_Jet1ComponentVtz);


  _outputEvt->Branch("nJet2Component", &nJet2Component);
  _outputEvt->Branch("v_Jet2ComponentE", &v_Jet2ComponentE);
  _outputEvt->Branch("v_Jet2ComponentPx", &v_Jet2ComponentPx);
  _outputEvt->Branch("v_Jet2ComponentPy", &v_Jet2ComponentPy);
  _outputEvt->Branch("v_Jet2ComponentPz", &v_Jet2ComponentPz);
  _outputEvt->Branch("v_Jet2ComponentP", &v_Jet2ComponentP);
  _outputEvt->Branch("v_Jet2ComponentPt", &v_Jet2ComponentPt);
  _outputEvt->Branch("v_Jet2ComponentD0", &v_Jet2ComponentD0);
  _outputEvt->Branch("v_Jet2ComponentZ0", &v_Jet2ComponentZ0);
  _outputEvt->Branch("v_Jet2ComponentR0", &v_Jet2ComponentR0);
  _outputEvt->Branch("v_Jet2ComponentD0Sig", &v_Jet2ComponentD0Sig);
  _outputEvt->Branch("v_Jet2ComponentZ0Sig", &v_Jet2ComponentZ0Sig);
  _outputEvt->Branch("v_Jet2ComponentR0Sig", &v_Jet2ComponentR0Sig);
  _outputEvt->Branch("v_Jet2ComponentConeE", &v_Jet2ComponentConeE);
  _outputEvt->Branch("v_Jet2ComponentEta", &v_Jet2ComponentEta);
  _outputEvt->Branch("v_Jet2ComponentY", &v_Jet2ComponentY);
  _outputEvt->Branch("v_Jet2ComponentTheta", &v_Jet2ComponentTheta);
  _outputEvt->Branch("v_Jet2ComponentPhi", &v_Jet2ComponentPhi);
  _outputEvt->Branch("v_Jet2ComponentPID", &v_Jet2ComponentPID);
  _outputEvt->Branch("v_Jet2ComponentGoodnessOfPID", &v_Jet2ComponentGoodnessOfPID);
  _outputEvt->Branch("v_Jet2ComponentCharge", &v_Jet2ComponentCharge);


  _outputEvt->Branch("nJet3Component", &nJet3Component);
  _outputEvt->Branch("v_Jet3ComponentE", &v_Jet3ComponentE);
  _outputEvt->Branch("v_Jet3ComponentPx", &v_Jet3ComponentPx);
  _outputEvt->Branch("v_Jet3ComponentPy", &v_Jet3ComponentPy);
  _outputEvt->Branch("v_Jet3ComponentPz", &v_Jet3ComponentPz);
  _outputEvt->Branch("v_Jet3ComponentP", &v_Jet3ComponentP);
  _outputEvt->Branch("v_Jet3ComponentPt", &v_Jet3ComponentPt);
  _outputEvt->Branch("v_Jet3ComponentD0", &v_Jet3ComponentD0);
  _outputEvt->Branch("v_Jet3ComponentZ0", &v_Jet3ComponentZ0);
  _outputEvt->Branch("v_Jet3ComponentR0", &v_Jet3ComponentR0);
  _outputEvt->Branch("v_Jet3ComponentD0Sig", &v_Jet3ComponentD0Sig);
  _outputEvt->Branch("v_Jet3ComponentZ0Sig", &v_Jet3ComponentZ0Sig);
  _outputEvt->Branch("v_Jet3ComponentR0Sig", &v_Jet3ComponentR0Sig);
  _outputEvt->Branch("v_Jet3ComponentConeE", &v_Jet3ComponentConeE);
  _outputEvt->Branch("v_Jet3ComponentEta", &v_Jet3ComponentEta);
  _outputEvt->Branch("v_Jet3ComponentY", &v_Jet3ComponentY);
  _outputEvt->Branch("v_Jet3ComponentTheta", &v_Jet3ComponentTheta);
  _outputEvt->Branch("v_Jet3ComponentPhi", &v_Jet3ComponentPhi);
  _outputEvt->Branch("v_Jet3ComponentPID", &v_Jet3ComponentPID);
  _outputEvt->Branch("v_Jet3ComponentGoodnessOfPID", &v_Jet3ComponentGoodnessOfPID);
  _outputEvt->Branch("v_Jet3ComponentCharge", &v_Jet3ComponentCharge);
  _outputEvt->Branch("v_Jet3ComponentVtx", &v_Jet3ComponentVtx);
  _outputEvt->Branch("v_Jet3ComponentVty", &v_Jet3ComponentVty);
  _outputEvt->Branch("v_Jet3ComponentVtz", &v_Jet3ComponentVtz);


  _outputEvt->Branch("nJet4Component", &nJet4Component);
  _outputEvt->Branch("v_Jet4ComponentE", &v_Jet4ComponentE);
  _outputEvt->Branch("v_Jet4ComponentPx", &v_Jet4ComponentPx);
  _outputEvt->Branch("v_Jet4ComponentPy", &v_Jet4ComponentPy);
  _outputEvt->Branch("v_Jet4ComponentPz", &v_Jet4ComponentPz);
  _outputEvt->Branch("v_Jet4ComponentP", &v_Jet4ComponentP);
  _outputEvt->Branch("v_Jet4ComponentPt", &v_Jet4ComponentPt);
  _outputEvt->Branch("v_Jet4ComponentD0", &v_Jet4ComponentD0);
  _outputEvt->Branch("v_Jet4ComponentZ0", &v_Jet4ComponentZ0);
  _outputEvt->Branch("v_Jet4ComponentR0", &v_Jet4ComponentR0);
  _outputEvt->Branch("v_Jet4ComponentD0Sig", &v_Jet4ComponentD0Sig);
  _outputEvt->Branch("v_Jet4ComponentZ0Sig", &v_Jet4ComponentZ0Sig);
  _outputEvt->Branch("v_Jet4ComponentR0Sig", &v_Jet4ComponentR0Sig);
  _outputEvt->Branch("v_Jet4ComponentConeE", &v_Jet4ComponentConeE);
  _outputEvt->Branch("v_Jet4ComponentEta", &v_Jet4ComponentEta);
  _outputEvt->Branch("v_Jet4ComponentY", &v_Jet4ComponentY);
  _outputEvt->Branch("v_Jet4ComponentTheta", &v_Jet4ComponentTheta);
  _outputEvt->Branch("v_Jet4ComponentPhi", &v_Jet4ComponentPhi);
  _outputEvt->Branch("v_Jet4ComponentPID", &v_Jet4ComponentPID);
  _outputEvt->Branch("v_Jet4ComponentGoodnessOfPID", &v_Jet4ComponentGoodnessOfPID);
  _outputEvt->Branch("v_Jet4ComponentCharge", &v_Jet4ComponentCharge);


  _outputEvt->Branch("TMjj_Tjet", &TMjj_Tjet);
  _outputEvt->Branch("TMjj_jet", &TMjj_jet);



  _outputEvt->Branch("NRecoPhoton", &_nRecoPhoton, "NRecoPhoton/I");


  // _outputEvt->Branch("v_RecoPhotonE", &v_RecoPhotonE, "v_RecoPhotonE/F");
  // _outputEvt->Branch("v_RecoPhotonPx", &v_RecoPhotonPx, "v_RecoPhotonPx/F");
  // _outputEvt->Branch("v_RecoPhotonPy", &v_RecoPhotonPy, "v_RecoPhotonPy/F");
  // _outputEvt->Branch("v_RecoPhotonPz", &v_RecoPhotonPz, "v_RecoPhotonPz/F");
  //
  // _outputEvt->Branch("v_RecoPhotonEta", &v_RecoPhotonEta, "v_RecoPhotonEta/F");
  // _outputEvt->Branch("v_RecoPhotonTheta", &v_RecoPhotonTheta, "v_RecoPhotonTheta/F");
  // _outputEvt->Branch("v_RecoPhotonPhi", &v_RecoPhotonPhi, "v_RecoPhotonPhi/F");
  //
  _outputEvt->Branch("v_RecoPhotonE", &v_RecoPhotonE);
  _outputEvt->Branch("v_RecoPhotonPx", &v_RecoPhotonPx);
  _outputEvt->Branch("v_RecoPhotonPy", &v_RecoPhotonPy);
  _outputEvt->Branch("v_RecoPhotonPz", &v_RecoPhotonPz);
  _outputEvt->Branch("v_RecoPhotonEta", &v_RecoPhotonEta);
  _outputEvt->Branch("v_RecoPhotonY", &v_RecoPhotonY);
  _outputEvt->Branch("v_RecoPhotonTheta", &v_RecoPhotonTheta);
  _outputEvt->Branch("v_RecoPhotonPhi", &v_RecoPhotonPhi);


  _outputEvt->Branch("NRecoLepton", &_nRecoLepton, "NRecoLepton/I");
  _outputEvt->Branch("v_RecoLeptonE", &v_RecoLeptonE );
  _outputEvt->Branch("v_RecoLeptonPx", &v_RecoLeptonPx);
  _outputEvt->Branch("v_RecoLeptonPy", &v_RecoLeptonPy);
  _outputEvt->Branch("v_RecoLeptonPz", &v_RecoLeptonPz);
  _outputEvt->Branch("v_RecoLeptonEta", &v_RecoLeptonEta);
  _outputEvt->Branch("v_RecoLeptonY", &v_RecoLeptonY);
  _outputEvt->Branch("v_RecoLeptonTheta", &v_RecoLeptonTheta);
  _outputEvt->Branch("v_RecoLeptonPhi", &v_RecoLeptonPhi);
  _outputEvt->Branch("v_RecoLeptonPID", &v_RecoLeptonPID);


  _outputEvt->Branch("NRecoPFO", &_nRecoPFO, "NRecoPFO/I");

  _outputEvt->Branch("v_RecoPFOE", &v_RecoPFOE );
  _outputEvt->Branch("v_RecoPFOPx", &v_RecoPFOPx);
  _outputEvt->Branch("v_RecoPFOPy", &v_RecoPFOPy);
  _outputEvt->Branch("v_RecoPFOPz", &v_RecoPFOPz);
  _outputEvt->Branch("v_RecoPFOD0", &v_RecoPFOD0);
  _outputEvt->Branch("v_RecoPFOZ0", &v_RecoPFOZ0);
  _outputEvt->Branch("v_RecoPFOR0", &v_RecoPFOR0);
  _outputEvt->Branch("v_RecoPFOD0Sig", &v_RecoPFOD0Sig);
  _outputEvt->Branch("v_RecoPFOZ0Sig", &v_RecoPFOZ0Sig);
  _outputEvt->Branch("v_RecoPFOR0Sig", &v_RecoPFOR0Sig);
  _outputEvt->Branch("v_RecoPFOConeE", &v_RecoPFOConeE);
  _outputEvt->Branch("v_RecoPFOEta", &v_RecoPFOEta);
  _outputEvt->Branch("v_RecoPFOY", &v_RecoPFOY);
  _outputEvt->Branch("v_RecoPFOTheta", &v_RecoPFOTheta);
  _outputEvt->Branch("v_RecoPFOPhi", &v_RecoPFOPhi);
  _outputEvt->Branch("v_RecoPFOPID", &v_RecoPFOPID);
  _outputEvt->Branch("v_RecoPFOCharge", &v_RecoPFOCharge);


  _outputEvt->Branch("TotalEn_RecoP", &_TotalEnRecoP, "TotalEnRecoP/F");
  _outputEvt->Branch("P_RecoP", &_P_RecoP, "P_RecoP[3]/F");
  _outputEvt->Branch("Mass_RecoP", &_Mass_RecoP, "Mass_RecoP/F");

  _outputEvt->Branch("TMlv", &_TMlv, "TMlv/F");
  _outputEvt->Branch("TMjj", &_TMjj, "TMjj/F");
  _outputEvt->Branch("TMlvG", &_TMlvG, "TMlvG/F");

  _outputEvt->Branch("Pjj", _Pjj, "Pjj[4]/F");
  _outputEvt->Branch("PjjP", _PjjP, "PjjP[4]/F");
  _outputEvt->Branch("Plv", _Plv, "Plv[4]/F");
  _outputEvt->Branch("Mjj", &_Mjj, "Mjj/F");
  _outputEvt->Branch("MjjP", &_MjjP, "MjjP/F");

  _outputEvt->Branch("MjjC", &_MjjC, "MjjC/F");

  _outputEvt->Branch("MjjReco", &_MjjReco, "MjjReco/F");

  _outputEvt->Branch("Mlv", &_Mlv, "Mlv/F");
  _outputEvt->Branch("MlvP", &_MlvP, "MlvP/F");

  _outputEvt->Branch("Pll", _Pll, "Pll[4]/F");
  _outputEvt->Branch("Plp", _Plp, "Plp[4]/F");	//leading Photon, maybe ISR
  _outputEvt->Branch("LeptonType", &_LeptonType,"LeptonType/I");
  _outputEvt->Branch("ISRFlag", &_ISRFlag, "ISRFlag/I");

  _outputEvt->Branch("MlvC", &_MlvC, "MlvC/F");
  _outputEvt->Branch("Pisr", _Pisr, "Pisr[4]/F");
  _outputEvt->Branch("MlvC_J", &_MlvC_J, "MlvC_J");
  _outputEvt->Branch("Pisr_J", _Pisr_J, "Pisr_J[4]/F");
  _outputEvt->Branch("Neumass", &_Neumass, "Neumass/F");

  // gDirectory->cd(*tree_file);

  h_mjj_reco=new TH1D("h_mjj_reco", "Recontruction mjj",300, 0, 150);
  h_mjj_truth=new TH1D("h_mjj_truth", "Truth mjj",300, 0, 150);
  h_mlv_reco=new TH1D("h_mlv_reco", "Recontruction mlv",300, 0, 150);
  h_mlv_truth=new TH1D("h_mlv_truth", "Truth mlv",300, 0, 150);

  h_mlvg_reco=new TH1D("h_mlvg_reco", "Recontruction mlvg",300, 0, 150);
  h_mlvg_truth=new TH1D("h_mlvg_truth", "Truth mlvg",300, 0, 150);


}

void PrintZHqqqq::processEvent( LCEvent * evtP )
{

  if (evtP)
  {
    _Mass_RecoP = 0;
    _Mass_MCP = 0;

    try
    {
      LCCollection* col_PFOs = evtP->getCollection( _colName ) ;

      _nPFOs=col_PFOs->getNumberOfElements();
      _eventNr=evtP->getEventNumber();
      _TotalEnRecoP = 0;
      _P_RecoP[0] = 0;
      _P_RecoP[1] = 0;
      _P_RecoP[2] = 0;
      _Neumass = 0;

      EventIndex=EventIndex+1;

      for(int k = 0; k < 4; k++)
      {
        _Pjj[k] = 0;
        _PjjP[k] = 0;
        _Plv[k] = 0;
        _Plp[k] = 0;
        _Pll[k] = 0;
        _Pisr[k] = 0;
        _Pisr_J[k] = 0;
      }


      _Mjj = 0;
      _MjjReco = 0;
      _Mlv = 0;
      _LeptonType = 0;	// Add isolation?
      _TMlv = 0;
      _TMjj = 0;
      _nMCP=0;
      _TotalEnMCP=0;

      _hasISR=0;

      _nJets=0;

      _nElectronReco=0;
      _nMuonReco=0;
      _TPhotonE=0;
      _nTPhoton=0;

      v_TPhotonE.clear();
      v_TPhotonPx.clear();
      v_TPhotonPy.clear();
      v_TPhotonPz.clear();

      v_TPhotonEta.clear();
      v_TPhotonY.clear();

      v_TPhotonTheta.clear();
      v_TPhotonPhi.clear();

      v_TQuarkE.clear();
      v_TQuarkPx.clear();
      v_TQuarkPy.clear();
      v_TQuarkPz.clear();
      v_TQuarkP.clear();
      v_TQuarkPt.clear();

      v_TQuarkEta.clear();
      v_TQuarkY.clear();

      v_TQuarkTheta.clear();
      v_TQuarkPhi.clear();
      v_TQuarkPID.clear();
      v_TQuarkVTXX.clear();
      v_TQuarkVTXY.clear();
      v_TQuarkVTXZ.clear();
      v_TQuarkEndPX.clear();
      v_TQuarkEndPY.clear();
      v_TQuarkEndPZ.clear();


      v_TLeptonE.clear();
      v_TLeptonPx.clear();
      v_TLeptonPy.clear();
      v_TLeptonPz.clear();

      v_TLeptonEta.clear();
      v_TLeptonY.clear();

      v_TLeptonTheta.clear();
      v_TLeptonPhi.clear();
      v_TLeptonPID.clear();
      v_TLeptonVTXX.clear();
      v_TLeptonVTXY.clear();
      v_TLeptonVTXZ.clear();
      v_TLeptonEndPX.clear();
      v_TLeptonEndPY.clear();
      v_TLeptonEndPZ.clear();


      nTFNeu=0;
      v_TFNeuE.clear();
      v_TFNeuPx.clear();
      v_TFNeuPy.clear();
      v_TFNeuPz.clear();
      v_TFNeuPt.clear();

      v_TFNeuEta.clear();
      v_TFNeuY.clear();
      v_TFNeuTheta.clear();
      v_TFNeuPhi.clear();
      v_TFNeuPID.clear();
      v_TFNeuMomPID.clear();
      v_TFNeuVTXX.clear();
      v_TFNeuVTXY.clear();
      v_TFNeuVTXZ.clear();
      v_TFNeuEndPX.clear();
      v_TFNeuEndPY.clear();
      v_TFNeuEndPZ.clear();
      v_TFNeuMomVTXX.clear();
      v_TFNeuMomVTXY.clear();
      v_TFNeuMomVTXZ.clear();
      v_TFNeuMomEndPX.clear();
      v_TFNeuMomEndPY.clear();
      v_TFNeuMomEndPZ.clear();



      nMC=0;
      v_MCE.clear();
      v_MCPx.clear();
      v_MCPy.clear();
      v_MCPz.clear();
      v_MCPt.clear();

      v_MCEta.clear();
      v_MCY.clear();
      v_MCTheta.clear();
      v_MCPhi.clear();
      v_MCCharge.clear();
      v_MomMCPID.clear();
      v_MCPID.clear();


      nhMC=0;
      v_hMCE.clear();
      v_hMCP.clear();
      v_hMCPx.clear();
      v_hMCPy.clear();
      v_hMCPz.clear();
      v_hMCPt.clear();

      v_hMCEta.clear();
      v_hMCY.clear();
      v_hMCTheta.clear();
      v_hMCPhi.clear();
      v_hGrandMomMCPID.clear();
      v_hMomMCPID.clear();
      v_hMCPID.clear();


      nTruthJet=0;
      nTJet1Component=0;
      nTJet2Component=0;
      nTJet3Component=0;
      nTJet4Component=0;

      v_TJetE.clear();
      v_TJetPx.clear();
      v_TJetPy.clear();
      v_TJetPz.clear();
      v_TJetP.clear();
      v_TJetPt.clear();

      v_TJetEta.clear();
      v_TJetY.clear();
      v_TJetTheta.clear();
      v_TJetPhi.clear();


      v_TJet1ComponentE.clear();
      v_TJet1ComponentPx.clear();
      v_TJet1ComponentPy.clear();
      v_TJet1ComponentPz.clear();
      v_TJet1ComponentP.clear();
      v_TJet1ComponentPt.clear();
      v_TJet1ComponentEta.clear();
      v_TJet1ComponentY.clear();
      v_TJet1ComponentTheta.clear();
      v_TJet1ComponentPhi.clear();
      v_TJet1ComponentPID.clear();
      v_TJet1ComponentGoodnessOfPID.clear();
      v_TJet1ComponentCharge.clear();


      v_TJet2ComponentE.clear();
      v_TJet2ComponentPx.clear();
      v_TJet2ComponentPy.clear();
      v_TJet2ComponentPz.clear();
      v_TJet2ComponentP.clear();
      v_TJet2ComponentPt.clear();
      v_TJet2ComponentEta.clear();
      v_TJet2ComponentY.clear();
      v_TJet2ComponentTheta.clear();
      v_TJet2ComponentPhi.clear();
      v_TJet2ComponentPID.clear();
      v_TJet2ComponentGoodnessOfPID.clear();
      v_TJet2ComponentCharge.clear();


      v_TJet3ComponentE.clear();
      v_TJet3ComponentPx.clear();
      v_TJet3ComponentPy.clear();
      v_TJet3ComponentPz.clear();
      v_TJet3ComponentP.clear();
      v_TJet3ComponentPt.clear();
      v_TJet3ComponentEta.clear();
      v_TJet3ComponentY.clear();
      v_TJet3ComponentTheta.clear();
      v_TJet3ComponentPhi.clear();
      v_TJet3ComponentPID.clear();
      v_TJet3ComponentGoodnessOfPID.clear();
      v_TJet3ComponentCharge.clear();


      v_TJet4ComponentE.clear();
      v_TJet4ComponentPx.clear();
      v_TJet4ComponentPy.clear();
      v_TJet4ComponentPz.clear();
      v_TJet4ComponentP.clear();
      v_TJet4ComponentPt.clear();
      v_TJet4ComponentEta.clear();
      v_TJet4ComponentY.clear();
      v_TJet4ComponentTheta.clear();
      v_TJet4ComponentPhi.clear();
      v_TJet4ComponentPID.clear();
      v_TJet4ComponentGoodnessOfPID.clear();
      v_TJet4ComponentCharge.clear();

      TMjj_Tjet=0;


      nFastJet=0;
      v_FastJetE.clear();
      v_FastJetPx.clear();
      v_FastJetPy.clear();
      v_FastJetPz.clear();
      v_FastJetP.clear();
      v_FastJetPt.clear();
      v_FastJetEta.clear();
      v_FastJetY.clear();
      v_FastJetTheta.clear();
      v_FastJetPhi.clear();

      TMjj_FastJet=0;

      v_TRJetdE.clear();
      v_TRJetAngle.clear();
      v_TRJetdR.clear();


      nRecoJet=0;
      nJet1Component=0;
      nJet2Component=0;
      nJet3Component=0;
      nJet4Component=0;

      v_JetE.clear();
      v_JetPx.clear();
      v_JetPy.clear();
      v_JetPz.clear();
      v_JetP.clear();
      v_JetPt.clear();

      v_JetEta.clear();
      v_JetY.clear();
      v_JetTheta.clear();
      v_JetPhi.clear();

      v_Jet_bTag_LCFIPlus.clear();
      v_Jet_cTag_LCFIPlus.clear();


      v_Jet1ComponentE.clear();
      v_Jet1ComponentPx.clear();
      v_Jet1ComponentPy.clear();
      v_Jet1ComponentPz.clear();
      v_Jet1ComponentP.clear();
      v_Jet1ComponentPt.clear();
      v_Jet1ComponentD0.clear();
      v_Jet1ComponentZ0.clear();
      v_Jet1ComponentR0.clear();
      v_Jet1ComponentD0Sig.clear();
      v_Jet1ComponentZ0Sig.clear();
      v_Jet1ComponentR0Sig.clear();
      v_Jet1ComponentConeE.clear();
      v_Jet1ComponentEta.clear();
      v_Jet1ComponentY.clear();
      v_Jet1ComponentTheta.clear();
      v_Jet1ComponentPhi.clear();
      v_Jet1ComponentPID.clear();
      v_Jet1ComponentGoodnessOfPID.clear();
      v_Jet1ComponentCharge.clear();
      v_Jet1ComponentVtx.clear();
      v_Jet1ComponentVty.clear();
      v_Jet1ComponentVtz.clear();


      v_Jet2ComponentE.clear();
      v_Jet2ComponentPx.clear();
      v_Jet2ComponentPy.clear();
      v_Jet2ComponentPz.clear();
      v_Jet2ComponentP.clear();
      v_Jet2ComponentPt.clear();
      v_Jet2ComponentD0.clear();
      v_Jet2ComponentZ0.clear();
      v_Jet2ComponentR0.clear();
      v_Jet2ComponentD0Sig.clear();
      v_Jet2ComponentZ0Sig.clear();
      v_Jet2ComponentR0Sig.clear();
      v_Jet2ComponentConeE.clear();
      v_Jet2ComponentEta.clear();
      v_Jet2ComponentY.clear();
      v_Jet2ComponentTheta.clear();
      v_Jet2ComponentPhi.clear();
      v_Jet2ComponentPID.clear();
      v_Jet2ComponentGoodnessOfPID.clear();
      v_Jet2ComponentCharge.clear();


      v_Jet3ComponentE.clear();
      v_Jet3ComponentPx.clear();
      v_Jet3ComponentPy.clear();
      v_Jet3ComponentPz.clear();
      v_Jet3ComponentP.clear();
      v_Jet3ComponentPt.clear();
      v_Jet3ComponentD0.clear();
      v_Jet3ComponentZ0.clear();
      v_Jet3ComponentR0.clear();
      v_Jet3ComponentD0Sig.clear();
      v_Jet3ComponentZ0Sig.clear();
      v_Jet3ComponentR0Sig.clear();
      v_Jet3ComponentConeE.clear();
      v_Jet3ComponentEta.clear();
      v_Jet3ComponentY.clear();
      v_Jet3ComponentTheta.clear();
      v_Jet3ComponentPhi.clear();
      v_Jet3ComponentPID.clear();
      v_Jet3ComponentGoodnessOfPID.clear();
      v_Jet3ComponentCharge.clear();
      v_Jet3ComponentVtx.clear();
      v_Jet3ComponentVty.clear();
      v_Jet3ComponentVtz.clear();


      v_Jet4ComponentE.clear();
      v_Jet4ComponentPx.clear();
      v_Jet4ComponentPy.clear();
      v_Jet4ComponentPz.clear();
      v_Jet4ComponentP.clear();
      v_Jet4ComponentPt.clear();
      v_Jet4ComponentD0.clear();
      v_Jet4ComponentZ0.clear();
      v_Jet4ComponentR0.clear();
      v_Jet4ComponentD0Sig.clear();
      v_Jet4ComponentZ0Sig.clear();
      v_Jet4ComponentR0Sig.clear();
      v_Jet4ComponentConeE.clear();
      v_Jet4ComponentEta.clear();
      v_Jet4ComponentY.clear();
      v_Jet4ComponentTheta.clear();
      v_Jet4ComponentPhi.clear();
      v_Jet4ComponentPID.clear();
      v_Jet4ComponentGoodnessOfPID.clear();
      v_Jet4ComponentCharge.clear();

      TMjj_jet=0;


      v_RecoPhotonE.clear();
      v_RecoPhotonPx.clear();
      v_RecoPhotonPy.clear();
      v_RecoPhotonPz.clear();

      v_RecoPhotonEta.clear();
      v_RecoPhotonY.clear();

      v_RecoPhotonTheta.clear();
      v_RecoPhotonPhi.clear();


      _nRecoLepton=0;
      v_RecoLeptonE.clear();
      v_RecoLeptonPx.clear();
      v_RecoLeptonPy.clear();
      v_RecoLeptonPz.clear();

      v_RecoLeptonEta.clear();
      v_RecoLeptonY.clear();
      v_RecoLeptonTheta.clear();
      v_RecoLeptonPhi.clear();
      v_RecoLeptonPID.clear();

      _nRecoPFO=0;
      v_RecoPFOE.clear();
      v_RecoPFOPx.clear();
      v_RecoPFOPy.clear();
      v_RecoPFOPz.clear();
      v_RecoPFOD0.clear();
      v_RecoPFOZ0.clear();
      v_RecoPFOR0.clear();
      v_RecoPFOD0Sig.clear();
      v_RecoPFOZ0Sig.clear();
      v_RecoPFOR0Sig.clear();
      v_RecoPFOConeE.clear();

      v_RecoPFOEta.clear();
      v_RecoPFOY.clear();
      v_RecoPFOTheta.clear();
      v_RecoPFOPhi.clear();
      v_RecoPFOPID.clear();
      v_RecoPFOCharge.clear();



      LCCollection * col_MCP = evtP->getCollection("MCParticle");
      TLorentzVector M_jj(0, 0, 0, 0);
      TLorentzVector M_lv(0, 0, 0, 0);
      TLorentzVector P_ISR(0, 0, 0, 0);
      TLorentzVector tmpP(0, 0, 0, 0);

      TVector3 VTX(0, 0, 0);
      TVector3 EndP(0, 0, 0);

      _nMCP=col_MCP->getNumberOfElements();
      //_nMCP=1;
        // col_MCP->getNumberOfElements();

       LCCollection *col_Jet=evtP->getCollection("RefinedJets");

       //lcfiplus::JetVec *v_myjets=0;

       //lcfiplus::Event::Instance()->Get("RefinedJets", v_myjets);

       //std::cout<< "v_myjets point: "<< v_myjets<< std::endl;
       //std::cout<< "Njets : "<< v_myjets->size()<< std::endl;

       _nJets=col_Jet->getNumberOfElements();
       std::cout<< "Number of Jets: "<< _nJets << std::endl;

      MCParticle *b_MCP;
      MCParticle *c_MCP;
      MCParticle *d_MCP;
      MCParticle *e_MCP;


      int count_nNeu=0;
      int count_nPho=0;
      int count_nLep=0;
      int count = 0, typecount=0;

      bool hasphoton=false;
      _channel=0;

      for(int MCP_i = 0; MCP_i < col_MCP->getNumberOfElements(); MCP_i++)
      {
       // MCParticle * a_MCP = dynamic_cast<EVENT::MCParticle *>(col_MCP->getElementAt(MCP_i));

       // if( MCP_i < 7) // ? <7
        {
          MCParticle * a_MCP = dynamic_cast<EVENT::MCParticle *>(col_MCP->getElementAt(MCP_i));
          if( a_MCP->getParents().size() == 0)
          {
            _TotalEnMCP+=a_MCP->getEnergy();

            tmpP.SetPxPyPzE(a_MCP->getMomentum()[0], a_MCP->getMomentum()[1], a_MCP->getMomentum()[2],a_MCP->getEnergy());
            if(fabs(a_MCP->getPDG()) < 7 )
            {
              M_jj += tmpP;

              v_TQuarkE.push_back(tmpP.E());
              v_TQuarkPx.push_back(tmpP.Px());
              v_TQuarkPy.push_back(tmpP.Py());
              v_TQuarkPz.push_back(tmpP.Pz());
              v_TQuarkP.push_back(tmpP.P());
              v_TQuarkPt.push_back(tmpP.Pt());

              v_TQuarkEta.push_back(tmpP.Eta());
              v_TQuarkY.push_back(tmpP.Rapidity());
              v_TQuarkTheta.push_back(tmpP.Theta());
              v_TQuarkPhi.push_back(tmpP.Phi());
              v_TQuarkPID.push_back(a_MCP->getPDG());
              VTX = a_MCP->getVertex();
              EndP= a_MCP->getEndpoint();

              v_TQuarkVTXX.push_back(VTX.X());
              v_TQuarkVTXY.push_back(VTX.Y());
              v_TQuarkVTXZ.push_back(VTX.Z());
              v_TQuarkEndPX.push_back(EndP.X());
              v_TQuarkEndPY.push_back(EndP.Y());
              v_TQuarkEndPZ.push_back(EndP.Z());


            }
            else if(fabs(a_MCP->getPDG()) > 10 && fabs(a_MCP->getPDG()) < 17)
            {
              M_lv += tmpP;

              v_TLeptonE.push_back(tmpP.E());
              v_TLeptonPx.push_back(tmpP.Px());
              v_TLeptonPy.push_back(tmpP.Py());
              v_TLeptonPz.push_back(tmpP.Pz());

              v_TLeptonEta.push_back(tmpP.Eta());
              v_TLeptonY.push_back(tmpP.Rapidity());
              v_TLeptonTheta.push_back(tmpP.Theta());
              v_TLeptonPhi.push_back(tmpP.Phi());
              v_TLeptonPID.push_back(a_MCP->getPDG());
              VTX = a_MCP->getVertex();
              EndP= a_MCP->getEndpoint();
              v_TLeptonVTXX.push_back(VTX.X());
              v_TLeptonVTXY.push_back(VTX.Y());
              v_TLeptonVTXZ.push_back(VTX.Z());
              v_TLeptonEndPX.push_back(EndP.X());
              v_TLeptonEndPY.push_back(EndP.Y());
              v_TLeptonEndPZ.push_back(EndP.Z());

            }
            else if(a_MCP->getPDG() == 22)
            {
              hasphoton=true;
              P_ISR += tmpP;
              _TPhotonE+=a_MCP->getEnergy();
              _nTPhoton+=1;

              v_TPhotonE.push_back(tmpP.E());
              v_TPhotonPx.push_back(tmpP.Px());
              v_TPhotonPy.push_back(tmpP.Py());
              v_TPhotonPz.push_back(tmpP.Pz());

              v_TPhotonEta.push_back(tmpP.Eta());
              v_TPhotonY.push_back(tmpP.Rapidity());
              v_TPhotonTheta.push_back(tmpP.Theta());
              v_TPhotonPhi.push_back(tmpP.Phi());

            }

            if(fabs(a_MCP->getPDG())==11)
            {
              _channel=1;
            }

            if(fabs(a_MCP->getPDG())==13)
            {
              _channel=2;
            }
          }// Parent = 0 loop


          if( a_MCP->getParents().size() != 0 && a_MCP->getDaughters().size() == 0)
          {
            tmpP.SetPxPyPzE(a_MCP->getMomentum()[0], a_MCP->getMomentum()[1], a_MCP->getMomentum()[2],a_MCP->getEnergy());
            VTX = a_MCP->getVertex();
            EndP = a_MCP->getEndpoint();
            if((fabs(a_MCP->getPDG()) == 12 || fabs(a_MCP->getPDG()) == 14 || fabs(a_MCP->getPDG()) == 16) && fabs(VTX.Mag()) < 100 && fabs(EndP.Mag()) > 100)
            {
              count_nNeu+=1;

              if(count_nNeu >= 0)
              {
                nTFNeu+=1;

                v_TFNeuE.push_back(tmpP.E());
                v_TFNeuPx.push_back(tmpP.Px());
                v_TFNeuPy.push_back(tmpP.Py());
                v_TFNeuPz.push_back(tmpP.Pz());
                v_TFNeuPt.push_back(tmpP.Pt());

                v_TFNeuEta.push_back(tmpP.Eta());
                v_TFNeuY.push_back(tmpP.Rapidity());
                v_TFNeuTheta.push_back(tmpP.Theta());
                v_TFNeuPhi.push_back(tmpP.Phi());
                v_TFNeuPID.push_back(a_MCP->getPDG());
                v_TFNeuVTXX.push_back(VTX.X());
                v_TFNeuVTXY.push_back(VTX.Y());
                v_TFNeuVTXZ.push_back(VTX.Z());
                v_TFNeuEndPX.push_back(EndP.X());
                v_TFNeuEndPY.push_back(EndP.Y());
                v_TFNeuEndPZ.push_back(EndP.Z());


                b_MCP = a_MCP->getParents()[0];
                v_TFNeuMomPID.push_back(b_MCP->getPDG());
                VTX = b_MCP->getVertex();
                EndP = b_MCP->getEndpoint();

                v_TFNeuMomVTXX.push_back(VTX.X());
                v_TFNeuMomVTXY.push_back(VTX.Y());
                v_TFNeuMomVTXZ.push_back(VTX.Z());
                v_TFNeuMomEndPX.push_back(EndP.X());
                v_TFNeuMomEndPY.push_back(EndP.Y());
                v_TFNeuMomEndPZ.push_back(EndP.Y());

              }
            }

          }// Daught =0 loop

          if( a_MCP->getGeneratorStatus() == 1 ) // stable particles only
          {
            nMC+=1;

            v_MCE.push_back(tmpP.E());
            v_MCPx.push_back(tmpP.Px());
            v_MCPy.push_back(tmpP.Py());
            v_MCPz.push_back(tmpP.Pz());
            v_MCPt.push_back(tmpP.Pt());

            v_MCEta.push_back(tmpP.Eta());
            v_MCY.push_back(tmpP.Rapidity());
            v_MCTheta.push_back(tmpP.Theta());
            v_MCPhi.push_back(tmpP.Phi());
            v_MCCharge.push_back(a_MCP->getCharge());

            v_MCPID.push_back(a_MCP->getPDG());
            e_MCP = a_MCP->getParents()[0];
            v_MomMCPID.push_back(e_MCP->getPDG());
          }// getGeneratorStatus() == 1

          jet_PID = -9999;
          if( a_MCP->getPDG() == 25 && a_MCP->getParents().size() == 1 && a_MCP->getDaughters().size() == 4 )
          {
            for(int p = 0; p < 2; p++)
            {
              b_MCP = a_MCP->getDaughters()[p];
              if( fabs(b_MCP->getPDG()) < 23 )
              {
                if(fabs(b_MCP->getPDG()) != 12 && fabs(b_MCP->getPDG()) != 14 && fabs(b_MCP->getPDG()) != 16 )
                {
                  typecount ++;
                }
                tmpP.SetPxPyPzE(b_MCP->getMomentum()[0], b_MCP->getMomentum()[1], b_MCP->getMomentum()[2],b_MCP->getEnergy());

                v_hMCE.push_back(tmpP.E());
                v_hMCP.push_back(tmpP.P());
                v_hMCPx.push_back(tmpP.Px());
                v_hMCPy.push_back(tmpP.Py());
                v_hMCPz.push_back(tmpP.Pz());
                v_hMCPt.push_back(tmpP.Pt());

                v_hMCEta.push_back(tmpP.Eta());
                v_hMCY.push_back(tmpP.Rapidity());
                v_hMCTheta.push_back(tmpP.Theta());
                v_hMCPhi.push_back(tmpP.Phi());

                v_hGrandMomMCPID.push_back(-99999);
                v_hMomMCPID.push_back(a_MCP->getPDG());
                v_hMCPID.push_back(b_MCP->getPDG());
                jet_PID = b_MCP->getPDG();
                count++;
								
								v_TQuarkE.push_back(tmpP.E());
								v_TQuarkPx.push_back(tmpP.Px());
								v_TQuarkPy.push_back(tmpP.Py());
								v_TQuarkPz.push_back(tmpP.Pz());
								v_TQuarkP.push_back(tmpP.P());
								v_TQuarkPt.push_back(tmpP.Pt());
								
								v_TQuarkEta.push_back(tmpP.Eta());
								v_TQuarkY.push_back(tmpP.Rapidity());
								v_TQuarkTheta.push_back(tmpP.Theta());
								v_TQuarkPhi.push_back(tmpP.Phi());
								v_TQuarkPID.push_back(b_MCP->getPDG());
								VTX = b_MCP->getVertex();
								EndP= b_MCP->getEndpoint();
								
								v_TQuarkVTXX.push_back(VTX.X());
								v_TQuarkVTXY.push_back(VTX.Y());
								v_TQuarkVTXZ.push_back(VTX.Z());
								v_TQuarkEndPX.push_back(EndP.X());
								v_TQuarkEndPY.push_back(EndP.Y());
								v_TQuarkEndPZ.push_back(EndP.Z());
              }

              else if( fabs(b_MCP->getPDG()) == 23 || fabs(b_MCP->getPDG()) == 24 )
              {
                for( int q = 0; q < 2; q++ )
                {
                  c_MCP = b_MCP->getDaughters()[q];
                  if( fabs(c_MCP->getPDG()) < 17 )
                  {
                    if(fabs(c_MCP->getPDG()) != 12 && fabs(c_MCP->getPDG()) != 14 && fabs(c_MCP->getPDG()) != 16 )
                    {
                      typecount ++;
                    }
                    tmpP.SetPxPyPzE(c_MCP->getMomentum()[0], c_MCP->getMomentum()[1], c_MCP->getMomentum()[2],c_MCP->getEnergy());

                    v_hMCE.push_back(tmpP.E());
                    v_hMCP.push_back(tmpP.P());
                    v_hMCPx.push_back(tmpP.Px());
                    v_hMCPy.push_back(tmpP.Py());
                    v_hMCPz.push_back(tmpP.Pz());
                    v_hMCPt.push_back(tmpP.Pt());

                    v_hMCEta.push_back(tmpP.Eta());
                    v_hMCY.push_back(tmpP.Rapidity());
                    v_hMCTheta.push_back(tmpP.Theta());
                    v_hMCPhi.push_back(tmpP.Phi());

                    v_hGrandMomMCPID.push_back(a_MCP->getPDG());
                    v_hMomMCPID.push_back(b_MCP->getPDG());
                    v_hMCPID.push_back(c_MCP->getPDG());
                    jet_PID = c_MCP->getPDG();
                    count++;
										
										v_TQuarkE.push_back(tmpP.E());
										v_TQuarkPx.push_back(tmpP.Px());
										v_TQuarkPy.push_back(tmpP.Py());
										v_TQuarkPz.push_back(tmpP.Pz());
										v_TQuarkP.push_back(tmpP.P());
										v_TQuarkPt.push_back(tmpP.Pt());
										
										v_TQuarkEta.push_back(tmpP.Eta());
										v_TQuarkY.push_back(tmpP.Rapidity());
										v_TQuarkTheta.push_back(tmpP.Theta());
										v_TQuarkPhi.push_back(tmpP.Phi());
										v_TQuarkPID.push_back(c_MCP->getPDG());
										VTX = c_MCP->getVertex();
										EndP= c_MCP->getEndpoint();
										
										v_TQuarkVTXX.push_back(VTX.X());
										v_TQuarkVTXY.push_back(VTX.Y());
										v_TQuarkVTXZ.push_back(VTX.Z());
										v_TQuarkEndPX.push_back(EndP.X());
										v_TQuarkEndPY.push_back(EndP.Y());
										v_TQuarkEndPZ.push_back(EndP.Z());

                  }
                }
              }
            }
          }
        }
//        else
//        {
//          break;
//        }
      }
      
      LCCollection *col_MCjet=evtP->getCollection("RefinedMCJets");
      LCCollection *col_FastJet = evtP->getCollection("RefinedFastJets");
      LCCollection *col_jet=evtP->getCollection("RefinedJets");
      // Genjet-RecoJet matching
      std::vector<Bool_t> matched_reco; // flags
      for (int jeti=0; jeti < col_jet->getNumberOfElements(); jeti++)
          matched_reco.push_back(false);
      TLorentzVector TBoson(0,0,0,0);
      for(unsigned int MCjeti=0; MCjeti<col_MCjet->getNumberOfElements(); MCjeti++)
      {
        ReconstructedParticle *MCjet=dynamic_cast<EVENT::ReconstructedParticle*>(col_MCjet->getElementAt(MCjeti));

        nTruthJet+=1;

        TLorentzVector lv_truthjet(0,0,0,0);
        lv_truthjet.SetPxPyPzE(MCjet->getMomentum()[0], MCjet->getMomentum()[1], MCjet->getMomentum()[2], MCjet->getEnergy());
        v_TJetE.push_back(lv_truthjet.E());
        v_TJetPx.push_back(lv_truthjet.Px());
        v_TJetPy.push_back(lv_truthjet.Py());
        v_TJetPz.push_back(lv_truthjet.Pz());
        v_TJetP.push_back(lv_truthjet.P());
        v_TJetPt.push_back(lv_truthjet.Pt());
        v_TJetEta.push_back(lv_truthjet.Eta());
        v_TJetPhi.push_back(lv_truthjet.Phi());
        v_TJetTheta.push_back(lv_truthjet.Theta());
        v_TJetY.push_back(lv_truthjet.Rapidity());

        TBoson=TBoson+lv_truthjet;

        // Get deltaE
        float angle, angle_min;
        float deltaE, deltaR;
        int matched_reco_jeti;
        angle_min = -1;
        for (int jeti=0; jeti < col_jet->getNumberOfElements(); jeti++) {
            if (matched_reco.at(jeti)) continue; // skip mattched recojet
            ReconstructedParticle *jet=dynamic_cast<EVENT::ReconstructedParticle*>(col_jet->getElementAt(jeti));
            TLorentzVector lv_recojet(0,0,0,0);
            lv_recojet.SetPxPyPzE(jet->getMomentum()[0], jet->getMomentum()[1], jet->getMomentum()[2], jet->getEnergy());
            angle = lv_truthjet.Angle(lv_recojet.Vect());
            if ( angle_min < 0 || angle < angle_min ) {
                angle_min = angle;
                deltaE = lv_truthjet.E() - lv_recojet.E();
                deltaR = lv_truthjet.DeltaR(lv_recojet);
                matched_reco_jeti = 0;
            }
        }
        matched_reco.at(matched_reco_jeti) = true;
        v_TRJetdE.push_back(deltaE);
        v_TRJetAngle.push_back(angle_min);
        v_TRJetdR.push_back(deltaR);



        ReconstructedParticleVec components=MCjet->getParticles();
        if(MCjeti==0){
          nTJet1Component = components.size();
        }
        if(MCjeti==1){
          nTJet2Component = components.size();
        }
        if(MCjeti==2){
          nTJet3Component = components.size();
        }
        if(MCjeti==3){
          nTJet4Component = components.size();
        }
        for(unsigned int icomp=0; icomp<components.size(); icomp++)
        {
          ReconstructedParticle *compPar=components.at(icomp);
          TLorentzVector lv_comp(0,0,0,0);
          lv_comp.SetPxPyPzE(compPar->getMomentum()[0], compPar->getMomentum()[1], compPar->getMomentum()[2], compPar->getEnergy());

          if(MCjeti==0)
          {
            v_TJet1ComponentE.push_back(lv_comp.E());
            v_TJet1ComponentPx.push_back(lv_comp.Px());
            v_TJet1ComponentPy.push_back(lv_comp.Py());
            v_TJet1ComponentPz.push_back(lv_comp.Pz());
            v_TJet1ComponentP.push_back(lv_comp.P());
            v_TJet1ComponentPt.push_back(lv_comp.Pt());

            v_TJet1ComponentEta.push_back(lv_comp.Eta());
            v_TJet1ComponentY.push_back(lv_comp.Rapidity());
            v_TJet1ComponentTheta.push_back(lv_comp.Theta());
            v_TJet1ComponentPhi.push_back(lv_comp.Phi());

            v_TJet1ComponentPID.push_back(compPar->getType());
            v_TJet1ComponentGoodnessOfPID.push_back(compPar->getGoodnessOfPID());
            v_TJet1ComponentCharge.push_back(compPar->getCharge());


          }

          if(MCjeti==1)
          {
            v_TJet2ComponentE.push_back(lv_comp.E());
            v_TJet2ComponentPx.push_back(lv_comp.Px());
            v_TJet2ComponentPy.push_back(lv_comp.Py());
            v_TJet2ComponentPz.push_back(lv_comp.Pz());
            v_TJet2ComponentP.push_back(lv_comp.P());
            v_TJet2ComponentPt.push_back(lv_comp.Pt());

            v_TJet2ComponentEta.push_back(lv_comp.Eta());
            v_TJet2ComponentY.push_back(lv_comp.Rapidity());
            v_TJet2ComponentTheta.push_back(lv_comp.Theta());
            v_TJet2ComponentPhi.push_back(lv_comp.Phi());
            v_TJet2ComponentPID.push_back(compPar->getType());
            v_TJet2ComponentGoodnessOfPID.push_back(compPar->getGoodnessOfPID());
            v_TJet2ComponentCharge.push_back(compPar->getCharge());
          }


          if(MCjeti==2)
          {
            v_TJet3ComponentE.push_back(lv_comp.E());
            v_TJet3ComponentPx.push_back(lv_comp.Px());
            v_TJet3ComponentPy.push_back(lv_comp.Py());
            v_TJet3ComponentPz.push_back(lv_comp.Pz());
            v_TJet3ComponentP.push_back(lv_comp.P());
            v_TJet3ComponentPt.push_back(lv_comp.Pt());

            v_TJet3ComponentEta.push_back(lv_comp.Eta());
            v_TJet3ComponentY.push_back(lv_comp.Rapidity());
            v_TJet3ComponentTheta.push_back(lv_comp.Theta());
            v_TJet3ComponentPhi.push_back(lv_comp.Phi());
            v_TJet3ComponentPID.push_back(compPar->getType());
            v_TJet3ComponentGoodnessOfPID.push_back(compPar->getGoodnessOfPID());
            v_TJet3ComponentCharge.push_back(compPar->getCharge());
          }

          if(MCjeti==3)
          {
            v_TJet4ComponentE.push_back(lv_comp.E());
            v_TJet4ComponentPx.push_back(lv_comp.Px());
            v_TJet4ComponentPy.push_back(lv_comp.Py());
            v_TJet4ComponentPz.push_back(lv_comp.Pz());
            v_TJet4ComponentP.push_back(lv_comp.P());
            v_TJet4ComponentPt.push_back(lv_comp.Pt());

            v_TJet4ComponentEta.push_back(lv_comp.Eta());
            v_TJet4ComponentY.push_back(lv_comp.Rapidity());
            v_TJet4ComponentTheta.push_back(lv_comp.Theta());
            v_TJet4ComponentPhi.push_back(lv_comp.Phi());
            v_TJet4ComponentPID.push_back(compPar->getType());
            v_TJet4ComponentGoodnessOfPID.push_back(compPar->getGoodnessOfPID());
            v_TJet4ComponentCharge.push_back(compPar->getCharge());
          }
        }


      }
      TMjj_Tjet=TBoson.M();

      TLorentzVector FastJetBoson(0,0,0,0);
      for(unsigned int fastjeti = 0; fastjeti < col_FastJet->getNumberOfElements(); fastjeti++) {
            ReconstructedParticle *fastjet = dynamic_cast<EVENT::ReconstructedParticle*>(col_FastJet->getElementAt(fastjeti));
            nFastJet += 1;
            TLorentzVector lv_fastjet(0,0,0,0);
            lv_fastjet.SetPxPyPzE(fastjet->getMomentum()[0], fastjet->getMomentum()[1], fastjet->getMomentum()[2], fastjet->getEnergy());
            v_FastJetE.push_back(lv_fastjet.E());
            v_FastJetPx.push_back(lv_fastjet.Px());
            v_FastJetPy.push_back(lv_fastjet.Py());
            v_FastJetPz.push_back(lv_fastjet.Pz());
            v_FastJetP.push_back(lv_fastjet.P());
            v_FastJetPt.push_back(lv_fastjet.Pt());
            v_FastJetEta.push_back(lv_fastjet.Eta());
            v_FastJetPhi.push_back(lv_fastjet.Phi());
            v_FastJetTheta.push_back(lv_fastjet.Theta());
            v_FastJetY.push_back(lv_fastjet.Y());

            FastJetBoson = FastJetBoson + lv_fastjet;

      }
      TMjj_FastJet = FastJetBoson.M();

      TLorentzVector RecoBoson(0,0,0,0);
      for(unsigned int jeti=0; jeti<col_jet->getNumberOfElements(); jeti++)
      {
        ReconstructedParticle *jet=dynamic_cast<EVENT::ReconstructedParticle*>(col_jet->getElementAt(jeti));

        nRecoJet+=1;

        TLorentzVector lv_recojet(0,0,0,0);
        lv_recojet.SetPxPyPzE(jet->getMomentum()[0], jet->getMomentum()[1], jet->getMomentum()[2], jet->getEnergy());
        v_JetE.push_back(lv_recojet.E());
        v_JetPx.push_back(lv_recojet.Px());
        v_JetPy.push_back(lv_recojet.Py());
        v_JetPz.push_back(lv_recojet.Pz());
        v_JetP.push_back(lv_recojet.P());
        v_JetPt.push_back(lv_recojet.Pt());
        v_JetEta.push_back(lv_recojet.Eta());
        v_JetPhi.push_back(lv_recojet.Phi());
        v_JetTheta.push_back(lv_recojet.Theta());
        v_JetY.push_back(lv_recojet.Rapidity());

        RecoBoson=RecoBoson+lv_recojet;


        ReconstructedParticleVec components=jet->getParticles();


        if(jeti==0){
          nJet1Component = components.size();
        }
        if(jeti==1){
          nJet2Component = components.size();
        }
        if(jeti==2){
          nJet3Component = components.size();
        }
        if(jeti==3){
          nJet4Component = components.size();
        }
        for(unsigned int icomp=0; icomp<components.size(); icomp++)
        {
          ReconstructedParticle *compPar=components.at(icomp);
          TLorentzVector lv_comp(0,0,0,0);
          lv_comp.SetPxPyPzE(compPar->getMomentum()[0], compPar->getMomentum()[1], compPar->getMomentum()[2], compPar->getEnergy());

          const EVENT::TrackVec & trkvec = compPar->getTracks();

          if(jeti==0)
          {
            v_Jet1ComponentE.push_back(lv_comp.E());
            v_Jet1ComponentPx.push_back(lv_comp.Px());
            v_Jet1ComponentPy.push_back(lv_comp.Py());
            v_Jet1ComponentPz.push_back(lv_comp.Pz());
            v_Jet1ComponentP.push_back(lv_comp.P());
            v_Jet1ComponentPt.push_back(lv_comp.Pt());

            float E     = compPar->getEnergy() ;
            float coneE = getConeEnergy( compPar, col_jet )/E;
            v_Jet1ComponentConeE.push_back(coneE);

            if (trkvec.size()!=0)
            {
              // TODO: more sophisticated pfo/track matching
              float d0 = fabs(trkvec[0]->getD0());
              float z0 = fabs(trkvec[0]->getZ0());
              float r0 = sqrt( d0*d0 + z0*z0 );
              float d0err = sqrt(trkvec[0]->getCovMatrix()[0]);
              float z0err = sqrt(trkvec[0]->getCovMatrix()[9]);

              float d0sig = d0err != 0 ? d0/d0err : 0;
              float z0sig = z0err != 0 ? z0/z0err : 0;
              float r0sig = sqrt( d0sig*d0sig + z0sig*z0sig );

              v_Jet1ComponentD0.push_back( d0 );
              v_Jet1ComponentZ0.push_back( z0 );
              v_Jet1ComponentR0.push_back( r0 );

              v_Jet1ComponentD0Sig.push_back( d0sig );
              v_Jet1ComponentZ0Sig.push_back( z0sig );
              v_Jet1ComponentR0Sig.push_back( r0sig );

            }

            v_Jet1ComponentEta.push_back(lv_comp.Eta());
            v_Jet1ComponentY.push_back(lv_comp.Rapidity());
            v_Jet1ComponentTheta.push_back(lv_comp.Theta());
            v_Jet1ComponentPhi.push_back(lv_comp.Phi());

            v_Jet1ComponentPID.push_back(compPar->getType());
            v_Jet1ComponentGoodnessOfPID.push_back(compPar->getGoodnessOfPID());
            v_Jet1ComponentCharge.push_back(compPar->getCharge());
          }

          if(jeti==1)
          {
            v_Jet2ComponentE.push_back(lv_comp.E());
            v_Jet2ComponentPx.push_back(lv_comp.Px());
            v_Jet2ComponentPy.push_back(lv_comp.Py());
            v_Jet2ComponentPz.push_back(lv_comp.Pz());
            v_Jet2ComponentP.push_back(lv_comp.P());
            v_Jet2ComponentPt.push_back(lv_comp.Pt());

            float E     = compPar->getEnergy() ;
            float coneE = getConeEnergy( compPar, col_jet )/E;
            v_Jet2ComponentConeE.push_back(coneE);

            if (trkvec.size()!=0)
            {
              // TODO: more sophisticated pfo/track matching
              float d0 = fabs(trkvec[0]->getD0());
              float z0 = fabs(trkvec[0]->getZ0());
              float r0 = sqrt( d0*d0 + z0*z0 );
              float d0err = sqrt(trkvec[0]->getCovMatrix()[0]);
              float z0err = sqrt(trkvec[0]->getCovMatrix()[9]);

              float d0sig = d0err != 0 ? d0/d0err : 0;
              float z0sig = z0err != 0 ? z0/z0err : 0;
              float r0sig = sqrt( d0sig*d0sig + z0sig*z0sig );

              v_Jet2ComponentD0.push_back( d0 );
              v_Jet2ComponentZ0.push_back( z0 );
              v_Jet2ComponentR0.push_back( r0 );

              v_Jet2ComponentD0Sig.push_back( d0sig );
              v_Jet2ComponentZ0Sig.push_back( z0sig );
              v_Jet2ComponentR0Sig.push_back( r0sig );

            }

            v_Jet2ComponentEta.push_back(lv_comp.Eta());
            v_Jet2ComponentY.push_back(lv_comp.Rapidity());
            v_Jet2ComponentTheta.push_back(lv_comp.Theta());
            v_Jet2ComponentPhi.push_back(lv_comp.Phi());

            v_Jet2ComponentPID.push_back(compPar->getType());
            v_Jet2ComponentGoodnessOfPID.push_back(compPar->getGoodnessOfPID());
            v_Jet2ComponentCharge.push_back(compPar->getCharge());

          }

          if(jeti==2)
          {
            v_Jet3ComponentE.push_back(lv_comp.E());
            v_Jet3ComponentPx.push_back(lv_comp.Px());
            v_Jet3ComponentPy.push_back(lv_comp.Py());
            v_Jet3ComponentPz.push_back(lv_comp.Pz());
            v_Jet3ComponentP.push_back(lv_comp.P());
            v_Jet3ComponentPt.push_back(lv_comp.Pt());

            float E     = compPar->getEnergy() ;
            float coneE = getConeEnergy( compPar, col_jet )/E;
            v_Jet3ComponentConeE.push_back(coneE);

            if (trkvec.size()!=0)
            {
              // TODO: more sophisticated pfo/track matching
              float d0 = fabs(trkvec[0]->getD0());
              float z0 = fabs(trkvec[0]->getZ0());
              float r0 = sqrt( d0*d0 + z0*z0 );
              float d0err = sqrt(trkvec[0]->getCovMatrix()[0]);
              float z0err = sqrt(trkvec[0]->getCovMatrix()[9]);

              float d0sig = d0err != 0 ? d0/d0err : 0;
              float z0sig = z0err != 0 ? z0/z0err : 0;
              float r0sig = sqrt( d0sig*d0sig + z0sig*z0sig );

              v_Jet3ComponentD0.push_back( d0 );
              v_Jet3ComponentZ0.push_back( z0 );
              v_Jet3ComponentR0.push_back( r0 );

              v_Jet3ComponentD0Sig.push_back( d0sig );
              v_Jet3ComponentZ0Sig.push_back( z0sig );
              v_Jet3ComponentR0Sig.push_back( r0sig );

            }

            v_Jet3ComponentEta.push_back(lv_comp.Eta());
            v_Jet3ComponentY.push_back(lv_comp.Rapidity());
            v_Jet3ComponentTheta.push_back(lv_comp.Theta());
            v_Jet3ComponentPhi.push_back(lv_comp.Phi());

            v_Jet3ComponentPID.push_back(compPar->getType());
            v_Jet3ComponentGoodnessOfPID.push_back(compPar->getGoodnessOfPID());
            v_Jet3ComponentCharge.push_back(compPar->getCharge());

          }

          if(jeti==3)
          {
            v_Jet4ComponentE.push_back(lv_comp.E());
            v_Jet4ComponentPx.push_back(lv_comp.Px());
            v_Jet4ComponentPy.push_back(lv_comp.Py());
            v_Jet4ComponentPz.push_back(lv_comp.Pz());
            v_Jet4ComponentP.push_back(lv_comp.P());
            v_Jet4ComponentPt.push_back(lv_comp.Pt());

            float E     = compPar->getEnergy() ;
            float coneE = getConeEnergy( compPar, col_jet )/E;
            v_Jet4ComponentConeE.push_back(coneE);

            if (trkvec.size()!=0)
            {
              // TODO: more sophisticated pfo/track matching
              float d0 = fabs(trkvec[0]->getD0());
              float z0 = fabs(trkvec[0]->getZ0());
              float r0 = sqrt( d0*d0 + z0*z0 );
              float d0err = sqrt(trkvec[0]->getCovMatrix()[0]);
              float z0err = sqrt(trkvec[0]->getCovMatrix()[9]);

              float d0sig = d0err != 0 ? d0/d0err : 0;
              float z0sig = z0err != 0 ? z0/z0err : 0;
              float r0sig = sqrt( d0sig*d0sig + z0sig*z0sig );

              v_Jet4ComponentD0.push_back( d0 );
              v_Jet4ComponentZ0.push_back( z0 );
              v_Jet4ComponentR0.push_back( r0 );

              v_Jet4ComponentD0Sig.push_back( d0sig );
              v_Jet4ComponentZ0Sig.push_back( z0sig );
              v_Jet4ComponentR0Sig.push_back( r0sig );

            }

            v_Jet4ComponentEta.push_back(lv_comp.Eta());
            v_Jet4ComponentY.push_back(lv_comp.Rapidity());
            v_Jet4ComponentTheta.push_back(lv_comp.Theta());
            v_Jet4ComponentPhi.push_back(lv_comp.Phi());

            v_Jet4ComponentPID.push_back(compPar->getType());
            v_Jet4ComponentGoodnessOfPID.push_back(compPar->getGoodnessOfPID());
            v_Jet4ComponentCharge.push_back(compPar->getCharge());

          }

        }
      }
      TMjj_jet=RecoBoson.M();


    //  if(_TotalEnMCP-250==0.01 && hasphoton==true)
      if(fabs(_TotalEnMCP-250)<0.01 && hasphoton==true)
      {
        _hasISR=1;
      }

      _TMjj = M_jj.M();
      std::cout<< "Truth Mjj: " << _TMjj << std::endl;
      _TMlv = M_lv.M();
      _TMlvG = (M_lv + P_ISR).M();

       h_mjj_truth->Fill(_TMjj);
       h_mlv_truth->Fill(_TMlv);
       h_mlvg_truth->Fill(_TMlvG);

      //float PhotonMaxE = 0;
      float LeptonMaxE = 0;

      _nRecoPhoton=0;

      for (int PFO_i=0; PFO_i < _nPFOs; PFO_i++)
      {
        EVENT::ReconstructedParticle *a_PFO=dynamic_cast<EVENT::ReconstructedParticle *>(col_PFOs->getElementAt(PFO_i));

        _energy=a_PFO->getEnergy();
        _mass=a_PFO->getMass();
        _Charge=a_PFO->getCharge();
        _Px=a_PFO->getMomentum()[0];
        _Py=a_PFO->getMomentum()[1];
        _Pz=a_PFO->getMomentum()[2];
        _Type = a_PFO->getType();

        _TotalEnRecoP += _energy;
        _P_RecoP[0] += _Px;
        _P_RecoP[1] += _Py;
        _P_RecoP[2] += _Pz;

        TLorentzVector pfo(0,0,0,0);
        pfo.SetPxPyPzE(_Px, _Py, _Pz, _energy);


        v_RecoPFOE.push_back(pfo.E());
        v_RecoPFOPx.push_back(pfo.Px());
        v_RecoPFOPy.push_back(pfo.Py());
        v_RecoPFOPz.push_back(pfo.Pz());

        float E     = a_PFO->getEnergy() ;
        float coneE = getConeEnergy( a_PFO, col_PFOs )/E;
        v_RecoPFOConeE.push_back(coneE);

        v_RecoPFOEta.push_back(pfo.Eta());
        v_RecoPFOY.push_back(pfo.Rapidity());
        v_RecoPFOTheta.push_back(pfo.Theta());
        v_RecoPFOPhi.push_back(pfo.Phi());
        v_RecoPFOPID.push_back(_Type);
        v_RecoPFOCharge.push_back(a_PFO->getCharge());


        _nRecoPFO+=1;

        const EVENT::TrackVec & trkvec = a_PFO->getTracks();

        if (trkvec.size()!=0)
        {
          // TODO: more sophisticated pfo/track matching
          float d0 = fabs(trkvec[0]->getD0());
          float z0 = fabs(trkvec[0]->getZ0());
          float r0 = sqrt( d0*d0 + z0*z0 );
          float d0err = sqrt(trkvec[0]->getCovMatrix()[0]);
          float z0err = sqrt(trkvec[0]->getCovMatrix()[9]);

          float d0sig = d0err != 0 ? d0/d0err : 0;
          float z0sig = z0err != 0 ? z0/z0err : 0;
          float r0sig = sqrt( d0sig*d0sig + z0sig*z0sig );

          v_RecoPFOD0.push_back( d0 );
          v_RecoPFOZ0.push_back( z0 );
          v_RecoPFOR0.push_back( r0 );

          v_RecoPFOD0Sig.push_back( d0sig );
          v_RecoPFOZ0Sig.push_back( z0sig );
          v_RecoPFOR0Sig.push_back( r0sig );

        }

        if(fabs(_Type)==11 || fabs(_Type)==13)
        {
          TLorentzVector lepton(0,0,0,0);
          lepton.SetPxPyPzE(_Px, _Py, _Pz, _energy);


          v_RecoLeptonE.push_back(lepton.E());
          v_RecoLeptonPx.push_back(lepton.Px());
          v_RecoLeptonPy.push_back(lepton.Py());
          v_RecoLeptonPz.push_back(lepton.Pz());

          v_RecoLeptonEta.push_back(lepton.Eta());
          v_RecoLeptonY.push_back(lepton.Rapidity());
          v_RecoLeptonTheta.push_back(lepton.Theta());
          v_RecoLeptonPhi.push_back(lepton.Phi());
          v_RecoLeptonPID.push_back(_Type);

          _nRecoLepton+=1;

        }


        if( fabs(_Type) == 13 && _energy > LeptonMaxE)
        {
          _nMuonReco+=1;
          LeptonMaxE = _energy;
          _LeptonType = _Type;
          _Pll[0] = _Px;
          _Pll[1] = _Py;
          _Pll[2] = _Pz;
          _Pll[3] = _energy;


        }

        if( fabs(_Type) == 11 && _energy > LeptonMaxE)
        {
          _nElectronReco+=1;
          LeptonMaxE = _energy;
          _LeptonType = _Type;
          _Pll[0] = _Px;
          _Pll[1] = _Py;
          _Pll[2] = _Pz;
          _Pll[3] = _energy;

        }

      //  if( _Type == 22 && _energy > PhotonMaxE)
        if( _Type == 22 )
        {
    //      PhotonMaxE += _energy;
          _Plp[0] += _Px;
          _Plp[1] += _Py;
          _Plp[2] += _Pz;
          _Plp[3] += _energy;
          _nRecoPhoton+=1;

          TLorentzVector photon(0,0,0,0);
          photon.SetPxPyPzE(_Px, _Py, _Pz, _energy);

          v_RecoPhotonE.push_back(photon.E());
          v_RecoPhotonPx.push_back(photon.Px());
          v_RecoPhotonPy.push_back(photon.Py());
          v_RecoPhotonPz.push_back(photon.Pz());

          v_RecoPhotonEta.push_back(photon.Eta());
          v_RecoPhotonY.push_back(photon.Rapidity());
          v_RecoPhotonTheta.push_back(photon.Theta());
          v_RecoPhotonPhi.push_back(photon.Phi());


        }

      }

      _ISRFlag = 0;

      if(fabs(_LeptonType) == 11 || fabs(_LeptonType) == 13)
      {
        _Pjj[3] = _TotalEnRecoP - _Pll[3];
        _Pjj[0] = _P_RecoP[0] - _Pll[0];
        _Pjj[1] = _P_RecoP[1] - _Pll[1];
        _Pjj[2] = _P_RecoP[2] - _Pll[2];

        _PjjP[3] = _TotalEnRecoP - _Pll[3]- _Plp[3];
        _PjjP[0] = _P_RecoP[0] - _Pll[0] - _Plp[0];
        _PjjP[1] = _P_RecoP[1] - _Pll[1] - _Plp[1];
        _PjjP[2] = _P_RecoP[2] - _Pll[2] - _Plp[2];

      }
      _Mjj = sqrt(_Pjj[3]*_Pjj[3] - _Pjj[0]*_Pjj[0] - _Pjj[1]*_Pjj[1] - _Pjj[2]*_Pjj[2]);
      _MjjP = sqrt(_PjjP[3]*_PjjP[3] - _PjjP[0]*_PjjP[0] - _PjjP[1]*_PjjP[1] - _PjjP[2]*_PjjP[2]);

      _Mlv = sqrt((250 - _Pjj[3])*(250 - _Pjj[3]) - _Pjj[0]*_Pjj[0] - _Pjj[1]*_Pjj[1] - _Pjj[2]*_Pjj[2]);  // recoil
      _MlvP = sqrt((250 - _PjjP[3])*(250 - _PjjP[3]) - _PjjP[0]*_PjjP[0] - _PjjP[1]*_PjjP[1] - _PjjP[2]*_PjjP[2]);  // recoil

      _Mass_RecoP = sqrt(_TotalEnRecoP*_TotalEnRecoP - _P_RecoP[0]*_P_RecoP[0] - _P_RecoP[1]*_P_RecoP[1] - _P_RecoP[2]*_P_RecoP[2]);

       h_mjj_reco->Fill(_Mjj);
       h_mlv_reco->Fill(_Mlv);



        TLorentzVector Wboson(0,0,0,0);

/*
        PIDHandler pidh(col_Jet);
        int algo=pidh.getAlgorithmID( "lcfiplus" );
        int ibtag=pidh.getParameterIndex(algo, "BTag");
        int ictag=pidh.getParameterIndex(algo, "CTag");

       for(int jet_i = 0; jet_i < col_Jet->getNumberOfElements(); jet_i++)
       {
         lcfiplus::Jet *myjet=dynamic_cast<lcfiplus::Jet *>(col_Jet->getElementAt(jet_i));
         std::cout<<"Jet point: " << myjet << std::endl;
//         const std::vector<const lcfiplus::Track*> v_track=myjet->getTracks();
//         std::cout<<"Ntracks: " << v_track.size() << std::endl;
         EVENT::ReconstructedParticle *a_jet=dynamic_cast<EVENT::ReconstructedParticle *>(col_Jet->getElementAt(jet_i));
         TLorentzVector jet(0,0,0,0);
         jet.SetPxPyPzE(a_jet->getMomentum()[0], a_jet->getMomentum()[1], a_jet->getMomentum()[2], a_jet->getEnergy());
         Wboson+=jet;
         const ParticleID &pid = pidh.getParticleID(a_jet, algo);
         std::cout<< "btag = " << pid.getParameters()[ibtag] << std::endl;
         std::cout<< "ctag = " << pid.getParameters()[ictag] << std::endl;

         v_Jet_bTag_LCFIPlus.push_back(pid.getParameters()[ibtag]);
         v_Jet_cTag_LCFIPlus.push_back(pid.getParameters()[ictag]);

       }*/

       _MjjReco=Wboson.M();

      _MjjC=0;

      //Scale Corrected:  ?? why this scale factor?

      float JetScale = 1.04;
      TLorentzVector Pjj, Ptotal, Pl, Precoil, Pgamma1, Pgamma2, Pneutrino1, Pneutrino2;
      Pjj.SetPxPyPzE( JetScale*_Pjj[0], JetScale*_Pjj[1], JetScale*_Pjj[2], JetScale*_Pjj[3] );
      Ptotal.SetPxPyPzE(0, 0, 0, 250);
      Pl.SetPxPyPzE(_Pll[0], _Pll[1], _Pll[2], _Pll[3]);
      Precoil = Ptotal - (Pjj + Pl);	//Neutrino + Mass
      _MjjC=Pjj.M();

      // 1 = 1, 0, 0, -1; 2 = 1, 0, 0, 1
      float E_isr_1 = 0.5*Precoil.M()*Precoil.M()/(Precoil.E() + Precoil.Pz());
      float E_isr_2 = 0.5*Precoil.M()*Precoil.M()/(Precoil.E() - Precoil.Pz());

      Pgamma1.SetPxPyPzE(0, 0, -1*E_isr_1, E_isr_1);
      Pgamma2.SetPxPyPzE(0, 0, E_isr_2, E_isr_2);

      Pneutrino1 = Precoil - Pgamma1;
      Pneutrino2 = Precoil - Pgamma2;

      std::cout<<"XX "<<Pgamma1.M()<<" PP "<<Pgamma2.M()<<std::endl;
//
      std::cout<<"Electron Direction, Gamma Energy "<<E_isr_1<<" neutrino mass "<<Pneutrino1.M()<<" Wlv "<<(Pneutrino1 + Pl).M()<<std::endl;
      std::cout<<"Positron Direction, Gamma Energy "<<E_isr_2<<" neutrino mass "<<Pneutrino2.M()<<" Wlv "<<(Pneutrino2 + Pl).M()<<std::endl;

      float M1 = (Pneutrino1 + Pl).M();
      float M2 = (Pneutrino2 + Pl).M();

      if(abs(M1 - 80.4) < abs(M2 - 80.4))
      {
        _Pisr[0] = 0; _Pisr[1] = 0; _Pisr[2] = -1*E_isr_1; _Pisr[3] = E_isr_1;
        _Pisr_J[0] = 0; _Pisr_J[1] = 0; _Pisr_J[2] = E_isr_2; _Pisr_J[3] = E_isr_2;
        _MlvC = M1;
        _MlvC_J = M2;
        _Neumass = Pneutrino1.M();
      }
      else
      {
        _Pisr[0] = 0; _Pisr[1] = 0; _Pisr[2] = E_isr_2; _Pisr[3] = E_isr_2;
        _Pisr_J[0] = 0; _Pisr_J[1] = 0; _Pisr_J[2] = -1*E_isr_1; _Pisr_J[3] = E_isr_1;
        _MlvC = M2;
        _MlvC_J = M1;
        _Neumass = Pneutrino2.M();
      }

      _outputEvt->Fill();

    }
     catch (lcio::DataNotAvailableException err) { }
  }



}

float PrintZHqqqq::getConeEnergy( ReconstructedParticle* pfo, LCCollection* _pfoCol) {
  float coneEC = 0, coneEN=0;

  TVector3 P( pfo->getMomentum() );
  int npfo = _pfoCol->getNumberOfElements();
  for ( int i = 0; i < npfo; i++ ) {
    ReconstructedParticle* pfo_i = dynamic_cast<ReconstructedParticle*>( _pfoCol->getElementAt(i) );

    // don't add itself to the cone energy
    if ( pfo == pfo_i ) continue;

    float charge = pfo_i->getCharge();
    TVector3 P_i( pfo_i->getMomentum() );
    float cosTheta = P.Dot( P_i )/(P.Mag()*P_i.Mag());
    if ( cosTheta >= 0.3 ){
      if( fabs(charge)>0.001)
        coneEC += pfo_i->getEnergy();
      else
        coneEN += pfo_i->getEnergy();
    }
  }

  return coneEC+coneEN;
}


void PrintZHqqqq::end()
{

  if (_outputEvt) {

    tree_file = _outputEvt->GetCurrentFile(); //just in case we switched to a new file

    // h_mlv_reco->SetDirectory(tree_file);
    //
    // h_mjj_reco->Write();
    // h_mlv_reco->Write();
    // h_mjj_truth->Write();
    // h_mlv_truth->Write();
    // h_mlvg_reco->Write();
    // h_mlvg_truth->Write();
    //
    tree_file->Write();
   // delete tree_file;

    tree_file->Close();
  }

}
