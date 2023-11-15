#include "gozen_interface.hpp"


/* AV CODEC */
int GoZenInterface::get_avcodec_version() {
  return static_cast<int>(avcodec_version());
}


String GoZenInterface::get_avcodec_build_config() {
  return avcodec_configuration();
}


String GoZenInterface::get_avcodec_license() {
  return avcodec_license();
}


/* AV FILTER */
int GoZenInterface::get_avfilter_version() {
  return avfilter_version();
}


String GoZenInterface::get_avfilter_build_config() {
  return avfilter_configuration();
}


String GoZenInterface::get_avfilter_license() {
  return avfilter_license();
}


/* AV IO */
String GoZenInterface::get_avio_find_protocol_name(String url) {
  return avio_find_protocol_name(url.utf8());
}


int GoZenInterface::get_avio_check(String url, int flags) {
  // This method is unsafe as the checked resource may change permission or its existence from one call to another.
  return avio_check(url.utf8(), flags);
}


/* AV FORMAT */
int GoZenInterface::get_avformat_version() {
  return avformat_version();
}


String GoZenInterface::get_avformat_build_config() {
  return avformat_configuration();
}


String GoZenInterface::get_avformat_license() {
  return avformat_license();
}


int GoZenInterface::get_av_filename_number_test(String filename) {
  return av_filename_number_test(filename.utf8());
}


/* AV DEVICE */
int GoZenInterface::get_avdevice_version() {
  return avdevice_version();
}


String GoZenInterface::get_avdevice_build_config() {
  return avdevice_configuration();
}


String GoZenInterface::get_avdevice_license() {
  return avdevice_license();
}


/* AV UTIL */
int GoZenInterface::get_avutil_version() {
  return avutil_version();
}


String GoZenInterface::get_av_version_info() {
  return av_version_info();
}


String GoZenInterface::get_avutil_configuration() {
  return avutil_configuration();
}


String GoZenInterface::get_avutil_license() {
  return avutil_license();
}


/* POST PROC */
int GoZenInterface::get_postproc_version() {
  return postproc_version();
}


String GoZenInterface::get_postproc_configuration() {
  return postproc_configuration();
}


String GoZenInterface::get_postproc_license() {
  return postproc_license();
}


/* SWSCALE */
int GoZenInterface::get_swscale_version() {
  return swscale_version();
}


String GoZenInterface::get_swscale_configuration() {
  return swscale_configuration();
}


String GoZenInterface::get_swscale_license() {
  return swscale_license();
}


/* CODEC STUFF */
Dictionary GoZenInterface::get_video_file_meta(String file_path) {
  AVFormatContext *p_format_context = NULL;
  const AVDictionaryEntry *p_tag = NULL;
  Dictionary dic = {};
 
  if (avformat_open_input(&p_format_context, file_path.utf8(), NULL, NULL)) {
    UtilityFunctions::printerr("Could not open file!");
    return dic;
  }
  
  if (avformat_find_stream_info(p_format_context, NULL) < 0) {
    UtilityFunctions::printerr("Could not find stream info!");
    return dic;
  }
  
  while ((p_tag = av_dict_iterate(p_format_context->metadata, p_tag)))
    dic[p_tag->key] = p_tag->value;
  
  avformat_close_input(&p_format_context);
  return dic;
}


bool GoZenInterface::is_codec_supported(CODEC codec) { 
  return ((const AVCodec*)avcodec_find_encoder(static_cast<AVCodecID>(codec)));
}


Dictionary GoZenInterface::get_supported_codecs() {
  Dictionary dic = {};
  Dictionary audio = {};
  Dictionary video = {};
  std::pair<CODEC, String> audio_codecs[] = {
    {MP3, "MP3"},
    {AAC, "AAC"},
    {OPUS, "OPUS"},
    {VORBIS, "VORBIS"},
    {FLAC, "FLAC"},
    {AC3, "AC3"},
    {EAC3, "EAC3"},
    {WAV, "WAV"},
  };
  std::pair<CODEC, String> video_codecs[] = {
    {H264, "H264"},
    {H265, "H265"},
    {VP9, "VP9"},
    {MPEG4, "MPEG4"},
    {MPEG2, "MPEG2"},
    {MPEG1, "MPEG1"},
    {AV1, "AV1"},
    {VP8, "VP8"},
  };
  
  /* Audio codecs */
  for (const auto& a_codec : audio_codecs) {
    const AVCodec* codec = avcodec_find_encoder(static_cast<AVCodecID>(a_codec.first));
    Dictionary entry = {};
    entry["supported"] = is_codec_supported(a_codec.first);
    entry["codec_id"] = a_codec.second;
    entry["hardware_accel"] = codec->capabilities & AV_CODEC_CAP_HARDWARE;
    audio[a_codec.second] = entry;
  }
  
  /* Video codecs */
  for (const auto& v_codec : video_codecs) {
    const AVCodec* codec = avcodec_find_encoder(static_cast<AVCodecID>(v_codec.first));
    Dictionary entry = {};
    entry["supported"] = is_codec_supported(v_codec.first);
    entry["codec_id"] = v_codec.second;
    entry["hardware_accel"] = codec->capabilities & AV_CODEC_CAP_HARDWARE;
    video[v_codec.second] = entry;
  }

  dic["audio"] = audio;
  dic["video"] = video;
  return dic;
}
