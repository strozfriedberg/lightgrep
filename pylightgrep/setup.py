
# Copyright 2024 Aon Cyber Solutions
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import setuptools


setuptools.setup(
    name='lightgrep',
    version='0.1.0',
    author='Joel Uckelman <joel.uckelman@aon.co.uk>',
    packages=['lightgrep'],
    package_data={
        'lightgrep': ['liblightgrep.so', 'liblightgrep.dylib']
    },
    include_package_data=True,
    has_ext_modules=lambda: True
)
