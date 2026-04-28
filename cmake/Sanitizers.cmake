function(enable_sanitizers target)
    if(NOT ENABLE_ASAN)
        return()
    endif()

    if(MSVC)
        target_compile_options(${target} PRIVATE
            $<$<CONFIG:Debug>:/fsanitize=address>
        )
    else()
        target_compile_options(${target} PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address,undefined>
            $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
        )

        target_link_options(${target} PRIVATE
            $<$<CONFIG:Debug>:-fsanitize=address,undefined>
        )
    endif()
endfunction()