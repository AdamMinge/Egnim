/* ------------------------------------ Qt ---------------------------------- */
#include <QGuiApplication>
#include <QImageReader>
#include <QScreen>
/* ----------------------------------- Local -------------------------------- */
#include "utils.h"
#include "document/document.h"
/* -------------------------------------------------------------------------- */

namespace utils {

int defaultDpi()
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

qreal defaultDpiScale()
{
  static auto dpi = []{
    if(const auto screen = QGuiApplication::primaryScreen())
      return screen->logicalDotsPerInchX() / 96.0;
    return 1.0;
  }();

  return dpi;
}

int dpiScaled(int value)
{
  return qRound(dpiScaled(static_cast<qreal>(value)));
}

qreal dpiScaled(qreal value)
{
#ifdef Q_OS_MAC
  return value;
#else
  static const auto scale = defaultDpiScale();
  return value * scale;
#endif
}

QSize dpiScaled(const QSize& value)
{
  return QSize(dpiScaled(value.width()),
               dpiScaled(value.height()));
}

QPoint dpiScaled(const QPoint& value)
{
  return QPoint(dpiScaled(value.x()),
                dpiScaled(value.y()));
}

QRectF dpiScaled(const QRectF& value)
{
  return QRectF(dpiScaled(value.x()),
                dpiScaled(value.y()),
                dpiScaled(value.width()),
                dpiScaled(value.height()));
}

QStringList projectSupportedFormats()
{
  auto supported_formats = QStringList();

  auto documents_extensions = Document::getDocumentExtensions();
  std::transform(documents_extensions.begin(), documents_extensions.end(), documents_extensions.begin(),
                 [](auto& extension){ return QString("*.%1").arg(extension); });

  auto image_extensions = QStringList();
  for(auto& extension : QImageReader::supportedImageFormats())
    image_extensions.append(QString("*.%1").arg(QString::fromLocal8Bit(extension)));

  supported_formats << documents_extensions
                    << image_extensions;

  return supported_formats;
}

} // namespace utils