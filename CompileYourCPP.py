import time, os, colorama

print("================================C++ File Compiler================================")
cppfile = input("Enter the C++ file name with extension (e.g., program.cpp): ")
outputfile = input("Enter the desired output executable name (without extension): ").strip().lower()
autorun = input("Do you want to autorun the executable after compilation? (yes/no): ").strip().lower()
try:
    compile_command = f"g++ {cppfile} -o {outputfile}"
    os.system(compile_command)
    print(f"Compilation command executed: {compile_command}")
    print(f"Executable '{outputfile}' created successfully.")
    if autorun == "yes" or autorun == "y":
        print(colorama.Fore.RED, "To bad its broken BOZOOO :/", colorama.Style.RESET_ALL)
        # os.system(f"./{outputfile}")
except Exception as e:
    print(f"An error occurred during compilation: {e}")