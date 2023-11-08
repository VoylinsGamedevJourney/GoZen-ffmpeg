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
  cmd += "-i - ";                             // Read input from pipe
  cmd += "-c:v libvpx-vp9 ";                  // Codec: VP9 video codec
  cmd += "-b:v 1M ";                          // Video bitrate
  cmd += "-pix_fmt yuv444p ";                 // Pixel format: yuv420p
  cmd += "-f webm ";                          // Output format: WebM
  cmd += output.utf8().get_data();            // Output file path

  // Debug to see if string is correct or not
  //UtilityFunctions::print(cmd.c_str());

  // Opening the pipe
  ffmpegPipe = popen(cmd.c_str(), "w");
  if (!ffmpegPipe) {
    UtilityFunctions::printerr("Failed to open ffmpeg pipe!");
    exit(1);
  } else {
    UtilityFunctions::print("FFMPEG data created successfully!");
  }
}


void GoZenPipeRenderer::add_frame(PackedByteArray frame_data) {
  if (ffmpegPipe) {
    //UtilityFunctions::print(fwrite(frame_data.ptr(), 1, frame_data.size(), ffmpegPipe));
    //UtilityFunctions::print(frame_data.size());
    //fflush(ffmpegPipe);

    size_t data_size = frame_data.size();
    size_t total_written = 0;

    while (total_written < data_size) {
      size_t bytes_written = fwrite(frame_data.ptrw() + total_written, 1, data_size - total_written, ffmpegPipe);
      if (bytes_written < 0) {
        // Handle the error
        UtilityFunctions::printerr("Error writing to pipe");
        break;
      }

      total_written += bytes_written;
      UtilityFunctions::print(bytes_written);
      UtilityFunctions::print(total_written);
    }

    // Flush the internal buffer
    UtilityFunctions::print(fflush(ffmpegPipe));
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
