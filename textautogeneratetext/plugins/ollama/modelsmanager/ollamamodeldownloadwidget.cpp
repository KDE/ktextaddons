/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodeldownloadwidget.h"

#include <KLocalizedString>

#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>

using namespace Qt::Literals::StringLiterals;
OllamaModelDownloadWidget::OllamaModelDownloadWidget(const QString &tagName, const QString &modelSize, bool alreadyInstalled, QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    auto infoLayout = new QVBoxLayout;
    mainLayout->setObjectName(u"infoLayout"_s);
    mainLayout->setContentsMargins({});

    auto labelTag = new QLabel(tagName, this);
    labelTag->setObjectName(u"labelTag"_s);
    infoLayout->addWidget(labelTag);
    QFont f = labelTag->font();
    f.setBold(true);
    labelTag->setFont(f);

    auto labelSize = new QLabel(modelSize, this);
    labelSize->setObjectName(u"labelSize"_s);
    infoLayout->addWidget(labelSize);

    mainLayout->addLayout(infoLayout);

    // TODO if already downloaded => disable it.
    auto toolButton = new QToolButton(this);
    toolButton->setEnabled(!alreadyInstalled);
    toolButton->setIcon(alreadyInstalled ? QIcon::fromTheme(u"dialog-ok"_s) : QIcon::fromTheme(u"download"_s));
    toolButton->setAutoRaise(true);
    toolButton->setObjectName(u"toolButton"_s);
    if (!alreadyInstalled) {
        toolButton->setToolTip(i18nc("@info:tooltip", "Download"));
    }
    mainLayout->addWidget(toolButton, 0, Qt::AlignTop);
    if (!alreadyInstalled) {
        connect(toolButton, &QToolButton::clicked, this, [this, tagName]() {
            Q_EMIT downloadModel(tagName);
        });
    }
}

OllamaModelDownloadWidget::~OllamaModelDownloadWidget() = default;

#include "moc_ollamamodeldownloadwidget.cpp"
