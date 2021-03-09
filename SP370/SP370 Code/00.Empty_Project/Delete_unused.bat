@Echo off
CLS
ECHO Delete all unused and temporary files includung files in subfolders
ECHO Files of the following type will be deleted:
ECHO (*.abs, *.brk, *.bak, *.hex, *.lin, *.lst, *.m51, *.obj, *.plg, *.lnp, *._IA, *.__I, *._II, *.ls1, *.src)
Pause
ECHO in progress
del /s *.abs
del /s *.brk
del /s *.bak
del /s *.hex
del /s *.lin
del /s *.lst
del /s *.m51
del /s *.obj
del /s *.plg
del /s *.lnp
del /s *._IA
del /s *.__I
del /s *._II
del /s *.ls1
del /s *.src
ECHO Done!


