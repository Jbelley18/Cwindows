$files = Get-ChildItem -Recurse -Include *.c | ForEach-Object { $_.FullName }
gcc $files -o cwindows.exe -Iinclude -Wall
