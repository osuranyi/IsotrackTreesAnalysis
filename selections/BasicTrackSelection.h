// Code for basic track selection

#include <TVector3.h>
#include "../IsotrackTreesAnalysis.h"

bool IsotrackTreesAnalysis::basicTrackSelection(int id){
    
    // Primary vertex selection condition
    // |z0| < 0.10
    /*float d0 = sqrt((m_tr_x[id]-m_vx[0])*(m_tr_x[id]-m_vx[0])+(m_tr_y[id]-m_vy[0])*(m_tr_y[id]-m_vy[0]));
    float z0 = fabs(m_tr_z[id]-m_vz[0]);

    if(!USE_PARTICLE_GUN && !(d0 < D0_CUT && z0 < Z0_CUT)){
        return false;
    }
    
    if(fabs(m_vz[m_tr_vertex_id[id]]) > 10.0){
        return false;
    }*/

    // Track quality criteria
    if(m_tr_chisq[id] / m_tr_ndf[id] > 10.0){
        return false;
    }

    // DCA cut --> FIXME: what is the unit of DCA?? Probably cm, cut should be 20um
    if(fabs(m_tr_dca_xy[id]) > 0.002 || fabs(m_tr_dca_z[id]) > 0.002){
        return false;
    }

    // Only considering those tracks which reaches at least the IHCal
    if (m_tr_cemc_eta[id] < -998 || m_tr_cemc_phi[id] < -998/* || m_tr_ihcal_eta[id] < -998 || m_tr_ihcal_phi[id] < -998*/) {
        return false;
    }
    
    // Track momentum cut
    if(m_tr_pt[id] < PT_CUT || fabs(m_tr_cemc_eta[id]) > 1.0){
        return false;
    }

    // Track isolation condition
    TVector3 v1, v2;

    // FIXME currently using quick fix for track projection, this should be fixed when appropritate projections are available
    v1.SetPtEtaPhi(1.0, m_tr_cemc_eta[id], /*0.5*(*/m_tr_cemc_phi[id]/*+m_tr_ihcal_phi[id])*/);

    for(int j = 0; j < m_trkmult; j++){
        if(id == j){ continue; }

        // FIXME currently using quick fix for track projection, this should be fixed when appropritate projections are available

        v2.SetPtEtaPhi(1.0, m_tr_cemc_eta[j], /*0.5*(*/m_tr_cemc_phi[j]/*+m_tr_ihcal_phi[j])*/);

        if(v2.Pt() > MATCHED_PT_CUT && v1.DeltaR(v2) < MATCHED_DR_CUT){
            return false;
        }
    }

    return true;
}
