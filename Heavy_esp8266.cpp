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

#include "Heavy_esp8266.hpp"

#define Context(_c) reinterpret_cast<Heavy_esp8266 *>(_c)



/*
 * C Functions
 */

extern "C" {
  HV_EXPORT HeavyContextInterface *hv_esp8266_new(double sampleRate) {
    return new Heavy_esp8266(sampleRate);
  }

  HV_EXPORT HeavyContextInterface *hv_esp8266_new_with_options(double sampleRate,
      int poolKb, int inQueueKb, int outQueueKb) {
    return new Heavy_esp8266(sampleRate, poolKb, inQueueKb, outQueueKb);
  }
} // extern "C"







/*
 * Class Functions
 */

Heavy_esp8266::Heavy_esp8266(double sampleRate, int poolKb, int inQueueKb, int outQueueKb)
    : HeavyContext(sampleRate, poolKb, inQueueKb, outQueueKb) {
  numBytes += sPhasor_k_init(&sPhasor_JOA2W8MW, 200.0f, sampleRate);
  numBytes += sBiquad_k_init(&sBiquad_k_taMtrbL8, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  numBytes += sLine_init(&sLine_Q6OGeD68);
  numBytes += cSlice_init(&cSlice_SQ5xeEEf, 1, 1);
  numBytes += cRandom_init(&cRandom_UWolHxZz, 1096272105);
  numBytes += cVar_init_f(&cVar_unroubjk, 1.0f);
  numBytes += cVar_init_f(&cVar_nqJtHtJl, 1.0f);
  numBytes += cVar_init_f(&cVar_udRIcUdu, 600.0f);
  numBytes += cBinop_init(&cBinop_19ygOCWz, 0.0f); // __div
  numBytes += cBinop_init(&cBinop_gHz9r6Xe, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_3cSMRM4G, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_8gIqzAvs, 0.0f); // __add
  numBytes += cBinop_init(&cBinop_vdjUUleS, 0.0f); // __mul
  numBytes += cBinop_init(&cBinop_vonCvVcR, 0.0f); // __div
  numBytes += sVarf_init(&sVarf_pWfuupqQ, 0.0f, 0.0f, false);
  numBytes += sVarf_init(&sVarf_PcXJkILP, 0.0f, 0.0f, false);
  numBytes += cSlice_init(&cSlice_X8pqmiKa, 1, -1);
  numBytes += cPack_init(&cPack_S5wRjce8, 2, 0.0f, 0.0f);
  numBytes += cSlice_init(&cSlice_MXjCu1xu, 2, 1);
  numBytes += cSlice_init(&cSlice_796Wk7I3, 0, 1);
  numBytes += cSlice_init(&cSlice_4aBr6PHs, 1, 1);
  numBytes += cDelay_init(this, &cDelay_gdwYOBYs, 0.0f);
  numBytes += cDelay_init(this, &cDelay_o6FTwvl1, 0.0f);
  numBytes += cDelay_init(this, &cDelay_VTj7TE52, 0.0f);
  numBytes += cBinop_init(&cBinop_Ft1WMD1I, 0.0f); // __mul
  numBytes += cVar_init_f(&cVar_qwpARROW, 100.0f);
  numBytes += sVari_init(&sVari_9vW7NGQX, 0, 0, false);
  numBytes += cSlice_init(&cSlice_9cEpcEsQ, 1, 1);
  numBytes += cRandom_init(&cRandom_5MKkpb7b, -1208361127);
  numBytes += cBinop_init(&cBinop_Ld4KJ117, 1.0f); // __pow
  numBytes += cRandom_init(&cRandom_qpC1Liuh, -1826299595);
  numBytes += cSlice_init(&cSlice_c5Wpta1r, 1, 1);
  
  // schedule a message to trigger all loadbangs via the __hv_init receiver
  scheduleMessageForReceiver(0xCE5CC65B, msg_initWithBang(HV_MESSAGE_ON_STACK(1), 0));
}

Heavy_esp8266::~Heavy_esp8266() {
  cPack_free(&cPack_S5wRjce8);
}

HvTable *Heavy_esp8266::getTableForHash(hv_uint32_t tableHash) {
  return nullptr;
}

void Heavy_esp8266::scheduleMessageForReceiver(hv_uint32_t receiverHash, HvMessage *m) {
  switch (receiverHash) {
    case 0xCE5CC65B: { // __hv_init
      mq_addMessageByTimestamp(&mq, m, 0, &cReceive_MXrw2mOu_sendMessage);
      break;
    }
    default: return;
  }
}

int Heavy_esp8266::getParameterInfo(int index, HvParameterInfo *info) {
  if (info != nullptr) {
    switch (index) {
      default: {
        info->name = "invalid parameter index";
        info->hash = 0;
        info->type = HvParameterType::HV_PARAM_TYPE_PARAMETER_IN;
        info->minVal = 0.0f;
        info->maxVal = 0.0f;
        info->defaultVal = 0.0f;
        break;
      }
    }
  }
  return 0;
}



/*
 * Send Function Implementations
 */


void Heavy_esp8266::cCast_Yzdwhiz4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_sgTZfcPL_sendMessage(_c, 0, m);
  cMsg_uH88bYNf_sendMessage(_c, 0, m);
}

