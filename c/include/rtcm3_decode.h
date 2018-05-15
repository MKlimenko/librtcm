/*
 * Copyright (C) 2017 Swift Navigation Inc.
 * Contact: Swift Navigation <dev@swiftnav.com>
 *
 * This source is subject to the license found in the file 'LICENSE' which must
 * be distributed together with this source. All other rights reserved.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef SWIFTNAV_RTCM3_DECODE_H
#define SWIFTNAV_RTCM3_DECODE_H

#include "rtcm3_messages.h"

int8_t rtcm3_decode_1001(const uint8_t *buff, rtcm_obs_message *msg_1001);
int8_t rtcm3_decode_1002(const uint8_t *buff, rtcm_obs_message *msg_1002);
int8_t rtcm3_decode_1003(const uint8_t *buff, rtcm_obs_message *msg_1003);
int8_t rtcm3_decode_1004(const uint8_t *buff, rtcm_obs_message *msg_1004);
int8_t rtcm3_decode_1005(const uint8_t *buff, rtcm_msg_1005 *msg_1005);
int8_t rtcm3_decode_1006(const uint8_t *buff, rtcm_msg_1006 *msg_1006);
int8_t rtcm3_decode_1007(const uint8_t *buff, rtcm_msg_1007 *msg_1007);
int8_t rtcm3_decode_1008(const uint8_t *buff, rtcm_msg_1008 *msg_1008);
int8_t rtcm3_decode_1010(const uint8_t *buff, rtcm_obs_message *msg_1010);
int8_t rtcm3_decode_1012(const uint8_t *buff, rtcm_obs_message *msg_1012);
int8_t rtcm3_decode_1029(const uint8_t *buff, rtcm_msg_1029 *msg_1029);
int8_t rtcm3_decode_1033(const uint8_t *buff, rtcm_msg_1033 *msg_1033);
int8_t rtcm3_decode_1230(const uint8_t *buff, rtcm_msg_1230 *msg_1230);
int8_t rtcm3_decode_msm4(const uint8_t *buff, rtcm_msm_message *msg_msm);
int8_t rtcm3_decode_msm5(const uint8_t *buff, rtcm_msm_message *msg_msm);
int8_t rtcm3_decode_msm6(const uint8_t *buff, rtcm_msm_message *msg_msm);
int8_t rtcm3_decode_msm7(const uint8_t *buff, rtcm_msm_message *msg_msm);

#endif /* SWIFTNAV_RTCM3_DECODE_H */
