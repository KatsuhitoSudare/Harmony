﻿include("${CMAKE_SOURCE_DIR}/.cmake/common.cmake")
init_main_module_setting(ModuleManager)
target_link_libraries(ModuleManager "EventManager" "Utility" "Object")