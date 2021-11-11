/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/export_template_list_model.h"
/* -------------------------------------------------------------------------- */

ExportTemplateListModel::ExportTemplateListModel(QObject* parent) :
  QAbstractListModel(parent)
{

}

ExportTemplateListModel::~ExportTemplateListModel() = default;

QVariant ExportTemplateListModel::data(const QModelIndex &index, int role) const
{
  if(index.row() < 0 || index.row() >= m_export_templates.size())
    return QVariant();

  switch(role) // NOLINT(hicpp-multiway-paths-covered)
  {
    case Qt::DisplayRole:
      // TODO : implementation //
      return QVariant();
  }

  return QVariant();
}

int ExportTemplateListModel::rowCount(const QModelIndex &parent) const
{
  return static_cast<int>(m_export_templates.size());
}

ExportTemplate* ExportTemplateListModel::getExportTemplate(const QModelIndex& index) const
{
  if(index.row() < 0 || index.row() >= m_export_templates.size())
    return nullptr;

  return m_export_templates.at(index.row()).get();
}

QModelIndex ExportTemplateListModel::getIndex(ExportTemplate* export_template) const
{
  auto found = std::find_if(m_export_templates.begin(), m_export_templates.end(),
                            [export_template](auto& preset){ return export_template == preset.get(); });

  if(found != m_export_templates.end())
    return createIndex(static_cast<int>(std::distance(m_export_templates.begin(), found)), 0);

  return QModelIndex();
}

QModelIndex ExportTemplateListModel::appendExportTemplate(std::unique_ptr<ExportTemplate> export_template)
{
  return insertExportTemplate(QModelIndex(), std::move(export_template));
}

QModelIndex ExportTemplateListModel::prependExportTemplate(std::unique_ptr<ExportTemplate> export_template)
{
  return insertExportTemplate(index(0), std::move(export_template));
}

QModelIndex ExportTemplateListModel::insertExportTemplate(const QModelIndex& index, std::unique_ptr<ExportTemplate> export_template)
{
  auto row = index.isValid() ? index.row() : rowCount(QModelIndex());
  auto insert_iter = m_export_templates.begin() + row;

  beginInsertRows(QModelIndex(), row, row);
  m_export_templates.insert(insert_iter, std::move(export_template));
  endInsertRows();

  return QAbstractListModel::index(row);
}

void ExportTemplateListModel::removeExportTemplate(const QModelIndex& index)
{
  Q_ASSERT(index.isValid());
  auto insert_iter = m_export_templates.begin() + index.row();

  beginRemoveRows(QModelIndex(), index.row(), index.row());
  m_export_templates.erase(insert_iter);
  endRemoveRows();
}
