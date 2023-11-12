#pragma once
// This is the importer which breaks down video files and sends the different streams to Godot
// get_video_streams - Error codes:
//    0: OK
//   -1: Failed to open video file
//   -2: Failed to get stream info
//   -3: Failed to find video stream
//   -4: Unsupported video codec
//   -5: Couldn't open codec


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

    int get_video_streams(String file_path);

  protected:
    static void _bind_methods() {
      ClassDB::bind_method(D_METHOD("get_video_streams"), &GoZenImporter::get_video_streams, "file_path");
    }
};