#pragma once
#include <TVector3.h>
#include <set>
#include "../IsotrackTreesAnalysis.h"

int IsotrackTreesAnalysis::mipShowerClassifier(int id, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters) {
    // calculate energy of matched clusters as a function of delta_R
    float R1CemcEnergy = cemcClusters.getTotalEnergy(0.1);
    float R1IhcalEnergy = ihcalClusters.getTotalEnergy(0.1);
    
    if(R1CemcEnergy > CEMC_MIP_ENERGY)
        return cemc;
  
    if(R1IhcalEnergy > IHCAL_MIP_ENERGY)
        return ihcal;

    return ohcal;

  // R2OhcalEnergy/m_tr_p[id] > 0.4

}
