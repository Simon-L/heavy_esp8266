/**
 * Copyright (c) 2018 Enzien Audio, Ltd.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the phrase "powered by heavy",
 *    the heavy logo, and a hyperlink to https://enzienaudio.com, all in a visible
 *    form.
 * 
 *   2.1 If the Application is distributed in a store system (for example,
 *       the Apple "App Store" or "Google Play"), the phrase "powered by heavy"
 *       shall be included in the app description or the copyright text as well as
 *       the in the app itself. The heavy logo will shall be visible in the app
 *       itself as well.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef _HEAVY_CONTEXT_ESP8266_HPP_
#define _HEAVY_CONTEXT_ESP8266_HPP_

// object includes
#include "HeavyContext.hpp"
#include "HvControlRandom.h"
#include "HvSignalLine.h"
#include "HvControlBinop.h"
#include "HvControlDelay.h"
#include "HvControlSystem.h"
#include "HvControlSlice.h"
#include "HvSignalVar.h"
#include "HvSignalPhasor.h"
#include "HvControlVar.h"
#include "HvSignalBiquad.h"
#include "HvMath.h"
#include "HvControlPack.h"
#include "HvControlUnop.h"
#include "HvControlCast.h"

class Heavy_esp8266 : public HeavyContext {

 public:
  Heavy_esp8266(double sampleRate, int poolKb=10, int inQueueKb=2, int outQueueKb=0);
  ~Heavy_esp8266();

  const char *getName() override { return "esp8266"; }
  int getNumInputChannels() override { return 0; }
  int getNumOutputChannels() override { return 1; }

  int process(float **inputBuffers, float **outputBuffer, int n) override;
  int processInline(float *inputBuffers, float *outputBuffer, int n) override;
  int processInlineInterleaved(float *inputBuffers, float *outputBuffer, int n) override;

  int getParameterInfo(int index, HvParameterInfo *info) override;

 private:
  HvTable *getTableForHash(hv_uint32_t tableHash) override;
  void scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) override;

  // static sendMessage functions
  static void cCast_Yzdwhiz4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_vKZtKM6G_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_uH88bYNf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_SQ5xeEEf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_UB4baJsI_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_00829pX1_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_E0f22RqL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cRandom_UWolHxZz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_i6hfDFim_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_TiCTRscT_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_unroubjk_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ltIHzUAw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_vNgMrtw4_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_Jn2CtLHF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_nqJtHtJl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_zZsVmWJ1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_udRIcUdu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_0Rkn7TWO_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_63N7OF3G_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_NpNHtNuR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_19ygOCWz_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_90QQASPN_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_A2bKttfJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_rK8b8aj0_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Omk4wsZM_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_gHz9r6Xe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_oW48Cg66_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xWMx5dh7_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_JnimDQ73_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_3cSMRM4G_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_8gIqzAvs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_7dmEU2Hi_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_JeSrqHNf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vdjUUleS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_vonCvVcR_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_XJQpuHpC_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cReceive_MXrw2mOu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_s9gO1RJD_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cSlice_X8pqmiKa_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cPack_S5wRjce8_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_MXjCu1xu_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_796Wk7I3_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_4aBr6PHs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_xD26U2Tx_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_gbvJ2Lpe_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_2jYpu7kg_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_c2VBrkR9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_gdwYOBYs_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cDelay_o6FTwvl1_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_iUO25s44_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_M4kPrxcW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_3T4mhG33_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_Ziz2PO7K_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cDelay_VTj7TE52_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_6eDd7bWl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_HoigNXS9_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_oATJb1Sf_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Ft1WMD1I_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_51VDBXzj_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cVar_qwpARROW_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_YiHsvXED_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSystem_wRxTscNJ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_pMLE3oSd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_sgTZfcPL_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_y0TkjEoS_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_IrGG6KYF_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_9cEpcEsQ_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_tL1mlzdq_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_p9VkiE4d_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cRandom_5MKkpb7b_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_A3RrZoVk_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_17l5NsN4_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_Ld4KJ117_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_2B83Frpw_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cBinop_58jIl81E_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cMsg_l3kmbzQv_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cRandom_qpC1Liuh_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSwitchcase_9lhMxNDk_onMessage(HeavyContextInterface *, void *, int letIn, const HvMessage *const, void *);
  static void cBinop_7GZDDEWd_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cUnop_7inEpTpK_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cSlice_c5Wpta1r_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_njWb8SNl_sendMessage(HeavyContextInterface *, int, const HvMessage *);
  static void cCast_ak4bStl2_sendMessage(HeavyContextInterface *, int, const HvMessage *);

  // objects
  SignalPhasor sPhasor_JOA2W8MW;
  SignalBiquad_k sBiquad_k_taMtrbL8;
  SignalLine sLine_Q6OGeD68;
  ControlSlice cSlice_SQ5xeEEf;
  ControlBinop cBinop_E0f22RqL;
  ControlRandom cRandom_UWolHxZz;
  ControlBinop cBinop_TiCTRscT;
  ControlVar cVar_unroubjk;
  ControlBinop cBinop_Jn2CtLHF;
  ControlVar cVar_nqJtHtJl;
  ControlBinop cBinop_zZsVmWJ1;
  ControlVar cVar_udRIcUdu;
  ControlBinop cBinop_0Rkn7TWO;
  ControlBinop cBinop_63N7OF3G;
  ControlBinop cBinop_NpNHtNuR;
  ControlBinop cBinop_19ygOCWz;
  ControlBinop cBinop_90QQASPN;
  ControlBinop cBinop_A2bKttfJ;
  ControlBinop cBinop_Omk4wsZM;
  ControlBinop cBinop_gHz9r6Xe;
  ControlBinop cBinop_JnimDQ73;
  ControlBinop cBinop_3cSMRM4G;
  ControlBinop cBinop_8gIqzAvs;
  ControlBinop cBinop_JeSrqHNf;
  ControlBinop cBinop_vdjUUleS;
  ControlBinop cBinop_vonCvVcR;
  ControlBinop cBinop_XJQpuHpC;
  SignalVarf sVarf_pWfuupqQ;
  SignalVarf sVarf_PcXJkILP;
  ControlSlice cSlice_X8pqmiKa;
  ControlPack cPack_S5wRjce8;
  ControlSlice cSlice_MXjCu1xu;
  ControlSlice cSlice_796Wk7I3;
  ControlSlice cSlice_4aBr6PHs;
  ControlDelay cDelay_gdwYOBYs;
  ControlDelay cDelay_o6FTwvl1;
  ControlDelay cDelay_VTj7TE52;
  ControlBinop cBinop_6eDd7bWl;
  ControlBinop cBinop_oATJb1Sf;
  ControlBinop cBinop_Ft1WMD1I;
  ControlVar cVar_qwpARROW;
  SignalVari sVari_9vW7NGQX;
  ControlSlice cSlice_9cEpcEsQ;
  ControlBinop cBinop_p9VkiE4d;
  ControlRandom cRandom_5MKkpb7b;
  ControlBinop cBinop_17l5NsN4;
  ControlBinop cBinop_Ld4KJ117;
  ControlBinop cBinop_2B83Frpw;
  ControlBinop cBinop_58jIl81E;
  ControlRandom cRandom_qpC1Liuh;
  ControlBinop cBinop_7GZDDEWd;
  ControlSlice cSlice_c5Wpta1r;
};

#endif // _HEAVY_CONTEXT_ESP8266_HPP_
