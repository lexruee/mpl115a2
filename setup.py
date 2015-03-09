from distutils.core import setup, Extension
setup(
	name="tentacle_pi.MPL115A2", 
	version="1.0",
	packages = ["tentacle_pi"],
	ext_modules = [
		Extension("tentacle_pi.MPL115A2", 
			sources = ["src/mpl115a2.c", "src/mpl115a2_ext.c"])
	]
)