void Heavy_esp8266::cMsg_vKZtKM6G_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.3f);
  msg_setFloat(m, 1, 5.0f);
  cSwitchcase_s9gO1RJD_onMessage(_c, NULL, 0, m, NULL);
  m = HV_MESSAGE_ON_STACK(3);
  msg_init(m, 3, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  msg_setFloat(m, 1, 100.0f);
  msg_setFloat(m, 2, 20.0f);
  cSwitchcase_s9gO1RJD_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_esp8266::cMsg_uH88bYNf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  sVarf_onMessage(_c, &Context(_c)->sVarf_pWfuupqQ, m);
}

void Heavy_esp8266::cSlice_SQ5xeEEf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_UWolHxZz, 1, m, &cRandom_UWolHxZz_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_esp8266::cUnop_UB4baJsI_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_vNgMrtw4_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_esp8266::cSwitchcase_00829pX1_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  switch (msg_getHash(m, 0)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_SQ5xeEEf, 0, m, &cSlice_SQ5xeEEf_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_UWolHxZz, 0, m, &cRandom_UWolHxZz_sendMessage);
      break;
    }
  }
}

void Heavy_esp8266::cBinop_E0f22RqL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_UB4baJsI_sendMessage);
}

void Heavy_esp8266::cRandom_UWolHxZz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_E0f22RqL_sendMessage);
}

void Heavy_esp8266::cCast_i6hfDFim_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_00829pX1_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_esp8266::cBinop_TiCTRscT_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_unroubjk, 1, m, &cVar_unroubjk_sendMessage);
}

void Heavy_esp8266::cVar_unroubjk_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_EQ, 0.0f, 0, m, &cBinop_TiCTRscT_sendMessage);
  cSwitchcase_Ziz2PO7K_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_esp8266::cCast_ltIHzUAw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_Yzdwhiz4_sendMessage);
}

void Heavy_esp8266::cSwitchcase_vNgMrtw4_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  switch (msg_getHash(m, 0)) {
    case 0x0: { // "0.0"
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_ltIHzUAw_sendMessage);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_ak4bStl2_sendMessage);
      break;
    }
  }
}

void Heavy_esp8266::cBinop_Jn2CtLHF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_taMtrbL8, 4, m);
}

void Heavy_esp8266::cVar_nqJtHtJl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 0.001f, 0, m, &cBinop_90QQASPN_sendMessage);
}

void Heavy_esp8266::cBinop_zZsVmWJ1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vonCvVcR, HV_BINOP_DIVIDE, 0, m, &cBinop_vonCvVcR_sendMessage);
}

void Heavy_esp8266::cVar_udRIcUdu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 6.28319f, 0, m, &cBinop_zZsVmWJ1_sendMessage);
}

void Heavy_esp8266::cBinop_0Rkn7TWO_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vdjUUleS, HV_BINOP_MULTIPLY, 1, m, &cBinop_vdjUUleS_sendMessage);
}

void Heavy_esp8266::cBinop_63N7OF3G_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_XJQpuHpC_sendMessage);
}

void Heavy_esp8266::cBinop_NpNHtNuR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_63N7OF3G_sendMessage);
}

void Heavy_esp8266::cBinop_19ygOCWz_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MIN, 1.0f, 0, m, &cBinop_JeSrqHNf_sendMessage);
}

