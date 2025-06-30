import os, sys

files = ["set(SOURCES\n"]
if os.listdir("./src"):
    for string in os.listdir("./src"):
        files.append(f"\tsrc/{string}\n")
    print("Sources have been read")
else:
    print("Folder with sources is empty")
    sys.exit(1)
files.append(")")

try:
    with open("./source.cmake", "w") as f:
        f.writelines(files)
    print("Sources have been written in sources.cmake")
except FileNotFoundError:
    print("File sources.cmake not found")