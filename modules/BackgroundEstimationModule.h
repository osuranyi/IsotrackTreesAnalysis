#pragma once
#include "../IsotrackTreesAnalysis.h"
#include <TVector3.h>
#include <string>


void IsotrackTreesAnalysis::initBackgroundEstimationModule(){
  std::string eta_list[] = {"central","forward"};
  std::string detector[] = {"cemc","ihcal","ohcal"};
  int centrality_list[] = {30,50,70,90};

  //histEoverP[0] = new TH2F("ep_cut","",20,0,20,200,0,10);
  //histEoverPBkg[0] = new TH2F("epBkg","",20,0,20,2000,0,20);


  //histEoverPBkg_NoEtaNoCent = new TH2F("epBkg" ,"",20,0,20,200,0,10);
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {

      histEoverP[4*i+j] = new TH2F(TString::Format("ep_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"", 20,0,20,200,0,10);
      histEoverPBkg[4*i+j] = new TH2F(TString::Format("epBkg_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,20);
      histEBkg[4*i+j] = new TH2F(TString::Format("eBkg_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
    }
  }
  
}

void IsotrackTreesAnalysis::backgroundEstimationModule(int id, float totalEnergy, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters){
  // calculate energy of matched clusters as a function of delta_R
  float R1CemcEnergy = cemcClusters.getTotalEnergy(0.1);
  float R1IhcalEnergy = ihcalClusters.getTotalEnergy(0.1);
    
  float R2CemcEnergy = cemcClusters.getTotalEnergy(0.2);
  float R2IhcalEnergy = ihcalClusters.getTotalEnergy(0.2);
  float R2OhcalEnergy = ohcalClusters.getTotalEnergy(0.2);

  float centrality_array[] = {20,40,60,80,100};

  if (R1CemcEnergy < CEMC_MIP_ENERGY && R1IhcalEnergy < IHCAL_MIP_ENERGY && R2OhcalEnergy/m_tr_p[id] > 0.4) {
  //if (R1CemcEnergy < CEMC_MIP_ENERGY && R2OhcalEnergy/m_tr_p[id] > 0.4) {

    float R1Energy = R1CemcEnergy + R1IhcalEnergy;
    float R2Energy = R2CemcEnergy + R2IhcalEnergy;

    //histEoverP[0]->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
    //histEoverPBkg[0]->Fill(m_tr_p[id], 4.0/3.0 * (R2Energy - R1Energy) / m_tr_p[id]);
    //histEoverPBkg[0]->Fill(m_tr_p[id], 4.0/3.0 * (R2CemcEnergy - R1CemcEnergy) / m_tr_p[id]);

    // E/p background estimated from sideband method
    // 4/3 is used to correct the are of the R1-R2 annulus to the are of the R2 circle
    //histEoverPBkg_NoEtaNoCent->Fill(m_tr_p[id], 4./3. * (R2CemcEnergy - R1CemcEnergy) / m_tr_p[id]);
    
    if (fabs(m_tr_cemc_eta[id]) < 0.5) { 
      for (int j = 1; j < 5; j++) {
        if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
          histEoverP[j-1]->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
          histEoverPBkg[j-1]->Fill(m_tr_p[id], 4./3. * (R2Energy - R1Energy) / m_tr_p[id]);
          histEBkg[j-1]->Fill(m_tr_p[id], 4./3. * (R2Energy - R1Energy));
        }
      }
    } else if (fabs(m_tr_cemc_eta[id]) < 1.0) {
      for (int j = 1; j < 5; j++) {
        if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
          histEoverP[3+j]->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
          histEoverPBkg[3+j]->Fill(m_tr_p[id], 4./3. * (R2Energy - R1Energy) / m_tr_p[id]);
          histEBkg[3+j]->Fill(m_tr_p[id], 4./3. * (R2Energy - R1Energy));
        }
      }
    }  
  }
}