void Heavy_esp8266::cBinop_90QQASPN_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_19ygOCWz, HV_BINOP_DIVIDE, 1, m, &cBinop_19ygOCWz_sendMessage);
}

void Heavy_esp8266::cBinop_A2bKttfJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_ADD, 1.0f, 0, m, &cBinop_Omk4wsZM_sendMessage);
}

void Heavy_esp8266::cCast_rK8b8aj0_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cVar_onMessage(_c, &Context(_c)->cVar_udRIcUdu, 0, m, &cVar_udRIcUdu_sendMessage);
}

void Heavy_esp8266::cBinop_Omk4wsZM_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_POW, 2.0f, 0, m, &cBinop_NpNHtNuR_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_vdjUUleS, HV_BINOP_MULTIPLY, 0, m, &cBinop_vdjUUleS_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_gHz9r6Xe, HV_BINOP_MULTIPLY, 0, m, &cBinop_gHz9r6Xe_sendMessage);
}

void Heavy_esp8266::cBinop_gHz9r6Xe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_8gIqzAvs, HV_BINOP_ADD, 1, m, &cBinop_8gIqzAvs_sendMessage);
}

void Heavy_esp8266::cSystem_oW48Cg66_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_vonCvVcR, HV_BINOP_DIVIDE, 1, m, &cBinop_vonCvVcR_sendMessage);
}

void Heavy_esp8266::cMsg_xWMx5dh7_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_oW48Cg66_sendMessage);
}

void Heavy_esp8266::cBinop_JnimDQ73_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_3cSMRM4G, HV_BINOP_MULTIPLY, 0, m, &cBinop_3cSMRM4G_sendMessage);
}

void Heavy_esp8266::cBinop_3cSMRM4G_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_taMtrbL8, 1, m);
}

void Heavy_esp8266::cBinop_8gIqzAvs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_3cSMRM4G, HV_BINOP_MULTIPLY, 1, m, &cBinop_3cSMRM4G_sendMessage);
}

void Heavy_esp8266::cUnop_7dmEU2Hi_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_0Rkn7TWO_sendMessage);
}

void Heavy_esp8266::cBinop_JeSrqHNf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_A2bKttfJ_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_8gIqzAvs, HV_BINOP_ADD, 0, m, &cBinop_8gIqzAvs_sendMessage);
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 2.0f, 0, m, &cBinop_JnimDQ73_sendMessage);
}

void Heavy_esp8266::cBinop_vdjUUleS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, -1.0f, 0, m, &cBinop_Jn2CtLHF_sendMessage);
}

void Heavy_esp8266::cBinop_vonCvVcR_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_gHz9r6Xe, HV_BINOP_MULTIPLY, 1, m, &cBinop_gHz9r6Xe_sendMessage);
  cUnop_onMessage(_c, HV_UNOP_COS, m, &cUnop_7dmEU2Hi_sendMessage);
  cBinop_onMessage(_c, &Context(_c)->cBinop_19ygOCWz, HV_BINOP_DIVIDE, 0, m, &cBinop_19ygOCWz_sendMessage);
}

void Heavy_esp8266::cBinop_XJQpuHpC_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sBiquad_k_onMessage(&Context(_c)->sBiquad_k_taMtrbL8, 5, m);
}

void Heavy_esp8266::cReceive_MXrw2mOu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_YiHsvXED_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_qwpARROW, 0, m, &cVar_qwpARROW_sendMessage);
  cSwitchcase_A3RrZoVk_onMessage(_c, NULL, 0, m, NULL);
  cVar_onMessage(_c, &Context(_c)->cVar_nqJtHtJl, 0, m, &cVar_nqJtHtJl_sendMessage);
  cMsg_xWMx5dh7_sendMessage(_c, 0, m);
  cVar_onMessage(_c, &Context(_c)->cVar_udRIcUdu, 0, m, &cVar_udRIcUdu_sendMessage);
  cVar_onMessage(_c, &Context(_c)->cVar_unroubjk, 0, m, &cVar_unroubjk_sendMessage);
}

