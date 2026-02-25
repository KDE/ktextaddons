/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonnetworkurlbutton.h"
#include <KLocalizedString>
#include <QDesktopServices>
#include <QUrl>

using namespace Qt::Literals::StringLiterals;
OllamaCommonNetworkUrlButton::OllamaCommonNetworkUrlButton(QWidget *parent)
    : QToolButton(parent)
{
    setIcon(QIcon::fromTheme(u"applications-network-symbolic"_s));
    setAutoRaise(true);
    connect(this, &QToolButton::clicked, this, [this]() {
        if (!mUrl.isEmpty()) {
            QDesktopServices::openUrl(QUrl(mUrl));
        }
    });
}

OllamaCommonNetworkUrlButton::~OllamaCommonNetworkUrlButton() = default;

QString OllamaCommonNetworkUrlButton::url() const
{
    return mUrl;
}

void OllamaCommonNetworkUrlButton::setUrl(const QString &newModelUrl)
{
    mUrl = newModelUrl;
    setToolTip(i18nc("@info:tooltip", "Open Url \"%1\"", mUrl));
}

#include "moc_ollamacommonnetworkurlbutton.cpp"
