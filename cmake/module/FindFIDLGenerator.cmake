cmake_minimum_required(VERSION 2.8)

set(COMMON_API_PATH "${CMAKE_SOURCE_DIR}/cgen/commonapi-generator/commonapi-generator-linux-x86_64")


function(FIDLGenerate idlfile)
    #message(STATUS "FIDLGenerate ${COMMON_API_PATH}")
    set(FILE_SRC_FULLPATH ${CMAKE_CURRENT_SOURCE_DIR}/${idlfile})
    set(FILE_DEST_FULLPATH ${CMAKE_CURRENT_BINARY_DIR}/${idlfile})
    set(GENERATION_STATUS 0)
    set(FILE_COPY         1)
    if (NOT EXISTS ${FILE_DEST_FULLPATH})
        message(STATUS "FIDLGenerate111 ${COMMON_API_PATH}")
        execute_process(COMMAND ${COMMON_API_PATH} -sk "${CMAKE_CURRENT_SOURCE_DIR}/${idlfile}"
                        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                        RESULT_VARIABLE result
                        OUTPUT_VARIABLE output)
        #message(STATUS ${output})
        #message(STATUS ${result})
        if(${result} EQUAL 1)
            set(GENERATION_STATUS 1)
        endif()
    else()
        execute_process(COMMAND find ${FILE_SRC_FULLPATH} -newer ${FILE_DEST_FULLPATH}
                        RESULT_VARIABLE result
                        OUTPUT_VARIABLE output)
        if (${output} MATCHES ${FILE_SRC_FULLPATH})
            execute_process(COMMAND ls -la ${idlfile}
                            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                            RESULT_VARIABLE result_src
                            OUTPUT_VARIABLE output_src)
            execute_process(COMMAND ls -la ${idlfile}
                            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                            RESULT_VARIABLE result_dst
                            OUTPUT_VARIABLE output_dst)   
            if (${output_src} STREQUAL ${output_dst})
                set(FILE_COPY 0)
            else()
                execute_process(COMMAND ${COMMON_API_PATH} -sk "${CMAKE_CURRENT_SOURCE_DIR}/${idlfile}"
                                WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                                RESULT_VARIABLE result
                                OUTPUT_VARIABLE output)
                if(${result} EQUAL 1)
                    set(GENERATION_STATUS 1)
                endif()
            endif()   
        else()
            message(STATUS "file abnormal!!!")
        endif()                    
    endif()

    if(${GENERATION_STATUS} EQUAL 0)
        if(${FILE_COPY} EQUAL 1)
            file(COPY ${FILE_SRC_FULLPATH} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
        endif()
    else()
        message(FATAL_ERROR "fild generation failed, please check")
    endif()
endfunction()
