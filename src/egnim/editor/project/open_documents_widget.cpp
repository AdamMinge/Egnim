/* ------------------------------------ Qt ---------------------------------- */
#include <QCoreApplication>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/editor/project/open_documents_widget.h>
#include <egnim/editor/document/no_document_widget.h>
/* -------------------------------------------------------------------------- */

/* ------------------------------- ProjectContext --------------------------- */

OpenDocumentsTabBar::OpenDocumentsTabBar(QWidget* parent) :
  QWidget(parent),
  m_tab_bar(new QTabBar(this))
{
  m_tab_bar->setExpanding(false);
  m_tab_bar->setDocumentMode(true);
  m_tab_bar->setTabsClosable(true);
  m_tab_bar->setMovable(true);
  m_tab_bar->setContextMenuPolicy(Qt::CustomContextMenu);

  auto vertical_layout = new QVBoxLayout(this);
  vertical_layout->addWidget(m_tab_bar);
  vertical_layout->setContentsMargins(0, 0, 0, 0);
  vertical_layout->setSpacing(0);

  connect(m_tab_bar, &QTabBar::currentChanged, this, &OpenDocumentsTabBar::currentIndexChanged);
  connect(m_tab_bar, &QTabBar::tabMoved, this, &OpenDocumentsTabBar::documentTabMoved);
  connect(m_tab_bar, &QTabBar::tabCloseRequested, m_tab_bar, &QTabBar::removeTab);
}

OpenDocumentsTabBar::~OpenDocumentsTabBar() = default;

void OpenDocumentsTabBar::openDocument(Document* document)
{
  Q_ASSERT(document);
  m_open_documents.emplace_back(document);

  auto document_index = m_tab_bar->addTab(document->getDisplayName());
  m_tab_bar->setTabToolTip(document_index, document->getFileName());

  connect(document, &Document::fileNameChanged, this,
          [this, document] { updateDocumentTab(document); });

  switchToDocument(document_index);
};

void OpenDocumentsTabBar::closeDocument(int index)
{
  auto document_to_remove = getDocument(index);
  Q_ASSERT(document_to_remove);

  auto removed_document_iter = std::remove_if(
    m_open_documents.begin(), m_open_documents.end(), [&document_to_remove](auto&& document){
      return document == document_to_remove;
    });

  m_tab_bar->removeTab(index);

  m_open_documents.erase(removed_document_iter, m_open_documents.end());
};

void OpenDocumentsTabBar::closeAllDocuments()
{
  while(!m_open_documents.empty())
    closeDocument(m_tab_bar->currentIndex());
};

Document* OpenDocumentsTabBar::getDocument(int index) const
{
  if(index < m_open_documents.size() && index >= 0)
    return m_open_documents.at(index);

  return nullptr;
};

Document* OpenDocumentsTabBar::getCurrentDocument() const
{
  auto index = m_tab_bar->currentIndex();
  return getDocument(index);
};

int OpenDocumentsTabBar::findDocument(Document *document) const
{
  auto found = std::find_if(m_open_documents.begin(), m_open_documents.end(), [document](auto& current_document){
    return current_document == document;
  });

  if(found != m_open_documents.end())
    return static_cast<int>(std::distance(m_open_documents.begin(), found));

  return -1;
};

void OpenDocumentsTabBar::switchToDocument(int index)
{
  m_tab_bar->setCurrentIndex(index);
};

void OpenDocumentsTabBar::switchToDocument(Document* document)
{
  auto found_iter = std::find_if(m_open_documents.begin(), m_open_documents.end(),
                                 [&document](auto&& current_document){
    return current_document == document;
  });

  Q_ASSERT(found_iter != m_open_documents.end());
  auto index = std::distance(m_open_documents.begin(), found_iter);
  switchToDocument(static_cast<int>(index));
};

void OpenDocumentsTabBar::currentIndexChanged()
{
  auto document = getCurrentDocument();
  currentDocumentChanged(document);
}

void OpenDocumentsTabBar::documentTabMoved(int from, int to)
{
  if(from > to)
    std::rotate(m_open_documents.rend() - from - 1,
                m_open_documents.rend() - from,
                m_open_documents.rend() - to);
  else
    std::rotate(m_open_documents.begin() + from,
                m_open_documents.begin() + from + 1,
                m_open_documents.begin() + to + 1);
}

void OpenDocumentsTabBar::updateDocumentTab(Document* document)
{
  const int index = findDocument(document);
  if (index == -1)
    return;

  m_tab_bar->setTabText(index, document->getDisplayName());
  m_tab_bar->setTabToolTip(index, document->getFileName());
}

/* ---------------------------- OpenDocumentsWidget ------------------------- */

OpenDocumentsWidget::OpenDocumentsWidget(QWidget* parent) :
  QWidget(parent),
  m_current_project(nullptr),
  m_editor_stack(new QStackedLayout()),
  m_project_documents_stack(new QStackedWidget()),
  m_no_document_widget(new NoDocumentWidget())
{
  m_project_documents_stack->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

  auto vertical_layout = new QVBoxLayout(this);
  vertical_layout->addWidget(m_project_documents_stack);
  vertical_layout->addLayout(m_editor_stack);
  vertical_layout->setContentsMargins(0, 0, 0, 0);
  vertical_layout->setSpacing(0);

  m_editor_stack->addWidget(m_no_document_widget.data());
}

