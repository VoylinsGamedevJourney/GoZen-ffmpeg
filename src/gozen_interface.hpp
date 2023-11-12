#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/variant/variant.hpp>

using namespace godot;

class GoZenInterface : public Resource {
  GDCLASS(GoZenInterface, Resource);

  public:
    GoZenInterface() {}
    ~GoZenInterface() {}

    void load_video(String file_path);

  private:
    bool load_frame(const char* filename, int* width, int* height, unsigned char** data);

  protected:
    static void _bind_methods();
};