@echo off
pushd BuildDirWindows
"%MSBUILD_HOME%\Bin\MSBuild.exe" /p:Configuration=Debug  /p:Platfrom=x64 App.sln
popd