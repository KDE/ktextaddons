# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none

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
    CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.texttranslator.yandex
    DESCRIPTION "yandex translator"
    EXPORT KTEXTADDONS
)

target_link_libraries(translator_yandex PRIVATE KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n)

install(TARGETS translator_yandex  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/translator/)
if (BUILD_TESTING)
    add_subdirectory(autotests)
endif()
