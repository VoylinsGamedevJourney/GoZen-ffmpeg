#include "gozen_importer.hpp"


int GoZenImporter::get_video_streams(String file_path) {
  AVFormatContext *p_format_context;
  AVCodecContext *p_video_codec_context = NULL, *p_audio_codec_context = NULL;
  AVStream *p_video_stream = NULL, *p_audio_stream = NULL;
  enum AVPixelFormat pix_fmt;
  AVFrame *p_frame = NULL;
  int width, height;

  uint8_t *p_video_dst_data[4] = {NULL};
  int video_dst_linesize[4], video_dst_bufsize;
 
  int video_stream_idx = -1, audio_stream_idx = -1;
  AVPacket *p_packet = NULL;
  int video_frame_count = 0, audio_frame_count = 0;

  int ret = 0;
  UtilityFunctions::print("test");
  // Opening file and allocate format context
  if (avformat_open_input(&p_format_context, file_path.utf8().get_data(), NULL, NULL)) {
    UtilityFunctions::printerr("Could not open source file!");
    return -1;
  }

  // Retrieve stream info
  if (avformat_find_stream_info(p_format_context, NULL) < 0) {
    UtilityFunctions::printerr("No stream info in source file!");
    return -1;
  }

  if (open_codec_context(&video_stream_idx, &p_video_codec_context, p_format_context, AVMEDIA_TYPE_VIDEO) >= 0) {
    p_video_stream = p_format_context->streams[video_stream_idx];

    // Allocate image where decoded image will be put
    width = p_video_codec_context->width;
    height = p_video_codec_context->height;
    pix_fmt = p_video_codec_context->pix_fmt;
    ret = av_image_alloc(p_video_dst_data, video_dst_linesize, width, height, pix_fmt, 1);
    if (ret < 0) {
      UtilityFunctions::printerr("Could not allocate raw video buffer!");
      goto end;
    }
    video_dst_bufsize = ret;
  }
  if (open_codec_context(&audio_stream_idx, &p_audio_codec_context, p_format_context, AVMEDIA_TYPE_AUDIO) >= 0) {
    p_audio_stream = p_format_context->streams[audio_stream_idx];
  }

  // Dumb input info in stderr 
  av_dump_format(p_format_context, 0, file_path.utf8(), 0);

  if (!p_audio_stream && !p_video_stream) {
    UtilityFunctions::printerr("Could not find audio or video stream in the input!");
    ret = 1;
    goto end;
  }
 
  p_frame = av_frame_alloc();
  if (!p_frame) {
    UtilityFunctions::printerr("Could not allocate frame\n");
    ret = AVERROR(ENOMEM);
    goto end;
  }
 
  p_packet = av_packet_alloc();
  if (!p_packet) {
    UtilityFunctions::printerr("Could not allocate packet!");
    ret = AVERROR(ENOMEM);
    goto end;
  }

  if (p_video_stream)
    UtilityFunctions::print("Demuxing video from file");
  if (p_audio_stream)
    UtilityFunctions::print("Demuxing audio from file");

  // Read frames from the file
  while (av_read_frame(p_format_context, p_packet) >= 0) {
    // Check if packet belongs to a stream we need
    if (p_packet->stream_index == video_stream_idx)
      ret = decode_packet(p_video_codec_context, p_packet, p_frame, width, height, pix_fmt);
    else if (p_packet->stream_index == audio_stream_idx)
      ret = decode_packet(p_audio_codec_context, p_packet, p_frame, width, height, pix_fmt);
    av_packet_unref(p_packet);
    if (ret < 0)
      break;
  }

  // Flush the decoders
  if (p_video_codec_context)
    decode_packet(p_video_codec_context, NULL, p_frame, width, height, pix_fmt);
  if (p_audio_codec_context)
    decode_packet(p_audio_codec_context, NULL, p_frame, width, height, pix_fmt);
  UtilityFunctions::print("Demuxing succeeded!");

end:
  avcodec_free_context(&p_video_codec_context);
  avcodec_free_context(&p_audio_codec_context);
  avformat_close_input(&p_format_context);
  
  av_packet_free(&p_packet);
  av_frame_free(&p_frame);
  av_free(p_video_dst_data[0]);

  return ret < 0;
}


