#ifndef UTILS_H
#define UTILS_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtGlobal>
#include <QPoint>
#include <QRectF>
#include <QSize>
/* -------------------------------------------------------------------------- */

namespace utils
{

  int defaultDpi();
  qreal defaultDpiScale();

  int dpiScaled(int value);
  qreal dpiScaled(qreal value);
  QSize dpiScaled(const QSize& value);
  QPoint dpiScaled(const QPoint& value);
  QRectF dpiScaled(const QRectF& value);

  QStringList projectSupportedFormats();

} // namespace utils

#endif //UTILS_H
