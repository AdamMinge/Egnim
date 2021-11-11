/* ----------------------------------- Local -------------------------------- */
#include "egnim/tools/editor/project/export_preset_list_model.h"
/* -------------------------------------------------------------------------- */

ExportPresetListModel::ExportPresetListModel(QObject* parent) :
  QAbstractListModel(parent)
{
  m_export_preset_type_to_icon.insert(
    std::make_pair(ExportPreset::Type::Windows, QIcon(":/images/64x64/windows.png")));
  m_export_preset_type_to_icon.insert(
    std::make_pair(ExportPreset::Type::Linux, QIcon(":/images/64x64/linux.png")));
  m_export_preset_type_to_icon.insert(
    std::make_pair(ExportPreset::Type::MacOS, QIcon(":/images/64x64/macos.png")));
  m_export_preset_type_to_icon.insert(
    std::make_pair(ExportPreset::Type::MacOS, QIcon(":/images/64x64/unknown_os.png")));
}

ExportPresetListModel::~ExportPresetListModel() = default;

QVariant ExportPresetListModel::data(const QModelIndex &index, int role) const
{
  if(index.row() < 0 || index.row() >= m_export_presets.size())
    return QVariant();

  switch(role) // NOLINT(hicpp-multiway-paths-covered)
  {
    case Qt::DisplayRole:
      return getExportPreset(index)->getName();

    case Qt::DecorationRole:
      return getProjectIcon(index);
  }

  return QVariant();
}

int ExportPresetListModel::rowCount(const QModelIndex &parent) const
{
  return static_cast<int>(m_export_presets.size());
}

ExportPreset* ExportPresetListModel::getExportPreset(const QModelIndex& index) const
{
  if(index.row() < 0 || index.row() >= m_export_presets.size())
    return nullptr;

  return m_export_presets.at(index.row()).get();
}

QModelIndex ExportPresetListModel::getIndex(ExportPreset* export_preset) const
{
  auto found = std::find_if(m_export_presets.begin(), m_export_presets.end(),
                            [export_preset](auto& preset){ return export_preset == preset.get(); });

  if(found != m_export_presets.end())
    return createIndex(static_cast<int>(std::distance(m_export_presets.begin(), found)), 0);

  return QModelIndex();
}

QModelIndex ExportPresetListModel::appendExportPreset(std::unique_ptr<ExportPreset> export_preset)
{
  return insertExportPreset(QModelIndex(), std::move(export_preset));
}

QModelIndex ExportPresetListModel::prependExportPreset(std::unique_ptr<ExportPreset> export_preset)
{
  return insertExportPreset(index(0), std::move(export_preset));
}

QModelIndex ExportPresetListModel::insertExportPreset(const QModelIndex& index, std::unique_ptr<ExportPreset> export_preset)
{
  auto row = index.isValid() ? index.row() : rowCount(QModelIndex());
  auto insert_iter = m_export_presets.begin() + row;

  connect(export_preset.get(), &ExportPreset::nameChanged, this, &ExportPresetListModel::nameChanged);

  beginInsertRows(QModelIndex(), row, row);
  m_export_presets.insert(insert_iter, std::move(export_preset));
  endInsertRows();

  return QAbstractListModel::index(row);
}

void ExportPresetListModel::removeExportPreset(const QModelIndex& index)
{
  Q_ASSERT(index.isValid());
  auto insert_iter = m_export_presets.begin() + index.row();

  beginRemoveRows(QModelIndex(), index.row(), index.row());
  m_export_presets.erase(insert_iter);
  endRemoveRows();
}

void ExportPresetListModel::nameChanged()
{
  auto preset = qobject_cast<ExportPreset*>(sender());
  dataChanged(getIndex(preset), getIndex(preset), {Qt::DisplayRole});
}

const QIcon& ExportPresetListModel::getProjectIcon(const QModelIndex& index) const
{
  auto export_preset = getExportPreset(index);
  if(!export_preset || !m_export_preset_type_to_icon.contains(export_preset->getType()))
    return m_export_preset_type_to_icon.at(ExportPreset::Type::Unknown);

  return m_export_preset_type_to_icon.at(export_preset->getType());
}


