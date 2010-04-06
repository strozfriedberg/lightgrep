import os
import os.path as p

scopeDir = 'vendors/scope'
boostDir = 'vendors/boost'

env = Environment(ENV=os.environ) # this builds in a dependency on the PATH, which is useful for ccache
env.Replace(CPPPATH=['#/include'])
env.Replace(CCFLAGS='-O3 -Wall -Wextra -I%s -I%s' % (scopeDir, boostDir))

env.SConscript('test/SConscript', exports='env')
