#pragma once
#include "../IsotrackTreesAnalysis.h"
#include <TVector3.h>
#include <string>

void IsotrackTreesAnalysis::initEOverPModule() {
  std::string eta_list[] = {"central","forward"};
  std::string detector[] = {"cemc","ihcal","ohcal"};
  int centrality_list[] = {30,50,70,90};

  histEPvEPBkg = new TH2F("ep_v_ep_bkg","",200,0,10,200,0,10);
  histBkgRatiovP = new TH2F("ep_bkg_ratio_v_p","",20,0,20,200,0,10);
  histCemcVOhcalRaw = new TH2F("ep_cemc_v_ohcal_raw","",200,0,10,200,0,10);
  histCemcVOhcal = new TH2F("ep_cemc_v_ohcal_cut","",200,0,10,200,0,10);  

  histEoverPRaw_NoEtaNoCent = new TH2F("ep_raw","",20,0,20,200,0,10);
  histEoverPBkg_NoEtaNoCent = new TH2F("epBkg" ,"",20,0,20,200,0,10);

  for (int i = 0; i < 2; i++) {

    for (int j = 0; j < 4; j++) {

      // I think actually not having a centrality and eta dependence right now would be okay
      histEoverPRaw[4*i+j] = new TH2F(TString::Format("ep_raw_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,200,0,10);
      histEoverP[4*i+j] = new TH2F(TString::Format("ep_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"", 20,0,20,200,0,10);
      histEoverPBkg[4*i+j] = new TH2F(TString::Format("epBkg_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,200,0,10);
      histECemcBkg[4*i+j] = new TH1F(TString::Format("cemc_ebkg_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",400,0,20);
      histEIhcalBkg[4*i+j] = new TH1F(TString::Format("ihcal_ebkg_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",400,0,20);
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

  histCemcVOhcalRaw->Fill(R2CemcEnergy / m_tr_p[id], R2OhcalEnergy / m_tr_p[id]);

  // Raw E/p distribution without any eta and centrality binning
  histEoverPRaw_NoEtaNoCent->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);

  if (fabs(m_tr_eta[id]) < 0.5) { 
    for (int j = 1; j < 5; j++) {
      if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
        histEoverPRaw[j-1]->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
      }
    }
  } else if (fabs(m_tr_eta[id]) < 1.0) {
    for (int j = 1; j < 5; j++) {
      if (!USE_CENTRALITY || (centrality > centrality_array[j-1]&& centrality < centrality_array[j])) {
        histEoverPRaw[3+j]->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
      }
    }
  }
  
  if (R1CemcEnergy < CEMC_MIP_ENERGY && R1IhcalEnergy < IHCAL_MIP_ENERGY && R2OhcalEnergy/m_tr_p[id] > 0.4) {

    float R1Energy = R1CemcEnergy + R1IhcalEnergy;
    float R2Energy = R2CemcEnergy + R2IhcalEnergy;

    float ep = totalEnergy / m_tr_p[id];
    float ep_bkg = (R2Energy - R1Energy) / m_tr_p[id];

    histEPvEPBkg->Fill(ep,ep_bkg);
    histBkgRatiovP->Fill(m_tr_p[id],ep_bkg/ep);
    histCemcVOhcal->Fill(R2CemcEnergy / m_tr_p[id], R2OhcalEnergy / m_tr_p[id]);

    // E/p background estimated from sideband method
    // 4/3 is used to correct the are of the R1-R2 annulus to the are of the R2 circle
    histEoverPBkg_NoEtaNoCent->Fill(m_tr_p[id], 4./3. * (R2Energy - R1Energy) / m_tr_p[id]);

    if (fabs(m_tr_eta[id]) < 0.5) { 
      for (int j = 1; j < 5; j++) {
        if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
          histEoverP[j-1]->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
          histEoverPBkg[j-1]->Fill(m_tr_p[id], (R2Energy - R1Energy) / m_tr_p[id]);
          histECemcBkg[j-1]->Fill(R2CemcEnergy - R1CemcEnergy);
          histEIhcalBkg[j-1]->Fill(R2IhcalEnergy - R1IhcalEnergy);
        }
      }
    } else if (fabs(m_tr_eta[id]) < 1.0) {
      for (int j = 1; j < 5; j++) {
        if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
          histEoverP[3+j]->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
          histEoverPBkg[3+j]->Fill(m_tr_p[id], (R2Energy - R1Energy) / m_tr_p[id]);
          histECemcBkg[3+j]->Fill(R2CemcEnergy - R1CemcEnergy);
          histEIhcalBkg[3+j]->Fill(R2IhcalEnergy - R1IhcalEnergy);
        }
      }
    }
  }
}
