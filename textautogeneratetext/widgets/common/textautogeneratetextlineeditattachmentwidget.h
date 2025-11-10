/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "core/textautogenerateattachmentutils.h"
#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextLineEditAttachmentClickableWidget;
class TextAutoGenerateFlowLayout;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextLineEditAttachmentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextLineEditAttachmentWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateTextLineEditAttachmentWidget() override;

    void addAttachement(const QString &fileName);

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo> attachmentElementInfoList() const;
    void clear();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemoveAttachment(const QString &fileName);
    QMap<QString, TextAutoGenerateTextLineEditAttachmentClickableWidget *> mMap;
    TextAutoGenerateFlowLayout *const mMainLayout;
};
}
