/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textgrammarcheck_export.h"
#include <QObject>
namespace TextGrammarCheck
{
/*!
 * \class TextGrammarCheck::GrammalecteManager
 * \inheaderfile TextGrammarCheck/GrammalecteManager
 * \inmodule TextGrammarCheck
 * \brief Manager for Grammalecte grammar checking service.
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTGRAMMARCHECK_EXPORT GrammalecteManager : public QObject
{
    Q_OBJECT
public:
    /*! Constructs a new GrammalecteManager. */
    explicit GrammalecteManager(QObject *parent = nullptr);
    /*! Destroys the manager. */
    ~GrammalecteManager() override;

    /*! Returns the global instance of GrammalecteManager. */
    static GrammalecteManager *self();

    /*! Returns the path to the Python interpreter. */
    [[nodiscard]] QString pythonPath() const;
    /*! Returns the path to the Grammalecte installation. */
    [[nodiscard]] QString grammalectePath() const;

    /*! Sets the path to the Python interpreter. */
    void setPythonPath(const QString &pythonPath);
    /*! Sets the path to the Grammalecte installation. */
    void setGrammalectePath(const QString &grammalectePath);
    /*! Returns the list of active grammar checking options. */
    [[nodiscard]] QStringList options() const;
    /*! Sets the list of grammar checking options to use. */
    void setOptions(const QStringList &saveOptions);

    /*! Loads settings from the configuration. */
    void loadSettings();
    /*! Saves settings to the configuration. */
    void saveSettings();

private:
    Q_DISABLE_COPY(GrammalecteManager)
    QStringList mOptions;
    QString mPythonPath;
    QString mGrammalectePath;
};
}
