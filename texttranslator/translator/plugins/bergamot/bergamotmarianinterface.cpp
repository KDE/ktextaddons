/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on translatelocally code
*/

#include "bergamotmarianinterface.h"
using namespace Qt::Literals::StringLiterals;

#include "libbergamot_debug.h"
#include <KLocalizedString>
#include <slimt/Frontend.hh>
#include <slimt/Model.hh>
#include <slimt/Response.hh>

struct TranslationInput {
    std::string text;
    slimt::Options options;
};

struct ModelDescription {
    BergamotEngineUtils::ModelFiles files;
    BergamotEngineUtils::SettingsInfo settings;
};

namespace
{
constexpr size_t kTranslationCacheSize = 1 << 16;
}

BergamotMarianInterface::BergamotMarianInterface(QObject *parent)
    : QObject{parent}
    , mPendingInput(nullptr)
    , mPendingModel(nullptr)
{
    // This worker is the only thread that talks to slimt. It processes a command
    // queue with only two possible commands: load a model, or translate an input.
    // There are no actual queues because we always want the last command: earlier
    // models and translations are already irrelevant by the time we get here.
    mWorker = std::thread([this]() {
        std::unique_ptr<slimt::Blocking> service;
        std::shared_ptr<slimt::Model> model;

        while (true) {
            std::unique_ptr<ModelDescription> modelChange;
            std::unique_ptr<TranslationInput> input;

            {
                // Wait for work
                std::unique_lock<std::mutex> lock(mMutex);
                mConditionVariable.wait(lock, [this] {
                    return mPendingModel || mPendingInput || mPendingShutdown;
                });

                if (mPendingShutdown) {
                    break;
                }

                // First check whether the command is loading a new model
                if (mPendingModel) {
                    modelChange = std::move(mPendingModel);
                }
                // Second check whether command is translating something.
                // Note: else if because we only process one command per iteration.
                else if (mPendingInput) {
                    input = std::move(mPendingInput);
                }
            }

            Q_EMIT pendingChanged(true);

            try {
                if (modelChange) {
                    slimt::Config config;
                    config.workers = std::max(1, modelChange->settings.numberOfThread);
                    config.cache_size = modelChange->settings.useLocalCache ? kTranslationCacheSize : 0;

                    // Free up the old service first, so the model it may still
                    // reference is released before we load the new one.
                    service.reset();
                    model.reset();

                    service = std::make_unique<slimt::Blocking>(config);

                    // languageLocallyStored() only reports the "tiny" models.
                    const slimt::Model::Config modelConfig = slimt::preset::tiny();
                    const slimt::Package<std::string> package{
                        .model = modelChange->files.model.toStdString(),
                        .vocabulary = modelChange->files.vocabulary.toStdString(),
                        .shortlist = modelChange->files.shortlist.toStdString(),
                        .ssplit = modelChange->files.ssplit.toStdString(),
                    };
                    model = std::make_shared<slimt::Model>(modelConfig, package);
                } else if (input) {
                    if (service && model) {
                        std::vector<std::string> sources;
                        sources.push_back(std::move(input->text));
                        std::vector<slimt::Response> responses = service->translate(model, std::move(sources), input->options);
                        if (responses.empty()) {
                            Q_EMIT errorText(i18n("Translation failed."));
                        } else {
                            Q_EMIT translationReady(Translation(std::move(responses.front())));
                        }
                    } else {
                        Q_EMIT errorText(i18n("Language model is not loaded."));
                    }
                }
            } catch (const std::exception &e) {
                qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << "slimt error:" << e.what();
                Q_EMIT errorText(QString::fromStdString(e.what()));
            }

            Q_EMIT pendingChanged(false);
        }
    });
}

BergamotMarianInterface::~BergamotMarianInterface()
{
    // Remove all pending changes and unlock worker (which will then break.)
    {
        std::unique_lock<std::mutex> lock(mMutex);

        mPendingShutdown = true;
        mPendingModel.reset();
        mPendingInput.reset();

        mConditionVariable.notify_one();
    }

    // Wait for worker to join as it depends on resources we still own.
    mWorker.join();
}

void BergamotMarianInterface::translate(const QString &str)
{
    // If we don't have a model yet (loaded, or queued to be loaded, doesn't matter)
    // then don't bother trying to translate something.
    if (mModelString.isEmpty()) {
        qCWarning(TRANSLATOR_LIBBERGAMOT_LOG) << " mModelString is not defined!!!";
        Q_EMIT errorText(i18n("Language model is not defined."));
        return;
    }

    auto input = std::make_unique<TranslationInput>();
    input->text = str.toStdString();
    input->options.alignment = false;
    input->options.html = false;

    std::unique_lock<std::mutex> lock(mMutex);
    std::swap(mPendingInput, input);

    mConditionVariable.notify_one();
}

QString BergamotMarianInterface::model() const
{
    return mModelString;
}

void BergamotMarianInterface::setModel(const QString &pathModelDir, const BergamotEngineUtils::SettingsInfo &settings)
{
    mModelString = pathModelDir;

    // Empty model string means just "unload" the model. We don't do that (yet),
    // instead this just causes translate(QString) to no longer work.
    if (mModelString.isEmpty()) {
        return;
    }

    const BergamotEngineUtils::ModelFiles files = BergamotEngineUtils::modelFiles(mModelString);
    if (!files.isValid()) {
        mModelString.clear();
        Q_EMIT errorText(i18n("Language model files are missing in %1.", pathModelDir));
        return;
    }

    auto model = std::make_unique<ModelDescription>(ModelDescription{files, settings});

    std::unique_lock<std::mutex> lock(mMutex);
    std::swap(mPendingModel, model);

    // notify worker if there wasn't already a pending model
    mConditionVariable.notify_one();
}

#include "moc_bergamotmarianinterface.cpp"
