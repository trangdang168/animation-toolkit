add_executable(a3-curve-editor curve_editor.cpp spline.cpp interpolator.cpp 
  interpolator_catmullrom.h interpolator_hermite.h interpolator_linear.h)
target_link_libraries(a3-curve-editor ${LIBS})

add_executable(a3-test-catmullrom test_catmullrom.cpp interpolator.cpp interpolator_catmullrom.h)
target_link_libraries(a3-test-catmullrom ${LIBS})

add_executable(a3-test-hermite test_hermite.cpp interpolator.cpp interpolator_hermite.h)
target_link_libraries(a3-test-hermite ${LIBS})

add_executable(a3-test-linear test_linear.cpp interpolator.cpp interpolator_linear.h)
target_link_libraries(a3-test-linear ${LIBS})

add_executable(a3-test-spline test_spline.cpp interpolator.cpp spline.cpp)
target_link_libraries(a3-test-spline ${LIBS})

add_executable(a3-unique unique.cpp interpolator.cpp spline.cpp
  interpolator_catmullrom.h interpolator_hermite.h interpolator_linear.h)
target_link_libraries(a3-unique ${LIBS})
