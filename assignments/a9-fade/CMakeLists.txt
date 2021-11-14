set(LIBS imgui ${LIBS})
#add_executable(a9-crossfade crossfade.cpp motion_blender.cpp)
#target_link_libraries(a9-crossfade ${LIBS})

add_executable(a9-iksimple iksimple.cpp)
target_link_libraries(a9-iksimple ${LIBS})

#add_executable(a9-controller controller.cpp)
#target_link_libraries(a9-controller ${LIBS})

add_executable(a9-unique unique.cpp)
target_link_libraries(a9-unique ${LIBS})
