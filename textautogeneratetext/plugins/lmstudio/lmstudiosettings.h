/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratelmstudio_export.h"
#include <QString>
#include <QUrl>
using namespace Qt::StringLiterals;
class QDebug;
class KConfigGroup;
class TEXTAUTOGENERATELMSTUDIO_EXPORT LMStudioSettings
{
    Q_GADGET
public:
    enum class ShareNameType : uint8_t {
        DoNotShare = 0,
        UserName,
        FullName,
    };
    Q_ENUM(ShareNameType)

    LMStudioSettings();
    ~LMStudioSettings();

    [[nodiscard]] QString displayName() const;
    void setDisplayName(const QString &newName);

    [[nodiscard]] QString currentModel() const;
    void setCurrentModel(const QString &newCurrentModel);

    void load(const KConfigGroup &config);
    void save(KConfigGroup &config);

    [[nodiscard]] QUrl serverUrl() const;
    void setServerUrl(const QUrl &newServerUrl);

    [[nodiscard]] bool thoughtProcessing() const;
    void setThoughtProcessing(bool newThoughtProcessing);

    [[nodiscard]] static LMStudioSettings::ShareNameType convertShareNameTypeFromString(const QString &str);
    [[nodiscard]] static QString convertShareNameTypeToString(LMStudioSettings::ShareNameType type);

    [[nodiscard]] LMStudioSettings::ShareNameType shareNameType() const;
    void setShareNameType(const LMStudioSettings::ShareNameType &newShareNameType);

    [[nodiscard]] QUrl defaultServerUrl() const;
    [[nodiscard]] bool defaultThoughtProcessing() const;
    [[nodiscard]] LMStudioSettings::ShareNameType defaultShareNameType() const;

    [[nodiscard]] bool operator==(const LMStudioSettings &other) const;

private:
    QString mDisplayName;
    QString mCurrentModel;
    QUrl mServerUrl = QUrl(u"http://127.0.0.1:1234"_s);
    LMStudioSettings::ShareNameType mShareNameType = ShareNameType::DoNotShare;
    bool mThoughtProcessing = false;
};
TEXTAUTOGENERATELMSTUDIO_EXPORT QDebug operator<<(QDebug d, const LMStudioSettings &t);
