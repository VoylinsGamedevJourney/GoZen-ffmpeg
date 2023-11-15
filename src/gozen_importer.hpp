#pragma once
// This is the importer which breaks down video files and sends the different streams to Godot

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

extern "C" {
  #include <libavutil/imgutils.h>
  #include <libavutil/samplefmt.h>
  #include <libavutil/timestamp.h>
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
}


using namespace godot;

class GoZenImporter : public Resource {
  GDCLASS(GoZenImporter, Resource);

  public:
    GoZenImporter() {}
    ~GoZenImporter() {}

  protected:
    static void _bind_methods() {
      //ClassDB::bind_method(D_METHOD("get_streams"), &GoZenImporter::get_streams, "file_path");
    }
};