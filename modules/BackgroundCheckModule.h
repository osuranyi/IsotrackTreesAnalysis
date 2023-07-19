#pragma once
#include "../IsotrackTreesAnalysis.h"
#include <TVector3.h>
#include <string>
#include <set>

double areaOverlapRatio(double r2, double dr) {
  double r1 = 0.2;
  if (dr <= r1 - r2) {
    return 1.0;
  } 
  double d1 = (r1*r1 - r2*r2 + dr*dr)/(2*dr);
  double d2 = dr - d1;
  return (r1*r1*acos(d1/r1) - d1*sqrt(r1*r1-d1*d1) + r2*r2*acos(d2/r2) - d2*sqrt(r2*r2-d2*d2))/(M_PI*r2*r2);
} 

void IsotrackTreesAnalysis::initBackgroundCheckModule() {
  std::string eta_list[] = {"central","forward"};
  int centrality_list[] = {30,50,70,90};

  // if we have truth information, want to compare background estimated from sideband vs. using truth level information
  // want to look at both the 2D histogram of e/p_bkg vs e/p_neutralNeighbors and ratio of e/p_bkg to e/p_neutralNeighbors as a function of momentum 

  // to close the e/p background we shuold have e/p_bkg_truth + e/p_neutral_neighbors = e/p_bkg_track <- looking at averages or something in the distribution
  // so we will need both the e/p_bkg distribution and the e/p_neutral_neighbors distributions on their own 
  // real equation is e/p_bkg_truth - e/p_neutral_neighbors_truth = e/p_bkg_track - e/p_neutral_neighbors_track
  
  for (int i = 0; i < 4; i++) {
    histNeutralEnergy[i] = new TH1F(TString::Format("neutral_energy_%d",centrality_list[i]),"",5000,0,100);
    histNeutralNumber[i] = new TH1F(TString::Format("neutral_number_%d",centrality_list[i]),"",500,0,500);
  }
  /*
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {

      histNNN[4*i+j] = new TH1F(TString::Format("NNN_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",50,0,50);
      histNNEMraw[4*i+j] = new TH1F(TString::Format("NNEM_raw_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",50,0,50);
      histNNHraw[4*i+j] = new TH1F(TString::Format("NNH_raw_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",50,0,50);
      histNNEM[4*i+j] = new TH1F(TString::Format("NNEM_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",50,0,50);
      histNNH[4*i+j] = new TH1F(TString::Format("NNH_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",50,0,50);

      histENN[4*i+j] = new TH2F(TString::Format("eNN_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histENNtest[4*i+j] = new TH2F(TString::Format("eNNtest_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histEoverPNN[4*i+j] = new TH2F(TString::Format("epNN_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,20);
      histEoverPNNtest[4*i+j] = new TH2F(TString::Format("epNNtest_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,20);
      histCemcE[4*i+j] = new TH2F(TString::Format("CemcENN_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histIhcalE[4*i+j] = new TH2F(TString::Format("IhcalENN_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histBkgE[4*i+j] = new TH2F(TString::Format("BkgENN_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histBkgEoverPNN[4*i+j] = new TH2F(TString::Format("epBkgNN_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,20);

      histENEM[4*i+j] = new TH2F(TString::Format("eNEM_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histENEMtest[4*i+j] = new TH2F(TString::Format("eNEMtest_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histEoverPNEM[4*i+j] = new TH2F(TString::Format("epNEM_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,20);
      histEoverPNEMtest[4*i+j] = new TH2F(TString::Format("epNEMtest_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,20);
      histCemcENEM[4*i+j] = new TH2F(TString::Format("CemcNEM_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histIhcalENEM[4*i+j] = new TH2F(TString::Format("IhcalNEM_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histBkgENEM[4*i+j] = new TH2F(TString::Format("BkgNEM_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histBkgEoverPNEM[4*i+j] = new TH2F(TString::Format("epBkgNEM_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,20);

      histENH[4*i+j] = new TH2F(TString::Format("eNH_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histENHtest[4*i+j] = new TH2F(TString::Format("eNHtest_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histEoverPNH[4*i+j] = new TH2F(TString::Format("epNH_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,20);
      histEoverPNHtest[4*i+j] = new TH2F(TString::Format("epNHtest_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,20);
      histCemcENH[4*i+j] = new TH2F(TString::Format("CemcNH_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histIhcalENH[4*i+j] = new TH2F(TString::Format("IhcalNH_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histBkgENH[4*i+j] = new TH2F(TString::Format("BkgNH_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,40);
      histBkgEoverPNH[4*i+j] = new TH2F(TString::Format("epBkgNH_%s_%d",eta_list[i].c_str(),centrality_list[j]),"",20,0,20,2000,0,20);
      
    }
  }*/
  
}

