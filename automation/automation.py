import os
import shutil
import subprocess
import argparse
import platform
import shlex
from enum import Enum

class Configuration(Enum):
    Debug = "Debug"
    Release = "Release"

class Action(Enum):
    CLEAN = "clean"
    GENERATE = "generate"
    BUILD = "build"
    CLANG_FORMAT = "clang_format"

class Platform(Enum):
    X64 = "x64"
    WIN32 = "Win32"

############ 

class Config:
    BUILD_FOLDER = "build"
    CMAKE_GENERATOR = ""
    PLATFORM = None
    FRESH = True
    CLEAN = True
    VERBOSE = False
    SOURCE_DIR = "Engine"

#######################

FRESH_ARG = "--fresh" if Config.FRESH else ""
CLEAR_ARG = "--clean-first" if Config.CLEAN else ""
VERBOSE_ARG = "--verbose" if Config.VERBOSE else ""


def remove_build_folder():
    folder_path = f"{Config.BUILD_FOLDER}"
    if os.path.exists(folder_path):
        shutil.rmtree(folder_path)
        print(f"Removed {Config.BUILD_FOLDER} folder.")
    else:
        print(f"Folder {Config.BUILD_FOLDER} doesn't exist.")


def get_cmake_command(action: Action, configuration: Configuration):
    if platform.system() == "Darwin":
        Config.CMAKE_GENERATOR = "Ninja"
    else:
        Config.CMAKE_GENERATOR = "Visual Studio 17 2022"

    cmake_flags = {
        "generator": f'-G "{Config.CMAKE_GENERATOR}"',
        "fresh": "--fresh" if Config.FRESH else "",
        "clean_first": "--clean-first" if Config.CLEAN else "",
        "verbose": "--verbose" if Config.VERBOSE else ""
    }

    if action == Action.GENERATE:
        return f'cmake .. {cmake_flags["generator"]} {cmake_flags["fresh"]}  -DCMAKE_BUILD_TYPE={configuration.value}'
    elif action == Action.BUILD:
        return f'cmake --build . {cmake_flags["clean_first"]} {cmake_flags["verbose"]} --config {configuration.value}'
    
    return None


def run_command(command):
    if isinstance(command, (list, tuple)):
        printable = " ".join(shlex.quote(str(x)) for x in command)
        result = subprocess.run(list(map(str, command)), shell=False)
    else:
        result = subprocess.run(command, shell=True)
    return result.returncode == 0


def generate_project_files(action: Action, configuration: Configuration):
    if not os.path.exists(Config.BUILD_FOLDER):
        os.makedirs(Config.BUILD_FOLDER)
        print(f"Created {Config.BUILD_FOLDER} folder.")

    os.chdir(Config.BUILD_FOLDER)
    command = get_cmake_command(action, configuration)
    print(f"Generated project files with command: {command}")

    if run_command(command):
        print("Project files generated successfully.")
    else:
        print("Failed to generate project files")
    os.chdir("..")        


def build_project(action: Action, configuration: Configuration):
    if not os.path.exists(Config.BUILD_FOLDER):
        print(f"{Config.BUILD_FOLDER} folder doesn't exist. Please generate project files first")
        return
    
    os.chdir(Config.BUILD_FOLDER)
    command = get_cmake_command(action, configuration)

    if run_command(command):
        print(f"Project built successfully in {configuration} mode.")
    else:
        print(f"Failed to build project in {configuration} mmode")
    os.chdir("..")


def get_source_files(source_dir, extensions):
    source_files = []
    for root, _, files in os.walk(source_dir):
        for file in files:
            if any(file.endswith(ext) for ext in extensions):
                source_files.append(os.path.join(root, file))
    return source_files      
         

def run_clang_format(source_dir):
    extensions = ['.cpp', '.h', '.hpp']
    format_sources = get_source_files(source_dir, extensions)

    if not format_sources:
        print(f"No source files found in {source_dir}")
        return
    
    # run clang-format command
    command = ['clang-format', '-i'] + format_sources
    if run_command(command):
        print('Clang-format successfully applied.')
    else:
        print('Error running clang-format command.')

if __name__ == "__main__":
    parser  = argparse.ArgumentParser(description="CMAKE Automation script")
    parser.add_argument("action", type=Action, choices=list(Action), help="Action to perform")
    parser.add_argument("--configuration", type=Configuration, choices=list(Configuration), help="Build Configuration")

    args = parser.parse_args()
    selected_action = args.action
    selected_configuration = args.configuration

    actions = {
        Action.CLEAN: remove_build_folder,
        Action.GENERATE: lambda: generate_project_files(Action.GENERATE, selected_configuration),
        Action.BUILD: lambda: build_project(Action.BUILD, selected_configuration),
        Action.CLANG_FORMAT: lambda: run_clang_format(Config.SOURCE_DIR)
    }

    if selected_action in actions:
        actions[selected_action]()
    else:
        print(f"Action '{selected_action}' is not implemented")