OpenDocumentsWidget::~OpenDocumentsWidget()
{
  closeAllDocuments();
  removeAllEditors();
}

void OpenDocumentsWidget::setCurrentProject(Project* project)
{
  if(m_current_project == project)
    return;

  if(m_open_documents_for_project.contains(m_current_project))
  {
    auto open_documents = m_open_documents_for_project[m_current_project];

    disconnect(open_documents, &OpenDocumentsTabBar::currentDocumentChanged, this, &OpenDocumentsWidget::projectCurrentDocumentChanged);
  }

  m_current_project = project;

  if(m_open_documents_for_project.contains(m_current_project))
  {
    auto open_documents = m_open_documents_for_project[m_current_project];

    m_project_documents_stack->setCurrentWidget(open_documents);
    currentDocumentChanged(open_documents->getCurrentDocument());

    connect(open_documents, &OpenDocumentsTabBar::currentDocumentChanged, this, &OpenDocumentsWidget::projectCurrentDocumentChanged);
  }
}

void OpenDocumentsWidget::addProject(Project* project)
{
  Q_ASSERT(!m_open_documents_for_project.contains(project));
  m_open_documents_for_project.insert(std::make_pair(project, new OpenDocumentsTabBar()));

  auto open_documents = m_open_documents_for_project[project];
  m_project_documents_stack->addWidget(open_documents);
}

void OpenDocumentsWidget::removeProject(Project* project)
{
  Q_ASSERT(m_open_documents_for_project.contains(project));
  auto open_documents = m_open_documents_for_project[project];
  m_project_documents_stack->removeWidget(open_documents);

  m_open_documents_for_project.erase(project);
}

void OpenDocumentsWidget::addEditor(Document::Type document_type, std::unique_ptr<DocumentEditor> editor)
{
  m_editor_stack->addWidget(editor->getEditorWidget());
  m_editor_for_document_type.insert(std::make_pair(document_type, std::move(editor)));
}

void OpenDocumentsWidget::removeEditor(Document::Type document_type)
{
  Q_ASSERT(m_editor_for_document_type.contains(document_type));
  m_editor_for_document_type.erase(document_type);
}

void OpenDocumentsWidget::removeAllEditors()
{
  while(!m_editor_for_document_type.empty())
    removeEditor(m_editor_for_document_type.begin()->first);
}

DocumentEditor* OpenDocumentsWidget::getEditor(Document::Type document_type) const
{
  if(m_editor_for_document_type.contains(document_type))
    return m_editor_for_document_type.at(document_type).get();

  return nullptr;
}

DocumentEditor* OpenDocumentsWidget::getCurrentEditor() const
{
  auto current_document = getCurrentDocument();
  return current_document ? getEditor(current_document->getType()) : nullptr;
}

void OpenDocumentsWidget::openDocument(Document* document)
{
  if(m_current_project)
    m_open_documents_for_project[m_current_project]->openDocument(document);
}

void OpenDocumentsWidget::closeDocument(int index)
{
  if(m_current_project)
    m_open_documents_for_project[m_current_project]->closeDocument(index);
}

void OpenDocumentsWidget::closeAllDocuments()
{
  if(m_current_project)
    m_open_documents_for_project[m_current_project]->closeAllDocuments();
}

Document* OpenDocumentsWidget::getDocument(int index) const
{
  if(m_current_project)
    return m_open_documents_for_project.at(m_current_project)->getDocument(index);

  return nullptr;
}

Document* OpenDocumentsWidget::getCurrentDocument() const
{
  if(m_current_project)
    return m_open_documents_for_project.at(m_current_project)->getCurrentDocument();

  return nullptr;
}

int OpenDocumentsWidget::findDocument(Document *document) const
{
  if(m_current_project)
    return m_open_documents_for_project.at(m_current_project)->findDocument(document);

  return -1;
}

void OpenDocumentsWidget::switchToDocument(int index)
{
  if(m_current_project)
    return m_open_documents_for_project[m_current_project]->switchToDocument(index);
}

void OpenDocumentsWidget::switchToDocument(Document* document)
{
  if(m_current_project)
    return m_open_documents_for_project[m_current_project]->switchToDocument(document);
}

void OpenDocumentsWidget::saveState()
{
  for(auto& [document_type, editor] : m_editor_for_document_type)
    editor->saveState();
}

void OpenDocumentsWidget::restoreState()
{
  for(auto& [document_type, editor] : m_editor_for_document_type)
    editor->restoreState();
}

void OpenDocumentsWidget::projectCurrentDocumentChanged(Document* document)
{
  if(auto prev_editor = getCurrentEditor(); prev_editor)
  {
    prev_editor->setCurrentDocument(nullptr);
  }

  auto editor = getCurrentEditor();

  if(editor)
  {
    editor->setCurrentDocument(document);
    m_editor_stack->setCurrentWidget(editor->getEditorWidget());
  }
  else
  {
    m_editor_stack->setCurrentWidget(m_no_document_widget.data());
  }

  Q_EMIT currentDocumentChanged(document);
}
