/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAskJob : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAskJob(QObject *parent = nullptr);
    ~TextAutoGenerateAskJob() override;
    [[nodiscard]] bool canStart() const;

    void start();

    [[nodiscard]] TextAutoGenerateManager *manager() const;
    void setManager(TextAutoGenerateManager *newManager);

    [[nodiscard]] QString text() const;
    void setText(const QString &newText);

Q_SIGNALS:
    void generateTextInProgress(const QString &str);
    void generateTextDone();
    void errorOccured(const QString &str);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAutogenerateFailed(const QString &msg);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotInitializeDone();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAskToLlmDone();
    QString mText;
    TextAutoGenerateManager *mManager = nullptr;
};
}
