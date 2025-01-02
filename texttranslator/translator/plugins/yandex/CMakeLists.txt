# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

add_library(translator_yandex MODULE)
target_sources(translator_yandex PRIVATE
    yandexengineclient.cpp
    yandexengineclient.h
    yandexengineplugin.cpp
    yandexengineplugin.h
)
ecm_qt_declare_logging_category(translator_yandex
    HEADER yandextranslator_debug.h
    IDENTIFIER TRANSLATOR_YANDEX_LOG
    CATEGORY_NAME org.kde.kf.texttranslator.yandex
    OLD_CATEGORY_NAMES org.kde.kf6.texttranslator.yandex
    DESCRIPTION "yandex translator"
    EXPORT KTEXTADDONS
)

target_link_libraries(translator_yandex PRIVATE KF6::TextTranslator KF6::I18n)

install(TARGETS translator_yandex  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/translator/)
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
