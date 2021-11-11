/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/issue.h"
/* -------------------------------------------------------------------------- */

Issue::Issue(Severity severity, QString text, Callback callback) :
  m_severity(severity),
  m_text(std::move(text)),
  m_callback(std::move(callback))
{

}

void Issue::setCallback(Callback callback)
{
  m_callback = std::move(callback);
}

Issue::Severity Issue::getSeverity() const
{
  return m_severity;
}

QString Issue::getText() const
{
  return m_text;
}

Issue::Callback Issue::getCallback() const
{
  return m_callback;
}

bool Issue::operator==(const Issue& other) const
{
  return m_severity == other.m_severity &&
         m_text == other.m_text;
}

bool Issue::operator!=(const Issue& other) const
{
  return m_severity != other.m_severity ||
         m_text != other.m_text;
}