/*  =========================================================================
    DataReader - DDS DataReader representation, allows the application to
                 declare the data it wishes to receive.

    Copyright (c) the Contributors as noted in the AUTHORS file.

    This file is part of sDDS:
    http://wwwvs.cs.hs-rm.de.
    =========================================================================
 */

#include "sDDS.h"

rc_t
DataWriter_init () {
    return SDDS_RT_OK;
}

#if defined(SDDS_TOPIC_HAS_SUB) || defined(FEATURE_SDDS_BUILTIN_TOPICS_ENABLED)
rc_t
DataWriter_write(DataWriter_t* self, Data data, void* waste) {
    assert (self);
    (void) waste;
    NetBuffRef_t* buffRef = NULL;
    Topic_t* topic = self->topic;
    domainid_t domain = topic->domain;
    Locator_t* dest = topic->dsinks.list;
    rc_t ret;

#ifdef SDDS_QOS_LATENCYBUDGET
#if SDDS_QOS_DW_LATBUD < 65536
    msecu16_t latBudDuration = self->qos.latBudDuration;
    time16_t deadline;
    ret = Time_getTime16(&deadline);
#else
    msecu32_t latBudDuration = self->qos.latBudDuration;
    time32_t deadline;
    rc_t ret = Time_getTime32(&deadline);
#endif

    // to do exact calculation
    deadline += (latBudDuration - SDDS_QOS_LATBUD_COMM - SDDS_QOS_LATBUD_READ);
#endif
    buffRef = findFreeFrame(dest);
    buffRef->addr = dest;
#ifdef SDDS_QOS_LATENCYBUDGET
    //  If new deadline is earlier
    if ((buffRef->sendDeadline == 0)) {
        buffRef->sendDeadline = deadline;
        Log_debug("sendDeadline: %d\n", buffRef->sendDeadline);
    }
#endif

    if (buffRef->curDomain != domain) {
        SNPS_writeDomain(buffRef, domain);
        buffRef->curDomain = domain;
    }

    if (buffRef->curTopic != topic) {
        SNPS_writeTopic(buffRef, topic->id);
        buffRef->curTopic = topic;
    }

    if (SNPS_writeData(buffRef, topic->Data_encode, data) != SDDS_RT_OK) {
        // something went wrong oO
        return SDDS_RT_FAIL;
    }

#ifdef SDDS_QOS_RELIABILITY
#if SDDS_QOS_RELIABILITY_KIND == KIND_BESTEFFORT
#if SDDS_QOS_RELIABILITY_SEQSIZE == SDDS_QOS_RELIABILITY_SEQSIZE_NORMAL
    if (SNPS_writeSeqNr(buffRef, self->qos.seqNr) != SDDS_RT_OK) {
        return SDDS_RT_FAIL;
    }
#elif SDDS_QOS_RELIABILITY_SEQSIZE == SDDS_QOS_RELIABILITY_SEQSIZE_SMALL
    if (SNPS_writeSeqNrSmall(buffRef, self->qos.seqNr) != SDDS_RT_OK) {
        return SDDS_RT_FAIL;
    }
#elif SDDS_QOS_RELIABILITY_SEQSIZE == SDDS_QOS_RELIABILITY_SEQSIZE_BIG
    if (SNPS_writeSeqNrBig(buffRef, self->qos.seqNr) != SDDS_RT_OK) {
        return SDDS_RT_FAIL;
    }
#elif SDDS_QOS_RELIABILITY_SEQSIZE == SDDS_QOS_RELIABILITY_SEQSIZE_HUGE
    if (SNPS_writeSeqNrHUGE(buffRef, self->qos.seqNr) != SDDS_RT_OK) {
        return SDDS_RT_FAIL;
    }
#endif
    self->qos.seqNr++;

#else
    //TODO
#endif
#endif
    Log_debug("writing to domain %d and topic %d \n", topic->domain, topic->id);

    ret = checkSending(buffRef);
    return ret;
}
#endif // SDDS_TOPIC_HAS_SUB


#ifdef FEATURE_SDDS_BUILTIN_TOPICS_ENABLED
rc_t
DataWriter_writeAddress(DataWriter_t* self,
                        castType_t castType,
                        addrType_t addrType,
                        uint8_t* addr,
                        uint8_t addrLen) {
    assert (self);
    NetBuffRef_t* buffRef = NULL;
    Topic_t* topic = _this->topic;
    domainid_t domain = topic->domain;
    Locator_t* dest = topic->dsinks.list;

    buffRef = findFreeFrame(dest);
    buffRef->addr = dest;

    if (buffRef->curDomain != domain) {
        SNPS_writeDomain(buffRef, domain);
        buffRef->curDomain = domain;
    }
    if (buffRef->curTopic != topic) {
        SNPS_writeTopic(buffRef, topic->id);
        buffRef->curTopic = topic;
    }

    if (SNPS_writeAddress(buffRef, castType, addrType, addr, addrLen) != SDDS_RT_OK) {
        // something went wrong oO
        return SDDS_RT_FAIL;
    }
    Log_debug("writing to domain %d and topic %d \n", topic->domain, topic->id);

    return SDDS_RT_OK;
}
#endif