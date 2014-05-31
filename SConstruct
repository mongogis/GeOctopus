import os
from project import Project

common_env = Environment(ENV=os.environ,CPPPATH=[],LIBPATH=[],CXXFLAGS="-std=c++11")
common_env.Append(CPPDEFINES={"VERSON":1})

release_env = common_env.Clone()
release_env.Append(CPPDEFINES=['RELEASE'])
release_env.VariantDir('build/release', 'src',duplicate=0)

debug_env = common_env.Clone()
debug_env.Append(CPPDEFINES=['DEBUG'])
debug_env.VariantDir('build/debug', 'src',duplicate=0)

modules = [
    'geoformat',
    'mpiobject'
]

Export("modules")

for mode, env in dict(release=release_env,
                      debug=debug_env).iteritems():
    env.SConscript('build/%s/SConscript' % mode, {'env': env})
