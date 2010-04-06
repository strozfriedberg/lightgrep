import os

env = Environment(ENV=os.environ) # this builds in a dependency on the PATH, which is useful for ccache

env.SConscript('test/SConscript', exports='env')
