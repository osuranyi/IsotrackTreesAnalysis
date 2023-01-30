#define IsotrackTreesAnalysis_cxx
#include "IsotrackTreesAnalysis.h"
#include "ClusterContainer.h"
#include "Tools.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

#include "selections/BasicEventSelection.h"
#include "selections/BasicTrackSelection.h"
#include "selections/TruthIsolatedTrackSelection.h"

#include "modules/TrackResolutionModule.h"
#include "modules/EOverPModule.h"
#include "modules/TrackRatesModule.h"

void IsotrackTreesAnalysis::Loop(){
    // Get the number of entries in the TChain
    long nentries = fChainTracks->GetEntries();

    ///////////////////////////////////////////////////
    // Initializations go here

    TFile* outputFile = new TFile("test_output.root", "RECREATE");

    initTrackResolutionModule();
    initEOverPModule();

    ///////////////////////////////////////////////////

    for(Long64_t jentry=0; jentry<nentries;jentry++) {
        LoadTree(jentry);
        GetEntry(jentry);
        processEvent();
    
        if(jentry % 1000 == 0)
            std::cout << jentry << "/" << nentries << " have been processed" << std::endl;
    }

    // Saving output file
    outputFile->Write();
}

// Process an event
void IsotrackTreesAnalysis::processEvent(){

    if(basicEventSelection()){

        for(int i = 0; i < m_trkmult; i++){
            if(basicTrackSelection(i)){
                //std::cout << "pass track selection" << std::endl;
                if(!USE_TRUTH_INFO || (USE_TRUTH_INFO && truthIsolatedTrackSelection(i))) {
                    processTrack(i);
                } 
            }
        }
    }
}

void IsotrackTreesAnalysis::processTrack(int id){

    MatchedClusterContainer cemcClusters;
    MatchedClusterContainer ihcalClusters;
    MatchedClusterContainer ohcalClusters;

    // Calculate the ids of all matched clusters
    if (USE_TOWER_INFO) {
        cemcClusters  = getMatchedTowers(id,cemc,CEMC_MATCHING_DR_CUT);
        ihcalClusters = getMatchedTowers(id,ihcal,IHCAL_MATCHING_DR_CUT);
        ohcalClusters = getMatchedTowers(id,ohcal,OHCAL_MATCHING_DR_CUT);
    } else {
        cemcClusters  = getMatchedClusters(id,cemc,CEMC_MATCHING_DR_CUT);
        ihcalClusters = getMatchedClusters(id,ihcal,IHCAL_MATCHING_DR_CUT);
        ohcalClusters = getMatchedClusters(id,ohcal,OHCAL_MATCHING_DR_CUT);
    }
    
    // Calculate energy of matched clusters
    float totalCemcEnergy = cemcClusters.getTotalEnergy();
    float totalIhcalEnergy = ihcalClusters.getTotalEnergy();
    float totalOhcalEnergy = ohcalClusters.getTotalEnergy();
    
    float totalEnergy = totalCemcEnergy + totalIhcalEnergy + totalOhcalEnergy;

    ///////////////////////////////////////////
    // Analysis modules should be added here //
    ///////////////////////////////////////////

    //trackResolutionModule(id, totalEnergy);
    eOverPModule(id, totalEnergy, cemcClusters, ihcalClusters, ohcalClusters);

}

