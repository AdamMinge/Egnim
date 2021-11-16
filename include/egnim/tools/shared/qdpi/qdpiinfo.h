#ifndef EGNIM_TOOLS_DPI_INFO_H
#define EGNIM_TOOLS_DPI_INFO_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QtGlobal>
#include <QPoint>
#include <QRectF>
#include <QSize>
/* -------------------------------- Tools Shared ---------------------------- */
#include <egnim/tools/shared/export.h>
/* -------------------------------------------------------------------------- */

namespace tools
{

  class TOOLS_SHARED_API QDpiInfo
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
    QDpiInfo() = default;
  };

} // namespace tools

#endif //EGNIM_TOOLS_DPI_INFO_H
