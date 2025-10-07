/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamanetworkurlbutton.h"
#include <KLocalizedString>
#include <QDesktopServices>
#include <QUrl>

using namespace Qt::Literals::StringLiterals;
OllamaNetworkUrlButton::OllamaNetworkUrlButton(QWidget *parent)
    : QToolButton(parent)
{
    setIcon(QIcon::fromTheme(u"applications-network-symbolic"_s));
    setToolTip(i18nc("@info:tooltip", "Open Model Information Url"));
    setAutoRaise(true);
    connect(this, &QToolButton::clicked, this, [this]() {
        if (!mModelUrl.isEmpty()) {
            QDesktopServices::openUrl(QUrl(mModelUrl));
        }
    });
}

OllamaNetworkUrlButton::~OllamaNetworkUrlButton() = default;

QString OllamaNetworkUrlButton::modelUrl() const
{
    return mModelUrl;
}

void OllamaNetworkUrlButton::setModelUrl(const QString &newModelUrl)
{
    mModelUrl = newModelUrl;
}

#include "moc_ollamanetworkurlbutton.cpp"
