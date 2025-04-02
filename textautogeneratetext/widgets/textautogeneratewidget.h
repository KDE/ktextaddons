/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QSplitter;
namespace TextAutogenerateText
{
class TextAutogenerateResultWidget;
class TextAutogenerateTextLineEditWidget;
class TextAutogenerateTextClient;
class TextAutogenerateTextPlugin;
class TextAutoGenerateMessage;
class TextAutogenerateHistoryWidget;
class TextAutogenerateHeaderWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutogenerateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateWidget(QWidget *parent = nullptr);
    ~TextAutogenerateWidget() override;

    [[nodiscard]] QString textLineEdit() const;

    void loadEngine();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditingFinished(const QString &str);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAutogenerateFinished(const TextAutoGenerateMessage &msg);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAutogenerateFailed(const QString &errorMessage);
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotConfigureChanged();

    TextAutogenerateResultWidget *const mTextAutogenerateResultWidget;
    TextAutogenerateTextLineEditWidget *const mTextAutogenerateTextLineEditWidget;

    TextAutogenerateTextClient *mTextAutogenerateClient = nullptr;
    TextAutogenerateTextPlugin *mTextAutogeneratePlugin = nullptr;
    QSplitter *const mSplitter;
    TextAutogenerateHistoryWidget *const mHistoryWidget;
    TextAutogenerateHeaderWidget *const mHeaderWidget;
};
}
