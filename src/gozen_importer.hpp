#pragma once
// This is the importer which breaks down video files and sends the different streams to Godot

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/utility_functions.hpp>


using namespace godot;

class GoZenImporter : public Resource {
  GDCLASS(GoZenImporter, Resource);

  public:
    GoZenImporter() {}
    ~GoZenImporter() {}

    void get_video_streams(String file_path);

  protected:
    static void _bind_methods() {
      ClassDB::bind_method(D_METHOD("get_video_streams"), &GoZenImporter::get_video_streams, "file_path");
    }
};