#ifndef DOCUMENT_H
#define DOCUMENT_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
/* -------------------------------------------------------------------------- */

class Document : public QObject
{
  Q_OBJECT

public:
  enum class Type;

public:
  ~Document() override;

  [[nodiscard]] Type getType() const;

  void setFileName(const QString& file_name);
  [[nodiscard]] const QString& getFileName() const;
  [[nodiscard]] QString getDisplayName() const;

  bool save(const QString& file_name);
  static std::unique_ptr<Document> load(const QString& file_name);

Q_SIGNALS:
  void fileNameChanged(const QString& new_file_name, const QString& old_file_name);

  void saved();

protected:
  explicit Document(Type type, QString file_name, QObject* parent = nullptr);

private:
  Type m_type;
  QString m_file_name;
};

enum class Document::Type
{
  Scene,
};

#endif //DOCUMENT_H
