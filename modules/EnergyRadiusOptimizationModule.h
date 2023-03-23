#pragma once
#include "../IsotrackTreesAnalysis.h"
#include "../selections/MipShowerClassifier.h"
#include <TVector3.h>
#include <string>

// Things that I want to know from the g4hits:
//   When passing my emcal energy cut, what is the e/p distribution in the ihcal+ohcal?
//   When passing my emcal energy cut, what is the e/p distribution in a deltaR < 0.2 cone in the ihcal+ohcal

void IsotrackTreesAnalysis::initEnergyRadiusOptimizationModule() {
  energy_radius_purity = new TEfficiency("energy_radius_purity","Mip Purity;DeltaR;Energy (GeV)",15,0.0375,0.4125,17,0.1875,0.6125);
  energy_radius_efficiency = new TEfficiency("energy_radius_eff","Mip Efficiency;DeltaR;Energy (GeV)",15,0.0375,0.4125,17,0.1875,0.6125);
  energy_dist_mip = new TH1F("energy_dist_mip","",200,0,2);
  energy_dist_shower = new TH1F("energy_dist_shower","",400,0,4);

}

void IsotrackTreesAnalysis::energyRadiusOptimizationModule(int id, MatchedClusterContainer cemcClusters){

  // already found the matching cluster containers, want to find the energy in emcal for a certain radius and then fill efficiency plot
  float radii[] = {0.05,0.075,0.1,0.125,0.15,0.175,0.2,0.225,0.25,0.275,0.3,0.325,0.35,0.375,0.4,0.45};
  float energies[] = {0.2,0.225,0.25,0.275,0.3,0.325,0.35,0.375,0.4,0.425,0.45,0.475,0.5,0.525,0.55,0.575,0.6};

  bool mip;
  bool pass_cut;
  int classify = mipShowerClassifier(id);
  //std::cout << classify << std::endl;
  if (classify <= 2 || classify == 7) { mip = false; }
  else { mip = true; }

  // calculating the mip purity as a function of deltaR and energy 
  for (int i = 0; i < 15; i++) {
    float cemc_energy = cemcClusters.getTotalEnergy(radii[i]);
    for (int j = 0; j < 17; j++) {
      if (cemc_energy < energies[j]) {
        energy_radius_purity->Fill(mip, radii[i], energies[j]);
      }
    }
  }

  // calculating the mip efficiency as a function of deltaR and energy
  if (mip == true) {
    energy_dist_mip->Fill(cemcClusters.getTotalEnergy(0.2));
    for (int i = 0; i < 15; i++) {
      float cemc_energy = cemcClusters.getTotalEnergy(radii[i]);
      for (int j = 0; j < 17; j++) {
        if (cemc_energy < energies[j]) { pass_cut = true; }
        else { pass_cut = false; }
        energy_radius_efficiency->Fill(pass_cut, radii[i], energies[j]);
      }
    }
  } else {
    energy_dist_shower->Fill(cemcClusters.getTotalEnergy(0.2));
  }
}
