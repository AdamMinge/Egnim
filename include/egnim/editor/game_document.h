#ifndef GAME_DOCUMENT_H
#define GAME_DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDateTime>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/document.h>
/* -------------------------------------------------------------------------- */

class GameDocument : public Document
{
  Q_OBJECT

public:
  explicit GameDocument(QString file_name, QObject* parent = nullptr);
  ~GameDocument() override;

  [[nodiscard]] const QDateTime& getLastModified() const;

  bool save(const QString& file_name) override;

Q_SIGNALS:
  void saved();

private:
  QDateTime m_last_modified;
};

#endif //GAME_DOCUMENT_H
