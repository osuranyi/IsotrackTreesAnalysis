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
    std::cout << "Selected" << std::endl;
  }
  else{
    std::cout << "Not selected" << std::endl;
  }

}
