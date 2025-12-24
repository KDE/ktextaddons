/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextopenfilejob.h"
#include "textautogeneratetextwidget_debug.h"
#include <QDir>
#include <QTemporaryDir>
#include <TextAutoGenerateText/TextAutoGenerateManager>
#include <kio/applicationlauncherjob.h>
#include <kio/jobuidelegatefactory.h>
#include <kjobuidelegate.h>
#include <memory>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextOpenFileJob::TextAutoGenerateTextOpenFileJob(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent)
    : TextAddonsWidgets::OpenFileJob{parent}
    , mManager(manager)
{
}

TextAutoGenerateTextOpenFileJob::~TextAutoGenerateTextOpenFileJob() = default;

void TextAutoGenerateTextOpenFileJob::downloadFile(const QUrl &fileUrl)
{
    if (mManager) {
        const QString fileName = mManager->generateAttachmentTemporaryFile();
    }
    // TODO generate file from fileUrl
    // TODO
    deleteLater();
}

void TextAutoGenerateTextOpenFileJob::runApplication(const KService::Ptr &offer)
{
    if (mManager) {
        const QString fileName = mManager->generateAttachmentTemporaryFile();
        auto job = new KIO::ApplicationLauncherJob(offer); // asks the user if offer is nullptr
        job->setUrls({QUrl::fromLocalFile(fileName)});
        job->setRunFlags(KIO::ApplicationLauncherJob::DeleteTemporaryFiles);
        job->setUiDelegate(KIO::createDefaultJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, mParentWidget));
        job->start();
    }
    deleteLater();
}

void TextAutoGenerateTextOpenFileJob::openUrl()
{
#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
    std::unique_ptr<QTemporaryDir> tempDir(new QTemporaryDir(QDir::tempPath() + "/textautogeneratetext_attachment_XXXXXX"_L1));
    if (!tempDir->isValid()) {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "Impossible to create attachment temporary file";
        return;
    }
    tempDir->setAutoRemove(false); // can't delete them, same problem as in messagelib ViewerPrivate::attachmentOpenWith
    const QString tempFile = tempDir->filePath(QUrl(mLink).fileName());
    const QUrl fileUrl = QUrl::fromLocalFile(tempFile);

#if 0
    const QUrl downloadUrl = mRocketChatAccount->urlForLink(mLink);
    auto *job = mRocketChatAccount->restApi()->downloadFile(downloadUrl, fileUrl, "text/plain"_ba);
    connect(job, &RocketChatRestApi::DownloadFileJob::downloadFileDone, this, [this](const QUrl &, const QUrl &localFileUrl) {
        if (!QDesktopServices::openUrl(localFileUrl)) {
            KMessageBox::error(mParentWidget, i18n("Impossible to open %1", localFileUrl.toDisplayString()), i18nc("@title:window", "Error Opening File"));
        }
        deleteLater();
    });
#endif
#endif
}

#include "moc_textautogeneratetextopenfilejob.cpp"
