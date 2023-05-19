void IsotrackTreesAnalysis::initVertexModule(){
    x_pv = new TH1F("x pv",";x_{PV} [cm];Entries",100,-0.2,0.2);
    y_pv = new TH1F("y pv",";y_{PV} [cm];Entries",100,-0.2,0.2);
    z_pv = new TH1F("z pv",";z_{PV} [cm];Entries",100, -20.,20.);
    r_pv = new TH1F("r pv",";r_{PV} [cm];Entries",100, 0.0,0.2);

    xy_pv = new TH2F("xy pv",";x_{PV} [cm];y_{PV} [cm]",100,-0.5,0.5,100,-0.5,0.5);
    zr_pv = new TH2F("zr pv",";z_{PV} [cm];r_{PV} [cm]",100,-20.,20.0,100, 0.0,0.5);

    nTrackRealVertex = new TH1F("ntrack real vertex",";Number of tracks;Entries",30,0,30);
    nTrackZeroPosVertex = new TH1F("ntrack zero pos vertex",";Number of tracks;Entries",30,0,30);
}

void IsotrackTreesAnalysis::vertexModule(){
    if(m_vtxmult > 0){
        if(fabs(m_vx[0]) > 1E-9 || fabs(m_vy[0]) > 1E-9 || fabs(m_vz[0]) > 1E-9){
            x_pv->Fill(m_vx[0]);
            y_pv->Fill(m_vy[0]);
            z_pv->Fill(m_vz[0]);
            float r = sqrt(m_vx[0]*m_vx[0]+m_vy[0]*m_vy[0]);
            r_pv->Fill(r);
            xy_pv->Fill(m_vx[0],m_vy[0]);
            zr_pv->Fill(m_vz[0],r);
            nTrackRealVertex->Fill(m_trkmult);
        }
        else{
            nTrackZeroPosVertex->Fill(m_trkmult);
        }
    }
}
