/*
 * Copyright (C) 2018 Swift Navigation Inc.
 * Contact: Swift Navigation <dev@swiftnav.com>
 *
 * This source is subject to the license found in the file 'LICENSE' which must
 * be distributed together with this source. All other rights reserved.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "rtcm3_msm_utils.h"

double msm_signal_frequency(const constellation_t cons,
                            const uint8_t signal_index,
                            const bool signal_mask[MSM_SIGNAL_MASK_SIZE],
                            const uint8_t sat_info) {
  (void)signal_mask;
  (void)sat_info;

  /* TODO: constellation support */

  switch (cons) {
    case CONSTELLATION_GPS:
      if (signal_index == 0) {
        return GPS_L1_FREQ;
      } else {
        return GPS_L2_FREQ;
      }
    case CONSTELLATION_SBAS:
    case CONSTELLATION_GLO:
    case CONSTELLATION_BDS2:
    case CONSTELLATION_QZS:
    case CONSTELLATION_GAL:
    case CONSTELLATION_INVALID:
    case CONSTELLATION_COUNT:
    default:
      return 0;
  }
}

/* Convert message number into MSM message type */
msm_enum to_msm_type(uint16_t msg_num) {
  if (msg_num < 1071 || msg_num > 1127) {
    return MSM_UNKNOWN;
  }
  switch (msg_num % 10) {
    case 1:
      return MSM1;
    case 2:
      return MSM2;
    case 3:
      return MSM3;
    case 4:
      return MSM4;
    case 5:
      return MSM5;
    case 6:
      return MSM6;
    case 7:
      return MSM7;
    default:
      return MSM_UNKNOWN;
  }
}

/* Convert message number into constellation enum */
constellation_t to_constellation(uint16_t msg_num) {
  if (msg_num < 1071) {
    return CONSTELLATION_INVALID;
  }
  if (msg_num < 1080) {
    return CONSTELLATION_GPS;
  }
  if (msg_num < 1090) {
    return CONSTELLATION_GLO;
  }
  if (msg_num < 1100) {
    return CONSTELLATION_GAL;
  }
  if (msg_num < 1110) {
    return CONSTELLATION_SBAS;
  }
  if (msg_num < 1120) {
    return CONSTELLATION_QZS;
  }
  if (msg_num < 1130) {
    return CONSTELLATION_BDS2;
  }
  return CONSTELLATION_INVALID;
}

uint8_t count_mask_bits(uint16_t mask_size, const bool mask[mask_size]) {
  uint8_t ret = 0;
  for (uint16_t i = 0; i < mask_size; i++) {
    ret += mask[i];
  }
  return ret;
}

uint8_t get_msm_gps_prn(uint8_t sat_id) {
  /*RTCM 10403.3 Table 3.5-90 */
  return sat_id + GPS_FIRST_PRN;
}

code_t get_msm_gps_code(uint8_t signal_id) {
  /* RTCM 10403.3 Table 3.5-91 */
  switch (signal_id) {
    case 2:
      return CODE_GPS_L1CA;
    case 3:
      return CODE_GPS_L1P;
    /* case 4: 1W */
    /* case 8: 2C */
    case 9:
      return CODE_GPS_L2P;
    /* case 10: 2W */
    case 15:
      return CODE_GPS_L2CM;
    case 16:
      return CODE_GPS_L2CL;
    case 17:
      return CODE_GPS_L2CX;
    case 22:
      return CODE_GPS_L5I;
    case 23:
      return CODE_GPS_L5Q;
    case 24:
      return CODE_GPS_L5X;
    /* case 30: 1S */
    /* case 31: 1L */
    /* case 32: 1X */
    default:
      /* other GPS codes cannot be represented in SBP */
      return CODE_INVALID;
  }
}

uint8_t get_msm_glo_prn(uint8_t sat_id) {
  /*RTCM 10403.3 Table 3.5-95 */
  return sat_id + GLO_FIRST_PRN;
}

code_t get_msm_glo_code(uint8_t signal_id) {
  /* RTCM 10403.3 Table 3.5-96 */
  switch (signal_id) {
    case 2:
      return CODE_GLO_L1OF;
    /* case 3: CODE_GLO_L1P; */
    case 8:
      return CODE_GLO_L2OF;
    /* case 9: CODE_GLO_L2P; */
    default:
      /* other GLO codes cannot be represented in SBP */
      return CODE_INVALID;
  }
}

