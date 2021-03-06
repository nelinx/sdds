/****************************************************************************
 * Copyright (C) 2017 RheinMain University of Applied Sciences              *
 *                                                                          *
 * This file is part of:                                                    *
 *      _____  _____   _____                                                *
 *     |  __ \|  __ \ / ____|                                               *
 *  ___| |  | | |  | | (___                                                 *
 * / __| |  | | |  | |\___ \                                                *
 * \__ \ |__| | |__| |____) |                                               *
 * |___/_____/|_____/|_____/                                                *
 *                                                                          *
 * This Source Code Form is subject to the terms of the Mozilla Public      *
 * License, v. 2.0. If a copy of the MPL was not distributed with this      *
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.                 *
 ****************************************************************************/

/**
 * @file      Qos.h
 * @author    Kai Beckmann
 * @copyright MPL 2 
 * @see       https://github.com/sdds/sdds
 * structure to hold the qos properties regarding a dw
 */



#ifndef  QOS_INC
#define  QOS_INC
#include "sdds_types.h"
#include "os-ssal/TimeMng.h"

#ifdef SDDS_QOS_LATENCYBUDGET
#ifndef SDDS_QOS_LATBUD_COMM
#define SDDS_QOS_LATBUD_COMM 0
#endif

#ifndef SDDS_QOS_LATBUD_READ
#define SDDS_QOS_LATBUD_READ 0
#endif

#ifndef SDDS_QOS_DW_LATBUD
#define SDDS_QOS_DW_LATBUD 0
#endif
#endif

#ifdef SDDS_HAS_QOS_RELIABILITY
#define SDDS_QOS_RELIABILITY_KIND_BESTEFFORT 1
#define SDDS_QOS_RELIABILITY_KIND_RELIABLE 2
#define SDDS_QOS_RELIABILITY_CONFIRMATIONTYPE_ACK 1
#define SDDS_QOS_RELIABILITY_CONFIRMATIONTYPE_NACK 2
#define SDDS_QOS_RELIABILITY_SEQSIZE_BASIC 4
#define SDDS_QOS_RELIABILITY_SEQSIZE_SMALL 8
#define SDDS_QOS_RELIABILITY_SEQSIZE_BIG 16
#define SDDS_QOS_RELIABILITY_SEQSIZE_HUGE 32
#endif

struct SourceQos_t {
#ifdef SDDS_QOS_LATENCYBUDGET
#if SDDS_QOS_DW_LATBUD < 65536
    msecu16_t latBudDuration;
#else
    msecu32_t latBudDuration;
#endif
#endif

    uint8_t subMsgNeeded;
};

#endif   /* ----- #ifndef QOS_INC  ----- */
