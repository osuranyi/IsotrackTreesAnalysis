#pragma once
#include "ClusterContainer.h"
//#include "IsotrackTreesAnalysis.h"
#include <TVector.h>

// Match clusters to tracks
MatchedClusterContainer IsotrackTreesAnalysis::getMatchedClusters(int id, caloType type, float dRThreshold){
    
    MatchedClusterContainer clusterContainer;
    TVector3 track, cluster;

    switch(type){

        case cemc:
            // Check if EMCal is reached
            for(int i = 0; i < m_clsmult_cemc; i++){ 
                if(m_tr_cemc_eta[id] > -998){
                    track.SetPtEtaPhi(1.0, m_tr_cemc_eta[id], m_tr_cemc_phi[id]); // for the track we only need the direction!
                    cluster.SetPtEtaPhi(m_cl_cemc_e[i]/cosh(m_cl_cemc_eta[i]), m_cl_cemc_eta[i], m_cl_cemc_phi[i]);
                    float dR = track.DeltaR(cluster);
                    if(dR < dRThreshold){
                        clusterContainer.addCluster(cluster, dR);
                    }
                }
            }
            break;

        case ihcal:
            // Check if IHCal is reached
            for(int i = 0; i < m_clsmult_ihcal; i++){ 
                if(m_tr_ihcal_eta[id] > -998){
                    track.SetPtEtaPhi(1.0, m_tr_ihcal_eta[id], m_tr_ihcal_phi[id]); // for the track we only need the direction!
                    cluster.SetPtEtaPhi(m_cl_ihcal_e[i]/cosh(m_cl_ihcal_eta[i]), m_cl_ihcal_eta[i], m_cl_ihcal_phi[i]);
                    float dR = track.DeltaR(cluster);
                    if(dR < dRThreshold){
                        clusterContainer.addCluster(cluster, dR);
                    }
                }
            }
            break;

        case ohcal:
            // Check if OHCal is reached
            for(int i = 0; i < m_clsmult_ihcal; i++){
                if(m_tr_ohcal_eta[id] > -998){
                    track.SetPtEtaPhi(1.0, m_tr_ohcal_eta[id], m_tr_ohcal_phi[id]); // for the track we only need the direction!
                    cluster.SetPtEtaPhi(m_cl_ohcal_e[i]/cosh(m_cl_ohcal_eta[i]), m_cl_ohcal_eta[i], m_cl_ohcal_phi[i]);
                    float dR = track.DeltaR(cluster);
                    if(dR < dRThreshold){
                        clusterContainer.addCluster(cluster, dR);
                    }
                }
            }
            break;
    }

    return clusterContainer;
}
