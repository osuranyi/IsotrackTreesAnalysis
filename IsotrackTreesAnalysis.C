#define IsotrackTreesAnalysis_cxx
#include "IsotrackTreesAnalysis.h"
#include "ClusterContainer.h"
#include "Tools.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

void IsotrackTreesAnalysis::Loop(){
    // Get the number of entries in the TChain
    Long64_t nentries = fChainTracks->GetEntriesFast();

    for(Long64_t jentry=0; jentry<nentries;jentry++) {
        LoadTree(jentry);
        GetEntry(jentry);
        processEvent();
    }
}

// Process an event
void IsotrackTreesAnalysis::processEvent(){

    const float CENTRALITY_CUT = 20.0;

    if(basicEventSelection(CENTRALITY_CUT)){
        const float D0_CUT = 0.15; // m
        const float Z0_CUT = 0.15; // m
        const float PT_CUT = 0.5;  // GeV
        const float MATCHED_PT_CUT = 0.2; // GeV
        const float MATCHED_DR_CUT = 0.4;

        for(int i = 0; i < m_trkmult; i++){
            if(basicTrackSelection(i,D0_CUT,Z0_CUT,PT_CUT,MATCHED_PT_CUT,MATCHED_DR_CUT)){
                processTrack(i);
            }
        }
    }
}

void IsotrackTreesAnalysis::processTrack(int id){

    // Calculate the ids of all matched clusters
    MatchedClusterContainer cemcClusters  = getMatchedClusters(id,cemc,0.2);
    MatchedClusterContainer ihcalClusters = getMatchedClusters(id,ihcal,0.2);
    MatchedClusterContainer ohcalClusters = getMatchedClusters(id,ohcal,0.2);

    // Calculate energy of matched clusters
    float totalCemcEnergy = cemcClusters.getTotalEnergy();
    float totalIhcalEnergy = ihcalClusters.getTotalEnergy();
    float totalOhcalEnergy = ohcalClusters.getTotalEnergy();
    
    float totalEnergy = totalCemcEnergy + totalIhcalEnergy + totalOhcalEnergy;

    ///////////////////////////////////////////
    // Analysis modules should be added here //
    ///////////////////////////////////////////

    //trackResolutionModule(id, totalEnergy);

    std::cout << "Isotrack found: " << m_tr_pt[id] << "\t" << m_tr_eta[id] << "\t" << m_tr_phi[id] << std::endl;
    std::cout << "Matched clusters: " << std::endl;

    for(int i = 0; i < cemcClusters.getNumberOfClusters(); i++){
        std::cout << cemcClusters.eta[i] << "\t" << cemcClusters.phi[i] << std::endl;
    }
}

