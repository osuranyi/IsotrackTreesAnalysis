#define IsotrackTreesAnalysis_cxx
#include "IsotrackTreesAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void IsotrackTreesAnalysis::Loop(){

   Long64_t nentries = fChainTracks->GetEntriesFast();

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      LoadTree(jentry);
      GetEntry(jentry);
      processEvent();
   }
}

void IsotrackTreesAnalysis::processEvent(){
    if(basicEventSelection()){
        for(int i = 0; i < m_trkmult; i++){
            if(basicTrackSelection(i)){
                processTrack(i);
            }
        }
    }
}

void IsotrackTreesAnalysis::processTrack(int id){
    std::cout << "Isotrack found: " << m_tr_pt[id] << "\t" << m_tr_eta[id] << "\t" << m_tr_phi[id] << std::endl;
}
