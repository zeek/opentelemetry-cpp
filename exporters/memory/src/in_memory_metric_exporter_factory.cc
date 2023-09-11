// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#include "opentelemetry/exporters/memory/in_memory_metric_exporter_factory.h"
#include "opentelemetry/exporters/memory/in_memory_metric_exporter.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace exporter
{
namespace metrics
{

std::unique_ptr<opentelemetry::sdk::metrics::PushMetricExporter>
InMemoryMetricExporterFactory::Create(sdk::metrics::AggregationTemporality aggregation_temporality)
{
  std::unique_ptr<opentelemetry::sdk::metrics::PushMetricExporter> exporter(
      new InMemoryMetricExporter(aggregation_temporality));
  return exporter;
}

}  // namespace metrics
}  // namespace exporter
OPENTELEMETRY_END_NAMESPACE
