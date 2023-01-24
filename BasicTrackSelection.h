// Code for basic track selection

#include <TVector3.h>
#include "IsotrackTreesAnalysis.h"

bool IsotrackTreesAnalysis::basicTrackSelection(int id, float d0Cut, float z0Cut, float ptCut, float matchedPtCut, float matchedDrCut){
    
    // Primary vertex selection condition
    // d0 < 0.15, z0 < 0.15
    float d0 = sqrt((m_tr_x[id]-m_vx[0])*(m_tr_x[id]-m_vx[0])+(m_tr_y[id]-m_vy[0])*(m_tr_y[id]-m_vy[0]));
    float z0 = fabs(m_tr_z[id]-m_vz[0]);

    if(!(d0 < d0Cut && z0 < z0Cut)){
        return false;
    }

    // Track momentum cut
    if(m_tr_pt[id] < ptCut){
        return false;
    }

    // Track isolation condition
    TVector3 v1, v2;
    v1.SetPtEtaPhi(m_tr_pt[id], m_tr_eta[id], m_tr_phi[id]);
    for(int j = 0; j < m_trkmult; j++){
        if(id == j){ continue; }

        v2.SetPtEtaPhi(m_tr_pt[j], m_tr_eta[j], m_tr_phi[j]);

        if(v2.Pt() > matchedPtCut && v1.DeltaR(v2) < matchedDrCut){
            return false;
        }
    }

    return true;
}
