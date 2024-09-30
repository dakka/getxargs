# ----------------------------------------------------------------------------------------
# args
# Copyright (C) 1993-2024 David L. Dight
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
# SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
# FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
# ----------------------------------------------------------------------------------------
# cmake config
#	clang
#		CXX="clang++" CC="clang" cmake ..
#	gcc
#		CXX="g++" CC="gcc" cmake ..
#
# min cmake version 3.20 (Mar 24, 2021)
# ----------------------------------------------------------------------------------------
cmake_minimum_required (VERSION 3.20)
project (getxargs
	LANGUAGES CXX
	HOMEPAGE_URL https://github.com/dakka/getxargs
	DESCRIPTION "C++ CLI argument processor"
	VERSION 2.0.1
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)
file(GLOB files "src/*.cpp")
add_library(getxargs STATIC ${files})
add_executable(example test/example.cpp)
add_executable(example1 test/example1.cpp)
target_link_libraries(example PRIVATE getxargs)
target_include_directories(example PRIVATE src)
target_link_libraries(example1 PRIVATE getxargs)
target_include_directories(example1 PRIVATE src)

