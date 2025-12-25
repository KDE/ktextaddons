/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <TextAddonsWidgets/OpenFileJob>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateTextOpenFileJob : public TextAddonsWidgets::OpenFileJob
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextOpenFileJob(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent = nullptr);
    ~TextAutoGenerateTextOpenFileJob() override;

    void downloadFile(const QUrl &fileUrl) override;
    void runApplication(const KService::Ptr &offer) override;
    void openUrl() override;

    [[nodiscard]] QByteArray attachmentId() const;
    void setAttachmentId(const QByteArray &newAttachmentId);

private:
    QByteArray mAttachmentId;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};

}
