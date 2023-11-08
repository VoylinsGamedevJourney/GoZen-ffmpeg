#include "gozen_pipe_renderer.hpp"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <godot_cpp/variant/utility_functions.hpp>


void GoZenPipeRenderer::setup(String output, int frame_rate) {
  std::string cmd = "ffmpeg ";
  cmd += "-y ";                               // Overwrites output file if already exists
  cmd += "-f image2pipe ";                    // Input format: image sequence
  cmd += "-r " + std::to_string(frame_rate);  // Setting the frame rate
  cmd += " -i - ";                            // Read input from pipe
  cmd += "-c:v libvpx-vp9 ";                  // Codec: VP9 video codec
  cmd += "-b:v 1M ";                          // Video bitrate
  cmd += "-pix_fmt yuv444p ";                 // Pixel format: yuv420p
  cmd += "-f webm ";                          // Output format: WebM
  cmd += output.utf8().get_data();            // Output file path

  // Debug to see if string is correct or not
  UtilityFunctions::print(cmd.c_str());

  // Opening the pipe
  ffmpegPipe = popen(cmd.c_str(), "w");
  if (!ffmpegPipe) {
    UtilityFunctions::printerr("Failed to open ffmpeg pipe!");
    exit(1);
  } else {
    UtilityFunctions::print("FFMPEG data created successfully!");
  }
}


void GoZenPipeRenderer::add_frame(Ref<Image> frame_image) {
  // If file does not render use print to see the return values of fwrite and fflush
  // When frame_data is too big in bytes, it stops working
  PackedByteArray frame_data = frame_image->save_webp_to_buffer(false, 1.0);
  if (ffmpegPipe) {
    fwrite(frame_data.ptrw(), 1, frame_data.size(), ffmpegPipe);
    fflush(ffmpegPipe);
  } else {
    UtilityFunctions::printerr("FFMPEG pipe does not exist!");
  }
}


void GoZenPipeRenderer::finish_video() {
  if (ffmpegPipe) {
    pclose(ffmpegPipe);
    ffmpegPipe = nullptr;
    UtilityFunctions::print("ffmpeg is closed");
  }
}
