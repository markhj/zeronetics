#include "glsl-shader-builder-test.h"

#include "glsl-shader-builder/glsl-shader-builder.h"
#include "zeronetics/core/io.h"


void ZEN::Tests::GLSLShaderBuilderTest::test() {
    simpleOrthographic();
    simplePerspective();
    attributes();
}

void ZEN::Tests::GLSLShaderBuilderTest::assertSource(const std::string &pathToExpected,
                                                     const std::string &actual) {
    ZEN::Path path("payloads/glsl-shader-builder/" + pathToExpected);
    assertTrue(path.exists()).because("File with payload must exist.");

    std::optional<ZEN::File> file = ZEN::File::load(path);
    Result<std::string> data = file->getData();
    assertFalse(data.isError()).because("Loading file with expected source must succeed.");

    assertEquals(data.result(), actual);
}

void ZEN::Tests::GLSLShaderBuilderTest::simpleOrthographic() {
    it("Makes a simple shader which has orthographic projection", [&]() {
        ZEN::GLSLShaderBuilder shaderBuilder;
        ZEN::ShaderBlueprint blueprint{
                .attributes = {VertexAttribute::Position3D},
        };

        assertSource("simple-ortho-vertex.glsl",
                     shaderBuilder.make(blueprint, ShaderStage::Vertex).value());
        assertSource("simple-frag.glsl",
                     shaderBuilder.make(blueprint, ShaderStage::Fragment).value());
    });
}

void ZEN::Tests::GLSLShaderBuilderTest::simplePerspective() {
    it("Makes a simple shader which has perspective projection", [&]() {
        ZEN::GLSLShaderBuilder shaderBuilder;
        ZEN::ShaderBlueprint blueprint{
                .attributes = {VertexAttribute::Position3D},
                .projection = Projection::Perspective,
        };

        assertSource("simple-perspective-vertex.glsl",
                     shaderBuilder.make(blueprint, ShaderStage::Vertex).value());
        assertSource("simple-frag.glsl",
                     shaderBuilder.make(blueprint, ShaderStage::Fragment).value());
    });
}

void ZEN::Tests::GLSLShaderBuilderTest::attributes() {
    it("Makes sure a set of varying attributes are entered correctly.", [&]() {
        ZEN::GLSLShaderBuilder shaderBuilder;
        ZEN::ShaderBlueprint blueprint{
                .attributes = {VertexAttribute::Position3D,
                               VertexAttribute::ColorRGB,
                               VertexAttribute::Normal3D},
        };

        assertSource("attributes-vertex.glsl",
                     shaderBuilder.make(blueprint, ShaderStage::Vertex).value());
        assertSource("attributes-frag.glsl",
                     shaderBuilder.make(blueprint, ShaderStage::Fragment).value());
    });
}
