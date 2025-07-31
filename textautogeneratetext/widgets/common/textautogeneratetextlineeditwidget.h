/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QToolButton;
namespace TextAutoGenerateText
{
class TextAutoGenerateTextLineEdit;
class TextAutoGenerateManager;
/**
 * @brief The TextAutoGenerateTextLineEditWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateTextLineEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextLineEditWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateTextLineEditWidget() override;

    [[nodiscard]] QString text() const;

    [[nodiscard]] QByteArray uuid() const;
    void setUuid(const QByteArray &newUuid);

    void setText(const QString &str);

    [[nodiscard]] QByteArray chatId() const;
    void setChatId(const QByteArray &newChatId);

Q_SIGNALS:
    void editingFinished(const QString &str, const QByteArray &uuid);
    void keyPressed(QKeyEvent *ev);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void clearLineEdit();
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateEnableState();
    TextAutoGenerateTextLineEdit *const mTextAutoGenerateTextLineEdit;
    QToolButton *const mSendMessage;
    QToolButton *const mAttachFile;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    QByteArray mUuid;
};
}
