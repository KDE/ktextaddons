/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
#include <memory>
namespace TextAutogenerateText
{
/**
 * @brief The TextAutogenerateTextPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class TextAutogenerateTextPluginPrivate;
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateTextPlugin : public QObject
{
    Q_OBJECT
public:
    explicit TextAutogenerateTextPlugin(QObject *parent = nullptr);
    ~TextAutogenerateTextPlugin() override;

    [[nodiscard]] virtual bool loadSettings() = 0;

    virtual void clear() = 0;
    [[nodiscard]] virtual QString result() = 0;

    virtual void setPrompt(const QString &text) = 0;

    void setHasError(bool error);
Q_SIGNALS:
    void errorOccurred(const QString &message);
    void finished(const QString &replyText);

private:
    std::unique_ptr<TextAutogenerateTextPluginPrivate> const d;
};
}
