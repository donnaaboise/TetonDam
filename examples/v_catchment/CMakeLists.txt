add_library(vcatch_f OBJECT
	qinit.f90
	setprob.f90
	vcatch_src2.f90
	vcatch_flooded.f90
)

target_link_libraries(vcatch_f PRIVATE 
  FORESTCLAW::GEOCLAW
)


add_executable(vcatch 
	vcatch_user.cpp
	vcatch_user.h
	vcatch_options.c 
	vcatch.cpp
)

target_include_directories(vcatch PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR} 
)

target_link_libraries(vcatch PRIVATE 
  vcatch_f
  FORESTCLAW::GEOCLAW
)