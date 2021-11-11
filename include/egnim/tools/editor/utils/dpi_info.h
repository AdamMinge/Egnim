#ifndef EGNIM_DPI_INFO_H
#define EGNIM_DPI_INFO_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtGlobal>
#include <QPoint>
#include <QRectF>
#include <QSize>
/* -------------------------------------------------------------------------- */

class DpiInfo
{
public:
  [[nodiscard]] static int defaultDpi();
  [[nodiscard]] static qreal defaultDpiScale();

  [[nodiscard]] static int dpiScaled(int value);
  [[nodiscard]] static qreal dpiScaled(qreal value);
  [[nodiscard]] static QSize dpiScaled(const QSize& value);
  [[nodiscard]] static QPoint dpiScaled(const QPoint& value);
  [[nodiscard]] static QRectF dpiScaled(const QRectF& value);

private:
  DpiInfo() = default;
};

#endif //EGNIM_DPI_INFO_H
