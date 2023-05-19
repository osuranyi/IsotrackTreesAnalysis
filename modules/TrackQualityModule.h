#pragma once
#include "../IsotrackTreesAnalysis.h"

void IsotrackTreesAnalysis::initTrackQualityModule() {
    d0 = new TH1F("d0",";d_{0} [cm];Entries",100,0,0.1);
    z0 = new TH1F("z0",";z_{0} [cm];Entries",100,-0.2,0.2);

    chi2ndf = new TH1F("chi2ndf",";#chi^{2}/ndf;Entries",100,0,30);

    dca_xy = new TH1F("dca_xy",";DCA_{xy};Entries",100,-0.05,0.05);
    dca_z = new TH1F("dca_z",";DCA_{z};Entries",100,-0.05,0.05);


    d0VsPt = new TH2F("d0 pt",";d_{0} [cm];p_{T} [GeV]",100,0,0.1,20,0,20);
    z0VsPt = new TH2F("z0 pt",";z_{0} [cm];p_{T} [GeV]",100,-0.2,0.2,20,0,20);

    chi2ndfVsPt = new TH2F("chi2ndf pt",";#chi^{2}/ndf;p_{T} [GeV]",100,0,30,20,0,20);

    dca_xyVsPt = new TH2F("dca_xy pt",";DCA_{xy};p_{T} [GeV]",100,-0.05,0.05,20,0,20);
    dca_zVsPt = new TH2F("dca_z pt",";DCA_{z};p_{T} [GeV]",100,-0.05,0.05,20,0,20);


    d0VsP = new TH2F("d0 p",";d_{0} [cm];p [GeV]",100,0,0.1,20,0,20);
    z0VsP = new TH2F("z0 p",";z_{0} [cm];p [GeV]",100,-0.2,0.2,20,0,20);

    chi2ndfVsP = new TH2F("chi2ndf p",";#chi^{2}/ndf;p [GeV]",100,0,30,20,0,20);

    dca_xyVsP = new TH2F("dca_xy p",";DCA_{xy} [cm];p [GeV]",100,-0.05,0.05,20,0,20);
    dca_zVsP = new TH2F("dca_z p",";DCA_{z} [cm];p [GeV]",100,-0.05,0.05,20,0,20);
}

void IsotrackTreesAnalysis::trackQualityModule(int id){
    d0->Fill(sqrt((m_tr_x[id]-m_vx[0])*(m_tr_x[id]-m_vx[0])+(m_tr_y[id]-m_vy[0])*(m_tr_y[id]-m_vy[0])));
    z0->Fill(m_tr_z[id]-m_vz[0]);
    chi2ndf->Fill(m_tr_chisq[id] / m_tr_ndf[id]);
    dca_xy->Fill(m_tr_dca_xy[id]);
    dca_z->Fill(m_tr_dca_z[id]);
    
    d0VsPt->Fill(sqrt((m_tr_x[id]-m_vx[0])*(m_tr_x[id]-m_vx[0])+(m_tr_y[id]-m_vy[0])*(m_tr_y[id]-m_vy[0])),m_tr_pt[id]);
    z0VsPt->Fill(m_tr_z[id]-m_vz[0],m_tr_pt[id]);
    chi2ndfVsPt->Fill(m_tr_chisq[id] / m_tr_ndf[id],m_tr_pt[id]);
    dca_xyVsPt->Fill(m_tr_dca_xy[id],m_tr_pt[id]); 
    dca_zVsPt->Fill(m_tr_dca_z[id],m_tr_pt[id]);

    d0VsP->Fill(sqrt((m_tr_x[id]-m_vx[0])*(m_tr_x[id]-m_vx[0])+(m_tr_y[id]-m_vy[0])*(m_tr_y[id]-m_vy[0])),m_tr_p[id]);
    z0VsP->Fill(m_tr_z[id]-m_vz[0],m_tr_p[id]);
    chi2ndfVsP->Fill(m_tr_chisq[id] / m_tr_ndf[id],m_tr_p[id]);
    dca_xyVsP->Fill(m_tr_dca_xy[id],m_tr_p[id]); 
    dca_zVsP->Fill(m_tr_dca_z[id],m_tr_p[id]);
}
