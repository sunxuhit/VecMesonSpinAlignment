#ifndef StVecMesonProManger_h
#define StVecMesonProManger_h

#include "TVector2.h"
#include "TString.h"
#include "StMessMgr.h"

class TProfile2D;
class TProfile;

class StVecMesonProManger
{
  public:
    StVecMesonProManger();
    virtual ~StVecMesonProManger();

    // ReCenter Correction
    void InitReCenter();
    void FillTrackEast(TVector2 q2Vector, Int_t Cent9, Int_t RunIndex, Int_t i, Int_t j, Float_t pt); // i = vertex pos/neg, j = eta_gap
    void FillTrackWest(TVector2 q2Vector, Int_t Cent9, Int_t RunIndex, Int_t i, Int_t j, Float_t pt); // i = vertex pos/neg, j = eta_gap
    void FillTrackFull(TVector2 q2Vector, Int_t Cent9, Int_t RunIndex, Int_t i, Float_t pt); // i = vertex pos/neg
    void WriteReCenter();

    // Shift Correction
    void InitShift();
    // Event Plane method
    void FillEventEast_EP(TVector2 Psi2Vector, Int_t Cent9, Int_t RunIndex, Int_t i, Int_t j, Int_t k); // i = vertex pos/neg, j = eta_gap, k = ShiftOrder
    void FillEventWest_EP(TVector2 Psi2Vector, Int_t Cent9, Int_t RunIndex, Int_t i, Int_t j, Int_t k); // i = vertex pos/neg, j = eta_gap, k = ShiftOrder
    void FillEventFull_EP(TVector2 Psi2Vector, Int_t Cent9, Int_t RunIndex, Int_t i, Int_t k); // i = vertex pos/neg, k = ShiftOrder
    void WriteShift();

    void InitChargedFlow();
    void FillEtaCharged2Flow(Float_t, Float_t, Float_t, Float_t, Float_t, Int_t, Int_t, Double_t);
    void FillRanCharged2Flow(Float_t, Float_t, Float_t, Float_t, Float_t, Int_t, Double_t);
    void WriteChargedFlow();

  private:
    // ReCenter Correction | x axis is RunIndex, y axis is Centrality
    // Event Plane method
    TProfile2D *p_mq2x_East_EP[2][4]; // 0 = vertex pos/neg, 1 = eta gap
    TProfile2D *p_mq2y_East_EP[2][4]; // 0 = vertex pos/neg, 1 = eta gap
    TProfile2D *p_mq2x_West_EP[2][4]; // 0 = vertex pos/neg, 1 = eta gap
    TProfile2D *p_mq2y_West_EP[2][4]; // 0 = vertex pos/neg, 1 = eta gap
    TProfile2D *p_mq2x_Full_EP[2];    // 0 = vertex pos/neg
    TProfile2D *p_mq2y_Full_EP[2];    // 0 = vertex pos/neg

    // Shift Correction | x axis is RunIndex, y axis is Centrality
    // Event Plane method
    TProfile2D *p_mcos2_East_EP[2][4][5]; // 0 = vertex pos/neg, 1 = eta gap, 2 = ShiftOrder
    TProfile2D *p_msin2_East_EP[2][4][5]; // 0 = vertex pos/neg, 1 = eta gap, 2 = ShiftOrder
    TProfile2D *p_mcos2_West_EP[2][4][5]; // 0 = vertex pos/neg, 1 = eta gap, 2 = ShiftOrder
    TProfile2D *p_msin2_West_EP[2][4][5]; // 0 = vertex pos/neg, 1 = eta gap, 2 = ShiftOrder
    TProfile2D *p_mcos2_Full_EP[2][5];    // 0 = vertex pos/neg, 1 = ShiftOrder
    TProfile2D *p_msin2_Full_EP[2][5];    // 0 = vertex pos/neg, 1 = ShiftOrder

    // charged flow eta sub
    TProfile *p_mV2_EP[10][4]; // 0: 0-8 Centrality, 9 minBias || 1 eta_gap

    // charged flow random sub
    TProfile *p_mV2_Ran_EP[10]; // 0: 0-8 Centrality, 9 minBias

    static TString mVStr[2];

    ClassDef(StVecMesonProManger,1)
};

#endif
