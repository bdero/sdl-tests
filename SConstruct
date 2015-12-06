# SCons build file

import os
import shutil


TARGET_DIR = 'bin'
SOURCE_DIR = 'src'

def idempotent_copytree(source, destination):
    try:
        os.makedirs(destination)
    except OSError:
        # Directory already exists
        pass

    try:
        shutil.copystat(source, destination)
    except WindowsError:
        # Can't copy file access times on Windows
        # Source: https://docs.python.org/2/library/shutil.html#copytree-example
        pass

    for filename in os.listdir(source):
        source_name = os.path.join(source, filename)
        destination_name = os.path.join(destination, filename)

        if os.path.islink(source_name):
            link = os.readlink(source_name)
            os.symlink(link, destination_name)
        elif os.path.isdir(source_name):
            idempotent_copytree(source_name, destination_name)
        else:
            shutil.copy2(source_name, destination_name)


def build_solution(name):
    BUILD_SOURCE_DIR = os.path.join(SOURCE_DIR, name)
    BUILD_TARGET_SOURCE_DIR = os.path.join(TARGET_DIR, SOURCE_DIR)
    BUILD_TARGET_DIR = os.path.join(BUILD_TARGET_SOURCE_DIR, name)

    # Create a new build environment
    env = Environment()

    # Copy the source tree to the build directory
    print "Copying", BUILD_SOURCE_DIR, "to", BUILD_TARGET_DIR + ".."
    idempotent_copytree(BUILD_SOURCE_DIR, BUILD_TARGET_DIR)

    # Collect the source files
    build_files = []
    for d, sd, files in os.walk(BUILD_SOURCE_DIR):
        # Replace the SOURCE_DIR with the TARGET_DIR in the path
        path = os.path.join(BUILD_TARGET_SOURCE_DIR, d[len(SOURCE_DIR) + 1:])

        build_files += [
            os.path.join(path, f) for f in files
            if f.lower().endswith(".cpp")
        ]

    if build_files:
        print "Collected", name, "build files:", build_files
    else:
        print "Skipping", name, "because there are no CPP files!"
        return

    # Read the library list
    build_libraries = []
    try:
        with open(os.path.join(BUILD_SOURCE_DIR, 'LINK')) as f:
            build_libraries = [l for l in f]
    except IOError:
        print "No `LINK` file found for", name + "."

    env.Append(LIBS=build_libraries)

    # Build the solution
    solution = env.Program(
        target=os.path.join(TARGET_DIR, 'Release', name),
        source=build_files
    )
    Default(solution)


for root in os.listdir(SOURCE_DIR):
    build_solution(root)
