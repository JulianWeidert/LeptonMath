set(INCLUDE_DIR "${LeptonMath_SOURCE_DIR}/include/LeptonMath")

set(SRC 
	"${INCLUDE_DIR}/Vector.h"
	"Vector.cpp"
)

add_library(LeptonMath ${SRC})

# include dir
target_include_directories(LeptonMath PUBLIC "${INCLUDE_DIR}/..")