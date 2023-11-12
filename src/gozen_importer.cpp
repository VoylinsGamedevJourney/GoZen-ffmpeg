#include "gozen_importer.hpp"

extern "C" {
  #include <libavcodec/avcodec.h>
  #include <libavutil/imgutils.h>
  #include <libavutil/pixfmt.h>
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}



int GoZenImporter::get_video_streams(String file_path) {
  // Start demuxing (splitting media file in chunks of data)

  // Opening the video file
  AVFormatContext *p_format_context = NULL;
  if (avformat_open_input(&p_format_context, file_path.utf8(), NULL, NULL) != 0) {
    UtilityFunctions::printerr("Could not open video file!");
    return -1;
  }

  // Get stream info
  if (avformat_find_stream_info(p_format_context, NULL)<0){
    UtilityFunctions::printerr("Couldn't find stream information!");
    return -2;
  }

  AVCodecParameters *p_codec_params = NULL;

  // Getting first video stream
  int video_stream = -1;
  for (int i = 0; i < p_format_context->nb_streams; i++) {
    if (p_format_context->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      video_stream = i;
      break;
    }
  }
  if (video_stream == -1) {
    UtilityFunctions::printerr("No video stream was found!");
    return -3;
  }
  p_codec_params = p_format_context->streams[video_stream]->codecpar;

  // Find decoder for video stream
  const AVCodec *p_codec = avcodec_find_decoder(p_codec_params->codec_id);
  if (p_codec == NULL) {
    UtilityFunctions::printerr("Unsupported codec!");
    return -4;
  }

  AVCodecContext *p_codec_context = NULL;
  AVDictionary *options = NULL;
  // Open codec
  if (avcodec_open2(p_codec_context, p_codec, NULL) < 0) {
    UtilityFunctions::printerr("Could not open codec!");
    return -5;
  }

  // Allocate video frame
  AVFrame *p_frame = NULL;
  p_frame = av_frame_alloc();

  // Allocate frame structure
  AVFrame *p_frame_rgb = av_frame_alloc();
  if (p_frame_rgb == NULL) {
    UtilityFunctions::printerr("Could not allocate frame structure!");
    return -6;
  }

  // Determine required buffer size and allocates it
  int num_bytes = av_image_get_buffer_size(AV_PIX_FMT_RGB24, p_codec_context->width, p_codec_context->height, 32);
  uint8_t *buffer = (uint8_t *)av_malloc(num_bytes * sizeof(uint8_t));

  // Assign buffer to image planes
  av_image_fill_arrays(p_frame_rgb, buffer, AV_PIX_FMT_RGB24, p_codec_context->width, p_codec_context->height);




  avcodec_close(p_codec_context);


  UtilityFunctions::print("Everything works ... so far");
  return 0;
}