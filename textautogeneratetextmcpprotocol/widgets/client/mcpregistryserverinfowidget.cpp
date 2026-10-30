/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpregistryserverinfowidget.h"
#include <KLocalizedString>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpRegistryServerInfo>

using namespace TextAutoGenerateTextMcpProtocolWidgets;
using namespace Qt::Literals::StringLiterals;
McpRegistryServerInfoWidget::McpRegistryServerInfoWidget(QWidget *parent)
    : QWidget{parent}
    , mTextBrowser(new QTextBrowser(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mTextBrowser->setObjectName(u"mTextBrowser"_s);
    mTextBrowser->setOpenExternalLinks(true);
    mTextBrowser->setPlaceholderText(i18nc("@info:placeholder", "Select a server to see its information."));
    mainLayout->addWidget(mTextBrowser);
}

McpRegistryServerInfoWidget::~McpRegistryServerInfoWidget() = default;

void McpRegistryServerInfoWidget::setServerInfo(const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo &info)
{
    mTextBrowser->setHtml(generateHtml(info));
}

namespace
{
QString link(const QString &url)
{
    const QString escaped = url.toHtmlEscaped();
    return u"<a href=\"%1\">%1</a>"_s.arg(escaped);
}
}

QString McpRegistryServerInfoWidget::generateHtml(const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo &info)
{
    if (!info.isValid()) {
        return {};
    }
    QString html = u"<h2>%1</h2>"_s.arg(info.displayName().toHtmlEscaped());
    if (!info.title().isEmpty()) {
        html += u"<p><i>%1</i></p>"_s.arg(info.name().toHtmlEscaped());
    }
    if (!info.description().isEmpty()) {
        html += u"<p>%1</p>"_s.arg(info.description().toHtmlEscaped());
    }
    html += u"<p>";
    if (!info.version().isEmpty()) {
        html += i18n("<b>Version:</b> %1", info.version().toHtmlEscaped()) + u"<br/>"_s;
    }
    if (!info.repositoryUrl().isEmpty()) {
        html += i18n("<b>Repository:</b> %1", link(info.repositoryUrl())) + u"<br/>"_s;
    }
    if (!info.websiteUrl().isEmpty()) {
        html += i18n("<b>Website:</b> %1", link(info.websiteUrl())) + u"<br/>"_s;
    }
    html += u"</p>";

    const auto remotes = info.remotes();
    if (!remotes.isEmpty()) {
        html += u"<h3>%1</h3><ul>"_s.arg(i18n("Remotes"));
        for (const auto &remote : remotes) {
            html += u"<li>%1 (%2)</li>"_s.arg(link(remote.url), remote.type.toHtmlEscaped());
        }
        html += u"</ul>";
    }

    const auto packages = info.packages();
    if (!packages.isEmpty()) {
        html += u"<h3>%1</h3>"_s.arg(i18n("Packages"));
        for (const auto &package : packages) {
            html += u"<p><b>%1</b>"_s.arg(package.identifier.toHtmlEscaped());
            if (!package.version.isEmpty()) {
                html += u" %1"_s.arg(package.version.toHtmlEscaped());
            }
            html += u"<br/>"_s + i18n("Registry: %1", package.registryType.toHtmlEscaped());
            if (!package.transportType.isEmpty()) {
                html += u"<br/>"_s + i18n("Transport: %1", package.transportType.toHtmlEscaped());
            }
            if (!package.runtimeHint.isEmpty()) {
                html += u"<br/>"_s + i18n("Runtime: %1", package.runtimeHint.toHtmlEscaped());
            }
            html += u"</p>";
            if (!package.environmentVariables.isEmpty()) {
                html += u"<p>%1</p><ul>"_s.arg(i18n("Environment variables:"));
                for (const auto &env : package.environmentVariables) {
                    html += u"<li><tt>%1</tt>"_s.arg(env.name.toHtmlEscaped());
                    if (env.isRequired) {
                        html += u" <b>%1</b>"_s.arg(i18n("(required)"));
                    }
                    if (env.isSecret) {
                        html += u" %1"_s.arg(i18n("(secret)"));
                    }
                    if (!env.description.isEmpty()) {
                        html += u"<br/>%1"_s.arg(env.description.toHtmlEscaped());
                    }
                    html += u"</li>";
                }
                html += u"</ul>";
            }
        }
    }
    return html;
}

#include "moc_mcpregistryserverinfowidget.cpp"
