# Einhard

Einhard 是一个简单好用的日志库，原作者多年未更新。现 Fork 之，并修复一些问题。

## 原始声明
Einhard is a simple logging API for small to medium sized C++ applications.

The focus is on simple use, both regarding programming on building of applications. To achieve this on the programming side the API uses the normal stream based output style of C++. To achieve this on the building side it limits its dependencies on to the C++ standard library and boost, unlike e.g. log4cxx which requires the Apache Portable Runtime.

For installation instructions please review the INSTALL file.

If you do your build configuration using CMake you can add the FindEinhard.cmake to your project to find a version of Einhard on your target system.

This software is maintained by Matthias Bach. You can reach me at marix@marix.org and you can find the source hosted at http://gitorious.org/einhard.

Einhard is licensed under the GNU General Public License Version 3. You can find the license text in the file COPYING.

