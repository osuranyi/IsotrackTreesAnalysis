#pragma once
#include "../IsotrackTreesAnalysis.h"

void IsotrackTreesAnalysis::initShowerSizeModule(){

    cemcSigmaEtaAll = new TH1F("cemc_sigma_eta_all","",500,0.0,1.0);
    cemcSigmaPhiAll = new TH1F("cemc_sigma_phi_all","",500,0.0,1.0);
    ohcalSigmaEtaAll = new TH1F("ohcal_sigma_eta_all","",500,0.0,1.0);
    ohcalSigmaPhiAll = new TH1F("ohcal_sigma_phi_all","",00,0.0,1.0);

    
    for(int i = 0; i < 6; i++){
        cemcDiffEta[i] = new TH1F(Form("cemc diff eta %d",i+1),";#Delta#eta;Entries",50,-0.15,0.15);
        cemcDiffPhi[i] = new TH1F(Form("cemc diff phi %d",i+1),";#Delta#phi;Entries",50,-0.15,0.15);

        ihcalDiffEta[i] = new TH1F(Form("ihcal diff eta %d",i+1),";#Delta#eta;Entries",50,-0.15,0.15);
        ihcalDiffPhi[i] = new TH1F(Form("ihcal diff phi %d",i+1),";#Delta#phi;Entries",50,-0.15,0.15);

        ohcalDiffEta[i] = new TH1F(Form("ohcal diff eta %d",i+1),";#Delta#eta;Entries",50,-0.15,0.15);
        ohcalDiffPhi[i] = new TH1F(Form("ohcal diff phi %d",i+1),";#Delta#phi;Entries",50,-0.15,0.15);

        
        cemcSigmaEta[i] = new TH1F(Form("cemc sigma eta %d",i+1),";#sigma_{#eta};Entries",50,0.0,0.15);
        cemcSigmaPhi[i] = new TH1F(Form("cemc sigma phi %d",i+1),";#sigma_{#phi};Entries",50,0.0,0.15);

        ihcalSigmaEta[i] = new TH1F(Form("ihcal sigma eta %d",i+1),";#sigma_{#eta};Entries",50,0.0,0.15);
        ihcalSigmaPhi[i] = new TH1F(Form("ihcal sigma phi %d",i+1),";#sigma_{#phi};Entries",50,0.0,0.15);

        ohcalSigmaEta[i] = new TH1F(Form("ohcal sigma eta %d",i+1),";#sigma_{#eta};Entries",50,0.0,0.15);
        ohcalSigmaPhi[i] = new TH1F(Form("ohcal sigma phi %d",i+1),";#sigma_{#phi};Entries",50,0.0,0.15);

    

        cemcDiffEtaVsE[i] = new TH2F(Form("cemc diff eta vs E %d",i+1),";#Delta#eta;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);
        cemcDiffPhiVsE[i] = new TH2F(Form("cemc diff phi vs E %d",i+1),";#Delta#phi;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);

        ihcalDiffEtaVsE[i] = new TH2F(Form("ihcal diff eta vs E %d",i+1),";#Delta#eta;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);
        ihcalDiffPhiVsE[i] = new TH2F(Form("ihcal diff phi vs E %d",i+1),";#Delta#phi;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);

        ohcalDiffEtaVsE[i] = new TH2F(Form("ohcal diff eta vs E %d",i+1),";#Delta#eta;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);
        ohcalDiffPhiVsE[i] = new TH2F(Form("ohcal diff phi vs E %d",i+1),";#Delta#phi;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);

        
        cemcSigmaEtaVsE[i] = new TH2F(Form("cemc sigma eta vs E %d",i+1),";#sigma_{#eta};E [GeV];Entries",50,0.0,0.15,50,0,4.0);
        cemcSigmaPhiVsE[i] = new TH2F(Form("cemc sigma phi vs E %d",i+1),";#sigma_{#phi};E [GeV];Entries",50,0.0,0.15,50,0,4.0);

        ihcalSigmaEtaVsE[i] = new TH2F(Form("ihcal sigma eta vs E %d",i+1),";#sigma_{#eta};E [GeV];Entries",50,0.0,0.15,50,0,4.0);
        ihcalSigmaPhiVsE[i] = new TH2F(Form("ihcal sigma phi vs E %d",i+1),";#sigma_{#phi};E [GeV];Entries",50,0.0,0.15,50,0,4.0);

        ohcalSigmaEtaVsE[i] = new TH2F(Form("ohcal sigma eta vs E %d",i+1),";#sigma_{#eta};E [GeV];Entries",50,0.0,0.15,50,0,4.0);
        ohcalSigmaPhiVsE[i] = new TH2F(Form("ohcal sigma phi vs E %d",i+1),";#sigma_{#phi};E [GeV];Entries",50,0.0,0.15,50,0,4.0);
        

        /*cemcDiffEtaVsPt[i] = new TH2F(Form("cemc diff eta vs E %d",i+1),";#Delta#eta;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);
        cemcDiffPhiVsPt[i] = new TH2F(Form("cemc diff phi vs E %d",i+1),";#Delta#phi;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);

        ihcalDiffEtaVsPt[i] = new TH2F(Form("ihcal diff eta vs E %d",i+1),";#Delta#eta;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);
        ihcalDiffPhiVsPt[i] = new TH2F(Form("ihcal diff phi vs E %d",i+1),";#Delta#phi;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);

        ohcalDiffEtaVsPt[i] = new TH2F(Form("ohcal diff eta vs E %d",i+1),";#Delta#eta;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);
        ohcalDiffPhiVsPt[i] = new TH2F(Form("ohcal diff phi vs E %d",i+1),";#Delta#phi;E [GeV];Entries",50,-0.15,0.15,50,0,4.0);

        
        cemcSigmaEtaVsPt[i] = new TH2F(Form("cemc sigma eta vs E %d",i+1),";#sigma_{#eta};E [GeV];Entries",50,0.0,0.15,50,0,4.0);
        cemcSigmaPhiVsPt[i] = new TH2F(Form("cemc sigma phi vs E %d",i+1),";#sigma_{#phi};E [GeV];Entries",50,0.0,0.15,50,0,4.0);

        ihcalSigmaEtaVsPt[i] = new TH2F(Form("ihcal sigma eta vs E %d",i+1),";#sigma_{#eta};E [GeV];Entries",50,0.0,0.15,50,0,4.0);
        ihcalSigmaPhiVsPt[i] = new TH2F(Form("ihcal sigma phi vs E %d",i+1),";#sigma_{#phi};E [GeV];Entries",50,0.0,0.15,50,0,4.0);

        ohcalSigmaEtaVsPt[i] = new TH2F(Form("ohcal sigma eta vs E %d",i+1),";#sigma_{#eta};E [GeV];Entries",50,0.0,0.15,50,0,4.0);
        ohcalSigmaPhiVsPt[i] = new TH2F(Form("ohcal sigma phi vs E %d",i+1),";#sigma_{#phi};E [GeV];Entries",50,0.0,0.15,50,0,4.0);
        */

    }
}


void IsotrackTreesAnalysis::showerSizeModule(int id, MatchedClusterContainer cemcTowers, MatchedClusterContainer ihcalTowers, MatchedClusterContainer ohcalTowers){
    
    int showerType = truthMipShowerClassifier(id) - 1;

    if(showerType == -1 || showerType == 6)
        return;
    
    /////////////////////////////////
    // Calculate CEMC shower width //
    /////////////////////////////////

    float cemc_eta_mean = 0;
    float cemc_phi_mean = 0;

    float cemc_eta_sigma2 = 0;
    float cemc_phi_sigma2 = 0;

    int numberOfCemcTowers = cemcTowers.getNumberOfClusters();
    float totalCemcEnergy = 0.0;

    for(int i = 0; i < numberOfCemcTowers; i++){
        //if(cemcTowers.e[i] > 0.08){
            totalCemcEnergy += cemcTowers.e[i];
            cemc_eta_mean += cemcTowers.e[i]*cemcTowers.eta[i];
            cemc_phi_mean += cemcTowers.e[i]*cemcTowers.phi[i];
        //}
    }

    //if(totalCemcEnergy > 0.16){
        cemc_eta_mean /= totalCemcEnergy;
        cemc_phi_mean /= totalCemcEnergy;
    
        for(int i = 0; i < numberOfCemcTowers; i++){
            //if(cemcTowers.e[i] > 0.08){
                cemc_eta_sigma2 += cemcTowers.e[i]*(cemcTowers.eta[i] - cemc_eta_mean)*(cemcTowers.eta[i] - cemc_eta_mean);
                cemc_phi_sigma2 += cemcTowers.e[i]*(cemcTowers.phi[i] - cemc_phi_mean)*(cemcTowers.phi[i] - cemc_phi_mean);
            //}
        }

        cemc_eta_sigma2 /= totalCemcEnergy;
        cemc_phi_sigma2 /= totalCemcEnergy;
    //}

    //////////////////////////////////
    // Calculate IHCal shower width //
    //////////////////////////////////

    float ihcal_eta_mean = 0;
    float ihcal_phi_mean = 0;

    float ihcal_eta_sigma2 = 0;
    float ihcal_phi_sigma2 = 0;

    int numberOfIhcalTowers = ihcalTowers.getNumberOfClusters();
    float totalIhcalEnergy = 0.0;

    for(int i = 0; i < numberOfIhcalTowers; i++){
        //if(ihcalTowers.e[i] > 0.03){
            totalIhcalEnergy += ihcalTowers.e[i];
            ihcal_eta_mean += ihcalTowers.e[i]*ihcalTowers.eta[i];
            ihcal_phi_mean += ihcalTowers.e[i]*ihcalTowers.phi[i];
        //}
    }

    //if(totalIhcalEnergy > 0.06){
        ihcal_eta_mean /= totalIhcalEnergy;
        ihcal_phi_mean /= totalIhcalEnergy;
    
        for(int i = 0; i < numberOfIhcalTowers; i++){
            //if(ihcalTowers.e[i] > 0.03){
                ihcal_eta_sigma2 += ihcalTowers.e[i]*(ihcalTowers.eta[i] - ihcal_eta_mean)*(ihcalTowers.eta[i] - ihcal_eta_mean);
                ihcal_phi_sigma2 += ihcalTowers.e[i]*(ihcalTowers.phi[i] - ihcal_phi_mean)*(ihcalTowers.phi[i] - ihcal_phi_mean);
            //}
        }

        ihcal_eta_sigma2 /= totalIhcalEnergy;
        ihcal_phi_sigma2 /= totalIhcalEnergy;
    //}

    //////////////////////////////////
    // Calculate OHCal shower width //
    //////////////////////////////////

    float ohcal_eta_mean = 0;
    float ohcal_phi_mean = 0;

    float ohcal_eta_sigma2 = 0;
    float ohcal_phi_sigma2 = 0;

    int numberOfOhcalTowers = ohcalTowers.getNumberOfClusters();
    float totalOhcalEnergy = 0.0;

    for(int i = 0; i < numberOfOhcalTowers; i++){
        //if(ohcalTowers.e[i] > 0.06){
            totalOhcalEnergy += ohcalTowers.e[i];
            ohcal_eta_mean += ohcalTowers.e[i]*ohcalTowers.eta[i];
            ohcal_phi_mean += ohcalTowers.e[i]*ohcalTowers.phi[i];
        //}
    }

    //if(totalOhcalEnergy > 0.12){
        ohcal_eta_mean /= totalOhcalEnergy;
        ohcal_phi_mean /= totalOhcalEnergy;
    
        for(int i = 0; i < numberOfOhcalTowers; i++){
            //if(ohcalTowers.e[i] > 0.06){
                ohcal_eta_sigma2 += ohcalTowers.e[i]*(ohcalTowers.eta[i] - ohcal_eta_mean)*(ohcalTowers.eta[i] - ohcal_eta_mean);
                ohcal_phi_sigma2 += ohcalTowers.e[i]*(ohcalTowers.phi[i] - ohcal_phi_mean)*(ohcalTowers.phi[i] - ohcal_phi_mean);
            //}
        }

        ohcal_eta_sigma2 /= totalOhcalEnergy;
        ohcal_phi_sigma2 /= totalOhcalEnergy;
    //}


    /////////////////////
    // Fill histograms //
    /////////////////////

        cemcSigmaEtaAll->Fill(sqrt(cemc_eta_sigma2));
        cemcSigmaPhiAll->Fill(sqrt(cemc_phi_sigma2));
        ohcalSigmaEtaAll->Fill(sqrt(ohcal_eta_sigma2));
        ohcalSigmaPhiAll->Fill(sqrt(ohcal_phi_sigma2));
    
    //if(totalCemcEnergy > 0.16){
        cemcDiffEta[showerType]->Fill(m_tr_cemc_eta[id] - cemc_eta_mean);
        cemcDiffPhi[showerType]->Fill(0.5*(m_tr_cemc_phi[id]+m_tr_ihcal_phi[id]) - cemc_phi_mean);
        cemcSigmaEta[showerType]->Fill(sqrt(cemc_eta_sigma2));
        cemcSigmaPhi[showerType]->Fill(sqrt(cemc_phi_sigma2));

        cemcDiffEtaVsE[showerType]->Fill(m_tr_cemc_eta[id] - cemc_eta_mean, totalCemcEnergy);
        cemcDiffPhiVsE[showerType]->Fill(m_tr_cemc_phi[id] - cemc_phi_mean, totalCemcEnergy);
        cemcSigmaEtaVsE[showerType]->Fill(sqrt(cemc_eta_sigma2), totalCemcEnergy);
        cemcSigmaPhiVsE[showerType]->Fill(sqrt(cemc_phi_sigma2), totalCemcEnergy);
    //}

    //if(totalIhcalEnergy > 0.06){
        ihcalDiffEta[showerType]->Fill(m_tr_ihcal_eta[id] - ihcal_eta_mean);
        ihcalDiffPhi[showerType]->Fill(m_tr_ihcal_phi[id]-m_tr_charge[id]*0.09 - ihcal_phi_mean);
        ihcalSigmaEta[showerType]->Fill(sqrt(ihcal_eta_sigma2));
        ihcalSigmaPhi[showerType]->Fill(sqrt(ihcal_phi_sigma2));

        ihcalDiffEtaVsE[showerType]->Fill(m_tr_ihcal_eta[id] - ihcal_eta_mean, totalIhcalEnergy);
        ihcalDiffPhiVsE[showerType]->Fill(m_tr_ihcal_phi[id] - ihcal_phi_mean, totalIhcalEnergy);
        ihcalSigmaEtaVsE[showerType]->Fill(sqrt(ihcal_eta_sigma2), totalIhcalEnergy);
        ihcalSigmaPhiVsE[showerType]->Fill(sqrt(ihcal_phi_sigma2), totalIhcalEnergy);
    //}

    //if(totalOhcalEnergy > 0.12){
        ohcalDiffEta[showerType]->Fill(m_tr_ohcal_eta[id] - ohcal_eta_mean);
        ohcalDiffPhi[showerType]->Fill(m_tr_ohcal_phi[id]+m_tr_charge[id]*0.04 - ohcal_phi_mean);
        ohcalSigmaEta[showerType]->Fill(sqrt(ohcal_eta_sigma2));
        ohcalSigmaPhi[showerType]->Fill(sqrt(ohcal_phi_sigma2));

        ohcalDiffEtaVsE[showerType]->Fill(m_tr_ohcal_eta[id] - ohcal_eta_mean, totalOhcalEnergy);
        ohcalDiffPhiVsE[showerType]->Fill(m_tr_ohcal_phi[id] - ohcal_phi_mean, totalOhcalEnergy);
        ohcalSigmaEtaVsE[showerType]->Fill(sqrt(ohcal_eta_sigma2), totalOhcalEnergy);
        ohcalSigmaPhiVsE[showerType]->Fill(sqrt(ohcal_phi_sigma2), totalOhcalEnergy);
   
    //}
}
