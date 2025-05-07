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
class TextAutoGenerateMessage;
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

    virtual void setPrompt(const QString &text) = 0;

    void setHasError(bool error);

    [[nodiscard]] bool ready() const;
    void setReady(bool newReady);

    void sendMessage(const QString &str);
    virtual void cancelRequest(const QByteArray &uuid) = 0;

    void editMessage(const QByteArray &uuid, const QString &str);

    [[nodiscard]] virtual QString engineName() const = 0;

    [[nodiscard]] QString currentModel() const;
    void setCurrentModel(const QString &newCurrentModel);

Q_SIGNALS:
    void errorOccurred(const QString &message);
    void finished(const TextAutoGenerateMessage &msg);
    void initializedDone();

protected:
    virtual void sendToLLM(const QString &message, const QByteArray &uuid) = 0;

private:
    std::unique_ptr<TextAutogenerateTextPluginPrivate> const d;
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QString generatePluginInfo() const;
};
}
