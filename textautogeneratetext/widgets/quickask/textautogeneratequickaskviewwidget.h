/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextLineEditWidget;
class TextAutoGenerateResultWidget;
class TextAutoGenerateManager;
class TextAutoGenerateQuickAskHeaderWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateQuickAskViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateQuickAskViewWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateQuickAskViewWidget() override;
    void slotConfigureInstances();
    void editMessage(const QByteArray &uuid, const QString &messageStr);

Q_SIGNALS:
    void editingFinished(const QString &str, const QByteArray &uuid, const QList<QByteArray> &lstTools);
    void configureChanged();
    void cancelRequested(const QByteArray &uuid);
    void refreshAnswerRequested(const QByteArray &charId, const QModelIndex &indexAnswer, const QList<QByteArray> &tools);
    void editMessageRequested(const QModelIndex &index, const QList<QByteArray> &tools);

private:
    TextAutoGenerateTextLineEditWidget *const mTextAutoGenerateTextLineWidget;
    TextAutoGenerateResultWidget *const mTextAutoGenerateResultWidget;
    TextAutoGenerateQuickAskHeaderWidget *const mTextAutoGenerateQuickAskHeaderWidget;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
