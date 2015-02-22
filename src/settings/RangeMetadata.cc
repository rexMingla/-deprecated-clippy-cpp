/* See the file "LICENSE.md" for the full license governing this code. */
#include "RangeMetadata.h"

#include "src/common/Logger.h"

#include <cassert>

namespace {
  Logger log("RangeSettingMetadata");
}

RangeMetadata::RangeMetadata(const QVariant& defaultValue, const QVariant& min, const QVariant& max)
  : SettingMetadata(RANGE, defaultValue),
    min_(min),
    max_(max) {
  assert(min.type() == max.type() &&
      QString("types must be the same. min=%1 max=%2").arg(min.type()).arg(max.type()).toStdString().c_str());
  assert(min.type() == defaultValue.type() &&
      QString("types must be the same. min=%1 defaultValue=%2").arg(min.type()).arg(defaultValue.type()).toStdString().c_str());
  assert(min.toInt() <= max.toInt());
}

RangeMetadata::~RangeMetadata() {
}

bool RangeMetadata::isValid(const QVariant& value, QString& error) const {
  bool isOk;
  int intValue = value.toInt(&isOk);
  if (!isOk) {
    error = QString("Only int value is supported at the moment. value=%1").arg(value.toString());
  } else if (intValue < min_.toInt() || intValue > max_.toInt()) {
    error = QString("Value must be between %1 and %2").arg(min_.toInt()).arg(max_.toInt());
  }
  return error.isEmpty();
}

const QVariant& RangeMetadata::min() const {
  return min_;
}

const QVariant& RangeMetadata::max() const {
  return max_;
}
