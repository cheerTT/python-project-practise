# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\coding\clion\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\coding\clion\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\codes\clion\clion_base\numcpp01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\codes\clion\clion_base\numcpp01\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\numcpp01.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\numcpp01.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\numcpp01.dir\flags.make

CMakeFiles\numcpp01.dir\main.cpp.obj: CMakeFiles\numcpp01.dir\flags.make
CMakeFiles\numcpp01.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\codes\clion\clion_base\numcpp01\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/numcpp01.dir/main.cpp.obj"
	D:\coding\vs2017\Community\VC\Tools\MSVC\14.13.26128\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\numcpp01.dir\main.cpp.obj /FdCMakeFiles\numcpp01.dir\ /FS -c E:\codes\clion\clion_base\numcpp01\main.cpp
<<

CMakeFiles\numcpp01.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/numcpp01.dir/main.cpp.i"
	D:\coding\vs2017\Community\VC\Tools\MSVC\14.13.26128\bin\Hostx86\x86\cl.exe > CMakeFiles\numcpp01.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\codes\clion\clion_base\numcpp01\main.cpp
<<

CMakeFiles\numcpp01.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/numcpp01.dir/main.cpp.s"
	D:\coding\vs2017\Community\VC\Tools\MSVC\14.13.26128\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\numcpp01.dir\main.cpp.s /c E:\codes\clion\clion_base\numcpp01\main.cpp
<<

# Object files for target numcpp01
numcpp01_OBJECTS = \
"CMakeFiles\numcpp01.dir\main.cpp.obj"

# External object files for target numcpp01
numcpp01_EXTERNAL_OBJECTS =

numcpp01.exe: CMakeFiles\numcpp01.dir\main.cpp.obj
numcpp01.exe: CMakeFiles\numcpp01.dir\build.make
numcpp01.exe: CMakeFiles\numcpp01.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\codes\clion\clion_base\numcpp01\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable numcpp01.exe"
	"D:\coding\clion\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\numcpp01.dir --manifests  -- D:\coding\vs2017\Community\VC\Tools\MSVC\14.13.26128\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\numcpp01.dir\objects1.rsp @<<
 /out:numcpp01.exe /implib:numcpp01.lib /pdb:E:\codes\clion\clion_base\numcpp01\cmake-build-debug\numcpp01.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\numcpp01.dir\build: numcpp01.exe

.PHONY : CMakeFiles\numcpp01.dir\build

CMakeFiles\numcpp01.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\numcpp01.dir\cmake_clean.cmake
.PHONY : CMakeFiles\numcpp01.dir\clean

CMakeFiles\numcpp01.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" E:\codes\clion\clion_base\numcpp01 E:\codes\clion\clion_base\numcpp01 E:\codes\clion\clion_base\numcpp01\cmake-build-debug E:\codes\clion\clion_base\numcpp01\cmake-build-debug E:\codes\clion\clion_base\numcpp01\cmake-build-debug\CMakeFiles\numcpp01.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\numcpp01.dir\depend