void Heavy_esp8266::cSwitchcase_s9gO1RJD_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  switch (msg_getHash(m, 0)) {
    case 0x7A5B032D: { // "stop"
      cSlice_onMessage(_c, &Context(_c)->cSlice_X8pqmiKa, 0, m, &cSlice_X8pqmiKa_sendMessage);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_M4kPrxcW_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_MXjCu1xu, 0, m, &cSlice_MXjCu1xu_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_4aBr6PHs, 0, m, &cSlice_4aBr6PHs_sendMessage);
      cSlice_onMessage(_c, &Context(_c)->cSlice_796Wk7I3, 0, m, &cSlice_796Wk7I3_sendMessage);
      break;
    }
  }
}

void Heavy_esp8266::cSlice_X8pqmiKa_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_c2VBrkR9_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_gbvJ2Lpe_sendMessage);
      break;
    }
    case 1: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_c2VBrkR9_sendMessage);
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_gbvJ2Lpe_sendMessage);
      break;
    }
    default: return;
  }
}

void Heavy_esp8266::cPack_S5wRjce8_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sLine_onMessage(_c, &Context(_c)->sLine_Q6OGeD68, 0, m, NULL);
}

void Heavy_esp8266::cSlice_MXjCu1xu_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cDelay_onMessage(_c, &Context(_c)->cDelay_gdwYOBYs, 1, m, &cDelay_gdwYOBYs_sendMessage);
      cDelay_onMessage(_c, &Context(_c)->cDelay_o6FTwvl1, 1, m, &cDelay_o6FTwvl1_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_esp8266::cSlice_796Wk7I3_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cDelay_onMessage(_c, &Context(_c)->cDelay_gdwYOBYs, 0, m, &cDelay_gdwYOBYs_sendMessage);
      cDelay_onMessage(_c, &Context(_c)->cDelay_o6FTwvl1, 0, m, &cDelay_o6FTwvl1_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_esp8266::cSlice_4aBr6PHs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cDelay_onMessage(_c, &Context(_c)->cDelay_o6FTwvl1, 0, m, &cDelay_o6FTwvl1_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_esp8266::cMsg_xD26U2Tx_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  cDelay_onMessage(_c, &Context(_c)->cDelay_gdwYOBYs, 1, m, &cDelay_gdwYOBYs_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_o6FTwvl1, 1, m, &cDelay_o6FTwvl1_sendMessage);
}

void Heavy_esp8266::cCast_gbvJ2Lpe_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_2jYpu7kg_sendMessage(_c, 0, m);
}

void Heavy_esp8266::cMsg_2jYpu7kg_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "stop");
  sLine_onMessage(_c, &Context(_c)->sLine_Q6OGeD68, 0, m, NULL);
}

void Heavy_esp8266::cCast_c2VBrkR9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_iUO25s44_sendMessage(_c, 0, m);
}

void Heavy_esp8266::cDelay_gdwYOBYs_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_gdwYOBYs, m);
  cPack_onMessage(_c, &Context(_c)->cPack_S5wRjce8, 0, m, &cPack_S5wRjce8_sendMessage);
}

void Heavy_esp8266::cDelay_o6FTwvl1_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_o6FTwvl1, m);
  cPack_onMessage(_c, &Context(_c)->cPack_S5wRjce8, 1, m, &cPack_S5wRjce8_sendMessage);
}

void Heavy_esp8266::cMsg_iUO25s44_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_gdwYOBYs, 0, m, &cDelay_gdwYOBYs_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_o6FTwvl1, 0, m, &cDelay_o6FTwvl1_sendMessage);
  cDelay_onMessage(_c, &Context(_c)->cDelay_o6FTwvl1, 0, m, &cDelay_o6FTwvl1_sendMessage);
}

void Heavy_esp8266::cCast_M4kPrxcW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_xD26U2Tx_sendMessage(_c, 0, m);
}

void Heavy_esp8266::cMsg_3T4mhG33_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 1.0f);
  sVarf_onMessage(_c, &Context(_c)->sVarf_PcXJkILP, m);
}

void Heavy_esp8266::cSwitchcase_Ziz2PO7K_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  switch (msg_getHash(m, 0)) {
    case 0x0: { // "0.0"
      cMsg_51VDBXzj_sendMessage(_c, 0, m);
      break;
    }
    case 0x7A5B032D: { // "stop"
      cMsg_51VDBXzj_sendMessage(_c, 0, m);
      break;
    }
    default: {
      cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_HoigNXS9_sendMessage);
      break;
    }
  }
}