int GoZenImporter::open_codec_context(int *stream_idx, AVCodecContext **codec_context, AVFormatContext *format_context, enum AVMediaType type) {
  int ret;
  ret = av_find_best_stream(format_context, type, -1, -1, NULL, 0);
  if (ret < 0) {
    UtilityFunctions::printerr("Could not find stream!");
    return -1;
  }
  
  int stream_index;
  AVStream *p_stream;
  const AVCodec *p_codec = NULL;

  stream_index = ret;
  p_stream = format_context->streams[stream_index];

  // Find decoder for stream
  p_codec = avcodec_find_decoder(p_stream->codecpar->codec_id);
  if(!p_codec){
    UtilityFunctions::printerr("Failed to find codec!");
    return AVERROR(EINVAL);
  }
  // Allocate codec context for the decoder
  *codec_context = avcodec_alloc_context3(p_codec);
  if (!*codec_context) {
    UtilityFunctions::printerr("Failed to allocate codec context!");
    return AVERROR(ENOMEM);
  }

  // Copy codec params from input stream to output codec context
  if ((ret = avcodec_parameters_to_context(*codec_context, p_stream->codecpar)) < 0) {
    UtilityFunctions::printerr("Failed to copy params to decoder context!");
    return ret;
  }

  // Initialize decoders
  if ((ret = avcodec_open2(*codec_context, p_codec, NULL)) < 0) {
    UtilityFunctions::printerr("Failed to open codec!");
    return ret;
  }
  return 0;
}


int GoZenImporter::decode_packet(AVCodecContext *codec, const AVPacket *packet, AVFrame *p_frame, int width, int height, enum AVPixelFormat pix_fmt) {
  int ret = 0;
 
  // Submit packet to decoder
  ret = avcodec_send_packet(codec, packet);
  if (ret < 0) {
    UtilityFunctions::printerr("Error submitting packet for decoding!");
    return ret;
  }
 
  // Get all available frames from the decoder
  while (ret >= 0) {
    ret = avcodec_receive_frame(codec, p_frame);
    if (ret < 0) {
      // Those two return values are special and mean there is no output frame available, but there were no errors
      if (ret == AVERROR_EOF || ret == AVERROR(EAGAIN))
        return 0;
      UtilityFunctions::printerr("Error during decoding!");
      return ret;
    }
 
    // write the frame data to output file
    if (codec->codec->type == AVMEDIA_TYPE_VIDEO)
      ret = output_video_frame(p_frame, width, height, pix_fmt);
    else
      ret = output_audio_frame(p_frame);
 
    av_frame_unref(p_frame);
    if (ret < 0)
      return ret;
  }
 
  return 0;
}


int GoZenImporter::output_video_frame(AVFrame *p_frame, int width, int height, enum AVPixelFormat pix_fmt)
{
  if (p_frame->width != width || p_frame->height != height ||
    p_frame->format != pix_fmt) {
    UtilityFunctions::printerr("Error: Width, height and pixel format have to be constant in a rawvideo file!");
    return -1;
  }
 
  // Copy decoded frame to destination buffer, rawvideo expects non aligned data
  //av_image_copy2(video_dst_data, video_dst_linesize, frame->data, frame->linesize, pix_fmt, width, height);
 
  // Write to raw file
  //fwrite(video_dst_data[0], 1, video_dst_bufsize, video_dst_file);
  return 0;
}
 

int GoZenImporter::output_audio_frame(AVFrame *p_frame)
{
  size_t unpadded_linesize = p_frame->nb_samples * av_get_bytes_per_sample((AVSampleFormat)p_frame->format); 

  // Write the raw audio data samples of the first plane
  //fwrite(frame->extended_data[0], 1, unpadded_linesize, audio_dst_file);
  return 0;
}
