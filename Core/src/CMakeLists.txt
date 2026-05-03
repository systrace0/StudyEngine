target_sources(TraceCore PRIVATE
    src/Window/Window.cpp
    src/Core/Logger.cpp
    src/Core/App.cpp
    src/Renderer/Shader.cpp
    src/Renderer/VertexArray.cpp
    src/Renderer/VertexBuffer.cpp
    src/Renderer/IndexBuffer.cpp
    src/Renderer/Mesh.cpp
    src/Renderer/Texture.cpp
    src/Renderer/Primitives.cpp
    src/Renderer/stb_image.cpp
    src/Camera/Camera.cpp
    src/ImGui/ImGuiManager.cpp
    src/ImGui/panels/LogPanel.cpp
    src/ImGui/panels/DebugPanel.cpp
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
target_link_libraries(TraceLib PUBLIC glad glfw imgui glm::glm)

target_include_directories(TraceLib PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_precompile_headers(TraceLib PRIVATE pch.h)
target_precompile_headers(${PROJECT_NAME} REUSE_FROM TraceLib)