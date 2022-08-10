#ifndef _Gen_hh_
#define _Gen_hh_

//#include <RConfigure.h>
#include <string>
#include <iostream>
#include <fstream>
#include <marlin/Processor.h>
#include <TNtuple.h>
#include <TObject.h>

#include <TTree.h>
#include <TFile.h>

class TTree;

class Gen  : public marlin::Processor
{
	public:

		Processor*  newProcessor() { return new Gen ; }

		Gen();

		~Gen() {};

		void init();

		//   void processRunHeader( LCRunHeader* run) { } 

		void processEvent( LCEvent * evtP );

		void end();

	protected:
		std::string _treeFileName;
		std::string _treeName;
		std::string _colName;
		std::string _colAdcVals;

		int _overwrite;
		TTree *_outputEvt;
		TTree *_outputMCP; 
		TTree *_outputPFO; 

		unsigned int _eventNr;
		int _PID, _GenStatus, _SimStatus, _parentnum, _daughternum, _Type, _nMCP, _nSelMCP, _nPFOs;
		float _mass, _Charge, _energy, _Px, _Py, _Pz; 
		float _Posx, _Posy, _Posz, _Vex_x, _Vex_y, _Vex_z; 

		float _TotalEnRecoP, _TotalEnMCP, _Mass_MCP, _Mass_RecoP; 
		float _P_RecoP[3], _P_MCP[3];
		float _Plv[4], _Plp[4], _Pjj[4], _Pll[4];
		float _Mjj, _Mlv; 

		int _LeptonType, _ISRFlag;

		int count;
		std::string _fileName;
		std::ostream *_output;

		std::string _histFileName;

};



#endif


