# add all directories to subdirectory
# 获取当前目录中的所有子目录
file(GLOB SUBDIRS LIST_DIRECTORIES true *)

foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY ${SUBDIR})
        # 检查是否存在 CMakeLists.txt 文件
        if(EXISTS ${SUBDIR}/CMakeLists.txt)
            message(STATUS "Adding subdirectory: ${SUBDIR}")
            add_subdirectory(${SUBDIR})
        endif()
    endif()
endforeach()