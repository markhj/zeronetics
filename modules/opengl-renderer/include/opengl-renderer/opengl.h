#pragma once

#include "zeronetics/contracts/renderer.h"
#include "zeronetics/contracts/shader.h"
#include "zeronetics/core/enums.h"
#include "zeronetics/core/tensors.h"

#include "opengl-renderer/abstracts/bindable.h"

#include <string>
#include <unordered_map>

namespace ZEN::OpenGL {
    using gl_uint = unsigned int;
    using gl_int = int;
    using gl_enum = int;
    using gl_float = float;

    class Renderer : public IRenderer {
    public:
        void initialize() override;

        [[nodiscard]] bool isInitialized() const noexcept override;

        void render() override;

        void clear() noexcept override;

        void setRenderManager(const std::shared_ptr<IRenderManager> &renderManager) noexcept(false) override;

        void setViewport(const Viewport &viewport) override;

    private:
        bool m_initialized = false;

        std::shared_ptr<IRenderManager> m_renderManager;

        void handleReallocations();

        inline void processRequest(const std::shared_ptr<IRendererRequest> &request);
    };

    /**
     * OpenGL-specific implementation of the ZEN::IShader contract.
     */
    class Shader : public IShader,
                   public StdBinding<gl_uint> {
    public:
        Shader();

        ~Shader();

        void create() noexcept(false) override;

        void setSource(ShaderStage shaderStage,
                       const std::string &source) noexcept override;

        void compile() noexcept(false) override;

        void use() noexcept override;

        /**
         * Set boolean value.
         * '
         * @param location
         * @param value
         */
        void set(const std::string &location, bool value) noexcept;

        /**
         * Set integer.
         *
         * @param location
         * @param value
         */
        void set(const std::string &location, int value) noexcept;

        /**
         * Set float.
         *
         * @param location
         * @param value
         */
        void set(const std::string &location, float value) noexcept;

        /**
         * Set 2-dimensional vector.
         *
         * @param location
         * @param value
         */
        void set(const std::string &location, ZEN::Vec2 value) noexcept;

        /**
         * Set 3-dimensional vector.
         *
         * @param location
         * @param value
         */
        void set(const std::string &location, ZEN::Vec3 value) noexcept;

        /**
         * Set 4-dimensional vector.
         *
         * @param location
         * @param value
         */
        void set(const std::string &location, ZEN::Vec4 value) noexcept;

        void set(const std::string &location, ZEN::Mat4x4 value) noexcept override;

        void bindTo(gl_uint context) override;

        [[nodiscard]] gl_uint getContextId() const override;

    protected:
        [[nodiscard]] std::optional<gl_uint> getCurrentContextId() const override;

    private:
        std::unordered_map<ShaderStage, std::string> sources;

        gl_uint m_programId;
    };


}

template<typename T>
void ZEN::OpenGL::StdBinding<T>::unbind() {
    bindTo(0);
}

template<typename T>
bool ZEN::OpenGL::StdBinding<T>::isBound() const noexcept {
    return getContextId() == getCurrentContextId();
}

template<typename T>
void ZEN::OpenGL::StdBinding<T>::with(const std::function<void()> &function) {
    std::optional<T> current = getCurrentContextId();
    bind();
    function();
    if (!current.has_value()) {
        unbind();
    } else if (current.value() != getContextId()) {
        bindTo(current.value());
    }
}

template<typename T>
void ZEN::OpenGL::StdBinding<T>::bind() {
    bindTo(getContextId());
}
