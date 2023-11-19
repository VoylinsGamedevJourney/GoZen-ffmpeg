#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "gozen_interface.hpp"
#include "ffmpeg_includes.hpp"

using namespace godot;


class GoZenRenderProfile: public Resource {
  GDCLASS(GoZenRenderProfile, Resource);

  public:
    String filename;
    AVCodecID video_codec, audio_codec;
    Vector2i video_size;
    int framerate = -1, bit_rate = -1;


    inline void set_filename(String new_filename) {
      filename = new_filename;
    }
    inline String get_filename() {
      return filename;
    }
    
    inline void set_video_codec(GoZenInterface::CODEC new_video_codec) {
      video_codec = static_cast<AVCodecID>(new_video_codec);
    }
    inline AVCodecID get_video_codec() {
      return video_codec;
    }
    inline GoZenInterface::CODEC get_video_codec_gozen() {
      return static_cast<GoZenInterface::CODEC>(video_codec);
    }

    inline void set_audio_codec(GoZenInterface::CODEC new_audio_codec) {
      audio_codec = static_cast<AVCodecID>(new_audio_codec);
    }
    inline AVCodecID get_audio_codec() {
      return audio_codec;
    }
    inline GoZenInterface::CODEC get_audio_codec_gozen() {
      return static_cast<GoZenInterface::CODEC>(audio_codec);
    }
 
    inline void set_video_size(Vector2i new_video_size) {
      video_size = new_video_size;
    }
    inline Vector2i get_video_size() {
      return video_size;
    }
   
    inline void set_framerate(int new_framerate) {
      framerate = new_framerate;
    }
    inline int get_framerate() {
      return framerate;
    }

    inline void set_bit_rate(int new_bit_rate) {
      bit_rate = new_bit_rate;
    }
    inline int get_bit_rate() {
      return bit_rate;
    }

    inline bool check() {
      return !(filename.is_empty() || !video_codec || !audio_codec || video_size == Vector2i(0,0) || framerate == -1 || bit_rate == -1);
    }

  protected:
    static inline void _bind_methods() {   
      ClassDB::bind_method(D_METHOD("set_filename", "new_filename"), &GoZenRenderProfile::set_filename);
      ClassDB::bind_method(D_METHOD("get_filename"), &GoZenRenderProfile::get_filename);
      
      ClassDB::bind_method(D_METHOD("set_video_codec", "new_video_codec:GoZenInterface.CODEC"), &GoZenRenderProfile::set_video_codec);
      //ClassDB::bind_method(D_METHOD("get_video_codec"), &GoZenRenderProfile::get_video_codec);
      ClassDB::bind_method(D_METHOD("get_video_codec_gozen"), &GoZenRenderProfile::get_video_codec_gozen);

      ClassDB::bind_method(D_METHOD("set_audio_codec", "new_video_codec:GoZenInterface.CODEC"), &GoZenRenderProfile::set_audio_codec);
      //ClassDB::bind_method(D_METHOD("get_audio_codec"), &GoZenRenderProfile::get_audio_codec);
      ClassDB::bind_method(D_METHOD("get_audio_codec_gozen"), &GoZenRenderProfile::get_audio_codec_gozen);
      
      ClassDB::bind_method(D_METHOD("set_video_size", "new_video_size"), &GoZenRenderProfile::set_video_size);
      ClassDB::bind_method(D_METHOD("get_video_size"), &GoZenRenderProfile::get_video_size);
      
      ClassDB::bind_method(D_METHOD("set_framerate", "new_framerate"), &GoZenRenderProfile::set_framerate);
      ClassDB::bind_method(D_METHOD("get_framerate"), &GoZenRenderProfile::get_framerate);
      
      ClassDB::bind_method(D_METHOD("set_bit_rate", "new_bit_rate"), &GoZenRenderProfile::set_bit_rate);
      ClassDB::bind_method(D_METHOD("get_bit_rate"), &GoZenRenderProfile::get_bit_rate);

      ADD_PROPERTY(PropertyInfo(Variant::STRING, "filename"), "set_filename", "get_filename");
      ADD_PROPERTY(PropertyInfo(Variant::VECTOR2I, "video_size"), "set_video_size", "get_video_size");
      ADD_PROPERTY(PropertyInfo(Variant::INT, "framerate"), "set_framerate", "get_framerate");
      ADD_PROPERTY(PropertyInfo(Variant::INT, "bit_rate"), "set_bit_rate", "get_bit_rate");
    }
};