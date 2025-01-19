# crow_cpp_app
# Steps to Generate the Solution

Follow the steps below to generate the solution for the project:

---

## Prerequisites

1. **Install CMake**  
   Ensure that you have CMake installed on your machine. You can download it from the official [CMake website](https://cmake.org/download/).

2. **Install Python**  
   Install Python from the official [Python website](https://www.python.org/downloads/). Make sure Python is added to your system's PATH.

3. **Install Conan**  
   Install Conan (a C++ package manager) by running the following command:
   ```bash
   pip install conan
4. **Generate the Conan profile**
5. **Open your terminal and run the following command to navigate to the crow_cpp_app directory**
   ```bash
   cd <crow_cpp_app>
   conan build . --profile=<conan_proile> –build=missing
6. **The solution file will be available at <crow_cpp_app>/build**
