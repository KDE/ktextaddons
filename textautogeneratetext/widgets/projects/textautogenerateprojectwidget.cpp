/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateprojectwidget.h"
#include <KIconButton>
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;

TextAutoGenerateProjectWidget::TextAutoGenerateProjectWidget(QWidget *parent)
    : QWidget{parent}
    , mName(new QLineEdit(this))
    , mIconName(new KIconButton(this))
{
    auto mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mName->setObjectName(u"mName"_s);
    mName->setClearButtonEnabled(true);
    mName->setPlaceholderText(i18nc("@info:placeholder", "Project name…"));
    KLineEditEventHandler::catchReturnKey(mName);
    connect(mName, &QLineEdit::textChanged, this, &TextAutoGenerateProjectWidget::slotNameChanged);

    mIconName->setObjectName(u"mIconName"_s);

    mainLayout->addRow(i18n("Name:"), mName);
    mainLayout->addRow(i18n("Icon:"), mIconName);
}

TextAutoGenerateProjectWidget::~TextAutoGenerateProjectWidget() = default;

void TextAutoGenerateProjectWidget::slotNameChanged(const QString &name)
{
    Q_EMIT enableOkButton(!name.trimmed().isEmpty());
}

void TextAutoGenerateProjectWidget::setProject(const TextAutoGenerateText::TextAutoGenerateProject &project)
{
    mProject = project;
    mName->setText(project.name());
    mIconName->setIcon(project.iconName());
}

TextAutoGenerateText::TextAutoGenerateProject TextAutoGenerateProjectWidget::project() const
{
    // copy => we keep identifier
    TextAutoGenerateText::TextAutoGenerateProject project = mProject;
    project.setName(mName->text().trimmed());
    project.setIconName(mIconName->icon());
    return project;
}

#include "moc_textautogenerateprojectwidget.cpp"
