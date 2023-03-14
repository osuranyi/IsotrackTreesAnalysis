#pragma once
#include "../IsotrackTreesAnalysis.h"
#include "TVirtualFFT.h"
#include "TComplex.h"

//void IsotrackTreesAnalysis::initFFT(){
//    fftR2C = TVirtualFFT::FFT(1, &N, "R2C");
//    fftC2R = TVirtualFFT::FFT(1, &N, "C2R");
//}

void IsotrackTreesAnalysis::backgroundDeconvolution(){
    
    histEoverPBkgDec = new TH2F("epBkgDec","",20,0,20,200,0,10);

    for(int i = 0; i < 20; i++){

        TH1F* measured = (TH1F*)histEoverPRaw_NoEtaNoCent->ProjectionY("mes_temp",i+1,i+1);
        TH1F* background = (TH1F*)histEoverPBkg_NoEtaNoCent->ProjectionY("bkg_temp",i+1,i+1);

        std::vector<double> m, b;

        for(int i = 0; i < 200; i++){
            m.push_back(measured->GetBinContent(i+1));
            b.push_back(background->GetBinContent(i+1));
        }

        std::vector<double> s = deconvolve(m,b);

        for(int j = 0; j < s.size(); j++){
            histEoverPBkgDec->SetBinContent(i+1,j+1,s[j]);
        }
    }
}


std::vector<double> IsotrackTreesAnalysis::deconvolve(std::vector<double> m, std::vector<double> b){
    int N = m.size();
    TVirtualFFT* fftR2C = TVirtualFFT::FFT(1, &N, "R2C");

    // Fourier transform the measured distribution
    fftR2C->SetPoints(m.data());
    
    fftR2C->Transform();

    std::vector<double> reFm(N),imFm(N);

    fftR2C->GetPointsComplex(reFm.data(),imFm.data());
    
    fftR2C->SetPoints(b.data());
    fftR2C->Transform();
    std::vector<double> reFb(N), imFb(N);
    fftR2C->GetPointsComplex(reFb.data(), imFb.data());

    // Calculate the real and imaginary part of the Fourier transform of the signal distribution
    std::vector<TComplex> Fs(N);
    std::vector<double> reFs(N), imFs(N);

    for(int i = 0; i < N; i++){
        Fs[i]   = TComplex(reFm[i],imFm[i]) / TComplex(reFb[i],imFb[i]);
        reFs[i] = Fs[i].Re();
        imFs[i] = Fs[i].Im();
    }

    // Inverse Fourier transform to get the signal distribution

    // Fourier transform the background distribution
    TVirtualFFT* fftC2R = TVirtualFFT::FFT(1, &N, "C2R");

    fftC2R->SetPointsComplex(reFs.data(),imFs.data());
    fftC2R->Transform();
    std::vector<double> s(N);
    fftC2R->GetPoints(s.data());
   
    //delete fftR2C;
    //delete fftC2R;

    return s;
}
