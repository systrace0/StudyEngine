target_sources(TraceApp PRIVATE
    main.cpp
)

target_link_libraries(TraceApp PRIVATE
    TraceCore
)

target_precompile_headers(TraceApp REUSE_FROM TraceCore)
