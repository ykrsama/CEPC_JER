#include <PrintZH.hh>
#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
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

PrintZH a_PrintZH_instance;

PrintZH::PrintZH()
	: Processor("PrintZH"),
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

void PrintZH::init() {

	printParameters();

	TFile *tree_file=new TFile(_treeFileName.c_str(),(_overwrite ? "RECREATE" : "UPDATE"));


	if (!tree_file->IsOpen()) {
		delete tree_file;
		tree_file=new TFile(_treeFileName.c_str(),"NEW");
	}

	_outputEvt = new TTree("Evt", "Evt");
        _outputEvt->SetAutoSave(32*1024*1024);  // autosave every 32MB
        _outputEvt->Branch("EventNr", &_eventNr, "EventNr/I");
	_outputEvt->Branch("NMCP",&_nMCP,"NMCP/I");
	_outputEvt->Branch("HDPID",&_HDPID,"HDPID/I");
	_outputEvt->Branch("ZDPID",&_ZDPID,"ZDPID/I");
	_outputEvt->Branch("Num", &_Num, "Num/I");
	_Num = 0; 
}

void PrintZH::processEvent( LCEvent * evtP ) 
{		

	if (evtP) 								
	{
		LCCollection* col_MCP = evtP->getCollection( "MCParticle" ) ;
		_nMCP=col_MCP->getNumberOfElements();
		_eventNr=evtP->getEventNumber();	
		int NDaughter = 0; 
		int NParent = 0; 
		int PDG = 0; 

		for(int j = 0; j < _nMCP; j++)
		{
			MCParticle* a_MCP = dynamic_cast<MCParticle*>(col_MCP->getElementAt(j));
			NDaughter = a_MCP->getDaughters().size();
			NParent = a_MCP->getParents().size();
			PDG = a_MCP->getPDG();
			if(NParent == 0 && fabs(PDG) < 20)
			{
				_ZDPID = fabs(PDG);
			}
			if(PDG == 25 && NParent != 0 && NDaughter != 0 )
			{
				MCParticle* b_MCP = a_MCP->getDaughters()[0];
				_HDPID = fabs(b_MCP->getPDG());
			}
		}

		_outputEvt->Fill();
		_Num ++;
	}  	  
}	

void PrintZH::end()
{

	if (_outputEvt) {

		TFile *tree_file = _outputEvt->GetCurrentFile(); //just in case we switched to a new file
		tree_file->Write();
		delete tree_file;

	}

}



