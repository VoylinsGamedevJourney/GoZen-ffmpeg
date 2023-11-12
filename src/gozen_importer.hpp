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

    int get_video_streams(String file_path);

  protected:
    static void _bind_methods() {
      ClassDB::bind_method(D_METHOD("get_video_streams"), &GoZenImporter::get_video_streams, "file_path");
    }
  
  private:
    static int open_codec_context(int *stream_index, AVCodecContext **codec_context, AVFormatContext *format_context, enum AVMediaType type); 
    static int decode_packet(AVCodecContext *codec, const AVPacket *packet, AVFrame *p_frame, int width, int height, enum AVPixelFormat pix_fmt);
    static int output_video_frame(AVFrame *p_frame, int width, int height, enum AVPixelFormat pix_fmt);
    static int output_audio_frame(AVFrame *p_frame);
};