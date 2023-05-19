bool IsotrackTreesAnalysis::trackQualitySelection(int id){
    
    // Primary vertex selection condition
    // |z0| < 0.10
    /*float d0 = sqrt((m_tr_x[id]-m_vx[0])*(m_tr_x[id]-m_vx[0])+(m_tr_y[id]-m_vy[0])*(m_tr_y[id]-m_vy[0]));
    float z0 = fabs(m_tr_z[id]-m_vz[0]);

    if(!USE_PARTICLE_GUN && !(d0 < D0_CUT && z0 < Z0_CUT)){
        return false;
    }
*/

    if(!USE_PARTICLE_GUN){
        if(fabs(m_vx[0]) < 1E-9 && fabs(m_vy[0]) < 1E-9 && fabs(m_vz[0]) < 1E-9){
            return false;
        }

        if(fabs(m_vz[m_tr_vertex_id[id]]) > 10.0){
            return false;
        }

        // DCA cut
        if(fabs(m_tr_dca_xy[id]) > 0.02 || fabs(m_tr_dca_z[id]) > 0.02){
            return false;
        }
    }


    // Track quality criteria
    if(m_tr_chisq[id] / m_tr_ndf[id] > 10.0){
        return false;
    }
    
    return true;
}
