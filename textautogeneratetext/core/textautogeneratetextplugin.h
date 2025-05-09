/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
#include <memory>
namespace TextAutoGenerateText
{
class TextAutoGenerateMessage;
class TextAutoGenerateTextPluginPrivate;
class TextAutoGenerateManager;
/**
 * @brief The TextAutoGenerateTextPlugin class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextPlugin : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextPlugin(QObject *parent = nullptr);
    ~TextAutoGenerateTextPlugin() override;

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

    void setManager(TextAutoGenerateText::TextAutoGenerateManager *manager);
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateManager *manager() const;
Q_SIGNALS:
    void errorOccurred(const QString &message);
    void finished(const TextAutoGenerateMessage &msg);
    void initializedDone();

protected:
    virtual void sendToLLM(const QString &message, const QByteArray &uuid) = 0;

private:
    std::unique_ptr<TextAutoGenerateTextPluginPrivate> const d;
};
}
