// Code for basic track selection

#include <TVector3.h>
#include "../IsotrackTreesAnalysis.h"

bool IsotrackTreesAnalysis::trackIsolationSelection(int id){
    
    // Only considering those tracks which reaches at least the IHCal
    if (m_tr_cemc_eta[id] < -998 || m_tr_cemc_phi[id] < -998/* || m_tr_ihcal_eta[id] < -998 || m_tr_ihcal_phi[id] < -998*/) {
        return false;
    }

    // Track isolation condition
    TVector3 v1, v2;

    // FIXME currently using quick fix for track projection, this should be fixed when appropritate projections are available
    v1.SetPtEtaPhi(1.0, m_tr_cemc_eta[id], 0.5*(m_tr_cemc_phi[id]+m_tr_ihcal_phi[id]));

    for(int j = 0; j < m_trkmult; j++){
        if(id == j){ continue; }

        // FIXME currently using quick fix for track projection, this should be fixed when appropritate projections are available

        v2.SetPtEtaPhi(1.0, m_tr_cemc_eta[j], 0.5*(m_tr_cemc_phi[j]+m_tr_ihcal_phi[j]));

        if(v2.Pt() > MATCHED_PT_CUT && v1.DeltaR(v2) < MATCHED_DR_CUT){
            return false;
        }
    }

    return true;
}