void IsotrackTreesAnalysis::backgroundCheckModule(int id, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters){

  const std::set<int> neutral_pid = {-3322,-3212,-3122,-2112,-421,-14,-12,12,14,22,111,130,310,421,
                    2112,3122,3212,3322};

  
  TVector3 v1, v2;
  v1.SetPtEtaPhi(m_tr_pt[id], m_tr_cemc_eta[id], 0.5*(m_tr_cemc_phi[id]+m_tr_outer_cemc_phi[id]));
  float centrality_array[] = {20,40,60,80,100};
  float e_nn = 0;
  int n_nn = 0;
  for (int k = 0; k < m_g4; k++) {
    if (neutral_pid.find(m_g4_pid[k]) == neutral_pid.end() || m_g4_pt[k] < MATCHED_NEUTRAL_TRUTH_PT_CUT || fabs(m_g4_eta[k]) > MATCHED_NEUTRAL_TRUTH_ETA_CUT) { continue; }
            
    v2.SetPtEtaPhi(m_g4_pt[k], m_g4_eta[k], m_g4_phi[k]);
    if (v1.DeltaR(v2) < MATCHED_DR_CUT) {
      if (m_g4_pid[k] == 111) { 
        continue;
      } else {
        n_nn++;
        e_nn += m_g4_e[k];
      }
    }
  }

  for (int j = 1; j < 5; j++) {
    if (centrality > centrality_array[j-1] && centrality < centrality_array[j]) {
      histNeutralEnergy[j-1]->Fill(e_nn);
      histNeutralNumber[j-1]->Fill(n_nn);
    }
  }
  /*
  // calculate energy of matched clusters as a function of delta_R
  float R1CemcEnergy = cemcClusters.getTotalEnergy(0.1);
  float R1IhcalEnergy = ihcalClusters.getTotalEnergy(0.1);
    
  float R2CemcEnergy = cemcClusters.getTotalEnergy(0.2);
  float R2IhcalEnergy = ihcalClusters.getTotalEnergy(0.2);
  float R2OhcalEnergy = ohcalClusters.getTotalEnergy(0.2);

  float centrality_array[] = {20,40,60,80,100};
  
  //if (R1CemcEnergy < CEMC_MIP_ENERGY && R1IhcalEnergy < IHCAL_MIP_ENERGY && R2OhcalEnergy/m_tr_p[id] > 0.4) {

    float R1Energy = R1CemcEnergy + R1IhcalEnergy;
    float R2Energy = R2CemcEnergy + R2IhcalEnergy;

    float ep_nn = 0;
    float ep_nn_test = 0;
    float ep_nem = 0;
    float ep_nem_test = 0;
    float ep_nh = 0;
    float ep_nh_test = 0;
    double dr = 0;
    double r_gamma = 0.022;
    double r_hadron = 0.2;

    int n_nn = 0;
    int n_nh = 0;
    int n_nem = 0;

    //std::cout << "Neutral neighbor check: e/p_bkg = " << ep_bkg << " p = " << m_tr_p[id] << std::endl;
    bool NEM = false;
    bool NH = false;

    TVector3 v1, v2;
    v1.SetPtEtaPhi(m_tr_pt[id], m_tr_cemc_eta[id], 0.5*(m_tr_cemc_phi[id]+m_tr_outer_cemc_phi[id]));
    for (int j = 0; j < m_g4; j++) {
      if (neutral_pid.find(m_g4_pid[j]) == neutral_pid.end() || m_g4_pt[j] < MATCHED_NEUTRAL_TRUTH_PT_CUT || fabs(m_g4_eta[j]) > MATCHED_NEUTRAL_TRUTH_ETA_CUT) { continue; }

      v2.SetPtEtaPhi(m_g4_pt[j], m_g4_eta[j], m_g4_phi[j]);
      dr = double(v1.DeltaR(v2));

      if (dr < 0.4) {

        n_nn++;
        // neutral em particles
        if (m_g4_pid[j] == 111) { 
          continue;
        } else if (m_g4_pid[j] == 22) { 
          NEM = true;
          n_nem++;
          ep_nem += m_g4_e[j];
          ep_nn += m_g4_e[j];
          ep_nem_test += areaOverlapRatio(r_gamma,dr) * m_g4_e[j];
          ep_nn_test += areaOverlapRatio(r_gamma,dr) * m_g4_e[j];

        // neutral hadrons 
        } else {
          NH = true;
          n_nh++;
          ep_nh += m_g4_e[j];
          ep_nn += m_g4_e[j];
          ep_nh_test += areaOverlapRatio(r_hadron,dr) * m_g4_e[j];
          ep_nn_test += areaOverlapRatio(r_hadron,dr) * m_g4_e[j];
        }
      }
    }

    if (fabs(m_tr_cemc_eta[id]) < 0.5) {
      for (int j = 1; j < 5; j++) {
        if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
          histENN[j-1]->Fill(m_tr_p[id], ep_nn);
          histENNtest[j-1]->Fill(m_tr_p[id], ep_nn_test);
          histBkgE[j-1]->Fill(m_tr_p[id], (4/3)*(R2Energy - R1Energy));
          histBkgEoverPNN[j-1]->Fill(m_tr_p[id], (4/3)*(R2Energy - R1Energy)/m_tr_p[id]);
          histNNN[j-1]->Fill(n_nn);
          histNNEMraw[j-1]->Fill(n_nem);
          histNNHraw[j-1]->Fill(n_nh);
          if (NEM && !NH) {
            histCemcENEM[j-1]->Fill(m_tr_p[id], R2CemcEnergy - R1CemcEnergy);
            histIhcalENEM[j-1]->Fill(m_tr_p[id], R2IhcalEnergy - R1IhcalEnergy);
            histBkgENEM[j-1]->Fill(m_tr_p[id], R2Energy - R1Energy);
            histENEM[j-1]->Fill(m_tr_p[id], ep_nem);
            histENEMtest[j-1]->Fill(m_tr_p[id], ep_nem_test);
            histBkgEoverPNEM[j-1]->Fill(m_tr_p[id], (4/3)*(R2Energy - R1Energy)/m_tr_p[id]);
            histNNEM[j-1]->Fill(n_nem);
          }
          if (!NEM && NH) {
            histCemcENH[j-1]->Fill(m_tr_p[id], R2CemcEnergy - R1CemcEnergy);
            histIhcalENH[j-1]->Fill(m_tr_p[id], R2IhcalEnergy - R1IhcalEnergy);
            histBkgENH[j-1]->Fill(m_tr_p[id], R2Energy - R1Energy);
            histENH[j-1]->Fill(m_tr_p[id], ep_nh);
            histENHtest[j-1]->Fill(m_tr_p[id], ep_nh_test);
            histBkgEoverPNH[j-1]->Fill(m_tr_p[id], (4/3)*(R2Energy - R1Energy)/m_tr_p[id]);
            histNNH[j-1]->Fill(n_nh);
          }
        }
      }
    } else if (fabs(m_tr_cemc_eta[id]) < 1.0) {
      for (int j = 1; j < 5; j++) {
        if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
          histENN[3+j]->Fill(m_tr_p[id], ep_nn);
          histENNtest[3+j]->Fill(m_tr_p[id], ep_nn_test);
          histBkgE[3+j]->Fill(m_tr_p[id], (4/3)*(R2Energy - R1Energy));
          histBkgEoverPNN[3+j]->Fill(m_tr_p[id], (4/3)*(R2Energy - R1Energy)/m_tr_p[id]);
          histNNN[3+j]->Fill(n_nn);
          histNNEMraw[3+j]->Fill(n_nem);
          histNNHraw[3+j]->Fill(n_nh);
          if (NEM && !NH) {
            histCemcENEM[3+j]->Fill(m_tr_p[id], R2CemcEnergy - R1CemcEnergy);
            histIhcalENEM[3+j]->Fill(m_tr_p[id], R2IhcalEnergy - R1IhcalEnergy);
            histBkgENEM[3+j]->Fill(m_tr_p[id], R2Energy - R1Energy);
            histENEM[3+j]->Fill(m_tr_p[id], ep_nem);
            histENEMtest[3+j]->Fill(m_tr_p[id], ep_nem_test);
            histBkgEoverPNEM[3+j]->Fill(m_tr_p[id], (4/3)*(R2Energy - R1Energy)/m_tr_p[id]);
            histNNEM[3+j]->Fill(n_nem);
          }
          if (!NEM && NH) {
            histCemcENH[3+j]->Fill(m_tr_p[id], R2CemcEnergy - R1CemcEnergy);
            histIhcalENH[3+j]->Fill(m_tr_p[id], R2IhcalEnergy - R1IhcalEnergy);
            histBkgENH[3+j]->Fill(m_tr_p[id], R2Energy - R1Energy);
            histENH[3+j]->Fill(m_tr_p[id], ep_nh);
            histENHtest[3+j]->Fill(m_tr_p[id], ep_nh_test);
            histBkgEoverPNH[3+j]->Fill(m_tr_p[id], (4/3)*(R2Energy - R1Energy)/m_tr_p[id]);
            histNNH[3+j]->Fill(n_nh);
          }
        }
      }
    }

    ep_nem /= m_tr_p[id];
    ep_nem_test /= m_tr_p[id];
    ep_nh /= m_tr_p[id];
    ep_nh_test /= m_tr_p[id];
    ep_nn /= m_tr_p[id];
    ep_nn_test /= m_tr_p[id];

    if (fabs(m_tr_cemc_eta[id]) < 0.5) { 
      for (int j = 1; j < 5; j++) {
        if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
          histEoverPNN[j-1]->Fill(m_tr_p[id], ep_nn);
          histEoverPNNtest[j-1]->Fill(m_tr_p[id], ep_nn_test);
          if (NEM && !NH) {
            histEoverPNEM[j-1]->Fill(m_tr_p[id], ep_nem);
            histEoverPNEMtest[j-1]->Fill(m_tr_p[id], ep_nem_test);
          }
          if (!NEM && NH) {
            histEoverPNH[j-1]->Fill(m_tr_p[id], ep_nh);
            histEoverPNHtest[j-1]->Fill(m_tr_p[id], ep_nh_test);
          }
        }
      }
    } else if (fabs(m_tr_cemc_eta[id]) < 1.0) {
      for (int j = 1; j < 5; j++) {
        if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
          histEoverPNN[3+j]->Fill(m_tr_p[id], ep_nn);
          histEoverPNNtest[3+j]->Fill(m_tr_p[id], ep_nn_test);
          if (NEM && !NH) {
            histEoverPNEM[3+j]->Fill(m_tr_p[id], ep_nem);
            histEoverPNEMtest[3+j]->Fill(m_tr_p[id], ep_nem_test);
          }
          if (!NEM && NH) {
            histEoverPNH[3+j]->Fill(m_tr_p[id], ep_nh);
            histEoverPNHtest[3+j]->Fill(m_tr_p[id], ep_nh_test);
          }
        }
      }
    }*/
  //}
}
