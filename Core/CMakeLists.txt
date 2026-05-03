target_sources(TraceCore PRIVATE
    src/Core/Logger.cpp
    src/Core/App.cpp
    src/Renderer/Shader.cpp
    src/Renderer/Mesh.cpp
    src/Renderer/Texture.cpp
    src/Renderer/VertexArray.cpp
    src/Renderer/VertexBuffer.cpp
    src/Renderer/IndexBuffer.cpp
    src/Renderer/Primitives.cpp
    src/Renderer/stb_image.cpp
    src/Renderer/RenderCommand.cpp
    src/Camera/Camera.cpp
    src/ImGui/ImGuiManager.cpp
    src/ImGui/panels/LogPanel.cpp
    src/ImGui/panels/DebugPanel.cpp
    src/Window/Window.cpp
)

target_include_directories(TraceCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external/glad/include
    ${CMAKE_SOURCE_DIR}/external/stb_image
)

target_link_libraries(TraceCore PUBLIC
    glad
    glfw
    imgui
    glm::glm
)

target_precompile_headers(TraceCore PRIVATE src/pch.h)