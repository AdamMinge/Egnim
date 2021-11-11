#ifndef EGNIM_ISSUE_H
#define EGNIM_ISSUE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QString>
/* --------------------------------- Standard ------------------------------- */
#include <functional>
/* -------------------------------------------------------------------------- */

class Issue
{
public:
  enum class Severity;
  using Callback = std::function<void()>;

public:
  explicit Issue(Severity severity, QString text, Callback callback = Callback{});

  void setCallback(Callback callback);

  [[nodiscard]] Severity getSeverity() const;
  [[nodiscard]] QString getText() const;
  [[nodiscard]] Callback getCallback() const;

  bool operator==(const Issue& other) const;
  bool operator!=(const Issue& other) const;

private:
  Severity m_severity;
  QString m_text;
  Callback m_callback;
};

enum class Issue::Severity
{
  Info,
  Warning,
  Error
};

#endif //EGNIM_ISSUE_H
