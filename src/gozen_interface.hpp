#pragma once

#include <vector>

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "ffmpeg_includes.hpp"


using namespace godot;

class GoZenInterface : public Resource {
  GDCLASS(GoZenInterface, Resource);

  public:
    enum CODEC {
      /* Audio codecs */
      MP3 = AV_CODEC_ID_MP3,
      AAC = AV_CODEC_ID_AAC,
      OPUS = AV_CODEC_ID_OPUS,
      VORBIS = AV_CODEC_ID_VORBIS,
      FLAC = AV_CODEC_ID_FLAC,
      PCM_UNCOMPRESSED = AV_CODEC_ID_PCM_S16LE,
      AC3 = AV_CODEC_ID_AC3,
      EAC3 = AV_CODEC_ID_EAC3,
      WAV = AV_CODEC_ID_WAVPACK,
      /* Video codecs */
      H264 = AV_CODEC_ID_H264,
      H265 = AV_CODEC_ID_HEVC,
      VP9 = AV_CODEC_ID_VP9,
      MPEG4 = AV_CODEC_ID_MPEG4,
      MPEG2 = AV_CODEC_ID_MPEG2VIDEO,
      MPEG1 = AV_CODEC_ID_MPEG1VIDEO,
      AV1 = AV_CODEC_ID_AV1,
      VP8 = AV_CODEC_ID_VP8,
    };


    GoZenInterface() {}
    ~GoZenInterface() {}

    /* AV CODEC */
    static int get_avcodec_version();
    static String get_avcodec_build_config();
    static String get_avcodec_license();
    
    /* AV FILTER */
    static int get_avfilter_version();
    static String get_avfilter_build_config();
    static String get_avfilter_license();

    /* AV IO */
    static String get_avio_find_protocol_name(String url);
    static int get_avio_check(String url, int flags);

    /* AV FORMAT */
    static int get_avformat_version();
    static String get_avformat_build_config();
    static String get_avformat_license();
    static int get_av_filename_number_test(String filename);

    /* AV DEVICE */
    static  int get_avdevice_version();
    static  String get_avdevice_build_config();
    static  String get_avdevice_license();

    /* AV UTIL */
    static int get_avutil_version();
    static String get_av_version_info();
    static String get_avutil_configuration();
    static String get_avutil_license();

    /* POST PROC */
    static int get_postproc_version();
    static String get_postproc_configuration();
    static String get_postproc_license();

    /* SWSCALE */
    static int get_swscale_version();
    static String get_swscale_configuration();
    static String get_swscale_license();

    /* CODEC STUFF */
    static Dictionary get_video_file_meta(String file_path); 
    static bool is_codec_supported(CODEC codec);
    static Dictionary get_supported_codecs();


  protected:
    static inline void _bind_methods() {
      /* AUDIO CODEC ENUMS */
      BIND_ENUM_CONSTANT(MP3);
      BIND_ENUM_CONSTANT(AAC);
      BIND_ENUM_CONSTANT(OPUS);
      BIND_ENUM_CONSTANT(VORBIS);
      BIND_ENUM_CONSTANT(FLAC);
      BIND_ENUM_CONSTANT(PCM_UNCOMPRESSED);
      BIND_ENUM_CONSTANT(AC3);
      BIND_ENUM_CONSTANT(EAC3);
      BIND_ENUM_CONSTANT(WAV);
      /* VIDEO CODEC ENUMS */
      BIND_ENUM_CONSTANT(H264);
      BIND_ENUM_CONSTANT(H265);
      BIND_ENUM_CONSTANT(VP9);
      BIND_ENUM_CONSTANT(MPEG4);
      BIND_ENUM_CONSTANT(MPEG2);
      BIND_ENUM_CONSTANT(MPEG1);
      BIND_ENUM_CONSTANT(AV1);
      BIND_ENUM_CONSTANT(VP8);

      /* AV CODEC */
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avcodec_version"), &GoZenInterface::get_avcodec_version);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avcodec_build_config"), &GoZenInterface::get_avcodec_build_config);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avcodec_license"), &GoZenInterface::get_avcodec_license);
      /* AV FILTER */
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avfilter_version"), &GoZenInterface::get_avfilter_version);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avfilter_build_config"), &GoZenInterface::get_avfilter_build_config);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avfilter_license"), &GoZenInterface::get_avfilter_license);
      /* AV IO */
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avio_find_protocol_name", "url:String"), &GoZenInterface::get_avio_find_protocol_name);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avio_check", "url:String", "flags:int"), &GoZenInterface::get_avio_check);
      /* AV FORMAT */
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avformat_version"), &GoZenInterface::get_avformat_version);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avformat_build_config"), &GoZenInterface::get_avformat_build_config);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avformat_license"), &GoZenInterface::get_avformat_license);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_av_filename_number_test", "filename:String"), &GoZenInterface::get_av_filename_number_test);
      /* AV DEVICE */
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avdevice_version"), &GoZenInterface::get_avdevice_version);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avdevice_build_config"), &GoZenInterface::get_avdevice_build_config);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avdevice_license"), &GoZenInterface::get_avdevice_license);
      /* AV UTIL */
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avutil_version"), &GoZenInterface::get_avutil_version);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_av_version_info"), &GoZenInterface::get_av_version_info);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avutil_configuration"), &GoZenInterface::get_avutil_configuration);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_avutil_license"), &GoZenInterface::get_avutil_license);
      /* POST PROC */
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_postproc_version"), &GoZenInterface::get_postproc_version);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_postproc_configuration"), &GoZenInterface::get_postproc_configuration);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_postproc_license"), &GoZenInterface::get_postproc_license);
      /* SWSCALE */
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_swscale_version"), &GoZenInterface::get_swscale_version);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_swscale_configuration"), &GoZenInterface::get_swscale_configuration);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_swscale_license"), &GoZenInterface::get_swscale_license);
      /* CODEC STUFF */
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_video_file_meta", "file_path:String"), &GoZenInterface::get_video_file_meta);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("is_codec_supported", "codec:CODEC"), &GoZenInterface::is_codec_supported);
      ClassDB::bind_static_method("GoZenInterface", D_METHOD("get_supported_codecs"), &GoZenInterface::get_supported_codecs);
    }
};

VARIANT_ENUM_CAST(GoZenInterface::CODEC);
