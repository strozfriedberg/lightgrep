import os
import os.path as p

def sub(src):
  return env.SConscript(p.join(src, 'SConscript'), exports='env', variant_dir=p.join('bin', src), duplicate=0)

scopeDir = 'vendors/scope'
boostDir = 'vendors/boost'

env = Environment(ENV=os.environ) # this builds in a dependency on the PATH, which is useful for ccache
env.Replace(CPPPATH=['#/include'])
env.Replace(CCFLAGS='-O2 -Wall -Wextra -I%s -I%s' % (scopeDir, boostDir))
env.Append(LIBPATH=['#/lib'])

#VariantDir('bin/src', 'src')
#VariantDir('bin/test', 'test')
#liblg = env.SConscript('src/SConscript', exports='env', variant_dir='bin/src')
liblg = sub('src')
libDir = env.Install('lib', liblg)
test = sub('test')
#test = env.SConscript('test/SConscript', exports='env', variant_dir='bin/test')
env.Command('unittests', test, './$SOURCE')
