param(
    [Parameter(ValueFromRemainingArguments = $true)]
    [string[]]$Names
)

foreach ($name in $Names) {
    $headerGuard = ($name.ToUpper() + "_H")

    # .c file
    Set-Content "$name.c" "// $name.c`n#include `"$name.h`""

    # .h file
    Set-Content "$name.h" @"
#ifndef $headerGuard
#define $headerGuard

#endif
"@
}