void Heavy_esp8266::cDelay_VTj7TE52_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const m) {
  cDelay_clearExecutingMessage(&Context(_c)->cDelay_VTj7TE52, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_VTj7TE52, 0, m, &cDelay_VTj7TE52_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_i6hfDFim_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_njWb8SNl_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_pMLE3oSd_sendMessage);
}

void Heavy_esp8266::cBinop_6eDd7bWl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Ft1WMD1I, HV_BINOP_MULTIPLY, 1, m, &cBinop_Ft1WMD1I_sendMessage);
}

void Heavy_esp8266::cCast_HoigNXS9_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_51VDBXzj_sendMessage(_c, 0, m);
  cDelay_onMessage(_c, &Context(_c)->cDelay_VTj7TE52, 0, m, &cDelay_VTj7TE52_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_i6hfDFim_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_njWb8SNl_sendMessage);
  cCast_onMessage(_c, HV_CAST_BANG, 0, m, &cCast_pMLE3oSd_sendMessage);
}

void Heavy_esp8266::cBinop_oATJb1Sf_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cDelay_onMessage(_c, &Context(_c)->cDelay_VTj7TE52, 2, m, &cDelay_VTj7TE52_sendMessage);
}

void Heavy_esp8266::cBinop_Ft1WMD1I_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MAX, 1.0f, 0, m, &cBinop_oATJb1Sf_sendMessage);
}

void Heavy_esp8266::cMsg_51VDBXzj_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "clear");
  cDelay_onMessage(_c, &Context(_c)->cDelay_VTj7TE52, 0, m, &cDelay_VTj7TE52_sendMessage);
}

void Heavy_esp8266::cVar_qwpARROW_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Ft1WMD1I, HV_BINOP_MULTIPLY, 0, m, &cBinop_Ft1WMD1I_sendMessage);
}

void Heavy_esp8266::cMsg_YiHsvXED_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setSymbol(m, 0, "samplerate");
  cSystem_onMessage(_c, NULL, 0, m, &cSystem_wRxTscNJ_sendMessage);
}

void Heavy_esp8266::cSystem_wRxTscNJ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 1000.0f, 0, m, &cBinop_6eDd7bWl_sendMessage);
}

void Heavy_esp8266::cCast_pMLE3oSd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_vKZtKM6G_sendMessage(_c, 0, m);
}

void Heavy_esp8266::cMsg_sgTZfcPL_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sVarf_onMessage(_c, &Context(_c)->sVarf_PcXJkILP, m);
}

void Heavy_esp8266::cMsg_y0TkjEoS_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 0.0f);
  sVarf_onMessage(_c, &Context(_c)->sVarf_pWfuupqQ, m);
}

void Heavy_esp8266::cMsg_IrGG6KYF_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(2);
  msg_init(m, 2, msg_getTimestamp(n));
  msg_setElementToFrom(m, 0, n, 0);
  msg_setFloat(m, 1, 1.0f);
  sVari_onMessage(_c, &Context(_c)->sVari_9vW7NGQX, m);
}

void Heavy_esp8266::cSlice_9cEpcEsQ_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_5MKkpb7b, 1, m, &cRandom_5MKkpb7b_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_esp8266::cUnop_tL1mlzdq_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_IrGG6KYF_sendMessage(_c, 0, m);
}

void Heavy_esp8266::cBinop_p9VkiE4d_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_tL1mlzdq_sendMessage);
}

void Heavy_esp8266::cRandom_5MKkpb7b_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 8388610.0f, 0, m, &cBinop_p9VkiE4d_sendMessage);
}

void Heavy_esp8266::cSwitchcase_A3RrZoVk_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  switch (msg_getHash(m, 0)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_9cEpcEsQ, 0, m, &cSlice_9cEpcEsQ_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_5MKkpb7b, 0, m, &cRandom_5MKkpb7b_sendMessage);
      break;
    }
  }
}

void Heavy_esp8266::cBinop_17l5NsN4_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_DIVIDE, 12.0f, 0, m, &cBinop_58jIl81E_sendMessage);
}

void Heavy_esp8266::cBinop_Ld4KJ117_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 440.0f, 0, m, &cBinop_2B83Frpw_sendMessage);
}

void Heavy_esp8266::cBinop_2B83Frpw_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  sPhasor_k_onMessage(_c, &Context(_c)->sPhasor_JOA2W8MW, 0, m);
}

