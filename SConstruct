import platform

env = SConscript("godot-cpp/SConstruct")
env.Append(CPPPATH=["/usr/include/gstreamer-1.0", "/usr/include/glib-2.0", "/usr/lib/glib-2.0/include", "/usr/include/sysprof-6", "src/"])

# Determine the platform and set the appropriate link flags
if platform.system() == "Linux": # Linux
  print("Linux system detected")
  env.Append(LIBS=["avcodec", "avformat", "avfilter", "avdevice", "avutil", "swscale", "swresample"])
  env.Append(LIBS=["gstreamer-1.0", "gobject-2.0", "glib-2.0"])
elif platform.system() == "Windows": # Windows - probably not working
  print("Windows system detected")
  env.Append(LIBS=["avcodec", "avformat", "avfilter", "avdevice", "avutil", "swscale", "swresample"])
elif platform.system() == "Darwin": # macOS - probably not working
  print("Mac system detected")
  env.Append(LIBS=["libavcodec", "libavformat", "libavfilter", "libavdevice", "libavutil", "libswscale", "libswresample"])

src = Glob("src/*.cpp")

libpath = "bin/libgozen{}{}".format(env["suffix"], env["SHLIBSUFFIX"])
print("libpath:", libpath)


sharedlib = env.SharedLibrary(libpath, src)
Default(sharedlib)
