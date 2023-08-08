/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on translatelocally code
*/

#include "bergamotmarianinterface.h"
#include "libbergamot_debug.h"
#include <KLocalizedString>
#include <bergamot-translator/src/translator/parser.h>
#include <bergamot-translator/src/translator/response.h>
#include <bergamot-translator/src/translator/service.h>
#include <chrono>
#include <future>
#include <memory>
#include <mutex>
#include <thread>
namespace
{

std::shared_ptr<marian::Options> makeOptions(const std::string &path_to_model_dir, const BergamotEngineUtils::SettingsInfo &settings)
{
    std::shared_ptr<marian::Options> options(marian::bergamot::parseOptionsFromFilePath(path_to_model_dir + "/config.intgemm8bitalpha.yml"));
    options->set("cpu-threads", settings.memoryByThread, "workspace", /*settings.workspace*/ 128, "mini-batch-words", 1000, "alignment", "soft", "quiet", true);
    return options;
}

int countWords(std::string input)
{
    const char *str = input.c_str();

    bool inSpaces = true;
    int numWords = 0;

    while (*str != '\0') {
        if (std::isspace(static_cast<unsigned char>(*str))) {
            inSpaces = true;
        } else if (inSpaces) {
            numWords++;
            inSpaces = false;
        }
        ++str;
    }
    return numWords;
}

} // Anonymous namespace

struct TranslationInput {
    std::string text;
    marian::bergamot::ResponseOptions options;
};

struct ModelDescription {
    std::string config_file;
    BergamotEngineUtils::SettingsInfo settings;
};

BergamotMarianInterface::BergamotMarianInterface(QObject *parent)
    : QObject{parent}
    , mPendingInput(nullptr)
    , mPendingModel(nullptr)
{
    // This worker is the only thread that can interact with Marian. Right now
    // it basically uses marian::bergamot::Service's non-blocking interface
    // in a blocking way to have an easy way to control how what the next
    // task will be, and to not start queueing up already irrelevant
    // translation operations.
    // This worker basically processes a command queue, except that there are
    // only two possible commands: load model & translate input. And there are
    // no actual queues because we always want the last command: we don't care
    // about previously pending models or translations. The semaphore
    // indicates whether there are 0, 1, or 2 commands pending. If a command
    // is pending but both "queues" are empty, we'll treat that as a shutdown
    // request.
    mWorke = std::thread([&]() {
        std::unique_ptr<marian::bergamot::AsyncService> service;
        std::shared_ptr<marian::bergamot::TranslationModel> model;

        std::mutex internal_mutex;

        while (true) {
            std::unique_ptr<ModelDescription> modelChange;
            std::unique_ptr<TranslationInput> input;

            {
                // Wait for work
                std::unique_lock<std::mutex> lock(mMutex);
                mConditionVariable.wait(lock, [&] {
                    return mPendingModel || mPendingInput || mPendingShutdown;
                });

                // First check whether the command is loading a new model
                if (mPendingModel)
                    modelChange = std::move(mPendingModel);

                // Second check whether command is translating something.
                // Note: else if because we only process one command per
                // iteration otherwise commandIssued_ would go out of sync.
                else if (mPendingInput)
                    input = std::move(mPendingInput);

                // Command without any pending change -> poison.
                else
                    break;
            }

            Q_EMIT pendingChanged(true);

            try {
                if (modelChange) {
                    // Reconstruct the service because cpu_threads might have changed.
                    // @TODO: don't recreate Service if cpu_threads didn't change?
                    marian::bergamot::AsyncService::Config serviceConfig;
                    serviceConfig.numWorkers = modelChange->settings.numberOfThread;
                    serviceConfig.cacheSize = /*modelChange->settings.translation_cache ? kTranslationCacheSize :*/ 0;

                    // Free up old service first (see https://github.com/browsermt/bergamot-translator/issues/290)
                    // Calling clear to remove any pending translations so we
                    // do not have to wait for those when AsyncService is destroyed.
                    service.reset();

                    service = std::make_unique<marian::bergamot::AsyncService>(serviceConfig);

                    // Initialise a new model. Old model will be released if
                    // service is done with it, which it is since all translation
                    // requests are effectively blocking in this thread.
                    auto modelConfig = makeOptions(modelChange->config_file, modelChange->settings);
                    model = std::make_shared<marian::bergamot::TranslationModel>(modelConfig, modelChange->settings.numberOfThread);
                } else if (input) {
                    if (model) {
                        std::future<int> wordCount = std::async(
                            countWords,
                            input->text); // @TODO we're doing an "unnecessary" string copy here (necessary because we std::move input into service->translate)

                        Translation translation;

                        // Measure the time it takes to queue and respond to the
                        // translation request
                        auto start = std::chrono::steady_clock::now(); // Time the translation
                        service->translate(
                            model,
                            std::move(input->text),
                            [&](auto &&val) {
                                auto end = std::chrono::steady_clock::now();
                                // Calculate translation speed in terms of words per second
                                double words = wordCount.get();
                                std::chrono::duration<double> elapsedSeconds = end - start;
                                int translationSpeed = std::ceil(words / elapsedSeconds.count());

                                std::unique_lock<std::mutex> lock(internal_mutex);
                                translation = Translation(std::move(val), translationSpeed);
                                mConditionVariable.notify_one();
                            },
                            input->options);

                        // Wait for either translate lambda to call back, or a reason to cancel
                        std::unique_lock<std::mutex> lock(internal_mutex);
                        mConditionVariable.wait(lock, [&] {
                            return translation || mPendingShutdown || mPendingModel;
                        });

                        if (translation)
                            Q_EMIT translationReady(translation);
                        else
                            service->clear(); // translation was interrupted. Clear pending batches
                                              // now to free any references to things that will go
                                              // out of scope.
                    } else {
                        // TODO: What? Raise error? Set model_ to ""?
                    }
                }
            } catch (const std::runtime_error &e) {
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
    mWorke.join();
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

    std::unique_lock<std::mutex> lock(mMutex);
    std::unique_ptr<TranslationInput> input(new TranslationInput{str.toStdString(), marian::bergamot::ResponseOptions{}});
    input->options.alignment = true;
    input->options.HTML = false;

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
    if (mModelString.isEmpty())
        return;

    // move my shared_ptr from stack to heap
    std::unique_lock<std::mutex> lock(mMutex);
    std::unique_ptr<ModelDescription> model(new ModelDescription{mModelString.toStdString(), settings});
    std::swap(mPendingModel, model);

    // notify worker if there wasn't already a pending model
    mConditionVariable.notify_one();
}

#include "moc_bergamotmarianinterface.cpp"
