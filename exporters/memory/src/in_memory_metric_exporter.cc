// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#include "opentelemetry/exporters/memory/in_memory_metric_exporter.h"
#include "opentelemetry/sdk/instrumentationscope/instrumentation_scope.h"
#include "opentelemetry/sdk/metrics/aggregation/default_aggregation.h"
#include "opentelemetry/sdk/metrics/aggregation/histogram_aggregation.h"
#include "opentelemetry/sdk/resource/resource.h"
#include "opentelemetry/sdk_config.h"

#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <map>
#include <mutex>

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace metrics
{

InMemoryMetricExporter::InMemoryMetricExporter(
    sdk::metrics::AggregationTemporality aggregation_temporality) noexcept
    : aggregation_temporality_(aggregation_temporality)
{}

sdk::metrics::AggregationTemporality InMemoryMetricExporter::GetAggregationTemporality(
    sdk::metrics::InstrumentType /* instrument_type */) const noexcept
{
  return aggregation_temporality_;
}

sdk::common::ExportResult InMemoryMetricExporter::Export(
    const sdk::metrics::ResourceMetrics &data) noexcept
{
  if (isShutdown())
  {
    OTEL_INTERNAL_LOG_ERROR("[InMemory Metric] Exporting "
                            << data.scope_metric_data_.size()
                            << " records(s) failed, exporter is shutdown");
    return sdk::common::ExportResult::kFailure;
  }

  if ( ! data.scope_metric_data_.empty() )
	  std::cout << "break" << std::endl;

  return sdk::common::ExportResult::kSuccess;
}

bool InMemoryMetricExporter::ForceFlush(std::chrono::microseconds /* timeout */) noexcept
{
  const std::lock_guard<opentelemetry::common::SpinLockMutex> locked(lock_);
  return true;
}

bool InMemoryMetricExporter::Shutdown(std::chrono::microseconds /* timeout */) noexcept
{
  const std::lock_guard<opentelemetry::common::SpinLockMutex> locked(lock_);
  is_shutdown_ = true;
  return true;
}

bool InMemoryMetricExporter::isShutdown() const noexcept
{
  const std::lock_guard<opentelemetry::common::SpinLockMutex> locked(lock_);
  return is_shutdown_;
}

}  // namespace metrics
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