void Heavy_esp8266::cBinop_58jIl81E_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_onMessage(_c, &Context(_c)->cBinop_Ld4KJ117, HV_BINOP_POW, 1, m, &cBinop_Ld4KJ117_sendMessage);
  cMsg_l3kmbzQv_sendMessage(_c, 0, m);
}

void Heavy_esp8266::cMsg_l3kmbzQv_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *const n) {
  HvMessage *m = nullptr;
  m = HV_MESSAGE_ON_STACK(1);
  msg_init(m, 1, msg_getTimestamp(n));
  msg_setFloat(m, 0, 2.0f);
  cBinop_onMessage(_c, &Context(_c)->cBinop_Ld4KJ117, HV_BINOP_POW, 0, m, &cBinop_Ld4KJ117_sendMessage);
}

void Heavy_esp8266::cRandom_qpC1Liuh_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_MULTIPLY, 60.0f, 0, m, &cBinop_7GZDDEWd_sendMessage);
}

void Heavy_esp8266::cSwitchcase_9lhMxNDk_onMessage(HeavyContextInterface *_c, void *o, int letIn, const HvMessage *const m, void *sendMessage) {
  switch (msg_getHash(m, 0)) {
    case 0x7E64BD01: { // "seed"
      cSlice_onMessage(_c, &Context(_c)->cSlice_c5Wpta1r, 0, m, &cSlice_c5Wpta1r_sendMessage);
      break;
    }
    default: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_qpC1Liuh, 0, m, &cRandom_qpC1Liuh_sendMessage);
      break;
    }
  }
}

void Heavy_esp8266::cBinop_7GZDDEWd_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cUnop_onMessage(_c, HV_UNOP_FLOOR, m, &cUnop_7inEpTpK_sendMessage);
}

void Heavy_esp8266::cUnop_7inEpTpK_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cBinop_k_onMessage(_c, NULL, HV_BINOP_SUBTRACT, 69.0f, 0, m, &cBinop_17l5NsN4_sendMessage);
}

void Heavy_esp8266::cSlice_c5Wpta1r_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  switch (letIn) {
    case 0: {
      cRandom_onMessage(_c, &Context(_c)->cRandom_qpC1Liuh, 1, m, &cRandom_qpC1Liuh_sendMessage);
      break;
    }
    case 1: {
      break;
    }
    default: return;
  }
}

void Heavy_esp8266::cCast_njWb8SNl_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cSwitchcase_9lhMxNDk_onMessage(_c, NULL, 0, m, NULL);
}

void Heavy_esp8266::cCast_ak4bStl2_sendMessage(HeavyContextInterface *_c, int letIn, const HvMessage *m) {
  cMsg_3T4mhG33_sendMessage(_c, 0, m);
  cMsg_y0TkjEoS_sendMessage(_c, 0, m);
}




/*
 * Context Process Implementation
 */

