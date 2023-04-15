#pragma once
#include "../IsotrackTreesAnalysis.h"
#include <TVector3.h>
#include <string>

void IsotrackTreesAnalysis::initEOverPModule() {
  std::string eta_list[] = {"central","forward"};
  std::string detector[] = {"cemc","ihcal","ohcal"};
  int centrality_list[] = {30,50,70,90};

  histEoverPRaw[0] = new TH2F("ep_raw","",20,0,20,200,0,10);
  histEHcalOverPRaw[0] = new TH2F("ep_raw_hcal","",20,0,20,200,0,10);

  histEoverP_EMCalShower = new TH2F("ep emcal shower","",20,0,20,200,0,10);
  histEoverP_EMCalMIP = new TH2F("ep emcal mip","",20,0,20,200,0,10);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      histEoverPRaw[4*i+j+1] = new TH2F(TString::Format("ep_raw_hcal_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,200,0,10);
      histEHcalOverPRaw[4*i+j+1]= new TH2F(TString::Format("ep_raw_hcal_%s_eta_centrality_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,200,0,10);
    }
  }
}

void IsotrackTreesAnalysis::eOverPModule(int id, float totalEnergy, float totalHcalEnergy){

  float centrality_array[] = {20,40,60,80,100};

  histEoverPRaw[0]->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
  histEHcalOverPRaw[0]->Fill(m_tr_p[id], totalHcalEnergy / m_tr_p[id]);

  if(truthMipShowerClassifier(id) <= 2){
    histEoverP_EMCalShower->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
  }
  else if(truthMipShowerClassifier(id) > 2){
    histEoverP_EMCalMIP->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
  }
 
  if (fabs(m_tr_cemc_eta[id]) < 0.5) { 
    for (int j = 1; j < 5; j++) {
      if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
        histEoverPRaw[j-1]->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
        histEHcalOverPRaw[j-1]->Fill(m_tr_p[id], totalHcalEnergy / m_tr_p[id]);
      }
    }
  } else if (fabs(m_tr_cemc_eta[id]) < 1.0) {
    for (int j = 1; j < 5; j++) {
      if (!USE_CENTRALITY || (centrality > centrality_array[j-1]&& centrality < centrality_array[j])) {
        histEoverPRaw[3+j]->Fill(m_tr_p[id], totalEnergy / m_tr_p[id]);
        histEHcalOverPRaw[3+j]->Fill(m_tr_p[id], totalHcalEnergy / m_tr_p[id]);
      }
    }
  }
  
}
