#  Copyright (c) Microsoft Corporation. All rights reserved.
#  Licensed under the MIT License.

cmake_minimum_required (VERSION 3.11)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project (demo_threadx C ASM)

SET(CMAKE_ASM_FLAGS "-mcpu=cortex-m4")

azsphere_configure_tools(TOOLS_REVISION "20.07")
azsphere_configure_api(TARGET_API_SET "6")

add_compile_definitions(OSAI_AZURE_RTOS)

add_link_options(-specs=nano.specs -specs=nosys.specs)

file(GLOB_RECURSE firmware_sources ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.c)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Includes)

# Create executable
add_executable (${PROJECT_NAME}
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_adc.c
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_dma.c
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_eint.c
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_gpio.c
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_gpioif.c
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_gpt.c
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_i2c.c
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_i2s.c
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_pwm.c
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_spim.c
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_uart.c
    mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/src/os_hal_wdt.c
    ./demo_threadx/demo_threadx.c 
    ./demo_threadx/rtcoremain.c
    ./demo_threadx/tx_initialize_low_level.S
    ${firmware_sources} "Includes/Custom.h"    )

target_include_directories(${PROJECT_NAME} PUBLIC mt3620_m4_software/MT3620_M4_Sample_Code/OS_HAL/inc)
target_include_directories(${PROJECT_NAME} PUBLIC
                            mt3620_m4_software/MT3620_M4_Driver/MHAL/inc
                            mt3620_m4_software/MT3620_M4_Driver/HDL/inc
                            mt3620_m4_software/MT3620_M4_BSP/CMSIS/include
                            mt3620_m4_software/MT3620_M4_BSP/mt3620/inc
                            mt3620_m4_software/MT3620_M4_BSP/printf)

add_subdirectory(mt3620_m4_software/MT3620_M4_Driver)

set(THREADX_ARCH "cortex_m4")
set(THREADX_TOOLCHAIN "gnu")
add_subdirectory(threadx)

#target_compile_options(${PROJECT_NAME} PUBLIC -specs=nosys.specs -mfloat-abi=hard -mfpu=fpv4-sp-d16 )
target_link_libraries(${PROJECT_NAME} PUBLIC MT3620_M4_Driver azrtos::threadx ${CMAKE_CURRENT_SOURCE_DIR}/lib_arm/libModel.a m)
#SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections -Wl,-T ${LINKER_SCRIPT}" CACHE STRING "" FORCE)

#target_link_libraries(${PROJECT_NAME} MT3620_M4_Driver azrtos::threadx  ${CMAKE_CURRENT_SOURCE_DIR}/lib_arm/libm.a)

set_target_properties (${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${PROJECT_SOURCE_DIR}/linker.ld)

# Add MakeImage post-build command
# include ("${AZURE_SPHERE_MAKE_IMAGE_FILE}")

azsphere_target_add_image_package(${PROJECT_NAME})

