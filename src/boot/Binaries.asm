%macro IncBin 2
  SECTION .rodata
  GLOBAL %1
%1:
  incbin %2
  db 0
  %1_size: dq %1_size - %1
%endmacro

IncBin Logo, "src/extern/logo.txt"
IncBin HelpText, "src/extern/help.txt"
IncBin LicenseText, "src/extern/license.txt"
IncBin CommandsText, "src/extern/cmd.txt"