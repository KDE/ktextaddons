ecm_add_qml_module(ktextaddonsquickplugin URI "org.kde.ktextaddons.emoticons" VERSION 1.0 GENERATE_PLUGIN_SOURCE)

target_sources(ktextaddonsquickplugin PRIVATE types.h)

target_link_libraries(ktextaddonsquickplugin PRIVATE
        Qt6::Qml
        KF6::TextEmoticonsCore
)

ecm_finalize_qml_module(ktextaddonsquickplugin)