uint8_t get_msm_gal_prn(uint8_t sat_id) {
  /*RTCM 10403.3 Table 3.5-98 */

  /* Note: need to check how these are encoded in SBP:
   *  51 - GIOVE-A
   *  52 - GIOVE-B
   */

  return sat_id + GAL_FIRST_PRN;
}

code_t get_msm_gal_code(uint8_t signal_id) {
  /* RTCM 10403.3 Table 3.5-99 */
  switch (signal_id) {
    case 2:                /* 1C */
      return CODE_GAL_E1C; /* pilot channel at E1 */
    /* case 3: 1A */
    case 4:                /* 1B */
      return CODE_GAL_E1B; /* data channel at E1 (1540 * 1.023 MHz) */
    case 5:                /* 1X */
      return CODE_GAL_E1X; /* combined tracking on E1 */
    /*case 6: 1Z */
    case 8: /* 6C */
      return CODE_GAL_E6C;
    /* case 9: 6A */
    case 10: /* 6B */
      return CODE_GAL_E6B;
    case 11:               /* 6X */
      return CODE_GAL_E6X; /* combined tracking on E6 */
    /* case 12: 6Z */
    case 14: /* 7I */
      return CODE_GAL_E7I;
    case 15: /* 7Q */
      return CODE_GAL_E7Q;
    case 16:               /* 7X */
      return CODE_GAL_E7X; /* combined tracking on E5b */
    case 18:               /* 8I */
    case 19:               /* 8Q */
    case 20:               /* 8X */
      return CODE_GAL_E8;  /* E5 AltBOC tracking ??*/
    case 22:               /* 5I */
      return CODE_GAL_E5I;
    case 23: /* 5Q */
      return CODE_GAL_E5Q;
    case 24:               /* 5X */
      return CODE_GAL_E5X; /* combined tracking on E5a */
    default:
      /* other GAL codes cannot be represented in SBP */
      return CODE_INVALID;
  }
}

uint8_t get_msm_sbas_prn(uint8_t sat_id) {
  /*RTCM 10403.3 Table 3.5-101 */
  return sat_id + SBAS_FIRST_PRN;
}

code_t get_msm_sbas_code(uint8_t signal_id) {
  /* RTCM 10403.3 Table 3.5-102 */
  switch (signal_id) {
    case 2:
      return CODE_SBAS_L1CA;
    /* case 22: 5I */
    /* case 23: 5Q */
    /* case 24: 5X */
    default:
      /* other SBAS codes cannot be represented in SBP */
      return CODE_INVALID;
  }
}

uint8_t get_msm_qzs_prn(uint8_t sat_id) {
  /*RTCM 10403.3 Table 3.5-104 */
  return sat_id + QZS_FIRST_PRN;
}

code_t get_msm_qzs_code(uint8_t signal_id) {
  /* RTCM 10403.3 Table 3.5-105 */
  switch (signal_id) {
    case 2: /* 1C */
      return CODE_QZS_L1CA;
    /* case 9:  6S */
    /* case 10:  6L */
    /* case 11:  6X */
    case 15: /* 2S */
      return CODE_QZS_L2CM;
    case 16: /* 2L */
      return CODE_QZS_L2CL;
    case 17: /* 2X */
      return CODE_QZS_L2CX;
    case 22: /* 5I */
      return CODE_QZS_L5I;
    case 23: /* 5Q */
      return CODE_QZS_L5Q;
    case 24: /* 5X */
      return CODE_QZS_L5X;
    /* case 30: 1S */
    /* case 31: 1L */
    /* case 32: 1X */
    default:
      /* other QZS codes cannot be represented in SBP */
      return CODE_INVALID;
  }
}

uint8_t get_msm_bds2_prn(uint8_t sat_id) {
  /*RTCM 10403.3 Table 3.5-107 */
  return sat_id + BDS2_FIRST_PRN;
}

code_t get_msm_bds2_code(uint8_t signal_id) {
  /* RTCM 10403.3 Table 3.5-108 */
  switch (signal_id) {
    case 2: /* 2I */
      return CODE_BDS2_B11;
    /* case 3:  2Q */
    /* case 4:  2X */
    /* case 8:  6I */
    /* case 9:  6Q */
    /* case 10:  6X */
    case 14: /* 7I */
      return CODE_BDS2_B2;
    /* case 15:  7Q */
    /* case 16:  7X */
    default:
      /* other BDS2 codes cannot be represented in SBP */
      return CODE_INVALID;
  }
}
