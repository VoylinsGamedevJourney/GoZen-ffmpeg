#include "gozen_importer.hpp"

extern "C" {
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libswscale/swscale.h>
}



void GoZenImporter::get_video_streams(String file_path) {
  // Start demuxing (splitting media file in chunks of data)

  // Opening the video file
  AVFormatContext *format_context = NULL;
  if(avformat_open_input(&format_context, file_path.utf8(), NULL, NULL) != 0) {
    UtilityFunctions::printerr("Could not open video file!");
    return;
  }

  // Get information of the streams
  if(avformat_find_stream_info(format_context, NULL)<0){
    UtilityFunctions::printerr("Couldn't find stream information!");
    return;
  }
}