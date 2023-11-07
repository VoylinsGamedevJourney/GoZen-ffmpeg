#pragma once
// This is the renderer, create an instance, feed it data, and make the finished video into a file.

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class GoZenRenderer : public Resource {
  GDCLASS(GoZenRenderer, Resource);

  public:
    GoZenRenderer() {}
    ~GoZenRenderer() {}

    void add_frame() {}
    void add_audio() {}
    void add_subtitles() {}
    void add_data() {}

    void finish_video() {}

  protected:
    static void _bind_methods() {
      ClassDB::bind_method(D_METHOD("add_frame"), &GoZenRenderer::add_frame);
      ClassDB::bind_method(D_METHOD("add_audio"), &GoZenRenderer::add_audio);
      ClassDB::bind_method(D_METHOD("add_subtitles"), &GoZenRenderer::add_subtitles);
      ClassDB::bind_method(D_METHOD("add_data"), &GoZenRenderer::add_data);
      
      ClassDB::bind_method(D_METHOD("finish_video"), &GoZenRenderer::finish_video);
    }
};