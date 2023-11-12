#include "gozen_interface.hpp"

#include <godot_cpp/variant/utility_functions.hpp>
extern "C" {
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
}


void GoZenInterface::load_video(String file_path) {
  UtilityFunctions::print_rich("[b]GoZenInterface:[/b] Getting video stream");
  std::string path_file = file_path.utf8().get_data();

  int frame_width, frame_height;
  unsigned char* frame_data;
  if (!load_frame(path_file.c_str(), &frame_width, &frame_height, &frame_data)) {
    UtilityFunctions::printerr("Couldn't load video frame!");
  }

}


bool GoZenInterface::load_frame(const char* filename, int* width, int* height, unsigned char** data) {
  
  // Open video file 
  AVFormatContext* av_format_ctx = avformat_alloc_context();
  if (!av_format_ctx) {
    UtilityFunctions::printerr("Could not create av format context!");
    return false;
  }

  if (avformat_open_input(&av_format_ctx ,filename, NULL, NULL) != 0) {
    UtilityFunctions::printerr("Could not open video file!");
    return false;
  }

  // Find video and audio stream of file
  int video_stream_index = -1;
  //int audio_stream_index = -1;
  AVCodecParameters* av_codec_params;
  const AVCodec* av_codec;

  for (int i = 0; i < av_format_ctx->nb_streams; i++) {
    auto stream = av_format_ctx->streams[i];
    av_codec_params = av_format_ctx->streams[i]->codecpar;
    av_codec = avcodec_find_decoder(av_codec_params->codec_id);
    
    if (!av_codec) {
      continue;
    }
    if (av_codec_params->codec_type == AVMEDIA_TYPE_VIDEO) {
      video_stream_index = i;
      UtilityFunctions::print("Video stream found");
      break;
    }
    //if (av_codec_params->codec_type == AVMEDIA_TYPE_AUDIO) {
    //  audio_stream_index = i;
    //  UtilityFunctions::print("Audio stream found");
    //}
    //if (video_stream_index != -1 && audio_stream_index != -1)
    //  break;  
  }

  if (video_stream_index == -1) {
    UtilityFunctions::printerr("Could not find stream!");
    return false;
  }
  //if (audio_stream_index == -1) {
  //  UtilityFunctions::printerr("Could not find audio stream!");
  //  return false;
  //}

  // Setup decoder with codec context
  AVCodecContext* av_codec_ctx = avcodec_alloc_context3(av_codec);
  if (!av_codec_ctx) {
    UtilityFunctions::printerr("Could not create AVCodecContext!");
    return false;
  }
  if (!avcodec_parameters_to_context(av_codec_ctx, av_codec_params)) {
    UtilityFunctions::printerr("Could not initialize AVCodecContext!");
    return false;
  }
  if (!avcodec_open2(av_codec_ctx, av_codec, NULL) < 0) {
    UtilityFunctions::printerr("Could not open codec!");
    return false;
  }

  AVFrame* av_frame = av_frame_alloc();
  if (!av_frame) {
    UtilityFunctions::printerr("Could not allocate AVFrame!");
    return false;
  }
  AVPacket* av_packet = av_packet_alloc();
  if (!av_packet) {
    UtilityFunctions::printerr("Could not allocate AVPacket!");
    return false;
  }

  avformat_close_input(&av_format_ctx);
  avformat_free_context(av_format_ctx);
  avcodec_free_context(&av_codec_ctx);

  UtilityFunctions::print("Everything okay");
  return true;
}


void GoZenInterface::_bind_methods() {
  ClassDB::bind_method(D_METHOD("load_video"), &GoZenInterface::load_video, "file_path");
  //ClassDB::bind_method(D_METHOD("load_frame"), &GoZenInterface::load_frame, "filename", "width", "height", "data");
}