int Heavy_esp8266::process(float **inputBuffers, float **outputBuffers, int n) {
  while (hLp_hasData(&inQueue)) {
    hv_uint32_t numBytes = 0;
    ReceiverMessagePair *p = reinterpret_cast<ReceiverMessagePair *>(hLp_getReadBuffer(&inQueue, &numBytes));
    hv_assert(numBytes >= sizeof(ReceiverMessagePair));
    scheduleMessageForReceiver(p->receiverHash, &p->msg);
    hLp_consume(&inQueue);
  }
  const int n4 = n & ~HV_N_SIMD_MASK; // ensure that the block size is a multiple of HV_N_SIMD

  // temporary signal vars
  hv_bufferf_t Bf0, Bf1, Bf2, Bf3, Bf4;
  hv_bufferi_t Bi0, Bi1;

  // input and output vars
  hv_bufferf_t O0;

  // declare and init the zero buffer
  hv_bufferf_t ZERO; __hv_zero_f(VOf(ZERO));

  hv_uint32_t nextBlock = blockStartTimestamp;
  for (int n = 0; n < n4; n += HV_N_SIMD) {

    // process all of the messages for this block
    nextBlock += HV_N_SIMD;
    while (mq_hasMessageBefore(&mq, nextBlock)) {
      MessageNode *const node = mq_peek(&mq);
      node->sendMessage(this, node->let, node->m);
      mq_pop(&mq);
    }

    

    // zero output buffers
    __hv_zero_f(VOf(O0));

    // process all signal functions
    __hv_phasor_k_f(&sPhasor_JOA2W8MW, VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f);
    __hv_sub_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_abs_f(VIf(Bf1), VOf(Bf1));
    __hv_var_k_f(VOf(Bf0), 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f);
    __hv_sub_f(VIf(Bf1), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf1), 6.28318530718f, 6.28318530718f, 6.28318530718f, 6.28318530718f, 6.28318530718f, 6.28318530718f, 6.28318530718f, 6.28318530718f);
    __hv_mul_f(VIf(Bf0), VIf(Bf1), VOf(Bf1));
    __hv_mul_f(VIf(Bf1), VIf(Bf1), VOf(Bf0));
    __hv_mul_f(VIf(Bf1), VIf(Bf0), VOf(Bf2));
    __hv_mul_f(VIf(Bf2), VIf(Bf0), VOf(Bf0));
    __hv_var_k_f(VOf(Bf3), 0.00783333333333f, 0.00783333333333f, 0.00783333333333f, 0.00783333333333f, 0.00783333333333f, 0.00783333333333f, 0.00783333333333f, 0.00783333333333f);
    __hv_var_k_f(VOf(Bf4), -0.166666666667f, -0.166666666667f, -0.166666666667f, -0.166666666667f, -0.166666666667f, -0.166666666667f, -0.166666666667f, -0.166666666667f);
    __hv_fma_f(VIf(Bf2), VIf(Bf4), VIf(Bf1), VOf(Bf1));
    __hv_fma_f(VIf(Bf0), VIf(Bf3), VIf(Bf1), VOf(Bf1));
    __hv_varread_f(&sVarf_pWfuupqQ, VOf(Bf3));
    __hv_varread_i(&sVari_9vW7NGQX, VOi(Bi0));
    __hv_var_k_i(VOi(Bi1), 16807, 16807, 16807, 16807, 16807, 16807, 16807, 16807);
    __hv_mul_i(VIi(Bi0), VIi(Bi1), VOi(Bi1));
    __hv_varwrite_i(&sVari_9vW7NGQX, VIi(Bi1));
    __hv_cast_if(VIi(Bi1), VOf(Bf0));
    __hv_var_k_f(VOf(Bf4), 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f, 4.65661e-10f);
    __hv_mul_f(VIf(Bf0), VIf(Bf4), VOf(Bf4));
    __hv_biquad_k_f(&sBiquad_k_taMtrbL8, VIf(Bf4), VOf(Bf4));
    __hv_var_k_f(VOf(Bf0), 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f);
    __hv_mul_f(VIf(Bf4), VIf(Bf0), VOf(Bf0));
    __hv_varread_f(&sVarf_PcXJkILP, VOf(Bf4));
    __hv_mul_f(VIf(Bf0), VIf(Bf4), VOf(Bf4));
    __hv_fma_f(VIf(Bf1), VIf(Bf3), VIf(Bf4), VOf(Bf4));
    __hv_line_f(&sLine_Q6OGeD68, VOf(Bf3));
    __hv_mul_f(VIf(Bf4), VIf(Bf3), VOf(Bf3));
    __hv_add_f(VIf(Bf3), VIf(O0), VOf(O0));

    // save output vars to output buffer
    __hv_store_f(outputBuffers[0]+n, VIf(O0));
  }

  blockStartTimestamp = nextBlock;

  return n4; // return the number of frames processed
}

int Heavy_esp8266::processInline(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(!(n4 & HV_N_SIMD_MASK)); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s)
  float **const bIn = NULL;

  // define the heavy output buffer for 1 channel(s)
  float **const bOut = &outputBuffers;

  int n = process(bIn, bOut, n4);
  return n;
}

int Heavy_esp8266::processInlineInterleaved(float *inputBuffers, float *outputBuffers, int n4) {
  hv_assert(n4 & ~HV_N_SIMD_MASK); // ensure that n4 is a multiple of HV_N_SIMD

  // define the heavy input buffer for 0 channel(s), uninterleave
  float *const bIn = NULL;

  // define the heavy output buffer for 1 channel(s)
  float *const bOut = outputBuffers;

  int n = processInline(bIn, bOut, n4);

  

  return n;
}
