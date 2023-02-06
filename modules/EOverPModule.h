#pragma once
#include "../IsotrackTreesAnalysis.h"
#include <TVector3.h>
#include <string>

void IsotrackTreesAnalysis::initEOverPModule() {
  std::string eta_list[] = {"central","forward"};
  int centrality_list[] = {30,50,70,90};

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      histEoverPRaw[4*i+j] = new TH2F(TString::Format("ep_raw_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,200,0,10);
      histEoverP[4*i+j] = new TH2F(TString::Format("ep_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"", 20,0,20,200,0.0,10);
      histEoverPBkg[4*i+j] = new TH2F(TString::Format("epBkg_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,200,0,10);
      histECemcBkg[4*i+j] = new TH1F(TString::Format("cemc_ebkg_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",400,0,20);
      histEIhcalBkg[4*i+j] = new TH1F(TString::Format("ihcal_ebkg_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",400,0,20);
      histCemcVOhcalRaw[4*i+j] = new TH2F(TString::Format("cemc_ohcal_raw_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",200,0,4,200,0,10);
      histCemcVOhcal[4*i+j] = new TH2F(TString::Format("cemc_ohcal_cut_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",200,0,4,200,0,10);
    }
  }
}

void IsotrackTreesAnalysis::eOverPModule(int id, float totalEnergy, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters){

	// calculate energy of matched clusters as a function of delta_R
  float R1CemcEnergy = cemcClusters.getTotalEnergy(0.1);
  float R1IhcalEnergy = ihcalClusters.getTotalEnergy(0.1);
    
  float R2CemcEnergy = cemcClusters.getTotalEnergy(0.2);
  float R2IhcalEnergy = ihcalClusters.getTotalEnergy(0.2);
  float R2OhcalEnergy = ohcalClusters.getTotalEnergy(0.2);

  float centrality_array[] = {20,40,60,80,100};
  
  if (m_tr_eta[id] < 0.5) { 
    for (int j = 1; j < 5; j++) {
      if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
        histCemcVOhcalRaw[j-1]->Fill(R2CemcEnergy / m_tr_p[id], R2OhcalEnergy / m_tr_p[id]); 
        histEoverPRaw[j-1]->Fill(totalEnergy / m_tr_p[id], m_tr_p[id]);
      }
    }
  } else {
    for (int j = 1; j < 5; j++) {
      if (!USE_CENTRALITY || (centrality > centrality_array[j-1]&& centrality < centrality_array[j])) {
        histCemcVOhcalRaw[3+j]->Fill(R2CemcEnergy / m_tr_p[id], R2OhcalEnergy / m_tr_p[id]);
        histEoverPRaw[3+j]->Fill(totalEnergy / m_tr_p[id], m_tr_p[id]);
      }
    }
  }
  
  if (R1CemcEnergy < CEMC_MIP_ENERGY && R1IhcalEnergy < IHCAL_MIP_ENERGY && R2OhcalEnergy/m_tr_p[id] > 0.6) {

    float R1Energy = R1CemcEnergy + R1IhcalEnergy;
    float R2Energy = R2CemcEnergy + R2IhcalEnergy;

    if (m_tr_eta[id] < 0.5) { 
      for (int j = 1; j < 5; j++) {
        if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
          histEoverP[j-1]->Fill(totalEnergy / m_tr_p[id], m_tr_p[id]);
          histEoverPBkg[j-1]->Fill((R2Energy - R1Energy) / m_tr_p[id], m_tr_p[id]);
          histECemcBkg[j-1]->Fill(R2CemcEnergy - R1CemcEnergy);
          histEIhcalBkg[j-1]->Fill(R2IhcalEnergy - R1IhcalEnergy);
          histCemcVOhcal[j-1]->Fill(R2CemcEnergy / m_tr_p[id], R2OhcalEnergy / m_tr_p[id]);
        }
      }
    } else {
      for (int j = 1; j < 5; j++) {
        if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
          histEoverP[3+j]->Fill(totalEnergy / m_tr_p[id], m_tr_p[id]);
          histEoverPBkg[3+j]->Fill((R2Energy - R1Energy) / m_tr_p[id], m_tr_p[id]);
          histECemcBkg[3+j]->Fill(R2CemcEnergy - R1CemcEnergy);
          histEIhcalBkg[3+j]->Fill(R2IhcalEnergy - R1IhcalEnergy);
          histCemcVOhcal[3+j]->Fill(R2CemcEnergy / m_tr_p[id], R2OhcalEnergy / m_tr_p[id]);
        }
      }
    }
  }
}
