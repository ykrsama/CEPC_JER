#include "marlin/MarlinConfig.h" // defines MARLIN_CLHEP

#ifdef MARLIN_CLHEP  // only if CLHEP is available !

#include <cstdlib>


#include "LGParticleFactory.h"
#include <iostream>
#include <TVector3.h>
#if ! LCIO_PATCHVERSION_GE( 1,51,3 )
//#warning "have to #define USE_CLHEP to activate code from LCIO header <UTIL/LCFourVector.h>"
#define USE_CLHEP // to activate code from LCIO header <UTIL/LCFourVector.h>
#endif

#include "UTIL/LCFourVector.h"

using namespace lcio ;


namespace marlin{

	LGParticleFactory::LGParticleFactory() :
		_momentumCut( 0.001 )  {

			_smearingVec.resize( NUMBER_OF_FASTMCPARTICLETYPES ) ;
		}


	void LGParticleFactory::setMomentumCut( double mCut ) {
		_momentumCut = mCut ;
	}

	void LGParticleFactory::setSmear( bool smear ) {
		_smear = smear ;
	}
	
	void LGParticleFactory::setNeutrino( bool neutrino ) {
		_rejectNeutrino = neutrino ;
	}

	void LGParticleFactory::registerIFourVectorSmearer( IFourVectorSmearer* sm , 
			FastMCParticleType type ) {
		_smearingVec[ type ] = sm ;

	}


	FastMCParticleType LGParticleFactory::getParticleType( const lcio::MCParticle* mcp ) {


		// assumes that mcp is a stable particle !

		FastMCParticleType type( UNKNOWN )  ;


		float charge =  mcp->getCharge()  ;

		if( charge > 1e-10 || charge < -1e-10  ){  

			type = CHARGED ;

		} else if(  mcp->getPDG() == 22 )  { // photon

			type = PHOTON ;

		} else if(  std::abs( mcp->getPDG() ) == 12 || std::abs( mcp->getPDG() ) == 14 ||
				std::abs( mcp->getPDG() ) == 16 || std::abs( mcp->getPDG() ) == 18 )  { // neutrinos - 18 is tau-prime

			type = NEUTRINO ;


		} else {  // treat everything else neutral hadron  

			type = NEUTRAL_HADRON ;
		}

		return type ;
	}


	ReconstructedParticle* LGParticleFactory::createReconstructedParticle( const MCParticle* mcp) {

		// this is where we do the fast Monte Carlo ....


#ifdef LCIO_PATCHVERSION_GE  // has been defined in 1.4.1 which has a bug fix in  LCFourVector<T>
		LCFourVector<MCParticle>  mc4V( mcp ) ;
#else
		HepLorentzVector mc4V( mcp->getMomentum()[0], mcp->getMomentum()[1],
				mcp->getMomentum()[2], mcp->getEnergy() )  ;
#endif



		FastMCParticleType type = getParticleType(mcp ) ;


		IFourVectorSmearer* sm = _smearingVec[ type ] ;

		HepLorentzVector reco4v(0.,0.,0.,0.)  ;


		TVector3 mc3V = TVector3( mcp->getMomentum() );
		if( fabs(mc3V.CosTheta()) > 0.998) return 0;

		//std::cout << "Prove it work" << std::endl;
		if( _smear == 0 && _rejectNeutrino)
		{
	
			//std::cout << "Prove it work" << std::endl;	
			if( fabs( mcp->getPDG() ) == 22 )
			{
			 //std::cout << "ISR Test " << std::endl;
			 MCParticle* b_parent = mcp->getParents()[0];

			 while(b_parent->getParents().size() != 0)
			 {
				 b_parent = b_parent->getParents()[0];
			 }
				//do{
				//	 b_parent = b_parent->getParents()[0];
				//}
				//while(b_parent->getParents().size() != 0);

			 if( b_parent->getParents().size() == 0 && abs(b_parent->getPDG()) == 22 )
			 {
				 std::cout << "Got you ISR photon" << std::endl;
				 return 0;
			 }
			}

			// if we don't have a smearer registered we don't reconstruct the particle, e.g for neutrinos
			else if(mcp->getParents().size()==1 && (fabs(mcp->getParents()[0]->getPDG())==12 || fabs(mcp->getParents()[0]->getPDG())==94) && fabs(mcp->getPDG()) == 12)
			{
				std::cout << "Veto the prompt electron neutrino" << std::endl;
				return 0;
			}

			else if(mcp->getParents().size()==1 && (fabs(mcp->getParents()[0]->getPDG())==14 || fabs(mcp->getParents()[0]->getPDG())==94) && fabs(mcp->getPDG()) == 14)
			{
				std::cout << "Veto the prompt muon neutrino" << std::endl;
				return 0;
			}
			else if(mcp->getParents().size()==1 && (fabs(mcp->getParents()[0]->getPDG())==16 || fabs(mcp->getParents()[0]->getPDG())==94) && fabs(mcp->getPDG()) == 16)
			{
				std::cout << "Veto the prompt tau neutrino" << std::endl;
				return 0;
			}										
		}

		if( _smear && sm != 0  && 	mc4V.vect().mag() >  _momentumCut  )   
			reco4v = sm->smearedFourVector( mc4V , mcp->getPDG() ) ;
		else
			reco4v =  mc4V ;

		//
		ReconstructedParticleImpl* rec = 0 ;
		if(  reco4v.vect().mag() >  _momentumCut  ) {  

			rec = new ReconstructedParticleImpl ;
			float p[3] ;
			p[0] = reco4v.px() ;
			p[1] = reco4v.py() ;
			p[2] = reco4v.pz() ;

			rec->setMomentum( p ) ;
			rec->setMass( reco4v.m() ) ;
			rec->setEnergy( reco4v.e() ) ;
			rec->setCharge( mcp->getCharge() ) ;
			//std::cout<<"charge pdg mass = " <<mcp->getCharge()<<" "<<mcp->getPDG()<<" "<<mcp->getMass()<<std::endl;
			float vtx[3] ;
			vtx[0] = mcp->getVertex()[0] ;
			vtx[1] = mcp->getVertex()[1] ;
			vtx[2] = mcp->getVertex()[2] ;
			rec->setReferencePoint( vtx ) ;

			rec->setType(   mcp->getPDG() ) ;
			ReconstructedParticleImpl* dummy_part = new ReconstructedParticleImpl() ;
            v_dummy_part.push_back(dummy_part);
			dummy_part->id();
			rec->addParticle( dummy_part ) ; // dummy track to make it look like a real particle
			/*
			if( fabs(mcp->getCharge())>0.01 ) {
				TrackImpl* dummy_trk = new TrackImpl() ;
                v_dummy_trk.push_back(dummy_trk);
				dummy_trk->id();
				//std::cout<<"cid = "<<dummy->id()<<std::endl;
				rec->addTrack  ( dummy_trk  ) ; // dummy track to make it look like a real particlea !!! memory leakage
			}
			{
				ClusterImpl* dummy_clu = new ClusterImpl() ;
                v_dummy_clu.push_back(dummy_clu);
				//std::cout<<"nid = "<<dummy->id()<<std::endl;a
				rec->addCluster( dummy_clu ) ; // dummy cluster to make it look like a real  particle !!! memory leakage
			}
			*/
		}
		//
		return  rec ;
	}

} // namespace
#endif // MARLIN_CLHEP

