// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "opentelemetry/common/spin_lock_mutex.h"
#include "opentelemetry/sdk/metrics/data/metric_data.h"
#include "opentelemetry/sdk/metrics/export/metric_producer.h"
#include "opentelemetry/sdk/metrics/instruments.h"
#include "opentelemetry/sdk/metrics/push_metric_exporter.h"
#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace resource
{
class Resource;
}  // namespace resource
}  // namespace sdk

namespace exporter
{
namespace metrics
{

/**
 * The InMemoryMetricExporter exports record data to memory.
 */
class InMemoryMetricExporter final : public opentelemetry::sdk::metrics::PushMetricExporter
{
public:
  /**
   * Create an InMemoryMetricExporter.
   */
  explicit InMemoryMetricExporter(sdk::metrics::AggregationTemporality aggregation_temporality =
                                  sdk::metrics::AggregationTemporality::kCumulative) noexcept;

  /**
   * Export
   * @param data metrics data
   */
  sdk::common::ExportResult Export(const sdk::metrics::ResourceMetrics &data) noexcept override;

  /**
   * Get the AggregationTemporality for in-memory exporter
   *
   * @return AggregationTemporality
   */
  sdk::metrics::AggregationTemporality GetAggregationTemporality(
	  sdk::metrics::InstrumentType instrument_type) const noexcept override;

  /**
   * Force flush the exporter.
   */
  bool ForceFlush(
      std::chrono::microseconds timeout = (std::chrono::microseconds::max)()) noexcept override;

  /**
   * Shut down the exporter.
   * @param timeout an optional timeout.
   * @return return the status of this operation
   */
  bool Shutdown(
      std::chrono::microseconds timeout = (std::chrono::microseconds::max)()) noexcept override;

private:
  bool is_shutdown_ = false;
  mutable opentelemetry::common::SpinLockMutex lock_;
  sdk::metrics::AggregationTemporality aggregation_temporality_;
  bool isShutdown() const noexcept;
};
}  // namespace metrics
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
