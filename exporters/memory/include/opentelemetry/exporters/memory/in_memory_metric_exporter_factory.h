// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <memory>

#include "opentelemetry/sdk/metrics/instruments.h"
#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace metrics
{
class PushMetricExporter;
}  // namespace metrics
}  // namespace sdk

namespace exporter
{
namespace metrics
{

/**
 * Factory class for InMemoryMetricExporter.
 */
class OPENTELEMETRY_EXPORT InMemoryMetricExporterFactory
{
public:
  /**
   * Creates an InMemoryMetricExporter.
   */
  static std::unique_ptr<opentelemetry::sdk::metrics::PushMetricExporter> Create(
      sdk::metrics::AggregationTemporality aggregation_temporality = sdk::metrics::AggregationTemporality::kCumulative);
};

}  // namespace metrics
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
