//------------------------------------------------------------------------------
//  FullscreenQuad.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "Core/Main.h"
#include "Gfx/Gfx.h"
#include "shaders.h"

using namespace Oryol;

class FullscreenQuadApp : public App {
public:
    AppState::Code OnRunning();
    AppState::Code OnInit();
    AppState::Code OnCleanup();
    
private:
    DrawState drawState;
    Shader::Params params;
};
OryolMain(FullscreenQuadApp);

//------------------------------------------------------------------------------
AppState::Code
FullscreenQuadApp::OnRunning() {
    // render one frame
    this->params.Time += 1.0f / 60.0f;
    Gfx::ApplyDefaultRenderTarget();
    Gfx::ApplyDrawState(this->drawState);
    Gfx::ApplyUniformBlock(this->params);
    Gfx::Draw();
    Gfx::CommitFrame();
    
    // continue running or quit?
    return Gfx::QuitRequested() ? AppState::Cleanup : AppState::Running;
}

//------------------------------------------------------------------------------
AppState::Code
FullscreenQuadApp::OnInit() {
    Gfx::Setup(GfxSetup::Window(600, 600, "Oryol Fullscreen Quad Sample"));
    auto quadSetup = MeshSetup::FullScreenQuad();
    this->drawState.Mesh[0] = Gfx::CreateResource(quadSetup);
    Id shd = Gfx::CreateResource(Shader::Setup());
    auto ps = PipelineSetup::FromLayoutAndShader(quadSetup.Layout, shd);
    this->drawState.Pipeline = Gfx::CreateResource(ps);
    this->params.Time = 0.0f;
    return App::OnInit();
}

//------------------------------------------------------------------------------
AppState::Code
FullscreenQuadApp::OnCleanup() {
    Gfx::Discard();
    return App::OnCleanup();
}
