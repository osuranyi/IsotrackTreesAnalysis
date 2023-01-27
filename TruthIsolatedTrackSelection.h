#pragma once
#include <TVector3.h>
#include <set>
#include "IsotrackTreesAnalysis.h"

const float MATCHED_PT_CUT = 0.2; // GeV
const float MATCHED_DR_CUT = 0.4;
const float MATCHED_ETA_CUT = 1.0;

const std::set<int> neutral_pid = {-3322,-3212,-3122,-2112,-421,-14,-12,12,14,22,111,130,310,421,
                         2112,3122,3212,3322};

bool IsotrackTreesAnalysis::truthIsolatedTrackSelection(int id, float matchedPtCut, float matchedEtaCut, float matchedDrCut) {

    // Truth isolation condition
    TVector3 v1, v2;
    v1.SetPtEtaPhi(m_tr_pt[id], m_tr_eta[id], m_tr_phi[id]);
    for (int j = 0; j < m_g4; j++) {
        if (neutral_pid.find(m_g4_pid[j]) == neutral_pid.end() || m_g4_pt[j] > matchedPtCut || m_g4_eta[j] > matchedEtaCut) { continue; }

        v2.SetPtEtaPhi(m_g4_pt[j], m_g4_eta[j], m_g4_phi[j]);

        if (v1.DeltaR(v2) < matchedDrCut) {
            return false;
        }
    }

    return true;
}