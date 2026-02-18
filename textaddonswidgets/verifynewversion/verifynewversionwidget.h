/*
   SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QMap>
#include <QObject>
class QAction;
namespace TextAddonsWidgets
{
/*!
 * \class TextAddonsWidgets::VerifyNewVersionWidget
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/VerifyNewVersionWidget
 *
 * \brief The VerifyNewVersionWidget class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTADDONSWIDGETS_EXPORT VerifyNewVersionWidget : public QObject
{
    Q_OBJECT
public:
    enum class OsVersion : uint8_t {
        Unknown,
        Windows,
        MacOsArm64,
        MacOs,
    };
    struct TEXTADDONSWIDGETS_EXPORT VerifyNewVersionInfo {
        TextAddonsWidgets::VerifyNewVersionWidget::OsVersion osVersion = TextAddonsWidgets::VerifyNewVersionWidget::OsVersion::Unknown;
        QString generatedUrl;
    };

    /*!
     * \brief Constructor for VerifyNewVersionWidget
     * \param parent The parent object
     */
    explicit VerifyNewVersionWidget(QObject *parent = nullptr);
    /*!
     * \brief Destructor for VerifyNewVersionWidget
     */
    ~VerifyNewVersionWidget() override;

    /*!
     * \brief Returns whether it's possible to verify a new version
     * \return True if verification is possible, false otherwise
     */
    [[nodiscard]] bool canVerifyNewVersion() const;

    /*!
     * \brief Returns the action for verifying a new version
     * \return The QAction for verifying new version
     */
    [[nodiscard]] QAction *verifyNewVersionAction();

    /*!
     * \brief Generates URL information for verifying a new version
     * \param stableBranchVersion The stable branch version
     * \param url The URL to check
     * \param stable Whether to check stable version
     */
    void generateUrlInfo(const QString &stableBranchVersion, const QString &url, bool stable);

    /*!
     * \brief Generates verification info for a new version
     * \param stableBranchVersion The stable branch version
     * \param url The URL to check
     * \param stable Whether to check stable version
     * \return VerifyNewVersionInfo containing the generated information
     */
    [[nodiscard]] VerifyNewVersionInfo generateVerifyNewVersionInfo(const QString &stableBranchVersion, const QString &url, bool stable) const;
#if TEXTADDONSWIDGETS_ENABLE_DEPRECATED_SINCE(1, 9)
    [[deprecated("use generateUrlInfo")]] void addOsUrlInfo(VerifyNewVersionWidget::OsVersion os, const QString &url);
#endif
private:
    TEXTADDONSWIDGETS_NO_EXPORT void slotVerifyNewVersion();
    QMap<VerifyNewVersionWidget::OsVersion, QString> mUrls;
    QAction *mVerifyNewVersionAction = nullptr;
};
}
