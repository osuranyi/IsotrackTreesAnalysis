#define IsotrackTreesAnalysis_cxx
#include "IsotrackTreesAnalysis.h"
#include "ClusterContainer.h"
#include "Tools.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <string>

#include "selections/BasicEventSelection.h"
#include "selections/BasicTrackSelection.h"
#include "selections/TrackKinematicSelection.h"
#include "selections/TrackIsolationSelection.h"
#include "selections/TrackQualitySelection.h"
#include "selections/TruthIsolatedTrackSelection.h"
#include "selections/TruthMipShowerClassifier.h"
#include "selections/MipShowerClassifier.h"

#include "modules/TrackResolutionModule.h"
#include "modules/EOverPModule.h"
#include "modules/TrackRatesModule.h"
#include "modules/ChecksModule.h"
#include "modules/TrackQualityModule.h"
#include "modules/VertexModule.h"
#include "modules/ZeroShowerEnergyModule.h"
#include "modules/BackgroundEstimationModule.h"
#include "modules/BackgroundCheckModule.h"
#include "modules/EnergyRadiusOptimizationModule.h"
#include "modules/ShowerSizeModule.h"

#include "postprocess/BackgroundDeconvolution.h"

void IsotrackTreesAnalysis::Loop(){
    
    // Get the number of entries in the TChain
    long nentries = fChainTracks->GetEntries();

    /////////////////////////////
    // Initializations go here //
    /////////////////////////////

    TFile* outputFile = new TFile(OUTPUT_FILENAME.c_str(), "RECREATE");

    initTrackQualityModule();
    initVertexModule();
    //initTrackResolutionModule();
    initTrackRatesModule();
    initEOverPModule();
    initChecksModule();
    //if (USE_PARTICLE_GUN) initEnergyRadiusOptimizationModule();

    initBackgroundEstimationModule();
    initBackgroundCheckModule();

    //initZeroShowerEnergyModule();
    //initShowerSizeModule();

    ///////////////////////////////////////////////////

    cutFlow = new TH1F("cut flow",";Selection;Selected events",7,0,7);

    for(Long64_t jentry=0;jentry<nentries;jentry++) {
        LoadTree(jentry);
        GetEntry(jentry);
        processEvent();
    
        if(jentry % 1000 == 0)
            std::cout << jentry << "/" << nentries << " have been processed" << std::endl;
    }

    // Postprocess 
    
    //backgroundDeconvolution();

    // Saving output file
    outputFile->Write();
}

// Process an event
void IsotrackTreesAnalysis::processEvent(){

    vertexModule();
    cutFlow->Fill(0);
    if (basicEventSelection()) {
        cutFlow->Fill(1);
        for (int i = 0; i < m_trkmult; i++){
            if(trackKinematicSelection(i) && trackIsolationSelection(i)){
                cutFlow->Fill(2);
                trackQualityModule(i);
                if(trackQualitySelection(i)){     //(basicTrackSelection(i)){
                    cutFlow->Fill(3);

                    MatchedClusterContainer cemcClusters;
                    MatchedClusterContainer ihcalClusters;
                    MatchedClusterContainer ohcalClusters;

                    // Calculate the ids of all matched clusters
                    if(USE_TOWER_INFO == 1){
                        cemcClusters  = getMatchedTowers(i,cemc,CEMC_MATCHING_DR_CUT);
                        ihcalClusters = getMatchedTowers(i,ihcal,IHCAL_MATCHING_DR_CUT);
                        ohcalClusters = getMatchedTowers(i,ohcal,OHCAL_MATCHING_DR_CUT);
                    }
                    else if(USE_TOWER_INFO == 2){
                        cemcClusters  = getMatchedSimTowers(i,cemc,CEMC_MATCHING_DR_CUT);
                        ihcalClusters = getMatchedSimTowers(i,ihcal,IHCAL_MATCHING_DR_CUT);
                        ohcalClusters = getMatchedSimTowers(i,ohcal,OHCAL_MATCHING_DR_CUT);
                    }
                    else {
                        cemcClusters  = getMatchedClusters(i,cemc,CEMC_MATCHING_DR_CUT);
                        ihcalClusters = getMatchedClusters(i,ihcal,IHCAL_MATCHING_DR_CUT);
                        ohcalClusters = getMatchedClusters(i,ohcal,OHCAL_MATCHING_DR_CUT);
                    }
                   
                    //assert(m_tr_cemc_eta[i] > -98 && m_tr_cemc_phi[i] > -98 && fabs(m_tr_cemc_eta[i]) <= 1.0);
                    //if (!USE_TRUTH_INFO || (USE_TRUTH_INFO && truthIsolatedTrackSelection(i))) {
                        //if (!USE_PARTICLE_GUN || (USE_PARTICLE_GUN && m_tr_truth_track_id[i] == 1 && mipTruthShowerClassifier(i) > 3)) {
                        //}
                    //}

                    // Process tracks which MIPs through the EMCal and starts to shower later

                    if (!USE_TRUTH_INFO || (USE_TRUTH_INFO && truthIsolatedTrackSelection(i))){
                        //FIXME if(mipShowerClassifier(i,cemcClusters,ihcalClusters,ohcalClusters) >= SHOWER_START){
                        cutFlow->Fill(4);
                        if(!USE_PARTICLE_GUN || (USE_PARTICLE_GUN && m_tr_truth_track_id[i] == 1)){ // FIXME
                            cutFlow->Fill(5);
                            processTrack(i,cemcClusters,ihcalClusters,ohcalClusters);
                        }
                        //}
                    }
                }
            }
        }
    }
}

void IsotrackTreesAnalysis::processTrack(int id, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters){

    // Calculate energy of matched clusters
    float totalCemcEnergy = cemcClusters.getTotalEnergy();
    float totalIhcalEnergy = ihcalClusters.getTotalEnergy();
    float totalOhcalEnergy = ohcalClusters.getTotalEnergy();
    
    float totalEnergy = totalCemcEnergy + totalIhcalEnergy + totalOhcalEnergy;
    float totalHcalEnergy = totalIhcalEnergy + totalOhcalEnergy;
    
    //else if(SHOWER_START == ihcal)
    //    totalEnergy = totalIhcalEnergy + totalOhcalEnergy;
    //else if(SHOWER_START == ohcal)
    //    totalEnergy = totalOhcalEnergy;

    ///////////////////////////////////////////
    // Analysis modules should be added here //
    ///////////////////////////////////////////

    //trackResolutionModule(id, totalEnergy);
    trackRatesModule(id);
    eOverPModule(id, totalEnergy, totalHcalEnergy);
    checksModule(cemcClusters, ihcalClusters, ohcalClusters);

    if(SHOWER_START == cemc){
      backgroundEstimationModule(id, totalEnergy, cemcClusters, ihcalClusters, ohcalClusters);
      backgroundCheckModule(id, cemcClusters, ihcalClusters, ohcalClusters);
    }
    
    if(USE_TOWER_INFO && USE_PARTICLE_GUN){
        cutFlow->Fill(6);
        showerSizeModule(id, cemcClusters, ihcalClusters, ohcalClusters);
        zeroShowerEnergyModule(id, totalCemcEnergy, totalIhcalEnergy, totalOhcalEnergy);
        energyRadiusOptimizationModule(id, cemcClusters);

    }
}
