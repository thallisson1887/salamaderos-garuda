add_subdirectory(libmsm)
add_subdirectory(modules)
add_subdirectory(msm)
add_subdirectory(notifier)

install(FILES garuda-category.desktop DESTINATION ${SERVICES_INSTALL_DIR})
