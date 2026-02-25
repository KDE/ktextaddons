/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonmodelavailableinfowidget.h"
#include "autogeneratetext_ollamacommon_debug.h"
#include "ollamacommonmodelavailableinfo.h"
#include "ollamacommonnetworkurlbutton.h"
#include "widgets/common/textautogenerateflowlayout.h"
#include <KLocalizedString>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

OllamaCommonModelAvailableInfoWidget::OllamaCommonModelAvailableInfoWidget(QWidget *parent)
    : QWidget{parent}
    , mNameLabel(new QLabel(this))
    , mMainLayout(new QVBoxLayout(this))
    , mNetworkUrlButton(new OllamaCommonNetworkUrlButton(this))
{
    mMainLayout->setObjectName(u"mMainLayout"_s);
    mNetworkUrlButton->setObjectName(u"mNetworkUrlButton");
    mMainLayout->addWidget(mNetworkUrlButton, 0, Qt::AlignTop);
    {
        auto label = new QLabel(i18n("Name:"), this);
        mMainLayout->addWidget(label, 0, Qt::AlignTop);
        changeFont(label);

        mNameLabel->setObjectName(u"mNameLabel"_s);
        mMainLayout->addWidget(mNameLabel, 0, Qt::AlignTop);
    }
}

OllamaCommonModelAvailableInfoWidget::~OllamaCommonModelAvailableInfoWidget() = default;

void OllamaCommonModelAvailableInfoWidget::changeFont(QLabel *label)
{
    QFont f = label->font();
    f.setBold(true);
    label->setFont(f);
}
void OllamaCommonModelAvailableInfoWidget::setOllamaModelAvailableInfo(const OllamaCommonModelAvailableInfo &info)
{
    mNetworkUrlButton->setUrl(info.url());
    mNameLabel->setText(info.name());
    if (mInfoWidget) {
        mMainLayout->removeWidget(mInfoWidget);
        mInfoWidget->deleteLater();
    }
    mInfoWidget = new QWidget(this);
    mMainLayout->addWidget(mInfoWidget, 1);
    auto infoLayout = new QVBoxLayout(mInfoWidget);
    infoLayout->setContentsMargins({});

    auto languagesGroupBox = new QGroupBox(i18n("Languages Supported"), mInfoWidget);
    infoLayout->addWidget(languagesGroupBox);
    auto vboxLanguagesLayout = new TextAutoGenerateText::TextAutoGenerateFlowLayout(languagesGroupBox);
    const auto languages = info.languages();
    for (const auto &lang : languages) {
        const QLocale locale(lang);
        if (locale.language() == QLocale::Language::C) {
            qCWarning(AUTOGENERATETEXT_OLLAMACOMMON_LOG) << " impossible to convert to language " << lang;
            continue;
        }
        vboxLanguagesLayout->addWidget(new QLabel(locale.nativeLanguageName(), mInfoWidget));
    }
    QStringList categoriesName;
    const TextAutoGenerateText::TextAutoGenerateManager::Categories categories = info.categories();
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Tools, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Multilingual, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Code, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Math, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Vision, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Embedding, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Reasoning, categories);
    appendCategories(categoriesName, TextAutoGenerateText::TextAutoGenerateManager::Category::Cloud, categories);
    if (!categoriesName.isEmpty()) {
        auto featuresGroupBox = new QGroupBox(i18n("Features Supported"), mInfoWidget);
        infoLayout->addWidget(featuresGroupBox);
        auto vboxfeaturesLayout = new TextAutoGenerateText::TextAutoGenerateFlowLayout(featuresGroupBox);
        for (const QString &name : std::as_const(categoriesName)) {
            vboxfeaturesLayout->addWidget(new QLabel(name, mInfoWidget));
        }
    }

    infoLayout->addStretch(1);
}

void OllamaCommonModelAvailableInfoWidget::appendCategories(QStringList &lst,
                                                            TextAutoGenerateText::TextAutoGenerateManager::Category cat,
                                                            TextAutoGenerateText::TextAutoGenerateManager::Categories categories)
{
    if (categories & cat) {
        lst.append(TextAutoGenerateText::TextAutoGenerateManager::convertCategoryToI18n(cat));
    }
}

#include "moc_ollamacommonmodelavailableinfowidget.cpp"
