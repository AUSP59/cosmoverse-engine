import ctypes, os
from ctypes import c_char_p, c_size_t, c_uint64
def _load():
    env = os.environ.get("COSMOVERSE_LIB")
    names = ["libcosmoverse.so","cosmoverse.dll","libcosmoverse.dylib"]
    if env and os.path.exists(env): return ctypes.CDLL(env)
    for n in names:
        try: return ctypes.CDLL(n)
        except OSError: pass
    raise OSError("Could not locate cosmoverse library; set COSMOVERSE_LIB.")
_lib = _load()
_lib.cosmoverse_version_c.restype = c_char_p
_lib.cosmoverse_fnv1a64_c.argtypes = [c_char_p, c_size_t]
_lib.cosmoverse_fnv1a64_c.restype = c_uint64
def version(): return _lib.cosmoverse_version_c().decode("utf-8")
def fnv1a64(data: bytes)->int: return int(_lib.cosmoverse_fnv1a64_c(data, len(data)))
