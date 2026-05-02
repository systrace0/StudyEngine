target_sources(TraceLib PRIVATE
    stb_image.cpp
    Window.cpp
    Shader.cpp
    VertexArray.cpp
    VertexBuffer.cpp
    IndexBuffer.cpp
    Mesh.cpp
    Logger.cpp
    imgui/ImGuiManager.cpp
    imgui/panels/LogPanel.cpp
    imgui/panels/DebugPanel.cpp
    Texture.cpp
)

# Thin executable just has main
target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

target_include_directories(TraceLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/stb_image
)

target_link_libraries(${PROJECT_NAME} PRIVATE TraceLib)
target_link_libraries(TraceLib PUBLIC glad glfw imgui)

target_include_directories(TraceLib PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_precompile_headers(TraceLib PRIVATE pch.h)
target_precompile_headers(${PROJECT_NAME} REUSE_FROM TraceLib)