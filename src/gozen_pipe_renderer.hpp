#pragma once
// Basic render system which uses ffmpeg command to render.
// For this method, ffmpeg needs to be installed on the system.

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>

using namespace godot;

class GoZenPipeRenderer : public Resource {
  GDCLASS(GoZenPipeRenderer, Resource);
  
  private:
    FILE* ffmpegPipe;

  public:
    GoZenPipeRenderer() {}
    ~GoZenPipeRenderer() {}

    void setup(String output, int frame_rate);
    void add_frame(PackedByteArray frame_data);
    void finish_video();

  protected:
    static void _bind_methods() {
      ClassDB::bind_method(D_METHOD("setup"), &GoZenPipeRenderer::setup, "output", "frame_rate");
      ClassDB::bind_method(D_METHOD("add_frame"), &GoZenPipeRenderer::add_frame, "frame_data");
      ClassDB::bind_method(D_METHOD("finish_video"), &GoZenPipeRenderer::finish_video);
    }
};