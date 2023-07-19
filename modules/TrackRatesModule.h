#pragma once
#include "../IsotrackTreesAnalysis.h"
#include <TVector3.h>
#include <string>

void IsotrackTreesAnalysis::initTrackRatesModule() {
  std::string eta_list[] = {"central","forward"};
  int centrality_list[] = {30,50,70,90};
  histTrackTotal = new TH1F("total_track_rate","",20,0,20);

  for (int j = 0; j < 4; j++) {
    histTrackRate[j] = new TH1F(TString::Format("track_rate_centrality_%d",centrality_list[j]),"",20,0,20);
  }
  
}

void IsotrackTreesAnalysis::trackRatesModule(int id) {

  histTrackTotal->Fill(m_tr_p[id]);
  
  float centrality_array[] = {20,40,60,80,100};

  for (int j = 1; j < 5; j++) {
    if (!USE_CENTRALITY || (centrality > centrality_array[j-1] && centrality < centrality_array[j])) {
      histTrackRate[j-1]->Fill(m_tr_p[id]);
    }
  }
  
}