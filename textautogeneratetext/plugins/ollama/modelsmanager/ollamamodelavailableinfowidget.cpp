/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailableinfowidget.h"
#include "autogeneratetext_ollama_debug.h"

#include "ollamamanager.h"
#include "ollamamodelavailableinfosmodel.h"
#include "ollamamodeldownloadwidget.h"
#include "widgets/common/textautogenerateflowlayout.h"
#include <KLocalizedString>
#include <QDesktopServices>
#include <QGroupBox>
#include <QLabel>
#include <QToolButton>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
OllamaModelAvailableInfoWidget::OllamaModelAvailableInfoWidget(OllamaManager *manager, QWidget *parent)
    : QWidget{parent}
    , mMainLayout(new QVBoxLayout(this))
    , mModelName(new QLabel(this))
    , mOllamaManager(manager)
    , mNetworkUrlButton(new QToolButton(this))
{
    mMainLayout->setObjectName(u"mainlayout"_s);
    mMainLayout->setContentsMargins({});
    QFont f = mModelName->font();
    f.setBold(true);
    mModelName->setFont(f);
    auto hbox = new QHBoxLayout;
    mMainLayout->addLayout(hbox);
    hbox->setContentsMargins({});
    hbox->addWidget(mModelName, 0, Qt::AlignHCenter);

    mNetworkUrlButton->setObjectName(u"mNetworkUrlButton");
    mNetworkUrlButton->setIcon(QIcon::fromTheme(u"applications-network-symbolic"_s));
    mNetworkUrlButton->setToolTip(i18nc("@info:tooltip", "Open Model Information Url"));
    mNetworkUrlButton->setAutoRaise(true);
    connect(mNetworkUrlButton, &QToolButton::clicked, this, [this]() {
        if (!mModelUrl.isEmpty()) {
            QDesktopServices::openUrl(QUrl(mModelUrl));
        }
    });
    hbox->addWidget(mNetworkUrlButton);
}

OllamaModelAvailableInfoWidget::~OllamaModelAvailableInfoWidget() = default;

void OllamaModelAvailableInfoWidget::generateWidget(const QModelIndex &index)
{
    if (mInfoWidget) {
        mMainLayout->removeWidget(mInfoWidget);
        mInfoWidget->deleteLater();
    }
    const QString modelName = index.data(OllamaModelAvailableInfosModel::ModelName).toString();
    mModelName->setText(modelName);

    const QString url = index.data(OllamaModelAvailableInfosModel::Url).toString();
    mModelUrl = url;

    mInfoWidget = new QWidget(this);
    auto infoLayout = new QVBoxLayout(mInfoWidget);

    auto languagesGroupBox = new QGroupBox(i18n("Languages Supported"), mInfoWidget);
    auto languagesGroupBoxLayout = new TextAutoGenerateText::TextAutoGenerateFlowLayout(languagesGroupBox);
    const QStringList languages = index.data(OllamaModelAvailableInfosModel::Languages).toStringList();
    for (const auto &l : languages) {
        const QLocale locale(l);
        if (locale.language() == QLocale::Language::C) {
            qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << " impossible to convert to language " << l;
            continue;
        }
        languagesGroupBoxLayout->addWidget(new QLabel(locale.nativeLanguageName(), mInfoWidget));
    }
    infoLayout->addWidget(languagesGroupBox);

    auto downloadModelGroupBox = new QGroupBox(i18n("Models"), mInfoWidget);

    infoLayout->addWidget(downloadModelGroupBox);
    auto downloadGroupBoxLayout = new QVBoxLayout(downloadModelGroupBox);
    const QList<OllamaModelAvailableInfo::ModelTag> tags = index.data(OllamaModelAvailableInfosModel::Tags).value<QList<OllamaModelAvailableInfo::ModelTag>>();
    for (const auto &t : tags) {
        const bool alreadyInstalled = mOllamaManager->isAlreadyInstalled(u"%1:%2"_s.arg(modelName, t.tag));
        auto downLoadWidget = new OllamaModelDownloadWidget(t.tag, t.size, alreadyInstalled, mInfoWidget);
        connect(downLoadWidget, &OllamaModelDownloadWidget::downloadModel, this, [this, modelName](const QString &tagName) {
            Q_EMIT downloadModel(u"%1:%2"_s.arg(modelName, tagName));
        });
        downloadGroupBoxLayout->addWidget(downLoadWidget);
    }
    mMainLayout->addWidget(mInfoWidget, 1, Qt::AlignTop);
}

#include "moc_ollamamodelavailableinfowidget.cpp"
