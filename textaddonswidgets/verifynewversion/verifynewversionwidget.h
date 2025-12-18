/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QMap>
#include <QObject>
class QAction;
namespace TextAddonsWidgets
{
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

    explicit VerifyNewVersionWidget(QObject *parent = nullptr);
    ~VerifyNewVersionWidget() override;

    [[nodiscard]] bool canVerifyNewVersion() const;

    [[nodiscard]] QAction *verifyNewVersionAction();

    void generateUrlInfo(const QString &stableBranchVersion, const QString &url, bool stable);

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
