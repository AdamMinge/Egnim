/* ------------------------------------ Qt ---------------------------------- */
#include <QGuiApplication>
#include <QScreen>
/* -------------------------------- Tools Shared ---------------------------- */
#include "egnim/tools/shared/qtdpi/qtdpiinfo.h"
/* -------------------------------------------------------------------------- */

namespace tools {

int QtDpiInfo::defaultDpi()
{
  static auto dpi = []{
    if(const auto screen = QGuiApplication::primaryScreen())
      return static_cast<int>(screen->logicalDotsPerInchX());

#ifdef Q_OS_MAC
    return 72;
#else
    return 96;
#endif
  }();

  return dpi;
}

qreal QtDpiInfo::defaultDpiScale()
{
  static auto dpi = []{
    if(const auto screen = QGuiApplication::primaryScreen())
      return screen->logicalDotsPerInchX() / 96.0;
    return 1.0;
  }();

  return dpi;
}

int QtDpiInfo::dpiScaled(int value)
{
  return qRound(dpiScaled(static_cast<qreal>(value)));
}

qreal QtDpiInfo::dpiScaled(qreal value)
{
#ifdef Q_OS_MAC
  return value;
#else
  static const auto scale = defaultDpiScale();
  return value * scale;
#endif
}

QSize QtDpiInfo::dpiScaled(const QSize& value)
{
  return QSize(dpiScaled(value.width()),
               dpiScaled(value.height()));
}

QPoint QtDpiInfo::dpiScaled(const QPoint& value)
{
  return QPoint(dpiScaled(value.x()),
                dpiScaled(value.y()));
}

QRectF QtDpiInfo::dpiScaled(const QRectF& value)
{
  return QRectF(dpiScaled(value.x()),
                dpiScaled(value.y()),
                dpiScaled(value.width()),
                dpiScaled(value.height()));
}

} // namespace tools
