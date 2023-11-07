import platform


env = SConscript("godot-cpp/SConstruct")
env.Append(CPPPATH="src/")


# Determine the platform and set the appropriate link flags
if platform.system() == "Linux": # Linux
  print("Linux system detected")
  env.Append(LINKFLAGS=["-lavcodec", "-lavformat", "-lavfilter", "-lavdevice", "-lavutil", "-lswscale", "-lswresample"])
elif platform.system() == "Windows": # Windows - probably not working
  print("Windows system detected")
  env.Append(LINKFLAGS=["-lavcodec", "-lavformat", "-lswscale"])
elif platform.system() == "Darwin": # macOS - probably not working
  print("Mac system detected")
  env.Append(LINKFLAGS=["libavcodec", "libavformat", "libavfilter", "libavdevice", "libavutil", "libswscale", "libswresample"])


src = Glob("src/*.cpp")


libpath = "bin/libgozen{}{}".format(env["suffix"], env["SHLIBSUFFIX"])
print("libpath:", libpath)


sharedlib = env.SharedLibrary(libpath, src)
Default(sharedlib)