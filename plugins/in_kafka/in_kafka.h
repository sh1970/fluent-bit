/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  Fluent Bit
 *  ==========
 *  Copyright (C) 2019-2021 The Fluent Bit Authors
 *  Copyright (C) 2015-2018 Treasure Data Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef FLB_IN_KAFKA_H
#define FLB_IN_KAFKA_H

#include <fluent-bit/flb_config.h>
#include <fluent-bit/flb_input.h>
#include <fluent-bit/flb_input_thread.h>
#include <fluent-bit/flb_kafka.h>
#include <fluent-bit/flb_log_event_encoder.h>
#include <fluent-bit/aws/flb_aws_msk_iam.h>


#define FLB_IN_KAFKA_DEFAULT_POLL_MS       "500"
#define FLB_IN_KAFKA_DEFAULT_FORMAT        "none"
#define FLB_IN_KAFKA_UNLIMITED             (size_t)-1
#define FLB_IN_KAFKA_BUFFER_MAX_SIZE       "4M"
#define FLB_IN_KAFKA_ENABLE_AUTO_COMMIT    "false"

enum {
    FLB_IN_KAFKA_FORMAT_NONE,
    FLB_IN_KAFKA_FORMAT_JSON,
};

struct flb_in_kafka_config {
    struct flb_kafka kafka;
    struct flb_input_instance *ins;
    struct flb_log_event_encoder *log_encoder;
    int poll_ms;
    int format;
    char *format_str;
    int coll_fd;
    size_t buffer_max_size;          /* Maximum size of chunk allocation */
    size_t polling_threshold;
    int poll_timeout_ms;
    bool enable_auto_commit;
    struct flb_kafka_opaque *opaque;

#ifdef FLB_HAVE_AWS_MSK_IAM
    flb_sds_t aws_msk_iam_cluster_arn;
    struct flb_aws_msk_iam *msk_iam;
#endif

    /* SASL mechanism configured in rdkafka.sasl.mechanism */
    int aws_msk_iam;
    flb_sds_t sasl_mechanism;
};

#endif
