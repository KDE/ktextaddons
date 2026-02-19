/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \class TextGrammarCheck::LanguageToolManager
 * \inheaderfile TextGrammarCheck/LanguageToolManager
 * \inmodule TextGrammarCheck
 * \brief Manager for LanguageTool grammar checking service.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT LanguageToolManager : public QObject
{
    Q_OBJECT
public:
    /*! Constructs a new LanguageToolManager. */
    explicit LanguageToolManager(QObject *parent = nullptr);
    /*! Destroys the manager. */
    ~LanguageToolManager() override;
    /*! Returns the global instance of LanguageToolManager. */
    static LanguageToolManager *self();

    /*! Returns the network access manager used for remote requests. */
    QNetworkAccessManager *networkAccessManager() const;

    /*! Returns the path to the LanguageTool installation. */
    [[nodiscard]] QString languageToolPath() const;
    /*! Sets the path to the LanguageTool installation. */
    void setLanguageToolPath(const QString &path);

    /*! Loads settings from the configuration. */
    void loadSettings();
    /*! Saves settings to the configuration. */
    void saveSettings();

    /*! Returns the currently selected language for grammar checking. */
    [[nodiscard]] QString language() const;
    /*! Sets the language for grammar checking. */
    void setLanguage(const QString &language);

    /*! Returns whether to use a local LanguageTool instance. */
    [[nodiscard]] bool useLocalInstance() const;
    /*! Sets whether to use a local LanguageTool instance. */
    void setUseLocalInstance(bool useLocalInstance);

    /*! Returns the path to the grammar check endpoint. */
    [[nodiscard]] QString languageToolCheckPath() const;

    /*! Returns the path to the languages list endpoint. */
    [[nodiscard]] QString languageToolLanguagesPath() const;

    /*! Converts a path to the appropriate language path format. */
    [[nodiscard]] static QString convertToLanguagePath(const QString &path);

    /*! Returns the color to use for highlighting the specified error type. */
    [[nodiscard]] QColor grammarColorForError(const QString &error);

    /*! Returns whether we are allowed to fetch the list of available languages. */
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
