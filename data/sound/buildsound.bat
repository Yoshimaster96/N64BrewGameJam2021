@echo off
rem BUILD SEQUENCES
copy C:\ultra\usr\lib\PR\soundbanks\GenMidiBank.ctl midi.ctl
copy C:\ultra\usr\lib\PR\soundbanks\GenMidiBank.tbl midi.tbl
for %%i in (seqs\*.mid) do (
	C:\nintendo\n64kit\misc\sgi2pc\tool\midicomp -o %%i "%%~di%%~pi%%~ni.seq"
)
C:\nintendo\n64kit\misc\sgi2pc\tool\SBC -Omidi.sbk^
 seqs\title.seq^
 seqs\over.seq^
 seqs\ending.seq^
 seqs\ready.seq^
 seqs\death.seq^
 seqs\win.seq^
 seqs\se_pause.seq^
 seqs\se_1up.seq^
 seqs\level1.seq^
 seqs\level2.seq
rem BUILD WAVES
rem TODO
rem WAIT FOR USER INPUT
pause