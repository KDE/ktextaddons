/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QHash>
#include <QObject>
class QColor;
class QNetworkAccessManager;
namespace TextGrammarCheck
{
class TEXTGRAMMARCHECK_EXPORT LanguageToolManager : public QObject
{
    Q_OBJECT
public:
    explicit LanguageToolManager(QObject *parent = nullptr);
    ~LanguageToolManager() override;
    static LanguageToolManager *self();

    QNetworkAccessManager *networkAccessManager() const;

    [[nodiscard]] QString languageToolPath() const;
    void setLanguageToolPath(const QString &path);

    void loadSettings();
    void saveSettings();

    [[nodiscard]] QString language() const;
    void setLanguage(const QString &language);

    [[nodiscard]] bool useLocalInstance() const;
    void setUseLocalInstance(bool useLocalInstance);

    [[nodiscard]] QString languageToolCheckPath() const;

    [[nodiscard]] QString languageToolLanguagesPath() const;

    [[nodiscard]] static QString convertToLanguagePath(const QString &path);

    [[nodiscard]] QColor grammarColorForError(const QString &error);

    [[nodiscard]] bool allowToGetListOfLanguages() const;

private:
    Q_DISABLE_COPY(LanguageToolManager)
    QHash<QString, QColor> mGrammarColor;
    QString mLanguage;
    QString mLanguageToolPath;
    QNetworkAccessManager *const mNetworkAccessManager;
    bool mUseLocalInstance = false;
};
}
